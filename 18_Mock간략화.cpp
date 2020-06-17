
#include <gmock/gmock.h>

enum Level { INFO, WARN };

struct Foo {
	virtual ~Foo() {}
	
	virtual void Send(Level level, const char* filename, const char* dir, int line) = 0;
};

class SUT {
public:
	void Do(Foo* p) {
		p->Send(INFO, "log.txt", "/tmp", 42);
	}
};

class MockFoo : public Foo {
public:
	// MOCK_METHOD(void, Send, (Level level, const char* filename, const char* dir, int line), (override));
	void Send(Level level, const char* filename, const char* dir, int line) override {
		Send(level, filename); // Mocking을 통해 생성된 함수를 호출한다.
	}

	// 테스트에서는 함수의 인자를 간략화하는 형태로 사용하고 싶다.
	MOCK_METHOD(void, Send, (Level level, const char* filename));
};

TEST(MockTest, FooTest) {
	MockFoo mock;
	SUT sut;

	// 검증에 관심있는 인자에 대해서만 체크하는 로직.
	EXPECT_CALL(mock, Send(INFO, "log.txt"));

	sut.Do(&mock);
}
