
// 1_시작.cpp

#include <gtest/gtest.h>  // 1. 헤더파일 포함이 반드시 필요합니다.

// 2. main 함수는 아래와 같이 작성하면 됩니다.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
