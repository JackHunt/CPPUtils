#include <boost/test/included/unit_test.hpp>

using namespace boost::unit_test;

void foo() {
  BOOST_TEST(true); // Dummy test.
}

test_suite* init_unit_test_suite(int argc, char* argv[]) {
  framework::master_test_suite().add(BOOST_TEST_CASE(&foo));
  framework::master_test_suite().add(BOOST_TEST_CASE_NAME(&foo, "foo-2"));
  return 0;
}