
#include <gmock/gmock.h>

class Foo {
public:
	virtual void First() = 0;
	virtual void Second() = 0;
	virtual void Third() = 0;
	virtual void Forth() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, First, (), (override));
	MOCK_METHOD(void, Second, (), (override));
	MOCK_METHOD(void, Third, (), (override));
	MOCK_METHOD(void, Forth, (), (override));
};

//       -- Second
//       | 
// First -
//       |
//       -- Third - Forth


void Do(Foo* p) {
	p->First();
	p->Second();
	p->Third();
}

TEST(MockTest, Foo) {
}








