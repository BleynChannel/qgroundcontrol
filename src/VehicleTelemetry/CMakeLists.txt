find_package(Qt6 REQUIRED COMPONENTS Core Mqtt)

qt_add_library(VehicleTelemetry STATIC
    VehicleTelemetry.h
    VehicleTelemetry.cc
)

target_link_libraries(VehicleTelemetry
    PRIVATE
        Settings
    PUBLIC
        Qt6::Core
		Qt6::Mqtt
)

target_include_directories(VehicleTelemetry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})