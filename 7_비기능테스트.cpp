#include <gtest/gtest.h>
#include <unistd.h>

// 비기능 테스트
//  : 기능적인 동작에 대한 부분이 아니라,
//    성능이나 메모리 등의 비기능적인 부분을 검증하는 것.

void foo() {
	sleep(1);
}

// 방법 1.  TestSuite 클래스의 SetUp/TearDown을 통해 제공하는 방법.
class FooTest : public ::testing::Test {
protected:
	time_t startTime;
	virtual void SetUp() override {
		startTime = time(0);
	}

	virtual void TearDown() override {
		time_t endTime = time(0);
		time_t duration = endTime - startTime;

		EXPECT_LE(duration, 2) << "시간 초과: " << duration << " 초가 걸렸습니다.";
	}
};

// 2초안에 수행되어야 한다.
TEST_F(FooTest, foo) {
	foo();
}








