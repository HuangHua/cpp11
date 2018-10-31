#pragma once

#include <condition_variable>
#include <list>
#include <mutex>
#include <thread>

template <typename T>
class SyncQueue
{
public:
	SyncQueue(size_t maxsize) : m_maxSize(maxsize), m_stopped(false)
	{
	}
	~SyncQueue() {}
	void put(const T& t) { 
		std::unique_lock<std::mutex> lock(m_mutex);
		m_notFull.wait(lock, [this]() { return m_stopped || notFull(); });
		if (m_stopped)
			return;
		m_list.push_back(t);
		m_notEmpty.notify_one();
	}
	void put(T&& t) { 
		std::unique_lock<std::mutex> lock(m_mutex);
		m_notFull.wait(lock, [this]() { return m_stopped || notFull(); });
		if (m_stopped)
			return;
		m_list.push_back(std::forward<T>(t));
		m_notEmpty.notify_one();
	}
	
	void take(T& t)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_notEmpty.wait(lock, [this]() { return m_stopped || notEmpty(); });
		if (m_stopped)
			return;
		t = m_list.front();
		m_list.pop_front();
		m_notFull.notify_one();
	}
	void take(std::list<T>& list)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_notEmpty.wait(lock, [this]() { return m_stopped || notEmpty(); });
		if (m_stopped)
			return;
		list = std::move(m_list);
		m_notFull.notify_one();
	}
	void stop()
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_stopped = true;
		}
		m_notEmpty.notify_all();
		m_notFull.notify_all();
	}
	size_t size() const {
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_list.size();
	}
	bool empty() const {
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_list.empty();
	}
	bool full() const {
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_list.size() == m_maxSize;
	}
private:
	bool notEmpty() const {
		return !m_list.empty();
	}
	bool notFull() const {
		return m_list.size() < m_maxSize;
	}
private:
	size_t m_maxSize;
	std::list<T> m_list;
	std::mutex m_mutex;
	std::condition_variable m_notEmpty;
	std::condition_variable m_notFull;
	bool m_stopped;
};

