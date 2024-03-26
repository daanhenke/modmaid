add_library(generic-example SHARED
    mod.cc
)

target_link_libraries(generic-example PRIVATE modmaid)
