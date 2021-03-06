#pragma once

#include <stdexcept>

namespace detail_range {

	template <typename T>
	class iterator
	{
	public:
		using value_type = T;
		using size_type = size_t;
	private:
		size_type cursor_;
		const value_type step_;
		value_type value_;
	public:
		iterator(size_type cur_start, value_type begin_val, value_type step_val)
			: cursor_(cur_start)
			, step_(step_val)
			, value_(begin_val)
		{
			value_ += step_ * cursor_;
		}

		value_type operator*() const { return value_; }
		bool operator !=(const iterator& rhs) const { return cursor_ != rhs.cursor_; }
		iterator& operator++(void)
		{
			value_ += step_;
			++cursor_;
			return *this;
		}
	};

	template <typename T>
	class impl
	{
	public:
		using value_type = T;
		using reference = value_type&;
		using const_reference = const value_type&;
		using iterator = detail_range::iterator<value_type>;
		using const_iterator = const detail_range::iterator<value_type>;
		using size_type = typename iterator::size_type;

	private:
		const value_type begin_;
		const value_type end_;
		const value_type step_;
		const size_type max_count_;

		// calculate the max iteration count
		size_type get_adjusted_count() const
		{
			if (step_ > 0 && begin_ >= end_)
				throw std::logic_error("End value must be greator than the begin value.");
			else if (step_ < 0 && begin_ <= end_)
				throw std::logic_error("End value must be smaller than the begin value.");
			size_type x = static_cast<size_type>((end_ - begin_) / step_);
			if (begin_ + step_ * x != end_)
				++x;
			return x;
		}

	public:
		impl(value_type begin_val, value_type end_val, value_type step_val)
			: begin_(begin_val)
			, end_(end_val)
			, step_(step_val)
			, max_count_(get_adjusted_count())
		{}

		// to support the new 'for(:)' loop in c++11
		size_type size() const { return max_count_; }
		const_iterator begin() const { return { 0, begin_, step_ }; }
		const_iterator end() const { return { max_count_, end_, step_ }; }
	};
}

/// wrapper function to make client call easier.
template <typename T>
detail_range::impl<T> range(T end)
{
	if (end >= 0)
		return { {}, end, 1 };
	else
		return { {}, end, -1 };
}

template <typename T>
detail_range::impl<T> range(T begin, T end)
{
	if (begin <= end)
		return { begin, end, 1 };
	else
		return { begin, end, -1 };
}

/// note the usage of decltype(begin+step). This is to allow client to use the 
/// case like 'range(1, 5, 0.2)'. The 'begin' and 'end' are integer type, but
/// the step is allowed to be a float number, so the return type should be float as well.
template <typename T, typename U>
auto range(T begin, T end, U step)->detail_range::impl<decltype(begin + step)>
{
	using r_t = detail_range::impl<decltype(begin + step)>;
	return r_t(begin, end, step);
}

