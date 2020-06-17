#include <gmock/gmock.h>

struct Element {};

class Foo {
public:
	// 상속을 통해 Mock을 만들 경우, 가상 소멸자가 반드시 제공되어야 합니다.
	virtual ~Foo() {}

	virtual int Add() {}
	// virtual int Add() = 0;
	//  => 아래에서 Mocking을 제공하지 않을 경우, 목 객체를 인스턴스화 할 수 없다.

	virtual int Add(Element x) {}
	virtual int Add(int times, Element x) {}
};

// 만약 모든 함수의 오버로드에 대해서 사용하지 않을 경우.
class MockFoo : public Foo {
public:
	using Foo::Add;
	// 부모 클래스에 기본 구현을 제공할 경우, 사용할 수 있다.
	MOCK_METHOD(int, Add, (int times, Element x), (override));   // O
};

TEST(MockFooTest, FooTest) {
	MockFoo mock;
}

#if 0
class MockFoo : public Foo {
public:
	MOCK_METHOD(int, Add, (Element x), (override));              // X
	MOCK_METHOD(int, Add, (int times, Element x), (override));   // O
};
#endif
