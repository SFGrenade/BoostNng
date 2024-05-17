#ifndef REQREP_HPP_
#define REQREP_HPP_

#include "boostNng/_export.hpp"
#include "boostNng/nngWrap.hpp"

namespace BoostNng {

class BOOSTNNG_API ReqRep : public NngWrap {
  public:
  enum class Status { Receiving, Sending };

  public:
  ReqRep( std::string const& host, bool isServer );
  ~ReqRep() override;

  protected:
  virtual bool canSend() const override;
  virtual void didSend() override;
  virtual bool canRecv() const override;
  virtual void didRecv() override;

  private:
  ReqRep::Status status_;
};

}  // namespace BoostNng

#endif /* REQREP_HPP_ */
