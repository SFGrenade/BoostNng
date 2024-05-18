#ifndef SURVRESP_HPP_
#define SURVRESP_HPP_

#include <vector>

#include "boostNng/_export.hpp"
#include "boostNng/nngWrap.hpp"

namespace BoostNng {

class BOOSTNNG_API_CLASSES SurvResp : public NngWrap {
  public:
  SurvResp( std::string const& host, bool isServer );
  ~SurvResp() override;

  protected:
  virtual bool canSend() const override;
  virtual void didSend() override;
  virtual bool canRecv() const override;
  virtual void didRecv() override;
};

}  // namespace BoostNng

#endif /* SURVRESP_HPP_ */
