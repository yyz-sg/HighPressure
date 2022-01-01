cmake_minimum_required(VERSION "3.6.0")

project(High_Pressure)

add_executable(${PROJECT_NAME} Main.cpp)

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PUBLIC src)

target_link_directories(${PROJECT_NAME} PRIVATE src)

target_link_libraries(${PROJECT_NAME} SCode)