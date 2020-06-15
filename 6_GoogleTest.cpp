
#include <gtest/gtest.h>

// xUnit
// 1. TestSuite - Fixture
// 2. Assertions

// ASSERT_XX
//    ASSERT_EQ / NE / LT / LE / GT / GE / TRUE / FALSE
//    => 테스트가 실패할 경우, 이후의 코드는 수행되지 않는다.
//    : 하나의 테스트 함수안에 하나의 단언문만 존재하는 것이 좋다.
//     -> 하나의 기능에 대해서 테스트가 많아질 수 있다.
//   
// EXPECT_XX
//      EQ / NE / LT / LE / GT / GE / TRUE / FALSE
//     : 검증이 실패해도, 이후의 코드를 계속 수행한다.
//       -> 죽은 단언문 문제를 해결하기 위한 GTest의 기능이다.
//
TEST(GoogleTest, Sample1) {
	int expected = 42;

	int actual1 = 30;
	int actual2 = 30;

	// ASSERT_EQ(expected, actual1) << "Reason 1";
	// ASSERT_EQ(expected, actual2) << "Reason 2";  // 죽은 단언문
	EXPECT_EQ(expected, actual1) << "Reason 1";
	EXPECT_EQ(expected, actual2) << "Reason 2";  // 죽은 단언문
}
