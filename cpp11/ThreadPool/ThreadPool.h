#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include "SyncQueue.h"

class ThreadPool
{
public:
	using Task = std::function<void()>;
	ThreadPool(size_t numThreads = std::thread::hardware_concurrency());
	~ThreadPool();

	void stop();
	void addTask(const Task& task);
	void addTask(Task&& task);
	
private:
	void start(int numThreads);
	void runInThread();
	void stopThreads();
private:
	std::list<std::shared_ptr<std::thread>> m_threads;
	SyncQueue<Task> m_tasks;
	std::atomic_bool m_running;
	std::once_flag m_once;
};

