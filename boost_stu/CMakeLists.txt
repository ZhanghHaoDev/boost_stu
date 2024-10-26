add_library(boost_stu STATIC 
    boost_stu.cpp
)

find_package(Boost REQUIRED COMPONENTS 
    system
    filesystem
    log
)

target_link_libraries(boost_stu PUBLIC
    Boost::system 
    Boost::filesystem
    Boost::log    
)