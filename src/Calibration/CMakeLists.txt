find_package(Qt6 REQUIRED COMPONENTS Core)

# include(FetchContent)
# FetchContent_Declare(libssh
#     GIT_REPOSITORY https://git.libssh.org/projects/libssh.git
#     GIT_TAG master
# )
# FetchContent_MakeAvailable(libssh)

qt_add_library(Calibration STATIC
    Calibration.h
    Calibration.cc
)

target_link_libraries(Calibration
    PRIVATE
        Settings
        ssh
    PUBLIC
        Qt6::Core
)

target_include_directories(Calibration PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})