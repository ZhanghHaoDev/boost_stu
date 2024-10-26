#define BOOST_TEST_MODULE BoostStuTest
#include <boost/test/included/unit_test.hpp>
#include "boost_stu.h"

BOOST_AUTO_TEST_CASE(boost_filesystem_test) {
    boost_stu module;
    int result = module.boost_filesystem();
    BOOST_CHECK_EQUAL(result, 0);
}