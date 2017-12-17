// offers some methods to calculate the nearist integer of sqrt(val)
// use it for fun!
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

// 0) iterate through 0 ~ i which i*i > val
static int sqrti0(int val)
{
	int i;
	if (val <= 1) return val;	// 0, 1: special
	for (i = 0; i <= val / 2; i++) {
		if (i * i > val) break;
	}
	return (val <= i * (i - 1)) ? i - 1 : i;
}

// 1) binary search among 0 ~ val / 2
static int bsearch_sqrt(int val, int beg, int end)
{
	while (1) {
		int m1 = (beg + end) / 2;
		int m2 = m1 + 1;
		if (val < m1 * m1) {			// [beg, m1)
			end = m1;
		} else if (val <= m2 * m2) {	// [m1, m2]
			return val <= m1 * m2 ? m1 : m2;
		} else {						// (m2, end]
			beg = m2;
		}
	}
}
static int sqrti1(int val)
{
	int i, maxi;
	if (val <= 0) return 0;
	maxi = val / 2;
	for (i = 1; i <= maxi; i <<= 1) {
		if (i * i > val) break;
	}
	return bsearch_sqrt(val, i >> 1, i);
}

// 2) Newton method, which should be the best, but will overflow on very large value
static int sqrti2(int val)
{
	if (val <= 1) return val;	// 0, 1: special
	int x = val / 2; // initial guess
	while (1) {
	    int dx = (val - x*x) / (2*x);    // dy / dx ~ D(x**2, x) = 2*x, so dx ~ dy / D
	    if (dx == 0) break;
	    x += dx;
	}
	return (val <= x * (x - 1)) ? x - 1 : x;
}

// exam
int main(int argc, char* argv[])
{
	int i;
	for (i = 0; i < INT_MAX; i++) {
		int d = sqrti2(i);
		float f = sqrtf(i);
		printf("%d\t%d\t%.2f\n", i, d, f);
		assert(abs(f - d) <= 0.5);
	}
	return 0;
}
