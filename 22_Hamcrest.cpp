
// Hamcrest Style
//   : 단언문을 사용할 때, 좀더 문장에 가깝게 표현할 수 있도록 하는
//     비교 표현의 확장 라이브러리
//      - 오류 메세지에 대한 표현이 기존의 단언문을 사용할 때 보다 좋다.
#include <gmock/gmock.h>

int Foo() { return 100; }
const char* Goo() { return "hello, Goo!"; }
const char* Hoo() { return "line"; }

using ::testing::AllOf;
using ::testing::Gt;
using ::testing::Lt;
using ::testing::StartsWith;
using ::testing::MatchesRegex;

TEST(HamcrestTest, FooGooHoo) {
	
	// Foo()의 반환값이 10보다 크고 100보다 작은지 검증하고 싶다.
	int ret = Foo();
	EXPECT_TRUE(ret > 10 && ret < 100);
	EXPECT_THAT(Foo(), AllOf(Gt(10), Lt(100)));

	EXPECT_THAT(Goo(), StartsWith("Hello"));
	EXPECT_THAT(Hoo(), MatchesRegex("Line"));
}

class User {
public:
	User(const std::string& n, int a) : name(n), age(a) {}

	std::string GetName() const { return name; }
	int GetAge() const { return age; }

	FRIEND_TEST(UserTest, Field_Property); // !!

private:
	std::string name;  // Field
	int age;     
};

// Field: 멤버 변수
// Property: Accessor Method(접근자 메소드) - Getter / Setter
using ::testing::Field;     // 멤버 변수 접근
using ::testing::Property;  // Getter 사용
using ::testing::Eq;
using ::testing::StartsWith;

std::ostream& operator<<(std::ostream& os, const User& user) {
    return os << "User(name=" << user.GetName() << ", age=" << user.GetAge() << ")";
}

TEST(UserTest, Field_Property) {
	User user("Bob", 32);

	EXPECT_THAT(user, Field(&User::age, Eq(42)));
	// EXPECT_EQ(42, user.age);
	
	EXPECT_THAT(user, Property(&User::GetName, StartsWith("Tom")));
}


























