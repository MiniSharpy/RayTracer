cmake_minimum_required (VERSION 3.12)

set(ALL_FILES
	"BuildPlease.cpp"
)

# Copy data folder to build directory. Hard links might be better, then there's less duplicate data. CMAKE_CURRENT_SOURCE_DIR might be better instead of LIST.
add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Data ${CMAKE_CURRENT_BINARY_DIR}/Data)

# Includes
find_package(SDL2 CONFIG REQUIRED)

# Create project as static library to link against in testing.
add_library(${PROJECT_NAME}_static STATIC ${ALL_FILES})

target_include_directories(${PROJECT_NAME}_static PRIVATE ${CMAKE_CURRENT_LIST_DIR}) # This is neccesary for the testing includes to find the path.

# Linking against static library.
target_link_libraries(${PROJECT_NAME}_static PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Add source to this project's executable.
add_executable(${PROJECT_NAME} "main.cpp")
add_dependencies(${PROJECT_NAME} copy_assets)

# Linking against executable, strictly speaking only what's included in main is neccesary.
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)