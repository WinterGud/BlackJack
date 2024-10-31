cmake_minimum_required(VERSION 3.10)

# Set C++ standart
set (CMAKE_CXX_STANDARD 26)

# Set the project name
project(Main)

# Create a sources variable with a link to all cpp files to compile
file(GLOB CPP_SOURCES "src/*.cpp")
file(GLOB CPP_MAIN "*.cpp")
file(GLOB HPP_SOURCES "src/*.hpp")
file(GLOB H_SOURCES "src/*.h")

include_directories("${PROJECT_SOURCE_DIR}/src")

#SDL2 SETTINGS

# Include directories for headers
set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include")
include_directories(${SDL2_INCLUDE_DIRS})

# Specify the path to the .dll and .lib files
set(LIB_PATH "${CMAKE_CURRENT_LIST_DIR}/lib")

# Link against the .lib file
link_directories(${LIB_PATH})

# Add the executable target
add_executable(${PROJECT_NAME}
    ${HPP_SOURCES} 
    ${H_SOURCES} 
    ${CPP_SOURCES} 
    ${CPP_MAIN})

target_link_libraries(${PROJECT_NAME} "${LIB_PATH}/SDL2.lib" "${LIB_PATH}/SDL2main.lib" "${LIB_PATH}/SDL2_image.lib")


add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    # Копіюємо необхідні .dll файли
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIB_PATH}/SDL2.dll"
        "${LIB_PATH}/SDL2_image.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
        
    # Копіюємо файл config.json
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/Main/config.json"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>

    # Копіюємо всю папку assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Main/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
)