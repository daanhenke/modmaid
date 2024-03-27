add_library(modmaid STATIC
    src/init.cc

    src/entrypoint.cc
    src/config.cc

    src/logging/logging.cc
    src/memory/memory.cc
    src/hooks/hooks.cc
)

if (WIN32)
  target_sources(modmaid PRIVATE
      src/memory/memory.windows.cc
      src/logging/logging.windows.cc
      src/hooks/hooks.windows.cc
      src/unload/unload.windows.cc
  )
elseif (UNIX)
  target_sources(modmaid PRIVATE
      src/memory/memory.unix.cc
  )
endif ()

target_include_directories(modmaid PUBLIC include)

target_link_libraries(modmaid PRIVATE minhook)
