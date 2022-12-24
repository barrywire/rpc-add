/* RPC Example: Add two numbers */
#include <stdio.h>
#include "add.h"


void add_prog_1(char *host, int a, int b)
{
	CLIENT *clnt;
	int *result_1;
	intpair add_1_arg;

#ifndef DEBUG
	clnt = clnt_create(host, ADD_PROG, ADD_VERS, "udp");
	if (clnt == NULL)
	{
		clnt_pcreateerror(host);
		exit(1);
	}

#endif /* DEBUG */

	add_1_arg.a = a;
	add_1_arg.b = b;

	result_1 = add_1(&add_1_arg, clnt);
	if (result_1 == (int *)NULL)
	{
		clnt_perror(clnt, "call failed");
	}
#ifndef DEBUG
	clnt_destroy(clnt);
#endif /* DEBUG */
}

int main(int argc, char *argv[])
{
	char *host;
	int a, b;

	if (argc != 4)
	{
		printf("Usage: %s server_host num1 num2\n", argv[0]);
	}

	host = argv[1];

	if ((a = atoi(argv[2])) == 0 && *argv[2] != '0')
	{
		fprintf(stderr, "invalid value: %s\n", argv[2]);
		exit(1);
	}
	if ((b = atoi(argv[3])) == 0 && *argv[3] != '0')
	{
		fprintf(stderr, "invalid value: %s\n", argv[3]);
		exit(1);
	}
	add_prog_1(host, a, b);

	exit(0);
}
