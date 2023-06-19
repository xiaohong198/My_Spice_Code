#pragma once
#define FASTPOW FastPow

/*快速幂函数模板*/
template <typename T>
T FastPow(T x, int n)
{
	T result = 1;

	while (n > 0) {
		if (n & 1)
			result *= x;
		x *= x;
		n >>= 1;
	}
	return result;
}