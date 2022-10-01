set_allowedarchs("windows|x64")
set_warnings("allextra")

add_rules("mode.debug", "mode.release")
add_requires("libsdl", "libsdl_ttf", "libsdl_image")


--target("XEngineStaticLibrary")
	--set_kind("static")
	--add_files("XEngineStaticLibrary/lib_src/*.cpp")
	--add_headerfiles("XEngineStaticLibrary/lib_include/*.h", "XEngineStaticLibrary/lib_include/*.hpp")
	--add_includedirs("XEngineStaticLibrary/lib_include")
	--add_packages("libsdl", "libsdl_ttf", "libsdl_image")
	
	--set_rundir("bin")
	--set_targetdir("bin/$(plat)_$(arch)_$(mode)_$(kind)")
	
--target("XEngineDynamicLibrary")
	--add_defines("LIB_COMPILING")
	--set_kind("shared")
	--add_files("XEngineDynamicLibrary/lib_src/*.cpp")
	--add_headerfiles("XEngineDynamicLibrary/lib_include/*.h", "XEngineDynamicLibrary/lib_include/*.hpp")
	--add_includedirs("XEngineDynamicLibrary/lib_include")
	--add_packages("libsdl", "libsdl_ttf", "libsdl_image")
	
	--set_rundir("bin")
	--set_targetdir("bin/$(plat)_$(arch)_$(mode)_$(kind)")
	
target("XEngineLibrary")
	set_kind("$(kind)")
	add_packages("libsdl", "libsdl_ttf", "libsdl_image")

	if is_kind("shared") then
		add_defines("LIB_COMPILING")
		add_files("XEngineDynamicLibrary/lib_src/*.cpp")
		add_headerfiles("XEngineDynamicLibrary/lib_include/*.h", "XEngineDynamicLibrary/lib_include/*.hpp")
		add_includedirs("XEngineDynamicLibrary/lib_include", "XEngine/include")
	
	elseif is_kind("static") then
		add_files("XEngineStaticLibrary/lib_src/*.cpp")
		add_headerfiles("XEngineStaticLibrary/lib_include/*.h", "XEngineStaticLibrary/lib_include/*.hpp")
		add_includedirs("XEngineStaticLibrary/lib_include", "XEngine/include")
	end
	
	set_rundir("bin")
	set_targetdir("bin/$(plat)_$(arch)_$(mode)_$(kind)")
	
target("XEngine")
	add_deps("XEngineLibrary")
	
	if is_kind("shared") then
		add_includedirs("XEngineDynamicLibrary/lib_include", "XEngine/include")
	elseif is_kind("static") then
		add_includedirs("XEngineStaticLibrary/lib_include", "XEngine/include")
	else
		add_includedirs("XEngine/include")
	end

    set_kind("binary")
    add_files("XEngine/src/*.cpp")
    add_headerfiles("XEngine/include/*.h", "XEngine/include/*.hpp")
    add_packages("libsdl", "libsdl_ttf", "libsdl_image")
	
    set_rundir("bin")
    set_targetdir("bin/$(plat)_$(arch)_$(mode)_$(kind)")
	



--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

