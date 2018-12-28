#include "ring_iterator.h"
#include "gtest/gtest.h"
#include <vector>
#include <iostream>

class empty_test : public ::testing::Test
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
	std::vector<int> empty{};
	std::vector<int> result;
};

TEST_F(empty_test, empty_container)
{
	ring_iterator it{ empty, empty.begin(), 0 };
	std::vector<int> expected{ empty };

	
	while (it != empty.end())
	{
		result.push_back(*it);
		++it;
	}

	EXPECT_EQ(result, expected);
}

TEST_F(empty_test, empty_container2)
{
	ring_iterator it{ empty, empty.begin(), 100 };
	std::vector<int> expected{ empty };

	
	while (it != empty.end())
	{
		result.push_back(*it);
		++it;
	}

	EXPECT_EQ(result, expected);
}

TEST_F(empty_test, infinite)
{
	ring_iterator it{ ring, ring.begin(), 0 };
	std::vector<int> expected{ 1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10 };

	for (int i = 0; i < 30; ++i)
	{
		result.push_back(*it);
		++it;
	} 

	EXPECT_EQ(result, expected);
}

TEST_F(empty_test, infinite2)
{
	ring_iterator it{ ring, ring.begin()+2, 0 };
	std::vector<int> expected{ 3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10, 1, 2 };

	for (int i = 0; i < 30; ++i)
	{
		result.push_back(*it);
		++it;
	} 

	EXPECT_EQ(result, expected);
}
