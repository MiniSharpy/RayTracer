cmake_minimum_required(VERSION 3.27)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}_Tests 
	"Maths/TupleTest.cpp"
	"Rendering/CanvasTest.cpp" "Maths/MatrixTest.cpp" "RayTest.cpp" "Shapes/SphereTest.cpp" "Rendering/LightTest.cpp" "Rendering/MaterialTest.cpp" "Rendering/WorldTest.cpp" "IntersectionTest.cpp" "Maths/TransformationTest.cpp" "Rendering/CameraTest.cpp" "Shapes/PlaneTest.cpp" "Rendering/PatternTest.cpp")

target_link_libraries(${PROJECT_NAME}_Tests  PRIVATE GTest::gtest_main GTest::gtest)
target_link_libraries(${PROJECT_NAME}_Tests  PRIVATE ${PROJECT_NAME}_static)
add_test(AllTest ${PROJECT_NAME}_Tests)