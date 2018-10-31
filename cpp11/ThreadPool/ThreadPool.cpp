#include "stdafx.h"
#include "ThreadPool.h"


ThreadPool::ThreadPool(size_t numThreads)
	: m_tasks(numThreads)
{
	start(numThreads);
}


ThreadPool::~ThreadPool()
{
	stop();
}

void ThreadPool::stop()
{
	std::call_once(m_once, [this]() { stopThreads(); });
}

void ThreadPool::addTask(const Task& task)
{
	m_tasks.put(task);
}

void ThreadPool::addTask(Task&& task)
{
	m_tasks.put(std::forward<Task>(task));
}

void ThreadPool::start(int numThreads)
{
	m_running = true;
	for (auto i = 0; i < numThreads; ++i)
	{
		m_threads.push_back(std::make_shared<std::thread>(&ThreadPool::runInThread, this));
	}
}

void ThreadPool::runInThread()
{
	while (m_running)
	{
#if 0
		std::list<Task> list;
		m_tasks.take(list);
		for (auto& task : list)
		{
			if (!m_running)
				return;
			task();
		}
#else
		Task task;
		m_tasks.take(task);
		if (!m_running)
			return;
		task();
#endif
	}
}

void ThreadPool::stopThreads()
{
	m_tasks.stop();
	m_running = false;
	for (auto& thread : m_threads)
		thread->join();
	m_threads.clear();
}