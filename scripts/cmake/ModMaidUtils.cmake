function(add_mod TARGET)
  add_library("${TARGET}" SHARED ${ARGN})
  target_link_libraries("${TARGET}" PUBLIC modmaid::core)
endfunction()

function(__maid_alias TARGET)
  string(SUBSTRING "${TARGET}" 1 -1 ALIAS_TARGET)
  string(REPLACE "_" "::" ALIAS_TARGET "${ALIAS_TARGET}")
  add_library("${ALIAS_TARGET}" ALIAS "${TARGET}")
endfunction()

macro(__maid_option VAR_NAME VAR_TYPE DEFAULT_VALUE DOCSTRING)
  set("${VAR_NAME}" "${DEFAULT_VALUE}" CACHE "${VAR_TYPE}" "${DOCSTRING}")
endmacro()
