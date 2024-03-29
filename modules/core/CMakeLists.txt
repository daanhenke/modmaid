add_library(_modmaid_core STATIC
    src/init.cc

    src/entrypoint.cc
    src/config.cc

    src/logging/logging.cc
    src/memory/memory.cc
    src/hooks/hooks.cc
)

if (WIN32)
  target_sources(_modmaid_core PRIVATE
      src/memory/memory.windows.cc
      src/logging/logging.windows.cc
      src/hooks/hooks.windows.cc
      src/unload/unload.windows.cc
  )
elseif (UNIX)
  target_sources(_modmaid_core PRIVATE
      src/memory/memory.unix.cc
  )
endif ()

target_include_directories(_modmaid_core PUBLIC include)

target_link_libraries(_modmaid_core PRIVATE minhook)
__maid_alias(_modmaid_core)
__maid_add_tests(modmaid::core)
