cmake_minimum_required(VERSION 3.29)
project(ClassicalStateMachineDesignPattern)

set(CMAKE_CXX_STANDARD 20)

#Include the src directory
add_subdirectory(src)

#Add the main executable
add_executable(ClassicalStateMachineDesignPattern
        main.cpp
)

# Add header files for better IDE support
target_sources(ClassicalStateMachineDesignPattern PRIVATE
        src/Events/Events.h
        src/States/States.h
        src/TransitionHandler.cpp
        src/ModuleProgressReport.h
)

# Link the src library to the executable
target_link_libraries(ClassicalStateMachineDesignPattern PRIVATE src)

