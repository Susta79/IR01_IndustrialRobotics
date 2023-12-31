cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project ("IR01_IndustrialRobotics")

message (STATUS "[${PROJECT_NAME}] Processing ${CMAKE_CURRENT_LIST_FILE}")

set (SAMPLE_TARGET_NAME ${PROJECT_NAME})
set (CMAKE_SCRIPTS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/_cmake_scripts" CACHE STRING "The path of the cmake scripts directory.")
set (SAMPLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/output/bin")
set (APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/appicon.rc")

include (${CMAKE_SCRIPTS_PATH}/cmake_detect_architecture.cmake)
detect_target_architecture (ARCH)

set (CMAKE_AUTOMOC TRUE)
set (CMAKE_AUTORCC TRUE)

if (MSVC)
    set (SAMPLE_TARGET_DEFINITION_ADDENDUM WIN32)
endif ()

add_executable (${SAMPLE_TARGET_NAME} ${SAMPLE_TARGET_DEFINITION_ADDENDUM} 
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/joint.cpp
    src/joint.h
    src/robot.cpp
    src/robot.h
    src/link.cpp
    src/link.h
    src/pose.cpp
    src/pose.h
    src/kinematic.cpp
    src/kinematic.h
    src/tcpclient.cpp
    src/tcpclient.h
    src/trajectory.cpp
    src/trajectory.h
    include/IR01/error_def.h
    ${APP_ICON_RESOURCE_WINDOWS}
)

target_include_directories(${SAMPLE_TARGET_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${SAMPLE_TARGET_NAME}>
    $<INSTALL_INTERFACE:include/${SAMPLE_TARGET_NAME}>
)

target_include_directories(${SAMPLE_TARGET_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

find_package (Threads REQUIRED)

find_package (Qt5 COMPONENTS Widgets Core Gui Network REQUIRED)
set(QT_INSTALL_PREFIX "${_qt5Core_install_prefix}")

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

target_link_libraries (${SAMPLE_TARGET_NAME}
    ${CMAKE_THREAD_LIBS_INIT}
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
    Qt5::Network
    Eigen3::Eigen
)

if ((CMAKE_CXX_COMPILER_ID MATCHES "GNU") OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    target_link_libraries (${SAMPLE_TARGET_NAME}
        atomic
    )
endif ()

# Set output directories for all configuration types (Debug, Release, etc.)
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Debug")
endif()
if (NOT CMAKE_CONFIGURATION_TYPES)
    set (CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE})
endif ()
if (CMAKE_CONFIGURATION_TYPES)
    foreach (CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
        string (TOUPPER ${CONFIGURATION_TYPE} CONFIGURATION_TYPE_UPPER)
        if (CONFIGURATION_TYPE_UPPER STREQUAL "RELEASE")
            set (SAMPLE_RUNTIME_OUTPUT_NAME ${SAMPLE_TARGET_NAME})
            set (SAMPLE_RUNTIME_OUTPUT_DIRECTORY ${SAMPLE_OUTPUT_PATH}/${ARCH})
        else ()
            string (TOLOWER ${CONFIGURATION_TYPE} CONFIGURATION_TYPE_LOWER)
            set (SAMPLE_RUNTIME_OUTPUT_NAME "${SAMPLE_TARGET_NAME}_${CONFIGURATION_TYPE_LOWER}")
            set (SAMPLE_RUNTIME_OUTPUT_DIRECTORY ${SAMPLE_OUTPUT_PATH}/${ARCH}/${CONFIGURATION_TYPE})
        endif ()
        set_target_properties (${SAMPLE_TARGET_NAME} PROPERTIES
            RUNTIME_OUTPUT_NAME_${CONFIGURATION_TYPE_UPPER} ${SAMPLE_RUNTIME_OUTPUT_NAME}
            RUNTIME_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE_UPPER} ${SAMPLE_RUNTIME_OUTPUT_DIRECTORY}
        )
        message (STATUS "[${PROJECT_NAME}] Cfg ${CONFIGURATION_TYPE} -> Output directory: ${SAMPLE_RUNTIME_OUTPUT_DIRECTORY}, Output name: ${SAMPLE_RUNTIME_OUTPUT_NAME}")
    endforeach ()
endif ()

if ((CMAKE_CXX_COMPILER_ID MATCHES GNU) OR (CMAKE_CXX_COMPILER_ID MATCHES Clang))
    # ignore errors in headers from qt widgets include directories
    foreach (INCLUDE_DIR ${Qt5Widgets_INCLUDE_DIRS})
        if (NOT "${INCLUDE_DIR}" STREQUAL "/usr/include")
            set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${INCLUDE_DIR}")
        endif ()
    endforeach ()
endif ()

set_target_properties(${SAMPLE_TARGET_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS NO
)

if (MSVC)
    target_compile_options (${SAMPLE_TARGET_NAME}
        PRIVATE "/bigobj"
        PRIVATE "/MP"
    )
endif ()

GET_PROPERTY(${LIBRARY_NAME_UPPER_VISION_API}_LIBRARIES_COPIED_LOCAL GLOBAL PROPERTY ${LIBRARY_NAME_UPPER_VISION_API}_LIBRARIES_COPIED)
if(NOT ${LIBRARY_NAME_UPPER_VISION_API}_LIBRARIES_COPIED_LOCAL)
    file (GLOB ids_peak_LIBS
        "${${LIBRARY_NAME_UPPER_VISION_API}_LIBRARY_DIR}/*${CMAKE_SHARED_LIBRARY_SUFFIX}"
    )
    foreach (ids_peak_LIBRARY ${ids_peak_LIBS})
        message (STATUS "[${PROJECT_NAME}] Add PostBuildStep for copy of ${ids_peak_LIBRARY}.")
        add_custom_command (TARGET ${SAMPLE_TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${ids_peak_LIBRARY}
            $<TARGET_FILE_DIR:${SAMPLE_TARGET_NAME}>
            COMMENT "Post build copy of ${ids_peak_LIBRARY} to output dir." VERBATIM
        )
    endforeach ()
    SET_PROPERTY(GLOBAL PROPERTY ${LIBRARY_NAME_UPPER_VISION_API}_LIBRARIES_COPIED ON)
endif()

GET_PROPERTY(${LIBRARY_NAME_LIBIMG_UPPER}_LIBRARIES_COPIED_LOCAL GLOBAL PROPERTY ${LIBRARY_NAME_LIBIMG_UPPER}_LIBRARIES_COPIED)
if(NOT ${LIBRARY_NAME_LIBIMG_UPPER}_LIBRARIES_COPIED_LOCAL)
    file (GLOB ids_peak_ipl_LIBS
        "${${LIBRARY_NAME_LIBIMG_UPPER}_LIBRARY_DIR}/*${CMAKE_SHARED_LIBRARY_SUFFIX}"
    )
    foreach (ids_peak_ipl_LIBRARY ${ids_peak_ipl_LIBS})
        message (STATUS "[${PROJECT_NAME}] Add PostBuildStep for copy of ${ids_peak_ipl_LIBRARY}.")
        add_custom_command (TARGET ${SAMPLE_TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${ids_peak_ipl_LIBRARY}
            $<TARGET_FILE_DIR:${SAMPLE_TARGET_NAME}>
            COMMENT "Post build copy of ${ids_peak_ipl_LIBRARY} to output dir." VERBATIM
        )
    endforeach ()
    SET_PROPERTY(GLOBAL PROPERTY ${LIBRARY_NAME_LIBIMG_UPPER}_LIBRARIES_COPIED ON)
endif()

if (WIN32)
    # copy qt libraries to the output folder
    message (STATUS "[${PROJECT_NAME}] Add PostBuildStep for copy of the Qt libs. ${QT_INSTALL_PREFIX}")
    add_custom_command (TARGET ${SAMPLE_TARGET_NAME} POST_BUILD
        COMMAND "${QT_INSTALL_PREFIX}/bin/windeployqt"
                $<$<CONFIG:Debug>:--debug>$<$<NOT:$<CONFIG:Debug>>:--release>
                --no-quick-import
                --no-translations
                --no-system-d3d-compiler
                --no-webkit2
                --no-angle
                --no-opengl-sw
                --no-svg
                --dir $<TARGET_FILE_DIR:${SAMPLE_TARGET_NAME}>
                $<TARGET_FILE:${SAMPLE_TARGET_NAME}>
    )
endif ()

# For unix Build we need the environment variable GENICAM_GENTL32_PATH respectivily GENICAM_GENTL64_PATH to find the GenTL producer libraries.
# To set these environment variables a shell script is used wich can be found in the samples root folder in _cmake_scripts.
# To run the samples run this script not the binary.
if (UNIX)
    string (TOLOWER ${CMAKE_BUILD_TYPE} CONFIGURATION_TYPE_LOWER)
    if(${CONFIGURATION_TYPE_LOWER} STREQUAL "release")
        set(VSSL_SAMPLE_BINARY_NAME ${PROJECT_NAME})
    else()
        set(VSSL_SAMPLE_BINARY_NAME ${PROJECT_NAME}_${CONFIGURATION_TYPE_LOWER})
    endif()
    configure_file(${CMAKE_SCRIPTS_PATH}/sample_starter.in ${CMAKE_CURRENT_BINARY_DIR}/${VSSL_SAMPLE_BINARY_NAME}.sh)
    file(COPY ${CMAKE_CURRENT_BINARY_DIR}/${VSSL_SAMPLE_BINARY_NAME}.sh
        DESTINATION ${SAMPLE_RUNTIME_OUTPUT_DIRECTORY}
        FILE_PERMISSIONS
            OWNER_READ OWNER_WRITE OWNER_EXECUTE
            GROUP_READ GROUP_EXECUTE
            WORLD_READ WORLD_EXECUTE
    )
endif (UNIX)
