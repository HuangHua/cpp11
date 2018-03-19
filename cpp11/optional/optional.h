#pragma once

#include <stdexcept>
#include <type_traits>

template <typename T>
class Optional
{
	using data_t = typename std::aligned_storage<sizeof(T), std::alignment_of<T>::value>::type;
public:
	Optional() {}
	Optional(const T& v) {
		Create(v); // create object vi()a internal placement new.
	}
	Optional(const Optional& rhs) {
		if (rhs.IsInit())
			Assign(rhs);
	}
	~Optional()
	{
		Destroy();
	}

	template <typename... Args>
	void Emplace(Args&&... args)
	{
		Destroy();
		Create(std::forward<Args>(args)...);
	}

	bool IsInit() const { return m_hasInit; }

	explicit operator bool() const
	{
		return IsInit();
	}

	T const& operator*() const
	{
		if(IsInit())
			return *((T*)(&m_data));
		throw std::logic_error("is not init");
	}
	Optional<T>& operator=(const Optional<T>& rhs)
	{
		if (&rhs != this && rhs.IsInit())
			Assign(rhs);
		return *this;
	}

private:
	template<typename... Args>
	void Create(Args&&... args)
	{
		new (&m_data)T(std::forward<Args>(args)...);
		m_hasInit = true;
	}

	void Destroy()
	{
		if (m_hasInit)
		{
			m_hasInit = false;
			((T*)(&m_data))->~T();
		}
	}

	void Assign(const Optional& rhs)
	{
		Destroy();
		if (rhs.IsInit())
		{
			new (&m_data) T(*((T*)(&rhs.m_data)));
			m_hasInit = true;
		}
	}

private:
	bool m_hasInit = false;
	data_t m_data;
};