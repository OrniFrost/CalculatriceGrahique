cmake_minimum_required(VERSION 3.24)
project(CalculatriceGrahique)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        Charts
        REQUIRED)

add_executable(CalculatriceGrahique main.cpp Parser/Numerics.cpp Parser/EquationSolver.cpp Parser/EquationSolver.h)
target_link_libraries(CalculatriceGrahique
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Charts
        )

