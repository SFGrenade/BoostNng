#include "boostNng/nngWrap.hpp"

#include <map>
#include <mutex>
#include <nng/nng.h>
#include <nng/protocol/bus0/bus.h>
#include <nng/protocol/pair0/pair.h>
#include <nng/protocol/pair1/pair.h>
#include <nng/protocol/pipeline0/pull.h>
#include <nng/protocol/pipeline0/push.h>
#include <nng/protocol/pubsub0/pub.h>
#include <nng/protocol/pubsub0/sub.h>
#include <nng/protocol/reqrep0/rep.h>
#include <nng/protocol/reqrep0/req.h>
#include <nng/protocol/survey0/respond.h>
#include <nng/protocol/survey0/survey.h>
#include <nng/supplemental/util/platform.h>
#include <nng/transport/zerotier/zerotier.h>
#include <queue>
#include <string>

namespace BoostNng {

#define NNG_FUNC_WITH_THROW( func, ... )                                                                            \
  int func##_##result = func( __VA_ARGS__ );                                                                        \
  if( func##_##result ) {                                                                                           \
    throw std::runtime_error( std::string( #func ) + " error: " + std::string( nng_strerror( func##_##result ) ) ); \
  }

class NngWrap::impl {
  public:
  std::string host_;
  bool isServer_;
  BoostNng::NngWrap::SocketType socketType_;

  nng_socket nngSocket_;
  nng_listener nngListener_;
  nng_dialer nngDialer_;

  std::mutex mutexForSendQueue_;
  std::queue< BoostNng::NetworkMessage > queueToSend_;
  std::map< std::string, BoostNng::Subscription > subscribedMessages_;
};

NngWrap::NngWrap( std::string const& host, bool isServer, BoostNng::NngWrap::SocketType socketType ) : pimpl( new impl ) {
  pimpl->host_ = host;
  pimpl->isServer_ = isServer;
  pimpl->socketType_ = socketType;
  switch( pimpl->socketType_ ) {
    case BoostNng::NngWrap::SocketType::Bus0: {
      NNG_FUNC_WITH_THROW( nng_bus0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Pair0: {
      NNG_FUNC_WITH_THROW( nng_pair0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Pair1: {
      NNG_FUNC_WITH_THROW( nng_pair1_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Pull0: {
      NNG_FUNC_WITH_THROW( nng_pull0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Push0: {
      NNG_FUNC_WITH_THROW( nng_push0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Pub0: {
      NNG_FUNC_WITH_THROW( nng_pub0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Sub0: {
      NNG_FUNC_WITH_THROW( nng_sub0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Rep0: {
      NNG_FUNC_WITH_THROW( nng_rep0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Req0: {
      NNG_FUNC_WITH_THROW( nng_req0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Respondent0: {
      NNG_FUNC_WITH_THROW( nng_respondent0_open, &pimpl->nngSocket_ );
      break;
    }
    case BoostNng::NngWrap::SocketType::Surveyor0: {
      NNG_FUNC_WITH_THROW( nng_surveyor0_open, &pimpl->nngSocket_ );
      break;
    }
    default:
      throw std::invalid_argument( "Socket type '" + std::to_string( static_cast< int >( pimpl->socketType_ ) ) + "' not supported!" );
  }
}

NngWrap::~NngWrap() {
  while( !pimpl->queueToSend_.empty() ) {
    pimpl->queueToSend_.pop();
  }
  pimpl->subscribedMessages_.clear();
  NNG_FUNC_WITH_THROW( nng_close, pimpl->nngSocket_ );
  delete pimpl;
  pimpl = nullptr;
}

void NngWrap::subscribe( BoostNng::NetworkMessage const& message, std::function< void( BoostNng::NetworkMessage const& ) > callback ) {
  std::string messageType = message.getTopic();
  auto found = pimpl->subscribedMessages_.find( messageType );
  if( found == pimpl->subscribedMessages_.end() ) {
    pimpl->subscribedMessages_[messageType] = Subscription{ callback };
  }
}

void NngWrap::sendMessage( BoostNng::NetworkMessage const& message ) {
  pimpl->mutexForSendQueue_.lock();
  pimpl->queueToSend_.push( message );
  pimpl->mutexForSendQueue_.unlock();
}

void NngWrap::run() {
  if( canSend() && !pimpl->queueToSend_.empty() ) {
    pimpl->mutexForSendQueue_.lock();
    BoostNng::NetworkMessage msgToSend = pimpl->queueToSend_.front();

    std::stringstream msgToSendStringStream;
    boost::archive::text_oarchive( msgToSendStringStream ) << msgToSend;
    std::string msgToSendString = msgToSendStringStream.str();
    int sendResult = nng_send( pimpl->nngSocket_, (void*)( msgToSendString.c_str() ), msgToSendString.size(), NNG_FLAG_NONBLOCK );
    if( !sendResult ) {
      // nng has result == 0 on success
      didSend();
      pimpl->queueToSend_.pop();
    } else {
    }
    pimpl->mutexForSendQueue_.unlock();
  } else if( canRecv() ) {
    void* receivedReply;
    size_t receivedReplySize;
    int recvResult = nng_recv( pimpl->nngSocket_, &receivedReply, &receivedReplySize, NNG_FLAG_NONBLOCK | NNG_FLAG_ALLOC );
    if( !recvResult ) {
      // nng has result == 0 on success
      didRecv();
      std::string receivedMsgString( static_cast< char* >( receivedReply ), receivedReplySize );
      nng_free( receivedReply, receivedReplySize );

      std::stringstream receivedMsgStringStream;
      receivedMsgStringStream << receivedMsgString;
      receivedMsgStringStream.seekg( 0, std::ios_base::beg );
      BoostNng::NetworkMessage receivedWrapper;
      boost::archive::text_iarchive( receivedMsgStringStream ) >> receivedWrapper;

      auto found = pimpl->subscribedMessages_.find( receivedWrapper.getTopic() );
      if( found != pimpl->subscribedMessages_.end() ) {
        found->second( receivedWrapper );
      } else {
        throw std::runtime_error( "Topic '" + receivedWrapper.getTopic() + "' not subscribed!" );
      }
    } else {
    }
  }
}

void NngWrap::connectSocket() {
  if( pimpl->isServer_ ) {
    NNG_FUNC_WITH_THROW( nng_listener_create, &pimpl->nngListener_, pimpl->nngSocket_, pimpl->host_.c_str() );
    NNG_FUNC_WITH_THROW( nng_listener_start, pimpl->nngListener_, 0 );
  } else {
    // pimpl->zmqSocket_.connect( pimpl->host_ );
  }
}

bool NngWrap::getIsServer() const {
  return pimpl->isServer_;
}

nng_socket NngWrap::getSocket() const {
  return pimpl->nngSocket_;
}

}  // namespace BoostNng
