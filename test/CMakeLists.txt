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

cmake_minimum_required( VERSION 3.12 )

# ----------------------------------------------------------------------------------------------------------------------
# Download latest version of doctest
# ----------------------------------------------------------------------------------------------------------------------

set( DOCTEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/doctest" )
set( DOCTEST_FILE "${DOCTEST_DIR}/doctest.h" )
set( DOCTEST_VERSION "${DOCTEST_DIR}/version.txt" )

option( REGENERATE_DOCTEST "Re-download the DOCTEST library." OFF )
message( STATUS "Re-download the DOCTEST library: " ${REGENERATE_DOCTEST} )

if ( NOT EXISTS ${DOCTEST_FILE} OR REGENERATE_DOCTEST )
    message( STATUS "Download the latest doctest library." )
    file(
        DOWNLOAD
        https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h
        ${DOCTEST_FILE}
        TIMEOUT 15
    )
    message( STATUS "Download the latest doctest library: 100%." )

    message( STATUS "Download the doctest version." )
    file(
        DOWNLOAD
        https://raw.githubusercontent.com/doctest/doctest/master/scripts/version.txt
        ${DOCTEST_VERSION}
        TIMEOUT 15
    )
    message( STATUS "Download the doctest version: 100%." )

else ()
    set( DOCTEST_VERSION_GIT "${DOCTEST_DIR}/git_version.txt" )

    message( STATUS "Download the git doctest version." )
    file(
        DOWNLOAD
        https://raw.githubusercontent.com/doctest/doctest/master/scripts/version.txt
        ${DOCTEST_VERSION_GIT}
        TIMEOUT 15
    )
    message( STATUS "Download the git doctest version: 100%." )

    file( STRINGS ${DOCTEST_VERSION_GIT} git_version LIMIT_COUNT 1 )
    file( STRINGS ${DOCTEST_VERSION} local_version LIMIT_COUNT 1 )

    if ( ${local_version} VERSION_LESS ${git_version} )
        message( STATUS "Download the latest doctest library." )
        file(
            DOWNLOAD
            https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h
            ${DOCTEST_FILE}
            TIMEOUT 15
        )
        message( STATUS "Download the latest doctest library: 100%." )
        message( STATUS "Update the doctest library." )

        file( RENAME ${DOCTEST_VERSION_GIT} ${DOCTEST_VERSION} )

    else ()
        file( REMOVE ${DOCTEST_VERSION_GIT} )

    endif ()

endif ()

# ----------------------------------------------------------------------------------------------------------------------
# Create the doctest library and the main function
# ----------------------------------------------------------------------------------------------------------------------

add_library( doctest INTERFACE )
target_compile_features( doctest INTERFACE cxx_std_20 )
target_include_directories( doctest INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/doctest" )

add_library( Test_Main OBJECT main.cpp )
target_compile_features( Test_Main PRIVATE cxx_std_20 )
target_link_libraries( Test_Main PRIVATE doctest )

# ----------------------------------------------------------------------------------------------------------------------
# Set all tests
# ----------------------------------------------------------------------------------------------------------------------

set(
    TestsToRun
    test_comparable_regular.cpp
    test_hashable.cpp
)

# ----------------------------------------------------------------------------------------------------------------------
# Create the executable AllTests
# ----------------------------------------------------------------------------------------------------------------------

add_executable( AllTests ${TestsToRun} $<TARGET_OBJECTS:Test_Main> )
target_compile_features( AllTests PRIVATE cxx_std_20 )
target_include_directories( AllTests PRIVATE "${PROJECT_SOURCE_DIR}/include" )

# ----------------------------------------------------------------------------------------------------------------------
# Create each unique test
# ----------------------------------------------------------------------------------------------------------------------

foreach ( test IN LISTS ${TestsToRun} )
    get_filename_component( TName ${test} NAME_WE )
    add_test( NAME ${TName} COMMAND AllTests ${TName} )

    add_executable( ${TName} "${TName}.cpp" $<TARGET_OBJECTS:Test_Main> )
    target_compile_features( ${TName} PRIVATE cxx_std_20 )
    target_include_directories( ${TName} PRIVATE "${PROJECT_SOURCE_DIR}/include" )
endforeach ()
