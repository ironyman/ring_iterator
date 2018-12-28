#include "ring_iterator.h"
#include "gtest/gtest.h"
#include <vector>
#include <iostream>

class writing_test : public ::testing::Test
{
protected:
	void SetUp() override {}

	void TearDown() override
	{
		std::ostream_iterator<int> out_it{ std::cout,", " };
		std::copy(result.begin(), result.end(), out_it);
		std::cout << '\n';
	}

	std::vector<int> input{ 1,2,3,4,5,6,7,8,9,10 };
	std::vector<int> result;
};

TEST_F(writing_test, writing)
{
	result.resize(10);
	ring_iterator it{ result, result.begin(), 30 };
	std::vector<int> expected{ input };

	std::copy(input.begin(), input.end(), it);

	EXPECT_EQ(result, expected);
}

TEST_F(writing_test, writing_infinite)
{
	result.resize(10);
	ring_iterator it{ result, result.begin(), 0 };
	std::vector<int> expected{ input };

	std::copy(input.begin(), input.end(), it);

	EXPECT_EQ(result, expected);
}

TEST_F(writing_test, writing_infinite2)
{
	result.resize(5);
	ring_iterator it{ result, result.begin(), 0 };
	std::vector<int> expected{ 6,7,8,9,10 };

	std::copy(input.begin(), input.end(), it);

	EXPECT_EQ(result, expected);
}

TEST_F(writing_test, reverse_writing_infinite2)
{
	result.resize(5);
	// ring_iterator<int, true> it{ result, std::make_reverse_iterator(result.begin()), 0 };
	auto it = make_ring_iterator(result, std::make_reverse_iterator(result.begin()), 0);
	std::vector<int> expected{ 10,9,8,7,6 };

	std::copy(input.begin(), input.end(), it);

	EXPECT_EQ(result, expected);
}

TEST_F(writing_test, reverse_writing_infinite3)
{
	result.resize(3);
	// ring_iterator<int, true> it{ result, std::make_reverse_iterator(result.begin()), 0 };
	auto it = make_ring_iterator(result, std::make_reverse_iterator(result.begin()), 0);
	std::vector<int> expected{ 9,8,10};

	std::copy(input.begin(), input.end(), it);

	EXPECT_EQ(result, expected);
}

TEST_F(writing_test, reverse_writing_infinite4)
{
	result.resize(3);
	// ring_iterator<int, true> it{ result, std::make_reverse_iterator(result.begin()+1), 0 };
	auto it = make_ring_iterator(result, std::make_reverse_iterator(result.begin()+1), 0);
	std::vector<int> expected{ 10, 9,8 };

	std::copy(input.begin(), input.end(), it);

	EXPECT_EQ(result, expected);
}
