#include<iostream>
#include "kiss_icp/pipeline/KissICP.hpp"
#include "map_closures/MapClosures.hpp"
#include<memory>


int main()
{
    // Construct the main KISS-ICP odometry node
    kiss_icp::pipeline::KISSConfig config;
    auto kiss_icp_ = std::make_unique<kiss_icp::pipeline::KissICP>(config);

    map_closures::Config map_c_config;
    auto map_closures = std::make_unique<map_closures::MapClosures>(map_c_config);
}