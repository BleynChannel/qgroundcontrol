# Find libssh library
find_library(SSH_LIBRARY
    NAMES ssh libssh
    PATHS ${CMAKE_SOURCE_DIR}/../libs/libssh/build/src
    NO_DEFAULT_PATH
    REQUIRED
)

# Add include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${SSH_INCLUDE_DIR})

# Link against libssh library
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${SSH_LIBRARY})

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        Calibration.h
        Calibration.cc
)



# Добавляем путь к заголовочным файлам текущего каталога
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})