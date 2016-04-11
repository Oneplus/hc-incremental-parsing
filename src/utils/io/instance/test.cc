#include "lisp.h"
#include <iostream>
#include <string>
#include <boost/assert.hpp>

using ZuoPar::IO::LispCell;
using ZuoPar::IO::read_lisp;

void test_1() {
  std::string token = "(+ 1 9)";
  LispCell root = read_lisp(token);
  BOOST_ASSERT_MSG(root.list.size() == 3, "token number should be 3");
  BOOST_ASSERT_MSG(root.list[0].val == "+", "should be +");
  BOOST_ASSERT_MSG(root.list[1].val == "1", "should be 1");
  BOOST_ASSERT_MSG(root.list[2].val == "9", "should be 9");
}

void test_2() {
  std::string token = "(VP (VV see) (NN you))";
  LispCell root = read_lisp(token);
  BOOST_ASSERT_MSG(root.list.size() == 3, "token number should be 3");
  BOOST_ASSERT_MSG(root.list[0].val == "VP", "should be VP");
  BOOST_ASSERT_MSG(root.list[1].list.size() == 2, "should be 2");
  BOOST_ASSERT_MSG(root.list[1].list[0].val == "VV", "should be VV");
  BOOST_ASSERT_MSG(root.list[2].list.size() == 2, "should be 9");
  BOOST_ASSERT_MSG(root.list[2].list[0].val == "NN", "should be NN");
}

int main() {
  test_1();
  test_2();
  return 0;
}
