#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}

	virtual int Add(int a, int b) { return a + b; }
	virtual void Say(const char* message) = 0;
};


class MockFoo : public Foo {
public:
	MOCK_METHOD(int, Add, (int a, int b), (override));

	MOCK_METHOD(void, Say, (const char* message), (override));
};

void Do(Foo* p) {
	p->Add(10, 20);
	p->Say("hello");
}

// Matcher: 인자/조건에 유효조건을 검증할 때 사용한다.

// 1. _
//  : 상관하지 않을 때
using ::testing::_;
using ::testing::Lt;
using ::testing::Gt;
using ::testing::Le;
using ::testing::Ge;
using ::testing::Eq;
using ::testing::Ne;
using ::testing::NotNull;

TEST(MockTest, Foo) {
	MockFoo mock;

	// EXPECT_CALL(mock, Add(10, 20));
	// EXPECT_CALL(mock, Add(_, 20));
	// EXPECT_CALL(mock, Add(Gt(10), Lt(20)));
	EXPECT_CALL(mock, Add(Ge(10), Le(20)));
	EXPECT_CALL(mock, Say(NotNull()));

	Do(&mock);
}

// 2. 인자 검증을 이용할 때, 목 객체의 함수 호출에 대한 횟수에 대해서 주의해야 합니다.
//  : Times 함수를 통해 함수 호출 횟수를 검증할 수 있다.
void Do2(Foo* p) {
	p->Add(10, 21);
	p->Add(10, 22);
	p->Add(10, 23);
	p->Add(10, 34);
}

void Do3(Foo* p) {
	p->Say("Hello");
}

using ::testing::HasSubstr;

TEST(MockTest, Foo5) {
	MockFoo mock;

	// Say라는 함수에서 인자에 Hello라는 문자열이 포함되었는지 여부를 검증하고 싶다.
	EXPECT_CALL(mock, Say(HasSubstr("Hello")));

	Do3(&mock);
}

// 1. 호출 여부 - EXPECT_CALL
// 2. 호출 횟수 - Times(AnyNumber, AtLeast, AtMost)
// 3. 호출 순서
// 4. 인자 검증 - Matcher

using ::testing::AllOf;
using ::testing::AnyOf;
using ::testing::Not;
TEST(MockTest, Foo4) {
	MockFoo mock;

	// 두번째 인자의 조건을 20 보다는 크고 30보다는 작거나 같아야 한다.
	//   && - AllOf
	//   || - AnyOf
	auto matcher = Not(AllOf(Gt(20), Le(30)));
	// EXPECT_CALL(mock, Add(10, Not(AllOf(Gt(20), Le(30))))).Times(4);
	EXPECT_CALL(mock, Add(10, matcher)).Times(4);

	Do2(&mock);
}

using ::testing::AnyNumber;
using ::testing::AtLeast;
using ::testing::AtMost;

TEST(MockTest, Foo3) {
	MockFoo mock;

	// 한번만 호출되길 기대합니다.
	// EXPECT_CALL(mock, Add(10, Ge(21)));
	// EXPECT_CALL(mock, Add(10, Ge(21))).Times(AnyNumber());
	// EXPECT_CALL(mock, Add(10, Ge(21))).Times(AtLeast(4)); // 4번 이상
	EXPECT_CALL(mock, Add(10, Ge(21))).Times(AtMost(4)); // 4번 이상

	Do2(&mock);
}


TEST(MockTest, Foo2) {
	MockFoo mock;

	EXPECT_CALL(mock, Add(10, 21));
	EXPECT_CALL(mock, Add(10, 22));
	EXPECT_CALL(mock, Add(10, 23));
	EXPECT_CALL(mock, Add(10, 24));

	Do2(&mock);
}





