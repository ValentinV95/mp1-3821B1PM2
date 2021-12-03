#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "malloc.h"
#include "math.h"
#include "selection_sort.h"
#include "radix_sort.h"
#include "merge_sort.h"
#include "comb_sorts.h"



int main()
{
	int choice;
	for (;;)
	{
		printf("You must choose which sorting you will use (just put the number):\n\n(1)Selection sort\n(2)Combination sort\n(3)Merge sort\n(4)Radix sort\n\n(0)exit program\n\n\n");
		scanf_s("%d", &choice);
		if (choice == 1)
		{
			c_selection_sort();
		}
		if (choice == 2)
		{
			c_comb_sort();
		}
		if (choice == 3)
		{
			c_merge_sort();
		}
		if (choice == 4)
		{
			c_radix_sort();
		}
		if (choice == 0)
		{
			break;
		}
	}

}