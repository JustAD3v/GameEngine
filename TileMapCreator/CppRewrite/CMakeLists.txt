cmake_minimum_required(VERSION 3.16)

project(tilemapcreator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS=1 ON)
add_definitions(-DMAP=$<CONFIG:Debug>)

#add_compile_options(-fsanitize=leak)
#add_link_options(-fsanitize=leak)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(spdlog REQUIRED)

qt_standard_project_setup()

add_executable(tilemapcreator
    Sources/main.cpp
    Sources/MainWindow.cpp
    Sources/ImportWindow.cpp
    Sources/TileMapScene.cpp
    Sources/TilePalette.cpp
    Sources/ClickableTile.cpp
)

target_link_libraries(tilemapcreator PRIVATE Qt6::Core Qt6::Widgets spdlog::spdlog)
