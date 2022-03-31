#include "Print.h"

// При x>1 или x<-1 ln(1+x) = 0

int main()
{
	int i = 1;
	while (1)
	{
		Choose();
		printf("\n\n\nContinue?\n1)Stop\nelse)Continue\n");
		scanf_s("%d", &i);
		if (i == 1) break;
	}
}
