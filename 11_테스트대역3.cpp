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

#include <gmock/gmock.h>

class MockFileSystem : public IFileSystem {
public:
	MOCK_METHOD(bool, IsValid, (const std::string& filename), (override));
};

class LoggerTest : public ::testing::Test {
};

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

TEST_F(LoggerTest, IsValidLogFilename_NameLoggerThan5Chars_ReturnsTrue) {
	NiceMock<MockFileSystem> stub;
	ON_CALL(stub, IsValid(_)).WillByDefault(Return(true));
	std::string validFilename = "valid_filename.log";
	Logger logger(&stub);

	EXPECT_TRUE(logger.IsValidLogFilename(validFilename)) << "파일명이 다섯글자 이상일 때";
}

TEST_F(LoggerTest, IsValidLogFilename_NameShorterThan5Chars_ReturnsFalse) {
	NiceMock<MockFileSystem> stub;
	ON_CALL(stub, IsValid(_)).WillByDefault([](const std::string& filename) {
		return true;
	});
	Logger logger(&stub);
	std::string invalidFilename = "bad.log";
	
	bool actual = logger.IsValidLogFilename(invalidFilename);

	EXPECT_FALSE(actual) << "파일명이 다섯글자 미만일 때";
}
