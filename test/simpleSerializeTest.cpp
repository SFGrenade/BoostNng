#include <boostNng/networkMessage.hpp>
#include <boostNng/subscription.hpp>
#include <gtest/gtest.h>

#define EXPECT_CALLBACK( type, name )                                                                                                                   \
  std::function< void( BoostNng::NetworkMessage const& ) > name = [myMessage]( BoostNng::NetworkMessage const& message ) {                              \
    EXPECT_EQ( myMessage, message.to< type >() ) << #type + std::string( " was unable to be converted correctly from: '" ) + message.getTopic() + "'/'" \
                                                        + message.getContent() + "'";                                                                   \
  };

TEST( BoostNng, Int8Conversion ) {
  int8_t myMessage = 8;

  EXPECT_CALLBACK( int8_t, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< int8_t >( myMessage ) );
}

TEST( BoostNng, Int16Conversion ) {
  int16_t myMessage = 16;

  EXPECT_CALLBACK( int16_t, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< int16_t >( myMessage ) );
}

TEST( BoostNng, Int32Conversion ) {
  int32_t myMessage = 32;

  EXPECT_CALLBACK( int32_t, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< int32_t >( myMessage ) );
}

TEST( BoostNng, Int64Conversion ) {
  int64_t myMessage = 64;

  EXPECT_CALLBACK( int64_t, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< int64_t >( myMessage ) );
}

TEST( BoostNng, Uint8Conversion ) {
  uint8_t myMessage = 8;

  EXPECT_CALLBACK( uint8_t, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< uint8_t >( myMessage ) );
}

TEST( BoostNng, Uint16Conversion ) {
  uint16_t myMessage = 16;

  EXPECT_CALLBACK( uint16_t, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< uint16_t >( myMessage ) );
}

TEST( BoostNng, Uint32Conversion ) {
  uint32_t myMessage = 32;

  EXPECT_CALLBACK( uint32_t, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< uint32_t >( myMessage ) );
}

TEST( BoostNng, Uint64Conversion ) {
  uint64_t myMessage = 64;

  EXPECT_CALLBACK( uint64_t, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< uint64_t >( myMessage ) );
}

TEST( BoostNng, FloatConversion ) {
  float myMessage = 3.14F;

  EXPECT_CALLBACK( float, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< float >( myMessage ) );
}

TEST( BoostNng, DoubleConversion ) {
  double myMessage = 3.1415;

  EXPECT_CALLBACK( double, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< double >( myMessage ) );
}

TEST( BoostNng, LongDoubleConversion ) {
  long double myMessage = 3.141592L;

  EXPECT_CALLBACK( long double, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< long double >( myMessage ) );
}

TEST( BoostNng, StringConversion ) {
  std::string myMessage = "MyTestString";

  EXPECT_CALLBACK( std::string, myCallback );
  BoostNng::Subscription sub( myCallback );

  sub( BoostNng::NetworkMessage::from< std::string >( myMessage ) );
}
