find_package(Doxygen)

set(DOCS_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}")

if(DOXYGEN_FOUND)
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in")
    set(DOXYGEN_OUT "${DOCS_OUT_DIR}/Doxyfile")

    string(JOIN " " DOXYGEN_INPUTS
        "${MAID_SOURCE_DIR}/modules/core/include"
        "${MAID_SOURCE_DIR}/modules/core/src"
        "${MAID_SOURCE_DIR}/modules/gui/include"
        "${MAID_SOURCE_DIR}/modules/gui/src"
    )

    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    add_custom_target(docs ALL
        COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
        WORKING_DIRECTORY "${DOCS_OUT_DIR}"
        COMMENT "Running doxygen..."
        VERBATIM
    )
endif()