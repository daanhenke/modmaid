find_package(Doxygen)

set(DOCS_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in")
    set(DOXYGEN_OUT "${DOCS_OUT_DIR}/Doxyfile")

    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    add_custom_target(docs ALL
        COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
        WORKING_DIRECTORY "${DOCS_OUT_DIR}"
        COMMENT "Running doxygen..."
        VERBATIM
    )
endif()