#    Copyright (c) 2010-2019, Delft University of Technology
#    All rigths reserved
#
#    This file is part of the Tudat. Redistribution and use in source and
#    binary forms, with or without modification, are permitted exclusively
#    under the terms of the Modified BSD license. You should have received
#    a copy of the license with this file. If not, please or visit:
#    http://tudat.tudelft.nl/LICENSE.
#


# Set the source files.
set(PYBINDINGS_SOURCES
        "${SRCROOT}${PYBINDINGS_DIR}/PyBindingsEntrypoint.cpp"
        "${SRCROOT}${PYBINDINGS_DIR}/DataStructures/eigenWrapper.cpp"
        "${SRCROOT}${PYBINDINGS_DIR}/Astodynamics/BasicAstrodynamics/unitConversions.cpp"
        "${SRCROOT}${PYBINDINGS_DIR}/Astodynamics/BasicAstrodynamics/physicalConstants.cpp"
        )

# Set the header files.
set(PYBINDINGS_HEADERS
        "${SRCROOT}${PYBINDINGS_DIR}/DataStructures/eigenWrapper.h"
        "${SRCROOT}${PYBINDINGS_DIR}/Astodynamics/BasicAstrodynamics/unitConversions.h"
        "${SRCROOT}${PYBINDINGS_DIR}/Astodynamics/BasicAstrodynamics/physicalConstants.h"
         )


macro(setup_pymodule_target target_name)
 set_property(TARGET ${target_name} PROPERTY RUNTIME_OUTPUT_DIRECTORY "${BINROOT}")
 set_target_properties(${target_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${BINROOT})
 install(TARGETS ${target_name} LIBRARY DESTINATION "${BINROOT}")
endmacro()

add_library(PyBindings MODULE ${PYBINDINGS_HEADERS} ${PYBINDINGS_SOURCES})
target_include_directories(PyBindings PRIVATE ${PYTHON_INCLUDE_DIRS})
set_target_properties(PyBindings PROPERTIES COMPILE_FLAGS " -fPIC ")
set_target_properties(PyBindings PROPERTIES LINK_FLAGS " -shared -Wl,-Bshareable")
set_target_properties(PyBindings PROPERTIES PREFIX "")
set_target_properties(PyBindings PROPERTIES OUTPUT_NAME "Tudat")
target_link_libraries(PyBindings -Wl,-Bshareable ${Boost_LIBRARIES}  ${PYTHON_LIBRARIES})

add_custom_command(
        TARGET PyBindings POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SRCROOT}${PYBINDINGS_DIR}/PyTudat/
        ${BINROOT}/PyTudat/)

add_custom_command(
        TARGET PyBindings POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SRCROOT}${PYBINDINGS_DIR}/PyTudat/
        ${BINROOT}/PyTudat/)

add_custom_command(
        TARGET PyBindings POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${BINROOT}/Tudat.so
        ${BINROOT}/PyTudat/Tudat.so)

add_custom_command(
        TARGET PyBindings POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SRCROOT}${PYBINDINGS_DIR}/MinimalWorkingExample.py
        ${BINROOT}/MinimalWorkingExample.py)

setup_pymodule_target(PyBindings)