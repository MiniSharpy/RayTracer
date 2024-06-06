cmake_minimum_required(VERSION 3.28)

# Create library and add modules used by the library.
add_library(${PROJECT_NAME}_static)
target_sources(${PROJECT_NAME}_static
  PUBLIC
    FILE_SET CXX_MODULES FILES
    "Maths/Matrix.ixx"
    "Maths/Tuple.ixx"
    "Rendering/Canvas.ixx"
     "Maths/FloatHelper.ixx" "Ray.ixx" "Shapes/Sphere.ixx" "RayTracer.ixx" "Shapes/Shape.ixx"  "Rendering/PointLight.ixx" "Rendering/Material.ixx" "Rendering/World.ixx" "Rendering/Camera.ixx" "Shapes/Plane.ixx"  "Rendering/Pattern.ixx")

add_executable(${PROJECT_NAME} "main.ixx")

# Link main to library..
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_static)
