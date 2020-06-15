
// 3A
//  : 단위 테스트를 구성하는 방법.

// SUT(System Under Test)
//  = CUT(Code / Class Under Test)

class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	Calculator() {}
};
//-------------------------------------
#include <gtest/gtest.h>

// Test Case의 이름(Test Suite 이름)은 테스트 대상 클래스의 마지막에 Test를 붙인 이름을 사용합니다.
//   Calculator -> CalculatorTest / CalculatorSpec

// 3A 
// 1. Arrange: 객체를 생성하고, 필요한 경우 설정하고 준비한다.  - Given
// 2. Act: 객체의 작용을 가한다.                                - When
// 3. Assert: 기대하는 바를 단언한다.                           - Then

// TDD(테스트 주도 개발) vs BDD(행위 주도 개발)
//  => 동일하지만, 용어가 조금 다릅니다.

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

// 테스트 코드의 품질
// 1. 가독성
// 2. 유지보수성
//   : 테스트 코드 안에서는 제어 구문의 발생을 최소화해야 한다.
//    - 조건문, 반복문, 예외 처리 등의 복잡한 코드의 발생을 최소화해야 한다.
// 3. 신뢰성

#define SPEC printf

// 테스트의 이름을 통해서, 테스트가 어떤 시나리오로 동작하는지를 포함하는 것이 좋다.
//  => 테스트의 이름을 "테스트대상함수_시나리오_기대값"의 형태로 작성한다.
TEST(CalculatorTest, PlusTest_2Plus30_Displays_32) {
	SPEC("2와 30을 더했을 때의 동작\n");
	Calculator* calc = new Calculator;

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(30);
	calc->PressEquals();

	// xUnit Test Framework는 조건에 부합되는지 여부를 검증하기 위한 함수를 제공한다.
	// => 단언문, 구글 테스트의 경우 매크로를 통해 제공됩니다.
	ASSERT_EQ(32, calc->Display()) << "2 + 30 하였을 때";
}






























