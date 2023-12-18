cmake_minimum_required(VERSION 3.27)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}_Tests 
	"TupleTest.cpp"
	"CanvasTest.cpp" "MatrixTest.cpp" "RayTest.cpp" "SphereTest.cpp" "LightTest.cpp" "MaterialTest.cpp" "WorldTest.cpp")

target_link_libraries(${PROJECT_NAME}_Tests  PRIVATE GTest::gtest_main GTest::gtest)
target_link_libraries(${PROJECT_NAME}_Tests  PRIVATE ${PROJECT_NAME}_static)
add_test(AllTest ${PROJECT_NAME}_Tests)