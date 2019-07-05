cmake_minimum_required(VERSION 2.8)

set(ALL_SAMPLES
    RawFetchFrame
#    SimpleView_FetchFrame
   )

find_package(OpenCV REQUIRED)
if (NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV library not found")
endif()

include_directories(${CMAKE_SOURCE_DIR}/../Include)
if (OPENCV_USED)
    include_directories(${CMAKE_SOURCE_DIR}/../ThirdPartyLib/Opencv-3.0/include)
endif()

foreach(sample ${ALL_SAMPLES})
    file(GLOB sources ${sample}/*.cpp)
    add_executable(${sample} ${sources})
    add_dependencies(${sample} tycam)
    if (OPENCV_USED)
        target_link_libraries(${sample} ${CMAKE_SOURCE_DIR}/../Lib/libtycam.so ${OpenCV_LIBS})
    else()
        target_link_libraries(${sample} ${CMAKE_SOURCE_DIR}/../Lib/libtycam.so)
    endif()
    set_target_properties(${sample} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
    install(TARGETS ${sample} RUNTIME DESTINATION bin/)
endforeach()

