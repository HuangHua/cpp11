#pragma once
#include "Optional.h"
#include <functional>
#include <type_traits>

template <typename T>
class Lazy
{
public:
	template <typename F, typename... Args>
	Lazy(F&& func, Args&&... args)
	{
		m_func = [&func, &args...]{ return func(args...); };
	}
	T& value()
	{
		if (!m_value.IsInit())
		{
			m_value = m_func();
		}
		return *m_value;
	}
	bool isValueCreated() const
	{
		return m_value.IsInit();
	}
private:
	std::function<T()> m_func;
	Optional<T> m_value;
};

template<class F, typename... Args>
Lazy<typename std::result_of<F(Args...)>::type> lazy(F&& func, Args&&... args)
{
	return Lazy<typename std::result_of<F(Args...)>::type>(std::forward<F>(func), std::forward<Args>(args)...);
}