#include <stdio.h>
#include "sin.h"
#include "cos.h"
#include "exp.h"
#include "ln.h"


int main()
{

	int f = 0;
	printf("select the function:\n\t1 - sin(x)\n\t2 - cos(x)\n\t3 - exp^(x)\n\t4 - ln(1+x)\n");
	scanf_s("%d", &f);

	switch (f)
	{
	case 1:
		sinchoose();
		break;
	case 2:
		coschoose();
		break;
	case 3:
		expchoose();
		break;
	case 4:
		lnchoose();
		break;
	}
	return 0;
}