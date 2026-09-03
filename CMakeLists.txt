cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0091 NEW)
project(FacElectronica LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Xml)

qt_add_executable(FacElectronica
    src/main.cpp
    src/client.cpp
    src/wsaalogin.cpp
    src/wsfemanager.cpp
    src/client.h
    src/wsaalogin.h
    src/wsfemanager.h
    src/wsfeform.ui
    src/sslclient.ui
    src/securesocketclient.qrc
)

target_include_directories(FacElectronica PRIVATE src)
target_compile_definitions(FacElectronica PRIVATE QT_ENABLE_FOREACH)
target_link_libraries(FacElectronica PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Xml
)

set_target_properties(FacElectronica PROPERTIES
    WIN32_EXECUTABLE TRUE
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
)

if(MSVC)
    set_property(TARGET FacElectronica PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
