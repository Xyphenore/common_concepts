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

cmake_minimum_required( VERSION 3.22 )

# ----------------------------------------------------------------------------------------------------------------------
# Download latest version of doctest
# ----------------------------------------------------------------------------------------------------------------------

set( DOCTEST_FILE "${CMAKE_CURRENT_SOURCE_DIR}/doctest/doctest.h" )
set( DOCTEST_VERSION "${CMAKE_CURRENT_SOURCE_DIR}/doctest/version.txt" )

option( REGENERATE_DOCTEST "Re-download the DOCTEST library." OFF )

if ( NOT EXISTS ${DOCTEST_FILE} OR REGENERATE_DOCTEST )
    message( "Download the latest doctest library." )
    file(
        DOWNLOAD
        https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h
        ${DOCTEST_FILE}
        INACTIVITY_TIMEOUT 15
        SHOW_PROGRESS
    )

    message( "Download the doctest version." )
    file(
        DOWNLOAD
        https://raw.githubusercontent.com/doctest/doctest/master/scripts/version.txt
        ${DOCTEST_VERSION}
        INACTIVITY_TIMEOUT 15
        SHOW_PROGRESS
    )

else ()
    set( DOCTEST_VERSION_GIT "${CMAKE_CURRENT_SOURCE_DIR}/doctest/git_version.txt" )

    message( "Download the git doctest version." )
    file(
        DOWNLOAD
        https://raw.githubusercontent.com/doctest/doctest/master/scripts/version.txt
        ${DOCTEST_VERSION_GIT}
        INACTIVITY_TIMEOUT 15
        SHOW_PROGRESS
    )

    file( READ ${DOCTEST_VERSION_GIT} git_version )
    file( READ ${DOCTEST_VERSION} local_version )

    if ( ${local_version} LESS ${git_version} )
        message( "Download the latest doctest library." )
        file(
            DOWNLOAD
            https://raw.githubusercontent.com/doctest/doctest/master/doctest/doctest.h
            ${DOCTEST_FILE}
            INACTIVITY_TIMEOUT 15
            SHOW_PROGRESS
        )
        message( "Update the doctest library." )

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

foreach ( test ${TestsToRun} )
    get_filename_component( TName ${test} NAME_WE )
    add_test( NAME ${TName} COMMAND AllTests ${TName} )

    add_executable( ${TName} "${TName}.cpp" $<TARGET_OBJECTS:Test_Main> )
    target_compile_features( ${TName} PRIVATE cxx_std_20 )
    target_include_directories( ${TName} PRIVATE "${PROJECT_SOURCE_DIR}/include" )
endforeach ()
