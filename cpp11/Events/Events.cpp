// Events.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "event.h"
#include <iostream>

int main()
{
	Event<std::function<void(int, int)>> myevent;
	auto key = myevent.connect([](int a, int b) { std::cout << "Simple function: " << a << ", " << b << std::endl; });

	struct A {
		void print(int a, int b) { std::cout << "Method of struct: " << a << ", " << b << std::endl; }
	};
	A a;
	myevent.connect(std::bind(&A::print, a, std::placeholders::_1, std::placeholders::_2));

	myevent.notify(1, 2);
	myevent.disconnect(key);
	myevent.notify(3, 4);
    return 0;
}

