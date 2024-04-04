add_library(_modmaid_gui STATIC
    src/init.cc
)

set(IMGUI_SOURCES
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
)

if(WIN32)
  target_sources(_modmaid_gui PRIVATE
      src/win32/init.cc

      src/dxcommon/dxcommon.cc
      src/directx11/init.cc
  )

  list(APPEND IMGUI_SOURCES
      backends/imgui_impl_win32.cpp
      backends/imgui_impl_dx11.cpp
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

CPMAddPackage(
  NAME imgui
  DOWNLOAD_ONLY
  GIT_REPOSITORY "https://github.com/ocornut/imgui"
  GIT_TAG "master"
)

list(TRANSFORM IMGUI_SOURCES PREPEND "${imgui_SOURCE_DIR}/")
target_sources(_modmaid_gui PRIVATE ${IMGUI_SOURCES})
target_include_directories(_modmaid_gui PRIVATE "${imgui_SOURCE_DIR}" "${imgui_SOURCE_DIR}/backends")