#include "ring_iterator.h"
#include "gtest/gtest.h"
#include <vector>
#include <iostream>

class ring_iterator_test : public ::testing::Test
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

TEST_F(ring_iterator_test, begin)
{
	// Starting at 1st element.
	ring_iterator it{ ring, ring.begin(), ring.size() };
	std::vector<int> expected{ ring };

	do
	{
		result.push_back(*it);
	} while (++it != ring.end());

	EXPECT_TRUE(std::equal(result.begin(), result.end(), expected.begin()));
}

TEST_F(ring_iterator_test, fourth)
{
	// Starting at 4th element.
	ring_iterator it{ ring, ring.begin() + 3, ring.size() };
	std::vector<int> expected{ 4, 5, 6, 7, 8, 9, 10, 1, 2, 3 };

	do
	{
		result.push_back(*it);
	} while (++it != ring.end());

	EXPECT_TRUE(std::equal(result.begin(), result.end(), expected.begin()));
}

TEST_F(ring_iterator_test, end)
{
	// Starting at end element.
	ring_iterator it{ ring, ring.end(), ring.size() };
	std::vector<int> expected{ ring };

	do
	{
		result.push_back(*it);
	} while (++it != ring.end());

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, begin_wrapper)
{
	std::vector<int> expected{ ring };

	for (int it : ring_ranged_wrapper{ ring, ring.begin(), ring.size() })
	{
		result.push_back(it);
	}

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, fifth_wrapper)
{
	// Starting at 5th element.
	std::vector<int> expected{ 5, 6, 7, 8, 9, 10, 1, 2, 3, 4 };

	for (int it : ring_ranged_wrapper{ ring, ring.begin() + 4, ring.size() })
	{
		result.push_back(it);
	}

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, end_wrapper)
{
	// Starting at end element.
	std::vector<int> expected{ ring };

	for (int it : ring_ranged_wrapper{ ring, ring.end(), ring.size() })
	{
		result.push_back(it);
	}

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_begin)
{
	// Starting at 4th element.
	ring_iterator<int, true> it{ ring, ring.rbegin(), ring.size() };
	std::vector<int> expected{ ring };

	std::reverse(expected.begin(), expected.end());

	do
	{
		result.push_back(*it);
	} while (++it != ring.rend());

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_begin2)
{
	// Starting at 4th element.
	ring_iterator<int, true> it{ ring, std::make_reverse_iterator(ring.end()), ring.size() };
	std::vector<int> expected{ ring };

	std::reverse(expected.begin(), expected.end());

	// ring_iterator contains generic end()!
	do
	{
		result.push_back(*it);
	} while (++it != it.end());

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_fourth)
{
	// Starting at one before 4th element.
	ring_iterator<int, true> it{ ring, std::make_reverse_iterator(ring.begin() + 3), ring.size() };
	std::vector<int> expected{ 3, 2, 1, 10, 9, 8, 7, 6, 5, 4 };

	do
	{
		result.push_back(*it);
	} while (++it != it.end());

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_end)
{
	// Starting at end element.
	ring_iterator<int, true> it{ ring, ring.rend(), ring.size() };
	std::vector<int> expected{ ring };

	std::reverse(expected.begin(), expected.end());

	do
	{
		result.push_back(*it);
	} while (++it != it.end());

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_end2)
{
	// Starting at end element.
	ring_iterator<int, true> it{ ring, std::make_reverse_iterator(ring.begin()), ring.size() };
	std::vector<int> expected{ ring };

	std::reverse(expected.begin(), expected.end());

	do
	{
		result.push_back(*it);
	} while (++it != it.end());

	EXPECT_EQ(result, expected);
}


TEST_F(ring_iterator_test, reverse_begin_wrapper)
{
	std::vector<int> expected{ ring };

	std::reverse(expected.begin(), expected.end());
	for (int it : ring_ranged_wrapper<true>{ ring, ring.rbegin(), ring.size() })
	{
		result.push_back(it);
	}

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_begin_wrapper2)
{
	std::vector<int> expected{ ring };

	std::reverse(expected.begin(), expected.end());
	for (int it : ring_ranged_wrapper<true>{ ring, std::make_reverse_iterator(ring.begin()), ring.size() })
	{
		result.push_back(it);
	}

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_fifth_wrapper)
{
	// Starting at one before 5th element.
	std::vector<int> expected{ 4, 3, 2, 1, 10, 9, 8, 7, 6, 5 };

	for (int it : ring_ranged_wrapper<true>{ ring, std::make_reverse_iterator(ring.begin() + 4), ring.size() })
	{
		result.push_back(it);
	}

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_end_wrapper)
{
	// Starting at end element.
	std::vector<int> expected{ ring };

	std::reverse(expected.begin(), expected.end());
	for (int it : ring_ranged_wrapper<true>{ ring, std::make_reverse_iterator(ring.end()), ring.size() })
	{
		result.push_back(it);
	}

	EXPECT_EQ(result, expected);
}

TEST_F(ring_iterator_test, reverse_end_wrapper2)
{
	// Starting at end element.
	std::vector<int> expected{ ring };

	std::reverse(expected.begin(), expected.end());
	for (int it : ring_ranged_wrapper<true>{ ring, ring.rbegin(), ring.size() })
	{
		result.push_back(it);
	}

	EXPECT_EQ(result, expected);
}
#if 0

void do_reverse()
{
	std::vector<int> A{ 1,2,3,4,5,6,7,8,9,10 };

	// Starting one before 4.
	ring_iterator<int, true> it{ A, std::make_reverse_iterator(A.begin() + 3), 10 };
	do
	{
		std::cout << *it << '\n';
	} while (++it != A.rend());
	std::cout << '\n';

	// Starting one before 5.
	for (auto it : ring_ranged_wrapper<true>{ A, std::make_reverse_iterator(A.begin() + 4), 10 })
	{
		std::cout << it << '\n';
	}
	// Starting one before 1.
	for (auto it : ring_ranged_wrapper<true>{ A, std::make_reverse_iterator(A.begin()), 10 })
	{
		std::cout << it << '\n';
	}

}
int main()
{
	std::vector<int> A{ 1,2,3,4,5,6,7,8,9,10 };

	// Starting at 4.
	ring_iterator it{ A, A.begin() + 3, 10 };
	do
	{
		std::cout << *it << '\n';
	} while (++it != A.end());
	std::cout << '\n';

	for (auto it : ring_ranged_wrapper{ A, A.begin() + 4, 10 })
	{
		std::cout << it << '\n';
	}

	std::cout << "doing reverse\n" << '\n';
	do_reverse();
	return 0;
}

#endif
