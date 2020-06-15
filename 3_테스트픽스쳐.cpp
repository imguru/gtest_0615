class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	Calculator(int n) {}
};
//-------------------------------------

// Test Fixture
//  정의: xUnit Test Pattern에서는 SUT를 실행하기 위해서 준비해야 하는 모든 것을
//        테스트 픽스쳐 라고 합니다.
//        픽스쳐를 구성하는 모든 로직 부분을 "픽스쳐 설치(Fixture Setup)" 라고 합니다.
//  픽스쳐 설치 방법
//   1. Inline Fixture Setup
//     : 모든 픽스쳐 설치를 테스트 함수 안에서 수행한다.
//     장점: 픽스쳐를 설치하는 과정과 검증 로직이 테스트 함수 안에 존재하기 때문에
//           인과관계를 쉽게 분석할 수 있다.
//     단점: 모든 테스트 코드 안에서 '코드 중복'이 발생한다.
//
#include <gtest/gtest.h>

#if 0
TEST(CalculatorTest, PlusTest) {
	Calculator* calc = new Calculator;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(30);
	calc->PressEquals();

	if (calc->Display() == 32) {
		SUCCEED();
	} else {
		FAIL() << "2 + 30 하였을 때";
	}
}

#define SPEC printf
TEST(CalculatorTest, PlusTest_2Plus30_Displays_32) {
	SPEC("2와 30을 더했을 때의 동작\n");
	Calculator* calc = new Calculator;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(30);
	calc->PressEquals();

	ASSERT_EQ(32, calc->Display()) << "2 + 30 하였을 때";
}
#endif

// 방법 2. Delegate Setup(위임 설치)

//             ::testing::Test

//                                  class CalcTest : public ::testing::Test {};
//                                
//  TEST(CalcTest, foo)             TEST_F(CalcTest, foo)


// 목표: CalculatorTest를 위한 별도의 테스트 유틸리티 함수를 제공한다.
// 1. TestCase 클래스를 만들어야 합니다.
class CalculatorTest : public testing::Test {
// 주의: 테스트 유틸리티 함수를 제공할 때, private으로 제공하면 자식의 테스트에서 접근이 불가능하다.
//       protected를 사용해야 합니다.
protected:
	Calculator* Create() { return new Calculator(0); }
};

// 2. TEST -> TEST_F
//  => CalculatorTest의 자식으로 클래스가 만들어진다.
TEST_F(CalculatorTest, PlusTest) {
	Calculator* calc = Create();

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(30);
	calc->PressEquals();

	if (calc->Display() == 32) {
		SUCCEED();
	} else {
		FAIL() << "2 + 30 하였을 때";
	}
}

#define SPEC printf
TEST_F(CalculatorTest, PlusTest_2Plus30_Displays_32) {
	SPEC("2와 30을 더했을 때의 동작\n");
	Calculator* calc = Create();

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(30);
	calc->PressEquals();

	ASSERT_EQ(32, calc->Display()) << "2 + 30 하였을 때";
}
