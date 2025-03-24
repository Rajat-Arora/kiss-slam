cmake_minimum_required(VERSION 3.16...3.26)
project(kiss_slam VERSION 0.0.1 LANGUAGES CXX)

option(USE_SYSTEM_EIGEN3 "Use system pre-installed Eigen" OFF)
option(USE_SYSTEM_TSL-ROBIN-MAP "Use system pre-installed tsl_robin" OFF)
option(USE_SYSTEM_G2O "Use a pre-installed version of g2o" OFF)

cmake_minimum_required(VERSION 3.18)
set(KISS_ICP_VERSION 1.2.3)
message(STATUS "Performing out-of-tree build, fetching KISS-ICP v${KISS_ICP_VERSION} Release from Github")
include(FetchContent)
FetchContent_Declare(
    ext_kiss_icp_core PREFIX kiss_icp_core
        URL https://github.com/PRBonn/kiss-icp/archive/refs/tags/v${KISS_ICP_VERSION}.tar.gz 
        SOURCE_SUBDIR cpp/kiss_icp
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
FetchContent_MakeAvailable(ext_kiss_icp_core)


include(FetchContent)
message(STATUS "Performing out-of-tree build, fetching map_closures from Github")
FetchContent_Declare(
    map_closures
        GIT_REPOSITORY https://github.com/PRBonn/MapClosures.git
        GIT_TAG main
        SOURCE_SUBDIR cpp
)
FetchContent_MakeAvailable(map_closures)

# ccache setup
if(USE_CCACHE)
  find_program(CCACHE_PATH ccache)
    if(CCACHE_PATH)
      set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
      set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
      message(STATUS "Using ccache: ${CCACHE_PATH}")
    endif()
endif()

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(3rdparty/find_dependencies.cmake)
include(cmake/CompilerOptions.cmake)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/voxel_map)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/pgo)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/occupancy_mapper)

add_executable(main_exec main.cpp)
target_link_libraries(main_exec PUBLIC kiss_icp_pipeline map_closures)






# pybind11_add_module(kiss_slam_pybind MODULE kiss_slam_pybind.cpp)
# target_link_libraries(kiss_slam_pybind PRIVATE pgo voxel_map Eigen3::Eigen occupancy_mapper)
# target_compile_features(kiss_slam_pybind PUBLIC cxx_std_20)
# install(TARGETS kiss_slam_pybind DESTINATION .)
