#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual void Pure(int n) = 0;
	virtual int Concreate(const char* str) {
		printf("Foo - Concreat\n");
	}
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Pure, (int n), (override));
	MOCK_METHOD(int, Concreate, (const char* str), (override));
	// 부모의 Concreate 구현을 가린다.
	//  Concreate가 호출되었을 때, 부모의 Concreate를 수행하고 싶다. - ON_CALL
	
	// 부모의 기능을 호출하는 함수를 제공해야만 한다.
	int FooConcreate(const char* str) {
		return Foo::Concreate(str);
	}
};

int foo() {
	printf("foo\n");
	return 42;
}

TEST(MockFooTest, FooTest) {
	MockFoo mock;

	/*
	ON_CALL(mock, Concreate).WillByDefault([&mock](const char* str) {
		return mock.Concreate(str);  // 재귀! 
	});
	*/
	ON_CALL(mock, Concreate).WillByDefault([&mock](const char* str) {
		// return foo();
		return mock.FooConcreate(str); 
	});

	mock.Concreate("aaa");
}



