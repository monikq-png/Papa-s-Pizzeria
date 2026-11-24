cmake_minimum_required(VERSION 3.28)

# NOTE: update EXECUTABLE_NAME in .github/workflows/cmake.yml when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}_main")
set(MAIN_LIBRARY_NAME "${MAIN_PROJECT_NAME}")
set(TESTS_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}_test")

# needs to be before `project()` to take effect
option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compilation database" ON)

project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

include(CTest)
include(cmake/RegisterTests.cmake)

###############################################################################

# External dependencies with FetchContent

# include(FetchContent)
#
# set(FETCHCONTENT_QUIET OFF CACHE INTERNAL "Override verbose output" FORCE)
# set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE INTERNAL "Override update strategy" FORCE)
#
# NOTE: Also update env vars used for caching in
#     - .github/actions/configure-cmake/action.yml
#     - .github/workflows/cmake.yml
# FetchContent_Declare(
#     SomeLib
#     SYSTEM         # keeps ext libs out of static code analysis
#     GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#     GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#     GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
#     GIT_PROGRESS   ON
# )
#
# FetchContent_MakeAvailable(SomeLib)

###############################################################################

# External dependencies with find_package

# find_package(Threads REQUIRED)

###############################################################################

# Configure sources

# always STATIC (simpler); TBD if we ever want dynamic for this; BUILD_SHARED_LIBS is for ext deps
add_library(${MAIN_LIBRARY_NAME} STATIC)

# NOTE: update EXECUTABLE_NAME in .github/workflows/cmake.yml when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
    app/main.cpp
)

target_sources(${MAIN_LIBRARY_NAME}
    PRIVATE
        src/Ingredient.cpp
        src/Pizza.cpp
        src/Customer.cpp
        src/Order.cpp
        src/Oven.cpp
        src/Game.cpp
        src/Services.cpp 
        src/Console.cpp
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS ${USE_ASAN} TARGET_NAMES ${MAIN_EXECUTABLE_NAME} ${MAIN_LIBRARY_NAME})

###############################################################################

# Configure includes

# app/ needs no include dir of its own:

target_link_libraries(${MAIN_EXECUTABLE_NAME}
    PRIVATE
        ${MAIN_LIBRARY_NAME}
)

install(TARGETS ${MAIN_EXECUTABLE_NAME} ${MAIN_LIBRARY_NAME}
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)