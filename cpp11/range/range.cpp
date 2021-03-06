// range.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "range.h"
#include <iostream>

int main()
{
	std::cout << "range(-15):";
	for (int i : range(-15))
		std::cout << " " << i;
	std::cout << std::endl;

	std::cout << "range(9, 6):";
	for (int i : range(9, 6))
		std::cout << " " << i;
	std::cout << std::endl;

	std::cout << "range(1):";
	for (int i : range(1))
		std::cout << " " << i;
	std::cout << std::endl;

	std::cout << "range(9, 6, -.3):";
	for (auto i : range(9, 6, -.3))
		std::cout << " " << i;
	std::cout << std::endl;

	std::cout << "range(1, 4, 0.5):";
	for (auto i : range(1, 4, 0.5))
		std::cout << " " << i;
	std::cout << std::endl;
    return 0;
}

