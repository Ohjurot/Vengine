-- uuid
project "uuid"
    -- Setup static lib
    vengine_project_vendor_static_lib("uuid", "src/vendor/uuid")
    kind "None"

    -- Customize
