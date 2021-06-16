add_subdirectory(utils)
add_subdirectory(engine)
add_subdirectory(karyotes)

add_executable(${EXECUTABLE_NAME} main.cpp engine/Engine.cpp engine/Engine.h)
set(EXECUTABLE_OUTPUT_PATH ..)

#target_link_libraries(${EXECUTABLE_NAME} PUBLIC tbb yaml-cpp)
target_link_libraries(${EXECUTABLE_NAME} utils karyotes engine)
target_link_libraries(${EXECUTABLE_NAME} sfml-window sfml-graphics)
