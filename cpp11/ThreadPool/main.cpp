// ThreadPool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ThreadPool.h"
#include <iostream>
#include <sstream>
#include <vector>

int main()
{
	ThreadPool pool;
	std::vector<std::string> m_data;
	m_data.resize(100);
	for (auto i = 0; i < 100; ++i)
	{
		pool.addTask([i, &m_data]() { 
			std::stringstream ss;
			ss << std::this_thread::get_id();
			m_data[i] = ss.str();
		});
	}

	for (auto i = 0; i < m_data.size(); ++i)
		std::cout << i << ": " << m_data[i] << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	getchar();
	pool.stop();
    return 0;
}

