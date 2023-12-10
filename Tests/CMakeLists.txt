cmake_minimum_required (VERSION 3.12)

find_package(GTest CONFIG REQUIRED)

add_executable(${PROJECT_NAME}_Tests 
	"Maths/TupleTest.cpp"
	"Maths/CanvasTest.cpp")

target_link_libraries(${PROJECT_NAME}_Tests  PRIVATE GTest::gtest_main GTest::gtest)
target_link_libraries(${PROJECT_NAME}_Tests  PRIVATE ${PROJECT_NAME}_static)
add_test(AllTest ${PROJECT_NAME}_Tests)