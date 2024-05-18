#ifndef PUBSUB_HPP_
#define PUBSUB_HPP_

#include "boostNng/_export.hpp"
#include "boostNng/nngWrap.hpp"

namespace BoostNng {

class BOOSTNNG_API_CLASSES PubSub : public NngWrap {
  public:
  PubSub( std::string const& host, bool isPublisher );
  ~PubSub() override;

  protected:
  virtual bool canSend() const override;
  virtual void didSend() override;
  virtual bool canRecv() const override;
  virtual void didRecv() override;
};

}  // namespace BoostNng

#endif /* PUBSUB_HPP_ */
