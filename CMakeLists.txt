cmake_minimum_required(VERSION 3.15)

project(kpdict
        VERSION 0.1
        LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/kpDict.cpp
        src/kpDict.h
        src/clipboard.cpp
        src/clipboard.h
        src/kpWebView.h
        src/kpWebView.cpp
        src/common.h
        src/settingsDialog.h
        src/settingsDialog.cpp
        )

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    data/icons.qrc
    ${PROJECT_SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER org.slbtty.${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(TARGETS ${PROJECT_NAME} DESTINATION bin)
endif ()

qt_finalize_executable(${PROJECT_NAME})
