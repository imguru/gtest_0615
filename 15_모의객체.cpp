// 14_스파이
#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR
};

struct DLoggerTarget {
	virtual ~DLoggerTarget() {}

	virtual void Write(Level level, const std::string& message) = 0;
};

class DLogger {
	std::vector<DLoggerTarget*> targets;
public:
	void AddTarget(DLoggerTarget* p) {
		targets.push_back(p);
	}

	void Write(Level level, const std::string& message) {
		for (DLoggerTarget* p : targets) {
			p->Write(level, message);
		}
	}
};

// Mock Object Pattern
//  의도: 함수를 호출하였을 때, 발생하는 부수 효과를 관찰 할 수 없어서, 테스트 안된 요구사항이 있을 때
//  방법: 행위 기반 검증을 수행한다.
//        = 동작 검증, 객체에 작용을 가한후 내부적으로 발생하는 함수의 호출 여부, 호출 순서, 호출 횟수 등을 통해
//                     검증 작업을 수행한다.
//        <=> 상태 검증: 객체에 작용을 가한후, 단언 함수를 이용해서 내부의 상태값을 확인하는 검증 방법.

// 모의 객체
//   : 내부적으로 발생한 함수의 호출 여부, 횟수, 순서등의 정보를 가지고 있다.
//   Mock Framework이 필요합니다.
//     Java: jMock, EasyMock, Mockito, Spock ...
//     C++: Google Mock

#include <gtest/gtest.h>
// Google Mock을 적용하는 방법.

// 1. include
#include <gmock/gmock.h>

// 2. Mock Object 생성 - Mocking
//   => Macro를 통해 Mocking하는 메소드를 자동으로 생성할 수 있습니다.
//   1.10 버전 이전
//    MOCK_METHOD{인자개수}(함수 이름, 함수의 타입)
//     => 스크립트를 통해 자동으로 Mocking에 관련된 코드를 생성하도록 하였다.
//       googletest/googlemock/scripts/generator/gmock_gen.py
//   1.10 버전 이후
//     : 새로운 형태의 매크로를 제공합니다.
//     MOCK_METHOD(반환타입, 함수이름, 함수 인자, 한정자)
class MockDLoggerTarget : public DLoggerTarget {
public:
	// virtual void Write(Level level, const std::string& message)
	// MOCK_METHOD2(Write, void(Level level, const std::string&);
	
#if 0
	void Write(Level level, const std::string& message) override {
	}
#endif
	MOCK_METHOD(void, Write, (Level level, const std::string& message), (override));
	// 마지막 한정자에 대해서는 괄호로 한번 묶어줘야 합니다.
};

TEST(DLoggerTest, WriteTest) {
	// Arrange
	DLogger logger;
	MockDLoggerTarget mock1, mock2;
	logger.AddTarget(&mock1);
	logger.AddTarget(&mock2);
	Level test_level = INFO;
	std::string test_message = "log_message";

	// Assert(기대 동작에 대한 부분을 먼저 명시해야 합니다.)
	EXPECT_CALL(mock1, Write(test_level, test_message));
	EXPECT_CALL(mock2, Write(test_level, test_message));

	// Act
	logger.Write(test_level, test_message);
} 
















