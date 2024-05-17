set_project( "BoostNng" )

set_version( "0.5.0", { build = "%Y%m%d", soname = true } )

set_warnings( "allextra" )

add_rules( "mode.debug", "mode.release", "mode.releasedbg", "mode.minsizerel" )
add_rules( "plugin.compile_commands.autoupdate", { outputdir = ".vscode" } )

if is_plat( "windows" ) then
    -- technically 11, but abseil (dep of protobuf-cpp) needs >=14, but uses >=17 types
    set_languages( "cxx17" )

    add_cxflags( "/Zc:__cplusplus" )
    add_cxflags( "/Zc:preprocessor" )

    add_cxflags( "/permissive-" )
else
    -- technically 11, but abseil (dep of protobuf-cpp) needs >=14, but uses >=17 types
    set_languages( "c++17" )
end

add_requireconfs( "*", { debug = get_config( "mode" ) == "debug", configs = { shared = get_config( "kind" ) == "shared" } } )

add_requires( "boost" )
add_requires( "hedley" )
add_requires( "nng" )

add_requireconfs( "boost", { configs = { serialization = true } } )

-- test framework
add_requires( "gtest" )

target( "BoostNng" )
    set_kind( "$(kind)" )
    set_default( true )
    set_group( "LIBS" )

    add_defines( "BOOSTNNG_COMPILING" )
    if is_kind( "shared" ) then
        add_defines( "BOOSTNNG_IS_SHARED" )
    end

    add_packages( "boost", { public = true } )
    add_packages( "hedley", { public = true } )
    add_packages( "nng", { public = true } )

    add_includedirs( "include", { public = true } )
    add_headerfiles( "include/(boostNng/*.hpp)" )
    add_files( "src/*.cpp" )

target( "BoostNng_Tests" )
    set_kind( "binary" )
    set_default( false )
    set_group( "TESTS" )

    add_deps( "BoostNng", { shared = get_config( "kind" ) == "shared", public = true } )
    add_packages( "gtest", { public = true } )

    add_files( "test/*.cpp" )
