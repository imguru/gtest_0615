
#include <gmock/gmock.h>

template <typename T>
struct StackInterface {
	virtual ~StackInterface() {}

	virtual int GetSize() const = 0;
	virtual void Push(const T& x) = 0;
};

// Template Mocking
template <typename T>
class MockStack : public StackInterface<T> {
public:
	MOCK_METHOD(int, GetSize, (), (override, const));
	MOCK_METHOD(void, Push, (const T& x), (override));
};

TEST(MockStackTest, Sample) {
	MockStack<int> mock;
}
