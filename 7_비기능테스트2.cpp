#include <gtest/gtest.h>
#include <unistd.h>

void foo() {
	sleep(3);
}

void goo() {
}


// 시간에 대한 부분을 측정해서 처리하는 ASSERT를 제공하면 좋습니다.
#define EXPECT_TIMEOUT(fn, sec)									\
	do {														\
		time_t s = time(0);										\
		fn;											  		    \
		time_t e = time(0);										\
		time_t d = e - s;										\
		EXPECT_LE(d, sec) << "Timeout: " << d << " sec";		\
	} while (0)


// 2초안에 수행되어야 한다.
TEST(FooTest, foo) {
	{
		time_t s = time(0);
		foo();
		time_t e = time(0);
		time_t d = e - s;
		EXPECT_LE(d, 2) << "Timeout: " << d << " sec";
	}
}

TEST(FooTest, goo) {
	EXPECT_TIMEOUT(foo(), 2);
}

















