add_library(_modmaid_gui STATIC
    src/init.cc
)

if(WIN32)
  target_sources(_modmaid_gui PRIVATE
      src/dxcommon/dxcommon.cc
      src/directx11/init.cc
  )
elseif(UNIX)
  #target_sources(_modmaid_gui PRIVATE)
endif()

target_include_directories(_modmaid_gui
  PUBLIC include
  PRIVATE src
)

target_link_libraries(_modmaid_gui PRIVATE _modmaid_core)
__maid_alias(_modmaid_gui)
