cmake_minimum_required(VERSION 3.16)
project(notlikeroguelike)

add_executable(
    notlikeroguelike
    source/main.cpp
    source/Camera.cpp
    source/Character.cpp
    source/KeyboardAndMouseState.cpp
    source/Player.cpp
    source/Projectile.cpp
    source/Selectable.cpp
    source/SelectionBox.cpp
)

target_include_directories(
    notlikeroguelike
    PUBLIC
    include
)

target_link_libraries(
    notlikeroguelike
    PUBLIC
    box2d
    sfml-graphics
    sfml-system
    sfml-window
)
