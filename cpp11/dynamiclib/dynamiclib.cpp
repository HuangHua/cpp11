// dynamiclib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dllparser.h"
#include <iostream>

int main()
{
	DllParser dllparser;
	dllparser.load("../x64/Debug/MyDll.dll");
	auto sum = dllparser.executeFunction<int(int, int)>("sum", 3, 4);
	std::cout << "sum(a,b) = " << sum << std::endl;
    return 0;
}

