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









