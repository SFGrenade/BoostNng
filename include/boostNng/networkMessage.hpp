#ifndef NETWORKMESSAGE_HPP_
#define NETWORKMESSAGE_HPP_

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/type_index.hpp>
#include <sstream>
#include <string>

namespace BoostNng {

class NetworkMessage {
  public:
  NetworkMessage();
  NetworkMessage( BoostNng::NetworkMessage const& other );
  NetworkMessage( std::string const& topic, std::string const& content );
  virtual ~NetworkMessage();

  template < typename T >
  static std::string getTypeName() {
    return boost::typeindex::type_id< T >().pretty_name();
  }

  template < typename T >
  static BoostNng::NetworkMessage from( T const& value ) {
    BoostNng::NetworkMessage ret;

    ret.setTopic( getTypeName< T >() );
    std::stringstream contentString;
    boost::archive::text_oarchive oarchive( contentString );
    oarchive << value;
    ret.setContent( contentString.str() );

    return ret;
  }

  template < typename T >
  T to() const {
    if( this->getTopic() != getTypeName< T >() ) {
      throw std::invalid_argument( "wrong type for topic '" + this->getTopic() + "'!" );
    }
    std::stringstream contentString;
    contentString << this->getContent();
    contentString.seekg( 0, std::ios_base::beg );
    boost::archive::text_iarchive iarchive( contentString );
    T ret;
    iarchive >> ret;
    return ret;
  }

  std::string getTopic() const;
  std::string getContent() const;

  private:
  void setTopic( std::string const& value );
  void setContent( std::string const& value );

  private:
  class impl;
  impl* pimpl;

  private:
  friend class boost::serialization::access;
  template < class Archive >
  void save( Archive& ar, const unsigned int /*version*/ ) const {
    ar << getTopic();
    ar << getContent();
  }
  template < class Archive >
  void load( Archive& ar, const unsigned int /*version*/ ) {
    std::string tmp;
    ar >> tmp;
    this->setTopic( tmp );
    ar >> tmp;
    this->setContent( tmp );
  }
  BOOST_SERIALIZATION_SPLIT_MEMBER()
};

}  // namespace BoostNng

#endif  // NETWORKMESSAGE_HPP_