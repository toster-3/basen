#include <stdio.h>
#include <stdlib.h>
#include "arg.h"

char *argv0;

void usage(int ret)
{
	fprintf(stderr, "Usage: %s [-i NUM] [-o NUM] NUM\n", argv0);
	exit(ret);
}

void err(char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	usage(1);
}

int getbasenint(int c)
{
	/* TODO: range check */

	if (c >= '0' && c <= '9')
		return c - '0';

	return c - 'a' + 10;
}

int getbasenchar(int n)
{
	if (n >= 0 && n <= 9)
		return n + '0';

	return n + 'a' - 10;
}

char *getbasenchars(int n, int base)
{
	char *ret = malloc(sizeof(char) * 64);
	int i = 0;

	if (n >= 0 && n <= 9) {
		ret[0] = (unsigned char)n + '0';
		ret[1] = '\0';
	} else if (n < base) {
		ret[0] = n + 'a' - 10;
		ret[1] = '\0';
	} else {
		int start = 0;
		char tmp;

		do {
			ret[i++] = getbasenchar(n % base);
			n /= base;
		} while (n > 0);
		ret[i] = '\0';
		i--;
		while (start < i) {
			tmp = ret[start];
			ret[start] = ret[i];
			ret[i] = tmp;
			start++;
			i--;
		}
	}

	return ret;
}

int main(int argc, char *argv[])
{
	int ibase = 10, obase = 16;
	char *tofree;

	ARGSTRUCT{
		{ "input", 'i' },
		{ "output", 'o' },
		{ "help", 'h' },
		{ 0, 0 },
	};

	ELONG_ARGBEGIN(usage(1))
	{
	case 'i':
		ibase = (int)strtol(EARGF(usage(1)), NULL, 10);
		break;
	case 'o':
		obase = (int)strtol(EARGF(usage(1)), NULL, 10);
		break;
	case 'h':
		usage(0);
	default:
		usage(1);
	}
	ARGEND

	switch (argc) {
	case 0:
		fprintf(stderr, "Error: provide an argument\n");
		usage(1);
		break;
	case 1:
		break;
	case 2:
		ibase = (int)strtol(*argv++, NULL, 10);
		break;
	case 3:
		ibase = (int)strtol(*argv++, NULL, 10);
		obase = (int)strtol(*argv++, NULL, 10);
		break;
	default:
		break;
	}

	printf("%s\n",
	       tofree = getbasenchars(strtol(*argv, NULL, ibase), obase));
	free(tofree);
	return 0;
}
