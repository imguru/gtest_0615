
// 12_Stub
//
//
// Test Stub Pattern
//   의도: '다른 컴포넌트로부터의 간접 입력'에 의존하는 로직을 독립적으로 검증하고 싶다.
//   방법: 실제 의존하는 객체를 테스트용 객체로 교체해서, SUT가 테스트하는데 필요한 결과를 보내도록 제어한다.
//    -> 특수한 상황을 시뮬레이션 하고 싶다.
//      : 네트워크 오류, 시간 등의 제어가 불가능한 환경을 제어하기 위해서 사용할 수 있다.
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

	// 인터페이스를 만들 때, 순수 가상함수로 제공하면, 자식이 해당 인터페이스를 반드시 구현해야 합니다.
	// 인터페이스에 기본 구현을 제공하는 것이 좋을 때가 있습니다.
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

#include <gtest/gtest.h>

// 기억할 점
//  - 인터페이스가 복잡하면, 테스트 대역을 만드는 부담이 늘어난다.
//  - 의존 객체가 많아질 수록, 작성해야 하는 테스트 대역의 양이 많아진다.
//  => 간단한 인터페이스가 좋다.
//     ISP: 범용 인터페이스 보다는 세분화된 인터페이스 좋다.
//      - 인터페이스의 문제점: 변화를 수용하기 어렵다.
//     
//     SOLID 원칙
//       - SRP(단일 책임의 원칙)
//       - OCP(개방 폐쇄의 원칙)
//       - LSP(리스코프 대체 원칙)
//       - ISP(인터페이스 분리 원칙)
//       - DIP(의존관계 역전 원칙)


// Test Double을 만드는 방법.
// 1. 의존하는 객체의 인터페이스를 구현한다.
//   Stub: "테스트에 필요한" 한가지의 동작을 수행하도록 한다.
class StubConnection : public IConnection {
public:
	void Move(int x, int y) override {
		throw NetworkException();
	}

	void Attack() override {
		throw NetworkException();
	}
};

class PlayerTest : public ::testing::Test {
};

// Network Connection이 제공되지 않을 때, Move의 동작이 NetworkException을 던지는지 확인하고 싶다.
// Google Test: EXPECT_THROW
TEST_F(PlayerTest, MoveTest) {
	// TcpConnection tcpConnection;
	// Player player(&tcpConnection);
	StubConnection stub;
	Player player(&stub);

	EXPECT_THROW(player.Move(10, 20), NetworkException);
}
