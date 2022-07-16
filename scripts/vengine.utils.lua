-- Generate premake workspace configurations
function vengine_workspace_configurations()
    configurations { "Debug", "DebugEditor", "Development", "DevelopmentEditor", "Shipping" }
    architecture "x64"
end

function vengine_project_defines()
    -- Name of project to be build
    defines { "VENGINE_BUILD_%{prj.name}" }

    -- Default DEBUG/NDEBUG
    filter "configurations:Debug or DebugEditor"
      defines { "VENGINE_DEBUG", "DEBUG" }
      symbols "On"
    filter {}
    filter "configurations:Development or DevelopmentEditor or Shipping"
      defines { "VENGINE_NDEBUG", "NDEBUG" }
      optimize "On"
    filter {}

    -- Default Configuration defines
    filter "configurations:Debug or DebugEditor"
      defines { "VENGINE_CONF_DEBUG" }
    filter {}
    filter "configurations:Development or DevelopmentEditor"
        defines { "VENGINE_CONF_DEVELOPMENT" }
    filter {}
    filter "configurations:Shipping"
      defines { "VENGINE_CONF_SHIPPING" }
    filter {}

    -- Default editor non editor
    filter "configurations:DevelopmentEditor or DebugEditor"
      defines { "VENGINE_EDITOR" }
    filter {}
    filter "configurations:Development or Debug or Shipping"
        defines { "VENGINE_NO_EDITOR" }
    filter {}
end

function vengine_project_default_setup(name, src_location)
    -- Metadata
    location("%{wks.location}/" .. src_location)
    targetname(name)
    files { 
        "%{prj.location}/**.lua",
        "%{prj.location}/**.h", 
        "%{prj.location}/**.hh", 
        "%{prj.location}/**.hpp",
        "%{prj.location}/**.c",  
        "%{prj.location}/**.cc", 
        "%{prj.location}/**.cpp", 
        "%{prj.location}/**.cxx"  
    }

    -- Language
    language "C++"
    cppdialect(vengine_cpp_version)

    -- Core linking and include
    includedirs { "%{prj.location}", "%{wks.location}/src/vendor/" }
    includedirs(vengine_lib_include)
    libdirs { "%{wks.location}/build/%{cfg.architecture}-%{cfg.buildcfg}/lib/" }
end

function vengine_project_game_application(name, src_location)
    kind("WindowedApp")

    -- Do default setup
    vengine_project_default_setup(name, src_location)

    -- Output names and location
    targetdir "%{wks.location}/build/%{cfg.architecture}-%{cfg.buildcfg}/bin/"
    objdir "%{wks.location}/build/%{cfg.architecture}-%{cfg.buildcfg}/obj/%{prj.name}/"

    -- Links
    links(vengine_core_links)

    -- Defines
    vengine_project_defines()
    defines { "VENGINE_GAME" }
end

function vengine_project_vendor_static_lib(name, src_location)
    kind("StaticLib")

    -- Do default setup
    vengine_project_default_setup("lib_" .. name, src_location)

    -- Output names and location
    targetdir "%{wks.location}/build/%{cfg.architecture}-%{cfg.buildcfg}/lib/"
    objdir "%{wks.location}/build/%{cfg.architecture}-%{cfg.buildcfg}/obj/%{prj.name}/"

    -- Defines
    vengine_project_defines()
    defines { "VENGINE_VENDOR_LIB" }

    -- Inject dependcies
    vengine_core_links[#vengine_core_links+1] = name;
end

function vengine_project_engine_static_lib(name, src_location)
  kind("StaticLib")

  -- Do default setup
  vengine_project_default_setup(name, src_location)

  -- Output names and location
  targetdir "%{wks.location}/build/%{cfg.architecture}-%{cfg.buildcfg}/lib/"
  objdir "%{wks.location}/build/%{cfg.architecture}-%{cfg.buildcfg}/obj/%{prj.name}/"

  -- Defines
  vengine_project_defines()
  defines { "VENGINE_ENGINE_LIB" }

  -- Inject dependcies
  vengine_core_links[#vengine_core_links+1] = name;
end
