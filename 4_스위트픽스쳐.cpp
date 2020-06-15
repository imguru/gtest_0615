#include <string>

#include <unistd.h>

// TestCase라는 이름 말고, 픽스쳐를 공유한다는 TestSuite이름을 사용하길 권장합니다.

// SetUpTestCase(); - static
// DatabaseTest *tc = new DatabaseTest
// tc->SetUp();
// tc->TestBody();
// tc->TearDown();
// delete tc;
//
// DatabaseTest *tc = new DatabaseTest
// tc->SetUp();
// tc->TestBody();
// tc->TearDown();
// delete tc;
// TearDownTestCase(); - static


// 가정: Connect / Disconnect가 느리다.
//  => 픽스쳐를 설치하거나, 해체하는 과정이 느리다.
//  => 새로운 테스트를 추가할 때마다, 느려진다.
//  => Slow Test(느린 테스트)
//   : 테스트를 수행하는 개발자의 생산성을 떨어뜨린다.
//     테스트가 느려서 아무도 코드가 변경되어도, 테스트를 수행하고자 하지 않는다.
//     * 해결 방법: 스위트 픽스쳐 설치/해체를 이용하면 된다.
class Database {
public:
	void Connect() { sleep(2); }
	void Disconnect() { sleep(1); }

	void Login(const std::string& id, const std::string& password) {}
	void Logout() {}

	bool IsLogin() { return true; }
};

//----------------------------------------
#include <gtest/gtest.h>

#if 0
class DatabaseTest : public ::testing::Test {
protected:
	Database* db;
	DatabaseTest() : db(nullptr) {}

	// Suite Fixture Setup
	static void SetUpTestCase() {
		printf("SetUpTestCase()\n");
	}
	// Suite Fixture TearDown
	static void TearDownTestCase() {
		printf("TearDownTestCase()\n");
	}

	virtual void SetUp() override {
		printf("SetUp()\n");
		db = new Database;
		db->Connect();
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
		db->Disconnect();
		delete db;
	}
};
#endif
class DatabaseTest : public ::testing::Test {
protected:
	static Database* db;  // !!

	//                           : SetUpTestCase / TearDownTestCase
	// Suite Fixture Setup - 1.10: SetUpTestSuite / TearDownTestSuite
	static void SetUpTestSuite() {
		printf("SetUpTestSuite()\n");
		db = new Database;
		db->Connect();
	}

	// Suite Fixture TearDown
	static void TearDownTestSuite() {
		printf("TearDownTestCase()\n");
		db->Disconnect();
		delete db;
	}

	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};
//
// Static 멤버 변수는 소스 파일에 정의가 필요합니다.
Database* DatabaseTest::db = nullptr;


TEST_F(DatabaseTest, LoginTest) {
	printf("DatabaseTest.LoginTest()\n");
	db->Login("test_id", "test_password");

	ASSERT_TRUE(db->IsLogin()) << "로그인 하였을 때";
}

TEST_F(DatabaseTest, LogoutTest) {
	printf("DatabaseTest.LogoutTest()\n");
	db->Login("test_id", "test_password");
	db->Logout();

	ASSERT_FALSE(db->IsLogin()) << "로그아웃 하였을 때";
}

#if 0
TEST(DatabaseTest, LoginTest) {
	Database* db = new Database;
	db->Connect();

	db->Login("test_id", "test_password");

	ASSERT_TRUE(db->IsLogin()) << "로그인 하였을 때";

	db->Disconnect();
	delete db;
}

TEST(DatabaseTest, LogoutTest) {
	Database* db = new Database;
	db->Connect();

	db->Login("test_id", "test_password");
	db->Logout();

	ASSERT_FALSE(db->IsLogin()) << "로그아웃 하였을 때";

	db->Disconnect();
	delete db;
}
#endif





