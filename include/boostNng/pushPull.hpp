#ifndef PUSHPULL_HPP_
#define PUSHPULL_HPP_

#include "boostNng/_export.hpp"
#include "boostNng/nngWrap.hpp"

namespace BoostNng {

class BOOSTNNG_API PushPull : public NngWrap {
  public:
  PushPull( std::string const& host, bool isPusher );
  ~PushPull() override;

  protected:
  virtual bool canSend() const override;
  virtual void didSend() override;
  virtual bool canRecv() const override;
  virtual void didRecv() override;
};

}  // namespace BoostNng

#endif /* PUSHPULL_HPP_ */
