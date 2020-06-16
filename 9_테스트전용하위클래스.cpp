// 9_테스트전용하위클래스
#include <stdio.h>

// SUT
class Engine {
public:
	Engine() { printf("Engine()\n"); }
	~Engine() {}
	
	virtual void Start() {
		printf("Engine Start!\n");
	}
};

class Car {
	Engine* engine;
public:
	Car(Engine* p) : engine(p) {}

	void Go() {
		// ...
		engine->Start();
	}
};

#include <gtest/gtest.h>

class CarTest : public ::testing::Test {};

// 테스트 전용 하위 클래스 패턴
//  : 테스트 하고자 하는 클래스가 테스트를 위한 기능을 제공하고 있지 않다면,
//    테스트 코드 안에서 자식 클래스를 통해 해당 기능을 제공하면 된다.
//     - SUT가 제공하는 인터페이스가 virtual 함수 이어야 한다.
class TestEngine : public Engine {
	// 테스트를 위한 속성
	bool isStart;
public:
	TestEngine() : isStart(false) {}

	virtual void Start() override {    // 부모의 기능을 그대로 사용한다.
		Engine::Start();
		isStart = true;
	}

	// 테스트 전용 메소드
	bool IsStart() const {
		return isStart;
	}
};

// Car 객체에 Go를 호출하였 을때, Engine의 Start가 제대로 호출되었는지 여부를 검증하고 싶다.
TEST_F(CarTest, GoTest2) {
	TestEngine engine;
	Car car(&engine);

	car.Go();
	
	EXPECT_TRUE(engine.IsStart()) << "자동차가 Go 하였을 때";
}

TEST_F(CarTest, GoTest) {
	Engine engine;
	Car car(&engine);

	car.Go();

	// ?
}




























