// template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <tuple>

///////////////////////////////////////////////////////////////
template <typename... T>
void f(T... args)
{
	std::cout << sizeof...(args) << std::endl;
}

///////////////////////////////////////////////////////////////
template <typename T>
void print(T t)
{
	std::cout << "parameter " << t << std::endl;
}
template <typename T, typename... Args>
void print(T head, Args... rest)
{
	std::cout << "parameter " << head << std::endl;
	print(rest...);
}

///////////////////////////////////////////////////////////////
template <std::size_t I = 0, typename Tuple>
typename std::enable_if<I == std::tuple_size<Tuple>::value>::type printtp(Tuple t)
{

}
template <std::size_t I = 0, typename Tuple>
typename std::enable_if < I < std::tuple_size<Tuple>::value>::type printtp(Tuple t)
{
	std::cout << std::get<I>(t) << std::endl;
	printtp<I + 1>(t);
}
template <typename... Args>
void print2(Args... args)
{
	printtp(std::make_tuple(args...));
}

///////////////////////////////////////////////////////////////
template <class T>
void printarg(T t)
{
	std::cout << t << std::endl;
}
template <typename... Args>
void expand(Args... args)
{
	//std::initializer_list<int>{ (printarg(args), 0)... };
	std::initializer_list<int>{ ([&] { std::cout << args << std::endl; }(), 0)... };
}

///////////////////////////////////////////////////////////////
template <typename... Args> struct Sum;
template <typename First, typename... Rest>
struct Sum<First, Rest...>
{
	enum { value = Sum<First>::value + Sum<Rest...>::value };
};
template <typename Last>
struct Sum<Last>
{
	enum { value = sizeof(Last) };
};

///////////////////////////////////////////////////////////////
template <int...> struct IndexSeq {};
template <int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};
template <int... Indexes>
struct MakeIndexes<0, Indexes...>
{
	typedef IndexSeq<Indexes...> type;
};
template <int... Indexes, typename... Args>
void print_helper(IndexSeq<Indexes...>, std::tuple<Args...>&& tup)
{
	print(std::get<Indexes>(tup)...);
}
template <typename... Args>
void print(Args... args)
{
	print_helper(typename MakeIndexes<sizeof...(Args)>::type(), std::make_tuple(args...));
}

///////////////////////////////////////////////////////////////
template <typename T, typename... Args>
T* instance(Args... args)
{
	return new T(std::forward<Args>(args)...);
}
struct A
{
	A(int) {}
};
struct B
{
	B(int, double) {}
};
int main()
{
	//f();
	//f(1, 2);
	//f(1, 2.5, "");

	//print(1, 2, 3, 4);

	//print2(1, 2, 3, 4);

	//expand(1, 2, 3, 4);

	//std::cout << Sum<int, double, short>::value << std::endl;

	using T = MakeIndexes<5>::type;
	std::cout << typeid(T).name() << std::endl;
	print(1, 2, 3, 4);

	A* pA = instance<A>(1);
	B* pB = instance<B>(1, 2.0);
    return 0;
}

