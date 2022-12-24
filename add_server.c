/* RPC Example: Add two numbers - SERVER*/

#include "add.h"

int *add_1_svc(intpair *argp, struct svc_req *rqstp)
{
	static int result;

	result = argp->a + argp->b;
	printf("Add: %d, %d = %d\n", argp->a, argp->b, result);

	return &result;
}
