#include "ring_iterator.h"
#include "gtest/gtest.h"
#include <vector>
#include <iostream>

class copy_test : public ::testing::Test
{
protected:
	void SetUp() override {}

	void TearDown() override
	{
		std::ostream_iterator<int> out_it{ std::cout,", " };
		std::copy(result.begin(), result.end(), out_it);
		std::cout << '\n';
	}

	std::vector<int> ring{ 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> result;
};

TEST_F(copy_test, begin)
{
	ring_iterator it{ ring, ring.begin(), 3 };
	std::vector<int> expected{ 1,2,3 };

	std::copy(it, it.end(), std::back_inserter(result));

	EXPECT_EQ(result, expected);
}

TEST_F(copy_test, begin9)
{
	ring_iterator it{ ring, ring.begin() + 9, 3 };
	std::vector<int> expected{ 10, 1, 2 };

	std::copy(it, it.end(), std::back_inserter(result));

	EXPECT_EQ(result, expected);
}

TEST_F(copy_test, begin30)
{
	ring_iterator it{ ring, ring.begin() + 2, 30 };
	std::vector<int> expected{ 3,4,5,6,7,8,9,10, 1,2,3,4,5,6,7,8,9,10, 1,2,3,4,5,6,7,8,9,10,1,2 };

	std::copy(it, it.end(), std::back_inserter(result));

	EXPECT_EQ(result, expected);
}
