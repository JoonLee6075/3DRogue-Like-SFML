cmake_minimum_required(VERSION 3.8)

# Add the executable for your project
add_executable(CMakeProject2 
    "CMakeProject2.cpp" 
    "CMakeProject2.h" 
    "game.h" 
    "game.cpp" 
    "player.h" 
    "player.cpp" 
    "FileManager.h" 
    "FileManager.cpp"
)

# Link SFML libraries
target_link_libraries(CMakeProject2 
    ${CMAKE_SOURCE_DIR}/library/sfml-graphics.lib
    ${CMAKE_SOURCE_DIR}/library/sfml-audio.lib
    ${CMAKE_SOURCE_DIR}/library/sfml-main.lib
    ${CMAKE_SOURCE_DIR}/library/sfml-system.lib
    ${CMAKE_SOURCE_DIR}/library/sfml-window.lib
    ${CMAKE_SOURCE_DIR}/library/sfml-network.lib
)

# Include the SFML headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Copy 'resources' folder to build directory after the executable is built
# Add custom commands to copy resources folder for both Debug and Release builds
add_custom_command(TARGET CMakeProject2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:CMakeProject2>/resources"
    COMMENT "Copying resources to build directory"
)
