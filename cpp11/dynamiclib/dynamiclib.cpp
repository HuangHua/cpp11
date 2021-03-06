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

	auto mul = dllparser.executeFunction<int(int, int)>("mul", 3, 5);
	std::cout << "mul(a,b) = " << mul << std::endl;

	auto div = dllparser.executeFunction<double(double, double)>("div", 3, 5);
	std::cout << "mul(a,b) = " << div << std::endl;

	auto tol = dllparser.executeFunction<float()>("tolerance");
	std::cout << "tolerance = " << tol << std::endl;
    return 0;
}

