#pragma once

#include <vector>
#include <type_traits>
#include <cstdint>
#include <cassert>

template <bool reverse = false, typename T = int>
struct ring_ranged_wrapper;

template <typename T, bool reverse = false>
struct ring_iterator
{
	// Making iterator_type private will make class template argument deduction fail for ring_ranged_wrapper {}!
	typedef typename std::conditional<!reverse,
		typename std::vector<T>::iterator,
		typename std::vector<T>::reverse_iterator>::type
		iterator_type;

	typedef ring_iterator self_type;
	typedef T value_type;
	typedef T& reference;
	typedef T* pointer;
	typedef std::forward_iterator_tag iterator_category;
	typedef int difference_type;
private:
	// We don't own the container.
	std::vector<T>& container;
	iterator_type pos;
	size_t ring_size;

	// Has to be (*)() const functions or else we'll get a near match error.
	template <typename ret = iterator_type>
	std::enable_if_t<reverse, ret> cont_begin() const { return container.rbegin(); }
	template <typename ret = iterator_type>
	std::enable_if_t<!reverse, ret> cont_begin() const { return container.begin(); }
	template <typename ret = iterator_type>
	std::enable_if_t<reverse, ret> cont_end() const { return container.rend(); }
	template <typename ret = iterator_type>
	std::enable_if_t<!reverse, ret> cont_end() const { return container.end(); }

	void check_end()
	{
		if (pos == this->cont_end())
		{
			pos = this->cont_begin();
		}
	}

	void ring_inc()
	{
		// A ring_size of 0 means iterator will never return end.
		if (ring_size != SIZE_MAX)
		{
			--ring_size;
			if (ring_size == 0)
			{
				pos = this->cont_end();
				return;
			}
		}

		++pos;
		check_end();
	}
public:

	// A ring_size of 0 means iterator will (effectively) never return end.
	ring_iterator(std::vector<T>& container, iterator_type const& pos, size_t ring_size)
		: container{ container }
		, pos{ pos }
		, ring_size{ ring_size }
	{
		check_end();
	}

	reference operator*() { return *pos; }

	bool operator==(const self_type& rhs) { return pos == rhs.pos; }
	bool operator!=(const self_type& rhs) { return !(*this == rhs); }

	// For while (++it != A.end());
	// Where it is of this type, A is of container type.
	bool operator==(const iterator_type& rhs) { return this->pos == rhs; }
	bool operator!=(const iterator_type& rhs) { return !(*this == rhs); }

	// https://en.cppreference.com/w/cpp/language/operator_incdec#Built-in_prefix_operators
	// Pre-increment.
	self_type& operator++() { ring_inc(); return *this; }
	// Post-increment
	self_type operator++(int) { self_type tmp = *this; ring_inc(); return tmp; }

	self_type operator+(size_t rhs) const
	{
		self_type tmp = *this;
		do
		{
			tmp.ring_inc();
		}
		while (--rhs != 0);
		return tmp;
	}

	// This is actually not used.
	// explicit operator typename std::vector<T>::iterator() const { return pos; }

	// Have to set pos to cont_end() manually because constructor does check_end().
	self_type end() { self_type ret = *this; ret.pos = this->cont_end(); return ret; }

	friend ring_ranged_wrapper<reverse, T>;
};

template <bool reverse, typename T>
struct ring_ranged_wrapper
{
	using iterator = ring_iterator<T, reverse>;
private:
	iterator it;
	size_t ring_size;
public:
	ring_ranged_wrapper(std::vector<T>& container, typename iterator::iterator_type const& pos, size_t ring_size)
		: it{ container, pos, ring_size }
		, ring_size{ ring_size }	
	{
		// Iterator has to end if used in a ranged for.
		assert(ring_size);
	}
	iterator begin() const { return it; }
	// iterator end() const { return iterator{ it.container, it.end(), 0 }; }
	iterator end() const { return it + ring_size; }
};

template <typename T>
using rring_iterator = ring_iterator<T, true>;
