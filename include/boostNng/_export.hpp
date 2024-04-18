#if defined( BOOSTNNG_DO_EXPORT_LINUX )

#define BOOSTNNG_EXPORT __attribute__( ( dllexport ) ) __attribute__( ( visibility( "default" ) ) )

#elif defined( BOOSTNNG_DO_EXPORT_MACOSX )

#define BOOSTNNG_EXPORT __attribute__( ( visibility( "default" ) ) )

#elif defined( BOOSTNNG_DO_EXPORT_WINDOWS )

#define BOOSTNNG_EXPORT __declspec( dllexport )

#else

#define BOOSTNNG_EXPORT

#endif
