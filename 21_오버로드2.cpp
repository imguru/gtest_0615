
#include <gmock/gmock.h>

class Printer {
public:
	virtual ~Printer() {}

	virtual void Print(int n) {}
	virtual void Print(char c) {}
};

class MockPrinter : public Printer {
public:
	MOCK_METHOD(void, Print, (int n), (override));
	MOCK_METHOD(void, Print, (char c), (override));
};

void foo(int) {
	printf("foo: int\n");
}

void foo(char) {
	printf("foo: char\n");
}

TEST(PrinterTest, Print2) {
	foo(10);
	foo('a');
}

using ::testing::An;
using ::testing::TypedEq;
using ::testing::Matcher;
using ::testing::Le;

#if 1
TEST(PrinterTest, Print) {
	MockPrinter mock;

	// '모호성 에러'가 발생하는 경우, 어떤 함수를 호출하는지 여부를 정확하게 명시해야 한다.
	// EXPECT_CALL(mock, Print(10));
	// EXPECT_CALL(mock, Print('c'));
	EXPECT_CALL(mock, Print(An<int>())); 
	EXPECT_CALL(mock, Print(TypedEq<int>(10)));
	EXPECT_CALL(mock, Print(Matcher<int>(Le(10))));

	mock.Print(10);
	mock.Print('c');
}
#endif









