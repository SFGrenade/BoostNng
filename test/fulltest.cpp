#include <boostNng/bus.hpp>
#include <boostNng/pair.hpp>
#include <boostNng/pubSub.hpp>
#include <boostNng/pushPull.hpp>
#include <boostNng/reqRep.hpp>
#include <boostNng/survResp.hpp>
#include <gtest/gtest.h>

TEST( BoostNng, ConstructorTest01 ) {
  BoostNng::Bus* network = new BoostNng::Bus( "tcp://127.0.0.1:13337", false );
  EXPECT_NE( network, nullptr );
  delete network;
}

TEST( BoostNng, ConstructorTest02 ) {
  BoostNng::Pair0* network = new BoostNng::Pair0( "tcp://127.0.0.1:13337", false );
  EXPECT_NE( network, nullptr );
  delete network;
}

TEST( BoostNng, ConstructorTest03 ) {
  BoostNng::Pair1* network = new BoostNng::Pair1( "tcp://127.0.0.1:13337", false );
  EXPECT_NE( network, nullptr );
  delete network;
}

TEST( BoostNng, ConstructorTest04 ) {
  BoostNng::PubSub* network = new BoostNng::PubSub( "tcp://127.0.0.1:13337", false );
  EXPECT_NE( network, nullptr );
  delete network;
}

TEST( BoostNng, ConstructorTest05 ) {
  BoostNng::PushPull* network = new BoostNng::PushPull( "tcp://127.0.0.1:13337", false );
  EXPECT_NE( network, nullptr );
  delete network;
}

TEST( BoostNng, ConstructorTest06 ) {
  BoostNng::ReqRep* network = new BoostNng::ReqRep( "tcp://127.0.0.1:13337", false );
  EXPECT_NE( network, nullptr );
  delete network;
}

TEST( BoostNng, ConstructorTest07 ) {
  BoostNng::SurvResp* network = new BoostNng::SurvResp( "tcp://127.0.0.1:13337", false );
  EXPECT_NE( network, nullptr );
  delete network;
}
