cmake_minimum_required(VERSION 3.15)

# Project name
project(QuizzApp)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Include Conan toolchain
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Include directories
include_directories(src/db src/services src/controllers src/routes)

# Include Conan dependencies
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Find and include Conan dependencies
find_package(cjson REQUIRED)
find_package(libmysqlclient REQUIRED)

# Source files
set(SOURCES
    src/main.c
    src/db/connect-db.c
    src/services/service.c
    src/controllers/controller.c
    src/routes/routes.c
)

# Add the executable
add_executable(server ${SOURCES})

# Link libraries
target_link_libraries(server cjson::cjson mysqlclient)