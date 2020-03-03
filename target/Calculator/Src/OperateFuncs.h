#pragma once
#include <exception>

template<class T>
T add(T x, T y)
{
	return x + y;
}
template<class T>
T sub(T x, T y)
{
	return x - y;
}
template<class T>
T mul(T x, T y)
{
	return x * y;
}
template<class T>
T div(T x, T y)
{
	if (y == 0)
	{
		throw std::exception("The divisor cannot be 0!");
	}
	return x / y;
}