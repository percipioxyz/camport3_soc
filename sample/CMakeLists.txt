cmake_minimum_required(VERSION 2.8)

set(ALL_SAMPLES
    RawFetchFrame
   )

include_directories(${CMAKE_SOURCE_DIR}/../include)

foreach(sample ${ALL_SAMPLES})
    file(GLOB sources ${sample}/*.cpp)
    add_executable(${sample} ${sources})
    add_dependencies(${sample} tycam)
    target_link_libraries(${sample} ${CMAKE_SOURCE_DIR}/../lib/libtycam.so)
    set_target_properties(${sample} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
    install(TARGETS ${sample} RUNTIME DESTINATION bin/)
endforeach()

