// 11_테스트대역
#include <string>

// 테스트 대역은 무조건 적용할 수 없습니다.
//  : 제품 코드가 테스트 대역을 적용할 수 있도록 설계되어 있어야 합니다.
//
//  왜 적용하는가?
//   : 의존하는 객체를 테스트 대역을 대체해서, SUT에 의해서만 테스트의 결과가 결정될 수 있도록 하고 싶다.
//
//  테스트 대역을 적용할 수 있는 설계 
//   : 의존하는 객체에 대해서 강한 결합이 아닌 느슨한 결합의 설계를 적용해야 합니다.
//   강한 결합: 의존하는 객체의 구체적인 타입에 의존하는 것.
//   약한 결합: 의존하는 객체의 구체적인 타입이 아닌 추상 타입이나 인터페이스에 의존하는 것.
//      핵심 - 의존하는 객체를 직접 생성하면 안된다.
//             new의 연산은 강한 결합의 원인이 됩니다.
//             외부에서 생성해서 전달 받아야 합니다.  - 의존성 주입(Dependency Injection) 
//             1) 생성자 주입
//               : 의존하는 객체가 필수적일 때
//             2) 메소드 주입
//               : 의존하는 객체가 필수적이지 않을 때
//             문제점
//                - 보일러플레이트가 발생합니다.
//				 B* b = new B;
//				 C* c = new C;
//				 A* a = new A(b, c);

// 1. 의존하는 객체에 인터페이스를 설계하자.
struct IFileSystem {
	virtual ~IFileSystem() {}

	virtual bool IsValid(const std::string& name) = 0;  // !!
};


// 2. 인터페이스를 구현해야 한다.
class FileSystem : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		// ....
		return false;
	}
};

class Logger {
	IFileSystem* fileSystem;
public:
	Logger(IFileSystem* p = nullptr) : fileSystem(p) {
		if (p == nullptr) {
			fileSystem = new FileSystem;
			// 기존의 사용법과 동일하게 만들어주는 것이 좋다 - 틈새 만들기
		}
	} 

	// file.log -> 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
	bool IsValidLogFilename(const std::string& filename) {
		//------------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);
		
		if (name.size() < 5) {
			return false;
		}
		//------------
		return fileSystem->IsValid(filename);
	}
};

// 결함 국소화: 단위 테스트가 실패하였을 때, 실패의 지점을 바로 알 수 있다.
#include <gtest/gtest.h>

class TestDouble : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		return true;
	}
};

class LoggerTest : public ::testing::Test {
};

// '의존성 주입 모델'을 사용하면
//  1. 테스트 대역을 쉽게 적용할 수 있다.
//  2. 제품 코드를 사용하는 방식과 동일하게 테스트 코드를 작성할 수 있다.

// 다섯글자 이상의 파일명에서 IsValidLogFilename이 true를 반환하는가?
TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	TestDouble td;
	Logger logger(&td);
	std::string validFilename = "valid_filename.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

// 다섯글자 미만의 파일명에서 IsValidLogFilename이 false를 반환하는가?
TEST_F(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	TestDouble td;
	Logger logger(&td);
	std::string invalidFilename = "bad.log";
	
	bool actual = logger.IsValidLogFilename(invalidFilename);

	EXPECT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}


// 테스트 대역 종류 - 4가지
// 1. Test Stub    -> Stub
// 2. Fake Object  -> Fake
// 3. Test Spy     -> Spy
// 4. Mock Object  -> Mock




















