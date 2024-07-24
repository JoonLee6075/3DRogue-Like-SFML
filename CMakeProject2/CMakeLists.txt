# CMakeList.txt: CMakeProject2에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.
#
cmake_minimum_required (VERSION 3.8)

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (CMakeProject2 "CMakeProject2.cpp" "CMakeProject2.h" "game.h" "game.cpp" "player.h" "player.cpp")
target_link_libraries(CMakeProject2 ${CMAKE_SOURCE_DIR}/library/sfml-graphics.lib)
target_link_libraries(CMakeProject2 ${CMAKE_SOURCE_DIR}/library/sfml-audio.lib)
target_link_libraries(CMakeProject2 ${CMAKE_SOURCE_DIR}/library/sfml-main.lib)
target_link_libraries(CMakeProject2 ${CMAKE_SOURCE_DIR}/library/sfml-system.lib)
target_link_libraries(CMakeProject2 ${CMAKE_SOURCE_DIR}/library/sfml-window.lib)
target_link_libraries(CMakeProject2 ${CMAKE_SOURCE_DIR}/library/sfml-network.lib)
include_directories(${CMAKE_SOURCE_DIR}/include)

# TODO: 필요한 경우 테스트를 추가하고 대상을 설치합니다.
