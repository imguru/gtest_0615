// 14_스파이
#include <string>
#include <vector>

enum Level {
	INFO, WARN, ERROR
};

// DLogger <-   FileTarget
//              NetTarget
//  log(INFO, "message")           

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


// Test Spy Pattern
//  의도: 함수를 호출하였을 때 발생하는 부수효과를 관찰할 수 없어서 테스트 안된 요구사항 있을 때
//  방법: 목격한 일을 기록해두었다가, 나중에 테스트에서 확인할 수 있도록 만들어진 테스트 대역
//        다른 컴포넌트로부터의 간접 출력을 저장해두었다가 검증한다.
#include <gtest/gtest.h>
#include <algorithm>

class SpyTarget : public DLoggerTarget {
	std::vector<std::string> history;

	std::string concat(Level level, const std::string& message) {
		static const char* levelStr[] = {
			"INFO", "WARN", "ERROR",
		};

		return std::string(levelStr[level]) + "@" + message;
	}

public:
	void Write(Level level, const std::string& message) override {
		history.push_back(concat(level, message));
	}

	// 테스트에서 확인할 수 있도록 하는 함수.
	bool IsReceived(Level level, const std::string& message) {
		return std::find(history.begin(), history.end(), concat(level, message)) != history.end();
	}
};

// DLogger에 대해서 2개 이상의 타겟을 등록하고, Write를 수행하였을 때, Target에 대해서 Write가 호출되었는지 여부를 
// 검증하고 싶다.
TEST(DLoggerTest, WriteTest) {
	// Arrange
	DLogger logger;
	SpyTarget spy1, spy2;
	logger.AddTarget(&spy1);
	logger.AddTarget(&spy2);
	Level test_level = INFO;
	std::string test_message = "log_message";

	// Act
	logger.Write(test_level, test_message);

	// Assert
	EXPECT_TRUE(spy1.IsReceived(test_level, test_message));
	EXPECT_TRUE(spy2.IsReceived(test_level, test_message));
}







































