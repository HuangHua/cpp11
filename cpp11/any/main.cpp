// any.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Any.h"
#include <assert.h>
#include <vector>

int main()
{
	std::vector<Any> vec;
	vec.push_back(1);
	vec.push_back('a');
	vec.push_back(1.0f);
	vec.push_back(std::string("hello world"));

	assert(vec[0].Is<int>());
	assert(vec[1].Is<char>());
	assert(vec[2].Is<float>());
	assert(vec[3].Is<std::string>());

	int a = vec[0].AnyCast<int>();
	char c = vec[1].AnyCast<char>();
	float d = vec[2].AnyCast<float>();
	std::string s = vec[3].AnyCast<std::string>();

    return 0;

}

