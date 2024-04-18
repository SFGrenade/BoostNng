#include "boostNng/pushPull.hpp"

namespace BoostNng {

PushPull::PushPull( std::string const& host, bool isPusher ) : NngWrap( host, isPusher, isPusher ? NngWrap::SocketType::Push0 : NngWrap::SocketType::Pull0 ) {
  connectSocket();
}

PushPull::~PushPull() {}

bool PushPull::canSend() const {
  return getIsServer();  // isPusher
}

void PushPull::didSend() {}

bool PushPull::canRecv() const {
  return !getIsServer();  // isPusher
}

void PushPull::didRecv() {}

}  // namespace BoostNng
