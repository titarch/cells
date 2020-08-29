set(engine_src_files
        Engine.h Engine.cpp GUI.cc GUI.hh)

add_library(engine ${engine_src_files})

target_link_libraries(engine PRIVATE)