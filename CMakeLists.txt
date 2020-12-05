# cmake -DBOX2D_LIB_DIR_PREFIX="C:\Source\box2d-2.4.1\build\bin" -DSFML_LIB_DIR_PREFIX="C:\Source\SFML-2.5.1\build\lib" -DBOX2D_INCLUDE_DIR="C:\Source\box2d-2.4.1\include" -DSFML_INCLUDE_DIR="C:\Source\SFML-2.5.1\include" -DCMAKE_BUILD_TYPE=Debug ../

cmake_minimum_required(VERSION 3.16)
project(notlikeroguelike)

file(GLOB_RECURSE GWAN_HEAD "include/*.h")
file(GLOB_RECURSE GWAN_SOURCE "source/*.cpp")

add_executable(
    notlikeroguelike
    ${GWAN_SOURCE}
    ${GWAN_HEAD}
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
    message(STATUS "Starting MSVC CMAKE bit")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX /W4")
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