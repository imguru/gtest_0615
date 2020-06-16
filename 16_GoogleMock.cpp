
#include <gtest/gtest.h>  // Google Test
#include <gmock/gmock.h>  // Google Mock

// main 함수는 Google Mock을 사용할 겨우 아래와 같이 작성하면 됩니다.
#if 0
int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);  // 내부적으로 ::testing::InitGoogleTest를 수행합니다.

	return RUN_ALL_TESTS();
}
#endif
