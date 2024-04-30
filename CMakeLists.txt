cmake_minimum_required(VERSION 3.2)

PROJECT(exectime)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

ModuleImportAll("thirdparty")
LibImport("execute_module" "src/execute_module")
ExeImport("tools" "execute_module")

INSTALL(DIRECTORY include/ DESTINATION include)
INSTALL(TARGETS exectime
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

AddUninstallTarget()