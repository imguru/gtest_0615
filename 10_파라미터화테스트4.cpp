#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <iostream>

class StlStringTest : public ::testing::TestWithParam<std::string> {
};

std::vector<std::string> GetParameterStrings() {
	std::vector<std::string> v;
	v.push_back("a");
	v.push_back("b");
	v.push_back("c");
	v.push_back("d");
	v.push_back("e");
	v.push_back("f");
	return v;
}

using ::testing::ValuesIn;

INSTANTIATE_TEST_SUITE_P(CharSequence,
		StlStringTest,
		ValuesIn(GetParameterStrings()));

TEST_P(StlStringTest, StrTest) {
	std::string s = GetParam();
	std::cout << s << std::endl;
}
