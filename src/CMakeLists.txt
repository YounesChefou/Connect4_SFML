# Declaring SFML variable to include library SFML during compilation
set(SFML
    -lsfml-graphics 
    -lsfml-window 
    -lsfml-system
    )

# Include headers and the current directories' files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Declaring current directory as variable name SOURCES
set(SOURCES
    Connect4.cpp
    Connect4_SFML.cpp)

# Building a library made of the Connect4 classes 
add_library(libconnect4 STATIC ${SOURCES})
set_target_properties(libconnect4 PROPERTIES OUTPUT_NAME "connect4")
target_include_directories(libconnect4 PUBLIC include)
target_link_libraries(libconnect4 ${SFML})

# Creating executable for the game
add_executable(connect4 Game_SFML.cpp)
target_link_libraries(connect4 libconnect4)
set_target_properties(connect4 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)