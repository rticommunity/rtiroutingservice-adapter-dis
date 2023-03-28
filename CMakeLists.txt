#
# (c) 2022 Copyright, Real-Time Innovations, Inc. (RTI) All rights reserved.
#
# RTI grants Licensee a license to use, modify, compile, and create derivative
# works of the Software solely in combination with RTI Connext DDS. Licensee
# may redistribute copies of the Software provided that all such copies are
# subject to this License. The Software is provided "as is", with no warranty
# of any type, including any warranty for fitness for any purpose. RTI is
# under no obligation to maintain or support the Software. RTI shall not be
# liable for any incidental or consequential damages arising out of the use or
# inability to use the Software. For purposes of clarity, nothing in this
# License prevents Licensee from using alternate versions of DDS, provided
# that Licensee may not combine or link such alternate versions of DDS with
# the Software.
#

cmake_minimum_required(VERSION 3.7)
project (DisAdapter)

if(CONNEXTDDS_IMPORTED_TARGETS_DEBUG)
    set(msg
        "You have selected to build the library in debug mode. It's recommended "
        "to run the debug version of Routing Service or otherwise you may run "
        "into undefined behavior")
    message(WARNING ${msg})
endif()

# Find RTI Connext dependencies
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/cmake/rticonnextdds-cmake-utils/cmake/Modules
)

find_package(
    RTIConnextDDS "6.0.1"
    REQUIRED
    COMPONENTS
        core
        routing_service
)

# Define the library that will provide the  Processor plugin
add_library(DisAdapter
    SHARED
    "${CMAKE_CURRENT_SOURCE_DIR}/src/DisAdapter.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/DisParser.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/DisSerializer.cxx"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/SocketUtil.cxx"
    )

# Set target properties for lang requirement output library name
set_target_properties(DisAdapter
    PROPERTIES
        CXX_STANDARD 98
        OUTPUT_NAME_DEBUG DisAdapterd
        LIBRARY_OUTPUT_DIRECTORY "${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY "${output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY "${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${output_dir}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${output_dir}"
)

target_link_libraries(DisAdapter
    RTIConnextDDS::cpp2_api
    RTIConnextDDS::routing_service_infrastructure)

target_include_directories(DisAdapter
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}")
