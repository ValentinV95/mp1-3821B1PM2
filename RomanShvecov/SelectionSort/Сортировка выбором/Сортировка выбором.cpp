// Сортировка выбором.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <stdio.h>
#include <stdlib.h>


  void main()
{
	const int N = 5;
	float array[] = { -5.342345 , -5.342341 , -5.342348 , -5.34234 , -5.342343 };
	float tmp = 0.0;

	for (int i = 0; i < N; i++)
	{
		
	}

	 for (int i = 0; i < N - 1; i++)
	 {
		 int min_idx = i;
		 for (int j = i+1.0; j < N; j++)
		 {
			 if (array[j] < array[min_idx])
			 {
				 min_idx = j;
			 }

		 }
		 if (i != min_idx)
		 {
			 tmp = array[i];
			 array[i] = array[min_idx];
			 array[min_idx] = tmp;
		 }
	 }
	 for (int i = 0; i < N; i++)
		 printf("%f\n", array[i]);
	 
	 

}