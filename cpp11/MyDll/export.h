#pragma once
#if _MY_DLL_EXPORT_
#define MY_DLL_EXPORT extern "C" __declspec(dllexport)
#else
#define MY_DLL_EXPORT __declspec(dllimport)
#endif
