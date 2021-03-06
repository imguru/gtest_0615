// Stub: 특수한 상황을 시뮬레이션 하고 싶다.
#include <string>

struct Time {
	virtual ~Time() {}

	virtual std::string GetCurrentTime() = 0;
};

class User {
public:
	Time* time;

	User(Time* t) : time(t) {
	}

	int Do() {
		std::string t = time->GetCurrentTime();
		if (t == "00:00") {
			return 42;	
		}

		return 0;
	}
};

#include <gtest/gtest.h>

class StubTime : public Time {
public:
	std::string GetCurrentTime() override {
		return "00:00";
	}
};

TEST(UserTest, DoTest) {
	StubTime stub;
	User user(&stub);

	int actual = user.Do();

	EXPECT_EQ(42, actual);
}









