// optional.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Optional.h"
#include "lazy.h"
#include <string>
#include <iostream>

struct MyStruct
{
	MyStruct() : m_a(0), m_b(0) {}
	MyStruct(int a, int b) : m_a(a), m_b(b) {}
	int m_a;
	int m_b;
};
void TestOptional()
{
	Optional<std::string> a("OK");
	Optional<std::string> b("OK");
	Optional<std::string> c("aa");

	c = a;

	Optional<MyStruct> op;
	op.Emplace(1, 2);
	MyStruct t;
	if (op)
		t = *op;

	op.Emplace(3, 4);
	t = *op;
}

void testLazy()
{
	int y = 4;
	auto lazy1 = lazy([](int x) { return x * 2; }, y);
	std::cout << lazy1.value() << std::endl;

	std::function<int(int)> f = [](int x) { return x + 3; };
	auto lazy2 = lazy(f, 3);
	std::cout << lazy2.value() << std::endl;
}
int main()
{
	TestOptional();
	testLazy();
    return 0;
}

