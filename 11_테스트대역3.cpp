// 11_테스트대역
#include <string>

struct IFileSystem {
	virtual ~IFileSystem() {}

	virtual bool IsValid(const std::string& name) = 0;  // !!
};


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
		}
	} 

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

#include <gtest/gtest.h>

class TestDouble : public IFileSystem {
public:
	bool IsValid(const std::string& filename) override {
		return true;
	}
};

class LoggerTest : public ::testing::Test {
};

TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	TestDouble td;
	Logger logger(&td);
	std::string validFilename = "valid_filename.log";

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

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




















