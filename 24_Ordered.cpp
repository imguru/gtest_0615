
#include <gmock/gmock.h>

// 함수 호출 여부 / 횟수 / '순서'
class Foo {
public:
	virtual void First() = 0;
	virtual void Second() = 0;
	virtual void Third() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, First, (), (override));
	MOCK_METHOD(void, Second, (), (override));
	MOCK_METHOD(void, Third, (), (override));
};

void Do(Foo* p) {
	p->First();
	p->Second();
	p->Third();
}

// EXPECT_CALL은 순서를 체크하지 않는다.
//  - 호출순서를 검증하고 싶다.
//     : InSequence 객체만 생성하면 됩니다.

// 주의사항
//  mock 객체 / InSequence 객체는 파괴되는 시점에 검증을 수행한다.
//   => 동적 메모리 할당을 생성하기 보다는 스택 객체로 생성하는 것이 좋다.
//	MockFoo* mock = new MockFoo;

using ::testing::InSequence;

TEST(MockTest, Foo) {
	InSequence seq;
	MockFoo mock;

	EXPECT_CALL(mock, First());
	EXPECT_CALL(mock, Second());
	EXPECT_CALL(mock, Third());

	Do(&mock);
}








