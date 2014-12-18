#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <assert.h>

static int sqrti0(int val) // sqrt for int
{
	int i;
	if (val <= 1) return val;	// 0, 1: special
	for (i = 0; i <= val / 2; i++) {
		if (i * i > val) break;
	}
	return (val <= i * (i - 1)) ? i - 1 : i;
}

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
static int sqrti2(int val)
{
	int i, maxi;
	if (val <= 0) return 0;
	maxi = val / 2;
	for (i = 1; i <= maxi; i <<= 1) {
		if (i * i > val) break;
	}
	return bsearch_sqrt(val, i >> 1, i);
}

int main(int argc, char* argv[])
{
	int i;
	for (i = 0; i < INT_MAX; i++) {
		int d = sqrti2(i);
		float f = sqrtf(i);
		assert(abs(f - d) <= 0.5);
		printf("%d\t%d\t%.2f\n", i, d, f);
	}
	return 0;
}
