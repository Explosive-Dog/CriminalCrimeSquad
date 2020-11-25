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
)

if (${MSVC})
    target_include_directories(
        notlikeroguelike
        PUBLIC
        ${SFML_INCLUDE_DIR}
        ${BOX2D_INCLUDE_DIR}
    )

    file(
        GLOB
        SFML_DLLS
        "${SFML_LIB_DIR_PREFIX}/${CMAKE_BUILD_TYPE}/*.dll"
    )

    file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_BINARY_DIR})

    target_link_directories(
        notlikeroguelike
        PUBLIC
        "${SFML_LIB_DIR_PREFIX}/${CMAKE_BUILD_TYPE}"
        "${BOX2D_LIB_DIR_PREFIX}/${CMAKE_BUILD_TYPE}"
    )
    if (${CMAKE_BUILD_TYPE} MATCHES Debug)
        target_link_libraries(
            notlikeroguelike
            PUBLIC
            sfml-graphics-d
            sfml-system-d
            sfml-window-d
        )
    else()
        target_link_libraries(
            notlikeroguelike
            PUBLIC
            sfml-graphics
            sfml-system
            sfml-window
        )
    endif() # CMAKE_BUILD_TYPE
else()
    target_link_libraries(
        notlikeroguelike
        PUBLIC
        sfml-graphics
        sfml-system
        sfml-window
    )
endif() # MSVC