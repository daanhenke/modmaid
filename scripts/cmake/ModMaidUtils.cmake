function(add_mod TARGET)
  add_library("${TARGET}" SHARED ${ARGN})
  target_link_libraries("${TARGET}" PUBLIC modmaid::core)
  __maid_use_static_stdlib("${TARGET}")
endfunction()

function(__maid_alias TARGET)
  string(SUBSTRING "${TARGET}" 1 -1 ALIAS_TARGET)
  string(REPLACE "_" "::" ALIAS_TARGET "${ALIAS_TARGET}")
  add_library("${ALIAS_TARGET}" ALIAS "${TARGET}")
endfunction()

macro(__maid_option VAR_NAME VAR_TYPE DEFAULT_VALUE DOCSTRING)
  set("${VAR_NAME}" "${DEFAULT_VALUE}" CACHE "${VAR_TYPE}" "${DOCSTRING}")
endmacro()

macro(__maid_add_tests LIBRARY_TARGET)
  string(REPLACE "::" "_" TESTS_TARGET "_${LIBRARY_TARGET}_tests")

  file(GLOB TESTS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cc")
  message(STATUS "Test sources for ${LIBRARY_TARGET}: ${TESTS_SOURCES}")
  add_executable("${TESTS_TARGET}" ${TESTS_SOURCES})
  __maid_use_static_stdlib("${TESTS_TARGET}")

  target_link_libraries("${TESTS_TARGET}"
    PRIVATE
      Catch2::Catch2WithMain
      "${LIBRARY_TARGET}"
  )
  target_include_directories("${TESTS_TARGET}" PRIVATE "tests")
endmacro()

macro(__maid_use_static_stdlib TARGET)
  if(WIN32)
    set_property(TARGET "${TARGET}" PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    )
  endif()
endmacro()