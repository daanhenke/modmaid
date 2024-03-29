add_mod(generic-example
    mod.cc
)

target_link_libraries(generic-example PRIVATE modmaid::gui)
