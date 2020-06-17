
#include <gmock/gmock.h>

class Bar {
public:
	int id;
	Bar(int n) : id(n) {}
};
struct Foo {
	virtual ~Foo() {}

	virtual Bar& GetBar() = 0;
	virtual const Bar& GetBar() const = 0;

	virtual int GetValue() = 0;
	virtual int Add(int a, int b) = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(Bar&, GetBar, (), (override));
	MOCK_METHOD(const Bar&, GetBar, (), (override, const));

	MOCK_METHOD(int, GetValue, (), (override));
	MOCK_METHOD(int, Add, (int a, int b), (override));
};

using ::testing::Return;     // T
using ::testing::ReturnRef;  // T&
using ::testing::NiceMock;
using ::testing::Const;

using ::testing::_;

void NonConstVersion(Foo& p) {
	Bar b = p.GetBar();
	printf("NonConstVersion: %d\n", b.id);
}

void ConstVersion(const Foo& p) {
	Bar b = p.GetBar();
	printf("ConstVersion: %d\n", b.id);
}

TEST(MockFoo, FooTest4) {
	MockFoo mock;
	Bar bar1(10), bar2(20);

	// const 아닌 버전에 대한 동작을 정의한다.
	EXPECT_CALL(mock, GetBar()).WillOnce(ReturnRef(bar1));
	// const 버전에 대한 동작을 정의한다.
	EXPECT_CALL(Const(mock), GetBar()).WillOnce(ReturnRef(bar2));

	NonConstVersion(mock);
	ConstVersion(mock);
}

TEST(MockFoo, FooTest3) {
	MockFoo mock;

#if 0
    // .WillRepeatedly() cannot appear more than once in an EXPECT_CALL()
	EXPECT_CALL(mock, Add(_, _))
		.WillRepeatedly(Return(10))
		.WillRepeatedly(Return(100));
#endif

#if 0
	EXPECT_CALL(mock, Add(10, 20))
		.WillRepeatedly(Return(100));
#endif

	printf("%d\n", mock.Add(10, 20));  // 100 
	printf("%d\n", mock.Add(10, 30));  // 10
}

TEST(MockFoo, FooTest2) {
	NiceMock<MockFoo> mock;

	ON_CALL(mock, Add(_, _)).WillByDefault(Return(420));
	// 뒤에 추가한 것이 우선순위가 높다. - 문서에서 확인할 수 있다.
	ON_CALL(mock, Add(10, 20)).WillByDefault(Return(42));

#if 0
	ON_CALL(mock, Add(_, 20)).WillByDefault(Return(42));
	ON_CALL(mock, Add(_, 30)).WillByDefault(Return(420));
#endif
	
	printf("%d\n", mock.Add(10, 20));  // 42? 420?
	printf("%d\n", mock.Add(10, 30));  // 420
}


// C++ 에서는 const 함수에 대해서 오버로드를 제공할 수 있다.
TEST(MockFoo, FooTest) {
	MockFoo mock;
	// ON_CALL - 검증이 포함되지 않는다.
	//  Mocking된 메소드를 호출 할때 결과를 제어할 때 사용한다.
	//   : WillByDefault(...)

	// EXPECT_CALL - 검증이 포함된다.
	//   1. 호출 여부 검증
	//   2. 호출 횟수 검증
	//   3. Mocking 메소드를 호출 할 때 결과를 제어하는 기능을 제공합니다.
	//     : .WillOnce + WillRepeatedly
	//        (1)        (0 ~ N)
	EXPECT_CALL(mock, GetValue())
		.WillOnce([] {                       // 1번은 무조건 호출된다.
			printf(".WillOnce - 1\n");
			return 10;
		})
		.WillOnce([] {                       // 1번은 무조건 호출된다.
			printf(".WillOnce - 2\n");
			return 20;
		})
		.WillOnce([] {                       // 1번은 무조건 호출된다.
			printf(".WillOnce - 3\n");
			return 30;
		})
		.WillRepeatedly([] {                 // 0 ~ N번 호출에 대해서 결과를 지정할 때 사용한다.
			printf(".WillRepeatedly\n");
			return 42;
		});

	// printf("%d\n", mock.GetValue());
	// printf("%d\n", mock.GetValue());
	// printf("%d\n", mock.GetValue());
	// printf("%d\n", mock.GetValue());
	// printf("%d\n", mock.GetValue());
}








