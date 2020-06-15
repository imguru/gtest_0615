
#include <gtest/gtest.h>
#include <string>

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
//       -> 하나라도 실패하면, 전체 테스트의 결과는 실패로 결정된다.
//
TEST(GoogleTest, Sample1) {
	int expected = 42;

	int actual1 = 42;
	int actual2 = 42;

	// ASSERT_EQ(expected, actual1) << "Reason 1";
	// ASSERT_EQ(expected, actual2) << "Reason 2";  // 죽은 단언문
	EXPECT_EQ(expected, actual1) << "Reason 1";
	EXPECT_EQ(expected, actual2) << "Reason 2"; 
}

// 2. C Style 문자열을 대상으로 사용할 때
//  : EXPECT_STREQ/NE
//    EXPECT_STRCASEEQ/NE
TEST(GoogleTest, Sample2) {
	std::string s1 = "hello";
	std::string s2 = "hello";

	// s1 == s2
	EXPECT_EQ(s1, s2);

	const char* s3 = "hello";
	const char* s4 = s2.c_str();

	// s3 == s4
	// EXPECT_EQ(s3, s4);
	// : C-Style 문자열 비교를 위해서는 아래 단언문을 사용해야 합니다.
	EXPECT_STREQ(s3, s4);
	EXPECT_STRCASEEQ(s3, s4);
}

// 3. 부동 소수점 - float, double
//    ASSERT_DOUBLE_EQ
//    ASSERT_NEAR
TEST(GoogleTest, Sample3) {
	double a = 0.7;
	double b = 0.1 * 7;

	// 부동 소수점 타입은 ==을 통해 값을 비교하는 것이 불가능하다.
	// ASSERT_EQ(a, b); - X
	ASSERT_DOUBLE_EQ(a, b); // 4ULP's

	// 오차 범위를 직접 설정하는 것이 가능합니다.
	EXPECT_NEAR(a, b, 0.000000001);
}




















































