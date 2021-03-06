// 13_가짜객체


#include <string>

class User {
	std::string name;
	int age;
public:
	User(const std::string& s, int n) : name(s), age(n) {}

	std::string GetName() const {
		return name;
	}

	int GetAge() const {
		return age;
	}
};

struct IDatabase {
	virtual ~IDatabase() {}

	virtual void SaveUser(const std::string& name, User* user) = 0;
	virtual User* LoadUser(const std::string& name) = 0;
};

class UserManager {
	IDatabase* database;
public:
	UserManager(IDatabase* p) : database(p) {}

	void Save(User* u) {
		// ...
		database->SaveUser(u->GetName(), u);
	}

	User* Load(const std::string& name) {
		// ...
		return database->LoadUser(name);
	}
};

// Fake Object Pattern
//  의도: 아직 준비되지 않은 의존 객체로 인해서, 테스트 안된 요구사항이 있을 때
//  방법: 동일한 기능을 제공하는 가벼운 테스트 대역을 만들어서, 문제를 해결하자.
//
//  1) 준비되지 않았을 때
//  2) 의존하는 객체를 사용하기 어려울 때
//  3) 의존하는 객체가 너무 느려서, 느린 테스트의 문제가 발생할 때
//
//  UserManager -> Database : IDatabase(준비되지 않음)

// Docker - Test
//           : CI - Jenkins, Travis CI, Circle CI

#include <gtest/gtest.h>
#include <map>

class FakeDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void SaveUser(const std::string& name, User* user) override {
		data[name] = user;
	}

	User* LoadUser(const std::string& name) override {
		return data[name];
	}
};

class UserManagerTest : public ::testing::Test {
};


// 사용자 정의 객체에 대해서 구글 테스트가 제공하는 단언 매크로를 이용하기 위해서는
// 연산자 재정의 함수가 제공되어야 합니다.
// EXPECT_EQ(==)
bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() &&
		lhs.GetAge() == rhs.GetAge();
}

// EXPECT_NE(!=)
bool operator!=(const User& lhs, const User& rhs) {
	return !(lhs == rhs);
}

// 사용자 정의 객체에 대해서 문자열로 표현하는 방식
std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User(name=" << user.GetName() << ", age=" << user.GetAge() << ")";
}

TEST_F(UserManagerTest, SaveTest) {
	FakeDatabase fake;
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	EXPECT_NE(actual, nullptr) << "Load 하였을 때";
	// EXPECT_EQ(*actual, expected) << "Load 하였을 때";
	EXPECT_NE(*actual, expected) << "Load 하였을 때";
}




























