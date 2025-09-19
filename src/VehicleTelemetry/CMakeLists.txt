target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        VehicleTelemetry.h
        VehicleTelemetry.cc
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt6::Mqtt)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})