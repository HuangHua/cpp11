#pragma once
#include <Windows.h>
#include <map>
#include <string>
#include <functional>

class DllParser
{
public:
	DllParser() : m_hMod(nullptr) {}
	~DllParser() {
		unload();
	}

	bool load(const std::string& dllpath)
	{
		m_hMod = LoadLibraryA(dllpath.data());
		return m_hMod != nullptr;
	}
	bool unload()
	{
		if (!m_hMod)
			return true;
		auto b = FreeLibrary(m_hMod);
		if (!b)
			return false;
		m_hMod = nullptr;
		return true;
	}
	template <typename T>
	std::function<T> getFunction(const std::string& funcName)
	{
		auto it = m_map.find(funcName);
		if (it == m_map.end())
		{
			auto addr = GetProcAddress(m_hMod, funcName.c_str());
			if (!addr)
				return nullptr;
			it = m_map.insert(m_map.end(), std::make_pair(funcName, addr));
		}
		return std::function<T>((T*)it->second);
	}
	template <typename T, typename... Args>
	typename std::result_of<std::function<T>(Args...)>::type executeFunction(const std::string& funcname, Args&&... args)
	{
		auto f = getFunction<T>(funcname);
		if (f == nullptr)
		{
			std::string s = "cannot find the function " + funcname;
			throw std::exception(s.c_str());
		}
		return f(std::forward<Args>(args)...);
	}
private:
	HMODULE m_hMod;
	std::map<std::string, FARPROC> m_map;
};