
#include <gmock/gmock.h>

class Foo {
public:
	virtual void Do(const std::vector<int>& numbers) = 0;
};

class MockFoo : public Foo {
public:
	MOCK_METHOD(void, Do, (const std::vector<int>& numbers), (override));
};

using ::testing::ElementsAreArray;
using ::testing::UnorderedElementsAreArray;

using ::testing::ElementsAre;
using ::testing::UnorderedElementsAre;

using ::testing::Matcher;
using ::testing::Le;
using ::testing::Ge;
using ::testing::_;

TEST(MockTest, FooTest) {
	MockFoo mock;

	// Matcher<int> expected_arg[] = { 1, 2, 4, 0, 5 };
	Matcher<int> expected_arg[] = { Le(1), 2, Ge(4), 0, _ };
	// EXPECT_CALL(mock, Do(ElementsAreArray(expected_arg)));
	// EXPECT_CALL(mock, Do(UnorderedElementsAreArray(expected_arg)));
	
	EXPECT_CALL(mock, Do(ElementsAre(1, 2, 0, 4, 5)));
	mock.Do({1, 2, 0, 4, 5});
}






