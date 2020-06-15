
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

// 4. 예외 테스트 기능
void IsValidFilename(const std::string& filename) {
	throw 1;
	if (filename.empty()) {
		throw std::invalid_argument("filename should not empty!");
	}
	// ...
}

// ASSERT_THROW / EXPECT_THROW
// ASSERT_ANY_THROW / EXPECT_ANY_THROW
TEST(GoogleTest, DISABLED_Sample4) {
	// 테스트 코드안에서 변수명을 사용할 때, 상황에 부합되는 변수명을 사용하는 것이 좋습니다.
	// std::string filename = "";
	std::string emptyFilename = "";
		
	// EXPECT_THROW(IsValidFilename(emptyFilename), std::invalid_argument);
	EXPECT_ANY_THROW(IsValidFilename(emptyFilename));
}

// 5. 테스트 비활성화 
//  - 특정한 테스트가 포함되지 않고, 테스트가 수행되길 원한다.
//   => 테스트를 주석처리하면, 잊혀진 테스트가 됩니다.
//   => TestSuite 이름 또는 Test의 이름이 DISABLED_로 시작하는 경우, 자동으로 비활성화됩니다.
//    : ./a.out --gtest_also_run_disabled_tests
//       - 비활성된 테스트도 구동할 수 있습니다.

// IsValidFileName에 빈문자열을 전달하였을 때, std::invalid_argument 예외가 발생하는지 여부를 검증하고 싶다.
#if 1
TEST(DISABLED_GoogleTest, Sample4_withoutExceptionTest) {
	std::string filename = "";
	
	try {
		IsValidFilename(filename);
		FAIL() << "예외가 발생하지 않음.";
	} catch (std::invalid_argument& e) {
		SUCCEED();
	} catch (...) {
		FAIL() << "다른 종류의 예외가 발생하였음.";
	}
}
#endif




































































