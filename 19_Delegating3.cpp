
#include <gmock/gmock.h>

struct Foo {
	virtual ~Foo() {};

	virtual int GetValue() = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(int, GetValue, (), (override));
};

// ON_CALL
// 결과를 제어하는 것이 가능하다.
//  : Stub
//    Fake
//    .WillByDefault(함수)

using ::testing::NiceMock;
using ::testing::Return;

TEST(FooTest, Sample) {
	NiceMock<MockFoo> mock;

	ON_CALL(mock, GetValue())
		.WillByDefault(Return(10));
#if 0
		.WillByDefault([] {     // 기본 동작을 정의한다.
			printf("WillByDefault\n");
			return 42;
		});
#endif

	printf("%d\n", mock.GetValue());
	printf("%d\n", mock.GetValue());
	printf("%d\n", mock.GetValue());
}
