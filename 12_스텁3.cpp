#include <iostream>

// Network Exception
class NetworkException : public std::exception {
public:
	const char* what() {
		return "Bad network state";
	}
};

struct IConnection {
	virtual ~IConnection() {}

	virtual void Move(int x, int y) = 0;
	virtual void Attack() = 0;

	virtual void Foo() {}
};

class Player {
	IConnection* conn;
public:
	Player(IConnection* p) : conn(p) {}

	void Move(int x, int y) {
		try {
			conn->Move(x, y);
		} catch (NetworkException& e) {
			//----
			printf("NetworkException 동작에 대한 처리 로직...\n");
			throw e;
			//----
		}
	}
};

#include <gmock/gmock.h>

class MockConnection : public IConnection {
public:
	MOCK_METHOD(void, Move, (int x, int y), (override));
	MOCK_METHOD(void, Attack, (), (override));
};

class PlayerTest : public ::testing::Test {
};

using ::testing::_;
using ::testing::Throw;

TEST_F(PlayerTest, MoveTest) {
	MockConnection stub;
	ON_CALL(stub, Move(_, _)).WillByDefault(Throw(NetworkException()));

	Player player(&stub);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}









