#ifndef PAIR_HPP_
#define PAIR_HPP_

#include "boostNng/_export.hpp"
#include "boostNng/nngWrap.hpp"

namespace BoostNng {

class BOOSTNNG_API Pair0 : public NngWrap {
  public:
  Pair0( std::string const& host, bool isServer );
  ~Pair0() override;

  protected:
  virtual bool canSend() const override;
  virtual void didSend() override;
  virtual bool canRecv() const override;
  virtual void didRecv() override;
};

class BOOSTNNG_API Pair1 : public NngWrap {
  public:
  Pair1( std::string const& host, bool isServer );
  ~Pair1() override;

  protected:
  virtual bool canSend() const override;
  virtual void didSend() override;
  virtual bool canRecv() const override;
  virtual void didRecv() override;
};

}  // namespace BoostNng

#endif /* PAIR_HPP_ */
