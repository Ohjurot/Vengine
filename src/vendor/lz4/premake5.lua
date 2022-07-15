-- LZ4 compression
project "lz4"
    -- Setup static lib
    vengine_project_vendor_static_lib("lz4", "src/vendor/lz4")

    -- Customize
    includedirs {"%{wks.location}/src/vendor/xxhash"}
