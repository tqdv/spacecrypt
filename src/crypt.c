/*Simple math functions for affine method*/

#define _CRT_SECURE_NO_WARNINGS
#include "crypt.h"

int pgcd(int a, int b) {
	int r;
	while (b != 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int invmod(int a, int b) {
	int r = a, u = 1, v = 0, rp = b, up = 0, vp = 1;
	int q, rs, us, vs;

	if (pgcd(a, b) != 1) {
		printfcolor("&rWarning! #");
		printf("%d and %d are not coprime integers...\n", a, b);
	}

	while (rp != 0) {
		q = r / rp;
		rs = r;
		us = u;
		vs = v;
		r = rp;
		u = up;
		v = vp;
		rp = rs - q * rp;
		up = us - q * up;
		vp = vs - q * vp;
	}

	return mod(u, 26);
}

int mod(int x, int n) {
	while (x < 0 || x >= n) {
		if (x < 0) {
			x += n;
		}
		else if (x >= n) {
			x -= n;
		}
	}
	return x;
}

void fctdecrypt(int* a, int* b) {
	*a = invmod(*a, 26);
	*b = mod(*a * -*b, 26);
}