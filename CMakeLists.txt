cmake_minimum_required(VERSION 3.15)

project(kopperdict VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

set(PROJECT_SOURCES
        main.cpp
        kpDict.cpp
        kpDict.h
        clipboard.cpp
        clipboard.h
        kpWebView.h
        kpWebView.cpp
        common.h
        )

qt_add_executable(kopperdict
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(kopperdict PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)

set_target_properties(kopperdict PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(TARGETS kopperdict DESTINATION bin)
endif ()

qt_finalize_executable(kopperdict)
