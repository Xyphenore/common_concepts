# ------------------------------------------------------------------------
# Common_Concepts - Concepts not included in the std::concepts.
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

cmake_minimum_required( VERSION 3.16.3..3.23.2 )

project(
    common_concepts
    DESCRIPTION "Concepts not included in the std::concepts."
    HOMEPAGE_URL https://github.com/Xyphenore/common_concepts
    VERSION 1.0.1
)

# ----------------------------------------------------------------------------------------------------------------------
# Set the build type
# ----------------------------------------------------------------------------------------------------------------------

set( BUILD_TYPE_AVAILABLE RELEASE DEBUG )

if ( NOT DEFINED CMAKE_BUILD_TYPE )
    set(
        CMAKE_BUILD_TYPE RELEASE CACHE STRING
        "Choose the type of build, options are: ${BUILD_TYPE_AVAILABLE}."
        FORCE
    )
endif ()

string( TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE )

if ( NOT "${CMAKE_BUILD_TYPE}" IN_LIST BUILD_TYPE_AVAILABLE )
    message( STATUS "Choose the type of build, options are: ${BUILD_TYPE_AVAILABLE}." )
endif ()

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
if ( ${CMAKE_CXX_COMPILER_ID} EQUAL "GNU" )
    set(
        EXTRA_FLAGS
        -fimplicit-constexpr -Wnoexcept -Wstrict-null-sentinel -Wcatch-value=2 -Wuseless-cast
        -Wsuggest-final-types -Wsuggest-final-methods
    )
elseif ( ${CMAKE_CXX_COMPILER_ID} EQUAL "clang" )
endif ()
target_compile_options(
    ${PROJECT_NAME}
    INTERFACE
    -Wall -Wextra -Weffc++ -Wpedantic
    -fstrict-enums
    -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual
    -Wmismatched-tags -Wmismatched-new-delete -Wzero-as-null-pointer-constant -Wextra-semi
    -Wsuggest-override -Wdouble-promotion
    ${EXTRA_FLAGS}
)

# ----------------------------------------------------------------------------------------------------------------------
# Set available options
# ----------------------------------------------------------------------------------------------------------------------

option( CONCEPTS_WITH_TESTS "Build the test directory" OFF )
option( CONCEPTS_NO_INSTALL "Don't install the library" OFF )
option( CONCEPTS_WITH_DOCUMENTATION "Build the documentation" OFF )

if ( NOT CONCEPTS_NO_INSTALL )
    message( "Installation." )
    include( GNUInstallDirs )
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
