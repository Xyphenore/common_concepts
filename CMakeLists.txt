# ------------------------------------------------------------------------
# Common_Concepts - Safe conversion from a string to integer.
# Copyright (C)  2022 Xyphenore
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
# ------------------------------------------------------------------------

cmake_minimum_required( VERSION 3.22 )

project(
    common_concepts
    DESCRIPTION "Concepts not included in the std::concepts."
    VERSION 1.0.1
)

include( GNUInstallDirs )

# ----------------------------------------------------------------------------------------------------------------------
# Create the common_concepts library
# ----------------------------------------------------------------------------------------------------------------------

add_library( ${PROJECT_NAME} INTERFACE )
target_compile_features(
    ${PROJECT_NAME}
    INTERFACE
    cxx_std_20
)
target_include_directories(
    ${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ----------------------------------------------------------------------------------------------------------------------
# Set available options
# ----------------------------------------------------------------------------------------------------------------------

option( CONCEPTS_WITH_TESTS "Build the test directory" OFF )
option( CONCEPTS_NO_INSTALL "Don't install the library" OFF )
option( CONCEPTS_WITH_DOCUMENTATION "Build the documentation" OFF )

if ( NOT CONCEPTS_NO_INSTALL )
    message( "Installation." )
    add_subdirectory( cmake )
endif ()

if ( CONCEPTS_WITH_TESTS )
    message( "Tests activate." )

    include( CTest )

    # Activate the CTest discovery
    enable_testing()

    add_subdirectory( test )
endif ()

if ( CONCEPTS_WITH_DOCUMENTATION )
    message( "Documentation activate." )
    add_subdirectory( doc )
endif ()
