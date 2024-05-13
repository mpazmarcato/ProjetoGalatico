cmake_minimum_required(VERSION 3.5)
project (PROJETOGALATICO VERSION 1.0.0 LANGUAGES CXX )

# Currently CMake (since 2.8.5) supports generation of compilation databases
# for Unix Makefile builds (Ninja builds in the works) with the option
# CMAKE_EXPORT_COMPILE_COMMANDS.
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

#=== SETTING VARIABLES ===#
set( APP_NAME "ProjetoGalatico")
# Appending to existing flags the correct way (two methods)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic")
# string(APPEND CMAKE_CXX_FLAGS " -Wall -Werror")


#=== INCLUDE DIRECTORIES ===#
include_directories(include)

#=== Main App ===
#file(GLOB SOURCES "src/*.cpp")

#add_executable( ${APP_NAME} ${SOURCES})
add_executable(${APP_NAME} 
    main.cpp
    impl/astronauta.cpp 
    impl/flight.cpp
    impl/interface.cpp
    impl/sistema.cpp
)
target_include_directories( ${APP_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib )
target_compile_features( ${APP_NAME}  PUBLIC cxx_std_17 )