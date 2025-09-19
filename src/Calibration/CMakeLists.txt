# Use local libssh library
set(LIBSSH_ROOT_DIR ${CMAKE_SOURCE_DIR}/libs/libssh)

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