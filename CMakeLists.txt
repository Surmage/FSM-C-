cmake_minimum_required(VERSION 3.25)
project(FSM_C++)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

SET(ROOT ${CMAKE_CURRENT_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/release>)

PROJECT(FSM)
FILE(GLOB FSM_headers FSM-C++/*.h)
FILE(GLOB FSM_sources FSM-C++/*.cc)

SET(FSM_C++ ${FSM_headers} ${FSM_sources})
SOURCE_GROUP("FSM" FILES ${FSM_C++})

ADD_EXECUTABLE(FSM ${FSM_C++})

ADD_LIBRARY(imgui STATIC 
			imgui/imconfig.h
			imgui/imconfig-SFML.h
			imgui/imgui.cpp
			imgui/imgui.h
			imgui/imgui_draw.cpp 
			imgui/imgui_internal.h
			imgui/imgui_tables.cpp
			imgui/imgui_widgets.cpp
			imgui/imgui-SFML.cpp
			imgui/imgui-SFML.h
			imgui/imgui-SFML_export.h
			imgui/imstb_rectpack.h
			imgui/imstb_textedit.h
			imgui/imstb_truetype.h
			)

TARGET_INCLUDE_DIRECTORIES(imgui PUBLIC imgui)
SET_TARGET_PROPERTIES(imgui PROPERTIES FOLDER "imgui")
TARGET_LINK_LIBRARIES(FSM INTERFACE imgui)

# Set the path to SFML directory
set(SFML_DIR SFML/lib/cmake/SFML/)

# Set SFML to use static libraries
set(SFML_STATIC_LIBRARIES TRUE)

# Find and include SFML
find_package(SFML 2.6.1 COMPONENTS graphics audio REQUIRED)
target_link_libraries(imgui PRIVATE sfml-graphics sfml-audio)
target_link_libraries(FSM PRIVATE sfml-graphics sfml-audio imgui)
IF(MSVC)
    set_property(TARGET FSM PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
ENDIF()
