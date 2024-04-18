package("boostnng")
    set_homepage("https://github.com/SFGrenade/BoostNng/")
    set_description("A helper to use zeromq and protobuf together")
    set_license("MPL-2.0")

    add_deps("boost")
    add_deps("nng")

    on_load("windows", "macosx", "linux", function (package)
        package:set("installdir", path.join(os.scriptdir(), package:plat(), package:arch(), package:mode()))
        --if not package:gitref() and package:version():lt("0.3") then
        --    package:add("deps", "fmt")
        --end
    end)

    on_fetch(function (package)
        local result = {}
        local libfiledir = (package:config("shared") and package:is_plat("windows", "mingw")) and "bin" or "lib"
        result.links = "BoostNng"
        result.linkdirs = package:installdir("lib")
        result.includedirs = package:installdir("include")
        result.libfiles = path.join(package:installdir(libfiledir), "BoostNng.lib")
        return result
    end)

    on_install("windows", "macosx", "linux", function (package)
        local configs = {}
        import("package.tools.xmake").install(package, configs)
    end)

    on_test(function (package)
        assert(package:check_cxxsnippets({test = [[
            void test() {
                BoostNng::ReqRep network( "tcp://127.0.0.1:13337", false );
                network.run();
            }
        ]]}, {configs = {languages = "c++14"}, includes = "boostNng/reqRep.hpp"}))
    end)
