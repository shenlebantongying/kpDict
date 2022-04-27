cmake_minimum_required(VERSION 3.16)

project(KopperDict VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_STANDARD 20)

find_package(Qt6 6.2 COMPONENTS Quick WebEngineQuick REQUIRED)

qt_add_executable(webdict
        main.cpp
        clipboard.h
        clipboard.cpp
        )

qt_add_qml_module(webdict
        URI qml_web
        VERSION 1.0
        QML_FILES main.qml
        )

set_target_properties(webdict PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        )

target_compile_definitions(webdict
        PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(webdict
        PRIVATE
        Qt6::Quick
        Qt::Core
        Qt::Gui
        Qt::WebEngineQuick)


