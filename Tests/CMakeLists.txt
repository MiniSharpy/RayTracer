cmake_minimum_required (VERSION 3.12)

find_package(GTest CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_executable(Tests 
	"Maths/TupleTest.cpp"
)

set_property(TARGET Tests PROPERTY CXX_STANDARD 20)

# Link GTest main, is not performed by default in case user needs to implement their own version.
target_link_libraries(Tests PRIVATE GTest::gtest_main GTest::gtest)
# Use everything the main project does just incase include paths get confused.
target_link_libraries(Tests PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Link against core project.
target_link_libraries(Tests PRIVATE ${PROJECT_NAME}_static)

# For VS Test Explorer (And CTest) to work.
add_test(Tests Tests)