class Calculator {
public:
	double Display() { return 0; }

	void Enter(double v) {}
	void PressPlus() {}
	void PressMinus() {}
	void PressEquals() {}

	Calculator() {}
};

// 방법 3. Implicit SetUp/TearDown(암묵적 설치/해체)
//   : 여러 테스트에서 같은 테스트 픽스쳐의 코드를 SetUp() 함수에서 생성한다.
//    => xUnit Test Framework이 지원하는 기능입니다.
//   장점: 테스트 코드 중복을 제거하고, 꼭 필요하지 않은 상호작용을 캡슐화할 수 있다.
//   단점: 픽스쳐 설치 코드가 테스트 함수 밖에 존재하기 때문에, 테스트 함수만으로 테스트 코드를
//         이해하기 어려울 수 있다.
//
#include <gtest/gtest.h>

#if 0
CalculatorTest* tc = new CalculatorTest();
tc->SetUp();
tc->PlusTest();
tc->TearDown();

CalculatorTest* tc = new CalculatorTest();
tc->SetUp();
tc->MinusTest();
tc->TearDown();

#endif

// xUnit Test Framework - 신선한 픽스쳐 전략


// Test 함수 안에서 ASSERT가 실패하면, 그 이후의 코드는 수행되지 않는다.
// xUnit Test Pattern 에서는 테스트를 구성하는 방법 - 4단계 테스트 패턴
// 1단계: 테스트의 픽스쳐를 설치하거나, 실제 결과를 관찰하기 위해 필요한 것을 집어넣는 작업을 한다. - SetUp()
// 2단계: SUT와 상호작용한다.     - TestBody()
// 3단계: 기대 결과를 확인한다.   - TestBody()
// 4단계: 테스트 픽스쳐를 해체해서, 테스트 시작 이전의 상태로 돌려놓는다. - TearDown()


// 1. TestCase 클래스를 만들어야 합니다.
class CalculatorTest : public ::testing::Test {
protected:
	CalculatorTest() { printf("CalculatorTest()\n"); }
	~CalculatorTest() { printf("~CalculatorTest()\n"); }

	Calculator* calc;
	virtual void SetUp() override {
		printf("SetUp()\n");
		calc = new Calculator;
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
		delete calc;
	}
};

// 2. TEST -> TEST_F
TEST_F(CalculatorTest, PlusTest) {
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

	calc->Enter(2);
	calc->PressPlus();
	calc->Enter(30);
	calc->PressEquals();

	ASSERT_EQ(32, calc->Display()) << "2 + 30 하였을 때";
}

