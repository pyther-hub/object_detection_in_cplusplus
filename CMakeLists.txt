cmake_minimum_required(VERSION 3.13)
project(yolo_ort)

option(ONNXRUNTIME_DIR "Path to built ONNX Runtime directory." STRING)
message(STATUS "ONNXRUNTIME_DIR: ${ONNXRUNTIME_DIR}")

find_package(OpenCV REQUIRED)
find_path(ONNX_RUNTIME_SESSION_INCLUDE_DIRS onnxruntime_cxx_api.h HINTS /usr/local/include/onnxruntime/core/session/)
find_library(ONNX_RUNTIME_LIB onnxruntime HINTS /usr/local/lib)


include_directories("include/")

add_executable(yolo_ort
               src/main.cpp
               src/detector.cpp
               src/utils.cpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
target_include_directories(yolo_ort PRIVATE ${ONNX_RUNTIME_SESSION_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(yolo_ort PRIVATE ${ONNX_RUNTIME_LIB} ${OpenCV_LIBRARIES})
# target_include_directories(yolo_ort PRIVATE "${ONNXRUNTIME_DIR}/include")
# # link_directories("${ONNXRUNTIME_DIR}/lib")
# target_compile_features(yolo_ort PRIVATE cxx_std_14)
# target_link_libraries(yolo_ort ${OpenCV_LIBS})
# target_link_libraries(yolo_ort "${ONNXRUNTIME_DIR}/lib/onnxruntime.lib")


# if (WIN32)
#     target_link_libraries(yolo_ort "${ONNXRUNTIME_DIR}/lib/onnxruntime.lib")
# endif(WIN32)

# if (UNIX)
#     target_link_libraries(yolo_ort "${ONNXRUNTIME_DIR}/lib/libonnxruntime.so")
# endif(UNIX)

