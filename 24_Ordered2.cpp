
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

void Do1(Foo* p) {
	p->First();
	p->Second();
	p->Third();
	p->Forth();
}

using ::testing::Sequence;
using ::testing::InSequence;

// First -> Second -> Third -> Forth
TEST(MockTest, Foo) {
	InSequence seq;
	MockFoo mock;

	EXPECT_CALL(mock, First());
	EXPECT_CALL(mock, Second());
	EXPECT_CALL(mock, Third());
	EXPECT_CALL(mock, Forth());

	Do1(&mock);
}

void Do2(Foo* p) {
	p->First();
	p->Second();
	p->Third();
	p->Forth();
}
//       -- Second              : s1
//       | 
// First -
//       |
//       -- Third - Forth       : s2
TEST(MockTest, Foo_Sequence) {
	Sequence s1, s2;
	MockFoo mock;

	EXPECT_CALL(mock, First()).InSequence(s1, s2);
	EXPECT_CALL(mock, Second()).InSequence(s1);
	EXPECT_CALL(mock, Third()).InSequence(s2);
	EXPECT_CALL(mock, Forth()).InSequence(s2);

	Do2(&mock);
}

