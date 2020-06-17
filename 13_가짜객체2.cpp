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


bool operator==(const User& lhs, const User& rhs) {
	return lhs.GetName() == rhs.GetName() &&
		lhs.GetAge() == rhs.GetAge();
}

bool operator!=(const User& lhs, const User& rhs) {
	return !(lhs == rhs);
}

#include <gmock/gmock.h>
#include <map>

std::ostream& operator<<(std::ostream& os, const User& user) {
	return os << "User(name=" << user.GetName() << ", age=" << user.GetAge() << ")";
}

class UserManagerTest : public ::testing::Test {
};

class MockDatabase : public IDatabase {
	std::map<std::string, User*> data;
public:
	void DelegateToFake() {
		ON_CALL(*this, SaveUser).WillByDefault([this](const std::string& name, User* user) {
			SaveUserImpl(name, user);
		});
		ON_CALL(*this, LoadUser).WillByDefault([this](const std::string& name) {
			return LoadUserImpl(name);
		});
	}

	MOCK_METHOD(void, SaveUser, (const std::string& name, User* user), (override));
	MOCK_METHOD(User*, LoadUser, (const std::string& name), (override));

private:
	void SaveUserImpl(const std::string& name, User* user) {
		data[name] = user;
	}

	User* LoadUserImpl(const std::string& name) {
		return data[name];
	}
};

using ::testing::NiceMock;
TEST_F(UserManagerTest, SaveTest) {
	NiceMock<MockDatabase> fake;
	fake.DelegateToFake();
	UserManager manager(&fake);
	std::string testName = "test_name";
	int testAge = 42;
	User expected(testName, testAge);

	manager.Save(&expected);
	User* actual = manager.Load(testName);

	EXPECT_NE(actual, nullptr) << "Load 하였을 때";
	EXPECT_EQ(*actual, expected) << "Load 하였을 때";
}
