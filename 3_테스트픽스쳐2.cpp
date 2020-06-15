class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	Calculator(int n) {}
};

#include <gtest/gtest.h>

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

