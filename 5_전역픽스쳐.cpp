
// 5_전역픽스쳐
//  => Google Test 고유의 기능입니다.
//  => 프로그램의 시작 때 수행되는 SetUp()
//     모든 테스트가 수행되고 난 이후의 TearDown()을 정의합니다.


// 설치하는 방법.
// 1. 전역 변수 - main을 직접 작성하지 않을 때
// 2. main함수를 통해 설치하는 방법. - main을 직접 작성할 때

#include <gtest/gtest.h>

// Google Test Framework에 사용자가 만든 객체를 등록할 때, 객체를 반드시 힙에 생성해야 합니다.
class MyTestEnvironment : public ::testing::Environment {
public:
	void foo() { printf("foo\n"); }

	static MyTestEnvironment& instance() {
		static MyTestEnvironment* env = new MyTestEnvironment;
		return *env;
	}

	void SetUp() {
		printf("Global SetUp()\n");
	}

	void TearDown() {
		printf("Global TearDown()\n");
	}
};


// 1. 전역 변수 - 프로그램이 시작하기 전에(main 수행전에) 전역 변수의 초기화가 일어나는 특성을 이용한다.
// ::testing::Environment* env = ::testing::AddGlobalTestEnvironment(new MyTestEnvironment);

// 2. main
int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	// ::testing::AddGlobalTestEnvironment(new MyTestEnvironment);
	MyTestEnvironment& env = MyTestEnvironment::instance();
	::testing::AddGlobalTestEnvironment(&env);

	return RUN_ALL_TESTS();
}


class FirstTest : public ::testing::Test {
protected:
	virtual void SetUp() override {
		printf("FirstTest.SetUp()\n");
		MyTestEnvironment& env = MyTestEnvironment::instance();
		env.foo();
	}

	virtual void TearDown() override {
		printf("FirstTest.TearDown()\n");
	}
};

TEST_F(FirstTest, foo) {}
TEST_F(FirstTest, goo) {}

TEST(SecondTest, foo) {}
TEST(SecondTest, goo) {}






























