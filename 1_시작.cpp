
// 1_시작.cpp

#include <gtest/gtest.h>  // 1. 헤더파일 포함이 반드시 필요합니다.


// TestCase  - Test의 집합
// TestSuite - 동일한 픽스쳐(Fixture)를 가지는 Test의 집합 
//  => TestCase와 TestSuite을 동일시 합니다.

// 테스트를 만드는 방법.
// TestCaseName.TestName
TEST(TestSuiteName, TestName) {
	FAIL();  // 명시적으로 테스트를 실패시킬 수 있습니다.
			 // 테스트를 실패할 때, 실패의 이유를 명시적으로 지정하는 것이 중요합니다.
}

TEST(SampleTest, FooTest) {
	FAIL() << "작성 중입니다...";
}

TEST(SampleTest, GooTest) {
	SUCCEED();
}



// gtest_main.cc에 존재하는 main을 라이브러리에 포함시킨 경우.
#if 0
// 2. main 함수는 아래와 같이 작성하면 됩니다.
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
#endif
