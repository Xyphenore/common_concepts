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

cmake_minimum_required(VERSION 3.22)

# ----------------------------------------------------------------------------------------------------------------------
# Load Doxygen
# ----------------------------------------------------------------------------------------------------------------------

find_package( Doxygen REQUIRED )

# ----------------------------------------------------------------------------------------------------------------------
# Create the library doxygen-awesome-css
# ----------------------------------------------------------------------------------------------------------------------

set( INPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}" )
set( CONFIG_TEMPLATE "${CMAKE_CURRENT_SOURCE_DIR}/DoxygenConfig.conf.in" )
set( CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/DoxygenConfig.conf" )
set( DOXYGEN_AWESOME_CSS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-css" )

configure_file( ${CONFIG_TEMPLATE} ${CONFIG_FILE} @ONLY )

option( REGENERATE_DOXYGEN_AWESOME_CSS "Re-download the DOXYGEN-AWESOME-CSS library." OFF )

if( NOT EXISTS ${DOXYGEN_AWESOME_CSS_PATH} OR REGENERATE_DOXYGEN_AWESOME_CSS )
    set(
        HASH_AWESOME_CSS
        a4ad0b630a3ec8b360637e345e6dcf6d3b05fa097574c2a43cf53cfd78bd6af84dc8919aab7db9c75edc8c5745558799407f80ea000f3a2bd2b2353ff1d92e9c
    )
    set( ARCHIVE_DOXYGEN_AWESOME_CSS "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-css.tar.gz" )
    set( AWESOME_CSS_EXTRACTED "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-css-extracted" )

    # Download awesome css doxygen
    message("Download the library doxygen-awesome-css.")
    file(
        DOWNLOAD https://github.com/jothepro/doxygen-awesome-css/archive/refs/tags/v2.1.0.tar.gz
        ${ARCHIVE_DOXYGEN_AWESOME_CSS}
        INACTIVITY_TIMEOUT 15
        SHOW_PROGRESS
        EXPECTED_HASH SHA3_512=${HASH_AWESOME_CSS}
    )

    file( ARCHIVE_EXTRACT INPUT ${ARCHIVE_DOXYGEN_AWESOME_CSS} DESTINATION ${AWESOME_CSS_EXTRACTED} )
    file( GLOB DOWNLOADED_AWESOME_CSS LIST_DIRECTORIES true "${AWESOME_CSS_EXTRACTED}/doxygen-awesome-css*/*" )

    message("Move the downloaded doxygen-awesome-css into the directory doxygen-awesome-css.")
    foreach(file ${DOWNLOADED_AWESOME_CSS})
        file( COPY ${file} DESTINATION ${DOXYGEN_AWESOME_CSS_PATH} )
    endforeach()
    file( REMOVE_RECURSE ${AWESOME_CSS_EXTRACTED} )

    message("Clean the downloaded archive.")
    file( REMOVE ${ARCHIVE_DOXYGEN_AWESOME_CSS} )
endif()

# ----------------------------------------------------------------------------------------------------------------------
# Download emoji
# ----------------------------------------------------------------------------------------------------------------------

# ----------------------------------------------------------------------------------------------------------------------
# Execute Doxygen script
# ----------------------------------------------------------------------------------------------------------------------

add_custom_target(
    docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${CONFIG_FILE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)
