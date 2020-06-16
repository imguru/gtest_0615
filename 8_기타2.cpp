#include <gtest/gtest.h>

class User {
protected:
	int age;
public:
	User() : age(42) {}
private:

};

// 접근하고자 하는 멤버 변수나 또는 함수의 접근 지정자가 protected인 경우
// 자식 클래스는 부모의 protected를 public으로 변경할 수 있습니다.

// 로버트 C 마틴
//  : private 메소드의 목적은 public 메소드의 가독성을 높이기 위해서 사용해야 한다. 
//   -Clean Code-

class TestUser : public User {
public:
	using User::age;     // protected -> public
};

TEST(UserTest, ageTest) {
	// User user;
	TestUser user;

	// ...

	ASSERT_EQ(42, user.age);
}
