cmake_minimum_required(VERSION 3.21)

PROJECT(exectime)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if ( MSVC )
    set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
    ADD_COMPILE_OPTIONS("/std:c++17")
endif()

ModuleImportAll("thirdparty")
LibImport("execute_module" "src/execute_module")

ExeImport("tools" "execute_module")

AddInstall("exectime" "")