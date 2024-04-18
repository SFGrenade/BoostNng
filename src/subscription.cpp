#include "boostNng/subscription.hpp"

namespace BoostNng {

class Subscription::impl {
  public:
  std::function< void( NetworkMessage const& ) > callback;
};

Subscription::Subscription() : pimpl( new impl ) {
  pimpl->callback = nullptr;
}

Subscription::Subscription( BoostNng::Subscription const& other ) : pimpl( new impl ) {
  pimpl->callback = other.pimpl->callback;
}

Subscription::Subscription( std::function< void( BoostNng::NetworkMessage const& ) > callback ) : pimpl( new impl ) {
  pimpl->callback = callback;
}

Subscription::~Subscription() {
  delete pimpl;
  pimpl = nullptr;
}

void Subscription::operator()( BoostNng::NetworkMessage const& message ) const {
  pimpl->callback( message );
}

}  // namespace BoostNng
