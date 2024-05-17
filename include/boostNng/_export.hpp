#include <hedley/hedley.h>

#if defined( BOOSTNNG_IS_SHARED ) && defined( BOOSTNNG_COMPILING )

#define BOOSTNNG_API HEDLEY_PUBLIC

#elif defined( BOOSTNNG_IS_SHARED )

#define BOOSTNNG_API HEDLEY_IMPORT

#else

#define BOOSTNNG_API

#endif
