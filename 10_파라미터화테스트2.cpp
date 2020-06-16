
// 10_파라미터화테스트
//   : 입력 데이터를 바꿔가면서, 수차례 반복 검사하는 데이터 중심의 테스트에서 코드 중복을 없애는 기법.
//   => xUnit Test Framework
bool IsPrime(int value) {
	for (int i = 2; i < value; ++i) {
		if (value % i == 0)
			return false;
	}

	return true;
}

#include <gtest/gtest.h>

// 1. TestCase(TestSuite) class - TestWithParm<InputDataType>
// class PrimeTest : public ::testing::Test {
class PrimeTest : public ::testing::TestWithParam<int> {
};

// 2. DataSet 정의
int data[] = { 2, 3, 5, 7, 11, 13, 17, 19 };
// 전역 변수를 만드는 매크로입니다.
// INSTANTIATE_TEST_CASE_P(변수명, TestSuiteName, 
// INSTANTIATE_TEST_CASE_P(PrimeValues, PrimeTest, ::testing::Values(2, 3, 5, 7, 11));

// INSTANTIATE_TEST_CASE_P  -> 1.10: Deprecated API
// INSTANTIATE_TEST_SUITE_P
INSTANTIATE_TEST_SUITE_P(PrimeValues, PrimeTest, ::testing::ValuesIn(data));

// 3. 이제 테스트 함수를 제공하면 됩니다.
//  : GetParam() -> 입력값을 얻어올 수 있습니다.
TEST_P(PrimeTest, IsPrimeTest) {
	EXPECT_TRUE(IsPrime(GetParam()));
}











