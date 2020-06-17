
#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {}
	virtual void Say() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Say, (), (override));
};

void foo(Foo* p) {
	p->Say();
}


// 1. MockFoo mock;
//    EXPECT_CALL 등의 검증에 대한 코드가 없는 상태로, mock에 대해 함수가 호출되면, 경고가 발생합니다.
//     : 검증 없는 테스트 코드에 대한 부분을 알수 있도록 하는 기능입니다.
#if 0
	GMOCK WARNING:
#endif

// 2. Mock 객체에 대해서 EXPECT_CALL을 하지 않는 의도로 사용한 경우, 경고를 제거하는 방법.
//   => NiceMock을 이용하면 됩니다.
//   NiceMock<MockFoo> mock;
using ::testing::NiceMock;

// 3. StrictMock
//   => EXPECT_CALL이 없을 경우, 테스트가 실패합니다.
using ::testing::StrictMock;
// 주의 할점: StrictMock을 사용할 경우, NiceMock을 사용할 때보다 테스트를 통과시키기 어려워질 수 있다.

TEST(MockTest, Foo) {
	StrictMock<MockFoo> mock;

	// EXPECT_CALL을 호출하고 있지 않습니다.
	EXPECT_CALL(mock, Say());

	foo(&mock);
}










