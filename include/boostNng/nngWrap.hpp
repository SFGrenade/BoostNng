#ifndef NNGWRAP_HPP_
#define NNGWRAP_HPP_

#include <nng/nng.h>

#include "boostNng/_export.hpp"
#include "boostNng/networkMessage.hpp"
#include "boostNng/subscription.hpp"

namespace BoostNng {

class BOOSTNNG_API NngWrap {
  public:
  enum class SocketType {
    Bus0,
    Pair0,
    Pair1,
    Pull0,
    Push0,
    Pub0,
    Sub0,
    Rep0,
    Req0,
    Respondent0,
    Surveyor0,
  };

  public:
  NngWrap() = delete;
  NngWrap( BoostNng::NngWrap const& ) = delete;
  NngWrap( std::string const& host, bool isServer, BoostNng::NngWrap::SocketType socketType );
  virtual ~NngWrap();

  void subscribe( BoostNng::NetworkMessage const& message, std::function< void( BoostNng::NetworkMessage const& ) > callback );
  virtual void sendMessage( BoostNng::NetworkMessage const& message );
  template < typename T >
  void sendMessageGeneric( T const& message ) {
    sendMessage( BoostNng::NetworkMessage::from< T >( message ) );
  };

  virtual void run();

  protected:
  virtual bool canSend() const = 0;
  virtual void didSend() = 0;
  virtual bool canRecv() const = 0;
  virtual void didRecv() = 0;

  void connectSocket();
  bool getIsServer() const;
  template < typename Tret, typename... Args >
  Tret callNngSockFunc( Tret ( *func )( nng_socket, Args... ), Args... args ) {
    return func( getSocket(), args... );
  }

  private:
  nng_socket getSocket() const;

  class impl;
  impl* pimpl;
};

}  // namespace BoostNng

#endif /* NNGWRAP_HPP_ */
