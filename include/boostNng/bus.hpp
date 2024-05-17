#ifndef BUS_HPP_
#define BUS_HPP_

#include "boostNng/_export.hpp"
#include "boostNng/nngWrap.hpp"

namespace BoostNng {

class BOOSTNNG_API Bus : public NngWrap {
  public:
  Bus( std::string const& host, bool isServer );
  ~Bus() override;

  protected:
  virtual bool canSend() const override;
  virtual void didSend() override;
  virtual bool canRecv() const override;
  virtual void didRecv() override;
};

}  // namespace BoostNng

#endif /* BUS_HPP_ */
