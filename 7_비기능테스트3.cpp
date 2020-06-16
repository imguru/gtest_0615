#include <gtest/gtest.h>

// new / delete의 재정의가 필요합니다.
// => 테스트에서만 이용 가능해야 합니다.
// => 약속된 매크로를 통해 조건부 컴파일 통해 처리될 수 있도록 하는 것이 좋습니다.
class Image {
public:
#ifdef GTEST_LEAK_TEST
	static int allocCount;
	void* operator new(size_t size) {
		++allocCount;
		return malloc(size);
	}

	void operator delete(void* p, size_t) {
		--allocCount;
		free(p);
	}
#endif
};

#ifdef GTEST_LEAK_TEST
int Image::allocCount = 0;
#endif

void foo() {
	Image* p1 = new Image;
	Image* p2 = new Image;
	Image* p3 = new Image;
	Image* p4 = new Image;
}

class ImageTest : public ::testing::Test {
protected:
#ifdef GTEST_LEAK_TEST
	int alloc;
#endif
	virtual void SetUp() override {
#ifdef GTEST_LEAK_TEST
		alloc = Image::allocCount;
#endif
	}

	virtual void TearDown() override {
#ifdef GTEST_LEAK_TEST
		int diff = Image::allocCount - alloc;
		EXPECT_EQ(0, diff) << diff << " Object(s) Leaks!";
#endif
	}
};

TEST_F(ImageTest, fooTest) {
	foo();
}



















