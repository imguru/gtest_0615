// 16_Mocking2.cpp

#include <gmock/gmock.h>

class Gadget {};

class Foo {
public:
	virtual ~Foo() {}
	virtual bool Transform(Gadget* g) = 0;
protected:
	virtual void Resume() {}
private:
	virtual int GetTimeOut() {}
};

// 모의 객체는 실제 함수의 구현을 호출하지 않는다.
// 함수에 대해서 호출된 사실만 기록할 뿐이다.

// 1. Google Mock은 추상 클래스에 대해서 모킹이 가능합니다.
class MockFoo : public Foo {
// 부모의 메소드의 접근 지정자에 상관없이 모두 public 으로 만들어야 합니다.
public:
	MOCK_METHOD(bool, Transform, (Gadget* g), (override));
	MOCK_METHOD(void, Resume, (), (override));

	// private 함수도 Mocking 할 수 있습니다.
	MOCK_METHOD(int, GetTimeOut, (), (override));
};
