add_executable(test 
    boost_stu_test.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/boost_stu)

find_package(Boost REQUIRED COMPONENTS system filesystem unit_test_framework )

target_link_libraries(test 
    boost_stu
    Boost::system 
    Boost::filesystem
    Boost::unit_test_framework 
)