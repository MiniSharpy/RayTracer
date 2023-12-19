cmake_minimum_required(VERSION 3.27)

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC main.cpp)

# Create library and add modules used by the library.
add_library(${PROJECT_NAME}_static)
target_sources(${PROJECT_NAME}_static
  PUBLIC
    FILE_SET modules TYPE CXX_MODULES FILES
    "Maths/Matrix.ixx"
    "Maths/Tuple.ixx"
    "Rendering/Canvas.ixx"
     "Maths/FloatHelper.ixx" "Ray.ixx" "Sphere.ixx" "Intersection.ixx" "RayTracer.ixx" "Shape.ixx"  "Rendering/PointLight.ixx" "Rendering/Material.ixx" "Rendering/World.ixx" "Rendering/Camera.ixx")

# Link main to library..
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_static)
