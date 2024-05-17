#ifndef SUBSCRIPTION_HPP_
#define SUBSCRIPTION_HPP_

#include <functional>

#include "boostNng/_export.hpp"
#include "boostNng/networkMessage.hpp"

namespace BoostNng {

class BOOSTNNG_API Subscription {
  public:
  Subscription();
  Subscription( BoostNng::Subscription const& other );
  Subscription( std::function< void( BoostNng::NetworkMessage const& ) > callback );
  ~Subscription();

  void operator()( BoostNng::NetworkMessage const& message ) const;

  private:
  class impl;
  impl* pimpl;
};

}  // namespace BoostNng

#endif /* SUBSCRIPTION_HPP_ */
