add_executable(modmaid-debug-app
    app.cc
    mod.cc
)

target_link_libraries(modmaid-debug-app PRIVATE modmaid)

