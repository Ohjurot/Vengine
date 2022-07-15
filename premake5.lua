-- Include all dependant lua files
include "scripts/vengine.utils.lua"
include "dependencies.lua"

-- Core linking
vengine_core_libs = {}
vengine_core_links = {}

-- Configure workspace
workspace "Vengine VDK"
    -- Workspace config
    vengine_workspace_configurations()
    startproject "sandbox"
    vengine_cpp_version = "C++20"

    -- 3rd party libs
    group "Vendor"
        include "src/vendor/xxhash/premake5.lua"
        include "src/vendor/lz4/premake5.lua"
        include "src/vendor/pugixml/premake5.lua"
        include "src/vendor/rapidjson/premake5.lua"
        -- TODO: freetype2
    group ""

    -- Engine code 
    group "Engine"
        -- === HAL (Hardware abstration layer) ===
        -- vengine_hal_core (Util of headers)
        -- vengine_hal_win_core (StaticLib implements win64/gdk/gdkx)
        -- vengine_hal_win_win64 (StaticLib implements win64)
        -- vengine_hal_win_gdk (StaticLib implements gdk)
        -- vengine_hal_win_xbox (StaticLib implements gdkx / xbox)
        -- vengine_hal_sony_ps5 (StaticLib implements ps5)
        -- vengine_hal_steamworks (StaticLib implements steam)

        -- === Platform independet ===
        -- vengine_common (StaticLib of util classes)
        -- vengine_runtime (StaticLib of runtime - rendering, scripting, io, ...)
        -- vengine_editor (StaticLib of editor)

        -- === C# Scripting ===
        -- TODO:
    group ""

    -- Game implementation
    group "Games"
        include "src/example/sandbox/premake5.lua"
        -- minimal (Application - used to show all functions)
    group ""
