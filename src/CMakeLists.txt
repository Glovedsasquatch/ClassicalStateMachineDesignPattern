# Create a library from the source files
add_library(src INTERFACE
        TransitionHandler.cpp
        ModuleProgressReport.h)

# Add the include subdirectories for the headers within the subdirectories
target_include_directories(src INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Events
    ${CMAKE_CURRENT_SOURCE_DIR}/States
    ${CMAKE_CURRENT_SOURCE_DIR}/Config
)