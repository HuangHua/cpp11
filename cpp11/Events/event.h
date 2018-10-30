#pragma once
#include <functional>
#include <map>

class Noncopyable
{
protected:
	Noncopyable() = default;
	virtual ~Noncopyable() = default;
	Noncopyable(const Noncopyable&) = delete;
	Noncopyable& operator=(const Noncopyable&) = delete;
};

template <typename F>
class Event : public Noncopyable
{
public:
	Event() : m_observerId(0) {}
	~Event() {}
	int connect(F&& f) { return assign(std::move(f)); }
	int connect(const F& f) { return assign(f); }
	void disconnect(int key) { m_connections.erase(key); }

	template <typename... Args>
	void notify(Args... args)
	{
		for (auto& cnn : m_connections)
		{
			cnn.second(std::forward<Args>(args)...);
		}
	}
private:
	int assign(F&& f)
	{
		int k = m_observerId++;
		m_connections.emplace(k, std::forward<F>(f));
		return k;
	}
private:
	int m_observerId;
	std::map<int, F> m_connections;
};