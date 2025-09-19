# Find or build ZLIB
set(ZLIB_EXTRA_OPTIONS)
if(WIN32)
    set(ZLIB_EXTRA_OPTIONS
        "ZLIB_INSTALL_COMPAT_DLL OFF"
    )
endif()

CPMAddPackage(
    NAME zlib
    GITHUB_REPOSITORY madler/zlib
    GIT_TAG develop
    OPTIONS
        "ZLIB_BUILD_TESTING OFF"
        "ZLIB_BUILD_SHARED OFF"
        "ZLIB_BUILD_STATIC ON"
        "ZLIB_BUILD_MINIZIP OFF"
        "ZLIB_INSTALL OFF"
        "ZLIB_PREFIX OFF"
        "${ZLIB_EXTRA_OPTIONS}"
)

# Make sure ZLIB::ZLIB is available as an alias for the static library
if(TARGET ZLIB::ZLIBSTATIC AND NOT TARGET ZLIB::ZLIB)
    add_library(ZLIB::ZLIB ALIAS ZLIB::ZLIBSTATIC)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ZLIB::ZLIBSTATIC)

#===========================================================================#

# Use local libssh library
set(LIBSSH_ROOT_DIR ${CMAKE_SOURCE_DIR}/libs/libssh)

# Set ZLIB_ROOT to help libssh find our zlib
set(ZLIB_ROOT ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})

# Add libssh as a subdirectory to build it as part of the project
add_subdirectory(${LIBSSH_ROOT_DIR} ${CMAKE_CURRENT_BINARY_DIR}/libssh EXCLUDE_FROM_ALL)

# Link against the local libssh library
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ssh)

# Add include directories for libssh
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${LIBSSH_ROOT_DIR}/include)

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        Calibration.h
        Calibration.cc
)



# Добавляем путь к заголовочным файлам текущего каталога
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})