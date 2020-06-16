#include <gtest/gtest.h>

enum Color { BLACK, GRAY, WHITE };
class AnimalTest
    : public testing::TestWithParam<std::tuple<const char*, Color> > {
protected:
	virtual void SetUp() override {
		printf("SetUp()\n");
	}

	virtual void TearDown() override {
		printf("TearDown()\n");
	}
};

using ::testing::Combine;
using ::testing::Values;
INSTANTIATE_TEST_SUITE_P(AnimalVariations, AnimalTest,
                          Combine(Values("cat", "dog"),
                                  Values(BLACK, WHITE)));

TEST_P(AnimalTest, AnimalLooksNice) {
	const char* animal = std::get<0>(GetParam());
	Color c = std::get<1>(GetParam());

	printf("%s - %d\n", animal, c);
}

