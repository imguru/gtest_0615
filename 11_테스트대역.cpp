// 11_테스트대역
#include <string>

// 아래 코드 문제점: 단위 테스트의 결과가 SUT가 아닌 의존 객체에 의해서 결정될 수 있다.
class FileSystem {
public:
	virtual bool IsValid(const std::string& filename) {
		// ....
		return false;
	}
};

class Logger {
public:
	// file.log -> 확장자를 제외한 파일의 이름이 5글자 이상이어야 한다.
	bool IsValidLogFilename(const std::string& filename) {
		//------------
		size_t index = filename.find_last_of(".");
		std::string name = filename.substr(0, index);
		
		if (name.size() < 5) {
			return false;
		}
		//------------

		FileSystem* fileSystem = new FileSystem;
		bool result = fileSystem->IsValid(filename);
		delete fileSystem;
		return result;
	}
};

// 결함 국소화: 단위 테스트가 실패하였을 때, 실패의 지점을 바로 알 수 있다.
#include <gtest/gtest.h>

class LoggerTest : public ::testing::Test {
};

// 다섯글자 이상의 파일명에서 IsValidLogFilename이 true를 반환하는가?
TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	Logger logger;
	std::string validFilename = "valid_filename.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

// 다섯글자 미만의 파일명에서 IsValidLogFilename이 false를 반환하는가?
TEST_F(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	Logger logger;
	std::string invalidFilename = "bad.log";
	
	bool actual = logger.IsValidLogFilename(invalidFilename);

	EXPECT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}











