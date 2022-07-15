-- JSON Lib
project "rapidjson"
    -- Setup static lib and override to None
    vengine_project_vendor_static_lib("rapidjson", "src/vendor/rapidjson")
    kind "None"

    -- Customize
