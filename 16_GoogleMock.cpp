
#include <gtest/gtest.h>  // Google Test
#include <gmock/gmock.h>  // Google Mock

struct Mp3 {
	virtual ~Mp3() {}

	virtual void Play() = 0;
	virtual void Stop(int n) = 0;
	
	virtual std::string GetName() const = 0;
	virtual void Foo() noexcept = 0;

	virtual std::pair<bool, int> GetPair() = 0;
	virtual bool CheckMap(std::map<int, double> a, bool b) = 0;
};

// 1. Mocking
//    MOCK_METHOD(반환타입, 메소드이름, (인자), (한정자));
// 한정자
//  - 1. override
//    2. const
//    3. noexcept
//    4. stdcall, cdecl ...
//
// 3. 테스트 대역의 인터페이스에서 제공하는 모든 함수에 대해서 작업해야 합니다.
class MockMp3 : public Mp3 {
public: 
	// 2. 주의할점
	// 1. 반환타입에 ,가 존재하는 경우, 괄호를 통해 닫아주어야 한다.
	// MOCK_METHOD((std::pair<bool, int>), GetPair, (), (override));
	// 2. 인자를 전달하는 괄호안에 쉼표도, 괄호를 통해 닫아주어야 한다.
	// MOCK_METHOD(bool, CheckMap, ((std::map<int, double> a), bool b), (override));
	
	// 다른 방법
	//  - C++ Type aliasing
	using BoolAndInt = std::pair<bool, int>;  
	MOCK_METHOD(BoolAndInt, GetPair, (), (override));

	using MapIntDouble = std::map<int, double>;
	MOCK_METHOD(bool, CheckMap, (MapIntDouble, bool), (override));

	MOCK_METHOD(void, Play, (), (override));
	MOCK_METHOD(void, Stop, (int n), (override));

	MOCK_METHOD(std::string, GetName, (), (override, const));
	MOCK_METHOD(void, Foo, (), (override, noexcept));
};













// main 함수는 Google Mock을 사용할 겨우 아래와 같이 작성하면 됩니다.
#if 0
int main(int argc, char** argv) {
	::testing::InitGoogleMock(&argc, argv);  // 내부적으로 ::testing::InitGoogleTest를 수행합니다.

	return RUN_ALL_TESTS();
}
#endif
