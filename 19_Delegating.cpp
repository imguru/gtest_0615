// Delegating

#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual int Add(int a, int b) = 0;
	virtual int Sub(int a, int b) = 0;
};

class FakeFoo : public Foo {
public:
	virtual int Add(int a, int b) {
		printf("FakeFoo - Add\n");
		return a + b;
	}

	virtual int Sub(int a, int b) {
		printf("FakeFoo - Sub\n");
		return a - b;
	}
};

void Do(Foo* p) {
	p->Add(10, 20);
	p->Sub(10, 20);
}

// Fake - Delegating
//  : MockFoo에 대해서 Add라는 동작이 수행되면, FakeFoo객체의 Add를 통해 기능을 제공하고 싶다.
class MockFoo : public Foo {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Sub, (int a, int b), (override));

	// Mock에 대한 함수의 호출을 다른 객체에게 위임하거나, 결과를 고정할 수 있는 매크로 - ON_CALL
	//  1) Fake
	//  2) Stub
	void DelegateToFake() {
		ON_CALL(*this, Add).WillByDefault([this](int a, int b) {
			return fake.Add(a, b);
		});
		ON_CALL(*this, Sub).WillByDefault([this](int a, int b) {
			return fake.Sub(a, b);
		});
	}
private:
	FakeFoo fake;
};

TEST(MockFoo, FooTest) {
	MockFoo mock;
	mock.DelegateToFake();

	// 호출 여부만 검증
	EXPECT_CALL(mock, Add(10, 20));
	EXPECT_CALL(mock, Sub(10, 20));

	EXPECT_EQ(30, mock.Add(10, 20));
	EXPECT_EQ(-10, mock.Sub(10, 20));
	// Do(&mock);
}













