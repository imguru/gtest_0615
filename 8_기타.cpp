#include <gtest/gtest.h>

// #include "User.h"
class User {
	int age;
public:
	User() : age(42) {}

	FRIEND_TEST(UserTest, ageTest);
private:

};

// Google Test는 'private 필드나 메소드'에 대한 접근이 가능하게 하는 
// 'FRIEND_TEST'라는 기능을 제공합니다.

TEST(UserTest, ageTest) {
	User user;

	// ...

	ASSERT_EQ(42, user.age);
}
