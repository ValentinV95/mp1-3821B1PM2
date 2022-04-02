#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef float(*function)(float, int, float);
enum fun {
	sinx = 1, cosx, expx, ln
};
enum fun f;


void first(float x, int choice_func, float* mas) {
	if (choice_func == sinx) {
		mas[0] = x;
	}
	if (choice_func == cosx) {
		mas[0] = 1;
	}
	if (choice_func == expx) {
		mas[0] = 1;
	}
	if (choice_func == ln) {
		mas[0] = x;
	}
}

float next_member_sin(float prev, int i, float x) {
	return (prev * (-1) * x * x) / (2 * (float)i * (2 * (float)i + 1));
}


float next_member_cos(float prev, int i, float x) {
	return (prev * (-1) * x * x) / (2 * (float)i * (2 * (float)i - 1));
}


float next_member_exp(float prev, int i, float x) {
	return (prev * x) / ((float)i);
}


float next_member_ln(float prev, int i, float x) {
	return (prev * (-1) * x * i) / ((float)i + 1);
}


void summf(float* mas, int n, float* summ_pr, float* summ_obrat, float* summ_twice) {

	int i, k = 0;

	for (i = 0; i < n; i++) {       //pryamaya
		*summ_pr = *summ_pr + mas[i];
	}

	for (i = n - 1; i >= 0; i--) {    //obratnaya
		*summ_obrat = *summ_obrat + mas[i];
	}

	for (i = 0, k = 0; i < n - 1; i = i + 2, k++) {     //poparnaya
		mas[k] = mas[i] + mas[i + 1];
	}
	for (k = n / 2 - 1; k >= 0; k--) {
		*summ_twice = *summ_twice + mas[k];
	}
}

void create_mas(float* mas, float x, int n, function next) {
	int i;
	for (i = 1; i < n; i++)
		mas[i] = next(mas[i - 1], i, x);
}

int main() {
	float* mas;
	int n = 100;
	int i = 0;
	enum f choice;
	float x = 0, summ_pr = 0, summ_obrat = 0, summ_twice = 0;
	mas = (float*)malloc(n * sizeof(float));

	printf("enter the number of series:\n1 - sinx\n2 - cosx\n3 - e(x)\n4 - ln(1+x):\n");
	scanf_s("%d", &choice);
	printf("enter x: ");
	scanf_s("%f", &x);

	first(x, choice, mas);

	if (choice == sinx) {
		create_mas(mas, x, n, next_member_sin);
		summf(mas, n, &summ_pr, &summ_obrat, &summ_twice);
		printf("direct summ = %.8f\nsumm backwards = %.8f\npairwise summ = %.8f\n", summ_pr, summ_obrat, summ_twice);
		printf("standart function sinx = %.8f\n", sinf(x));

		printf("relative error = %.8f%%\n", fabsf(((summ_pr - sinf(x)) / summ_pr) * 100.f));
		printf("relative error = %.8f%%\n", fabsf(((summ_obrat - sinf(x)) / summ_obrat) * 100.f));
		printf("relative error = %.8f%%\n", fabsf(((summ_twice - sinf(x)) / summ_twice) * 100.f));

		printf("absolute error = %.8f\n", fabsf(summ_pr - sinf(x)));
		printf("absolute error = %.8f\n", fabsf(summ_obrat - sinf(x)));
		printf("absolute error = %.8f\n", fabsf(summ_twice - sinf(x)));

	}
	if (choice == cosx) {
		create_mas(mas, x, n, next_member_cos);
		summf(mas, n, &summ_pr, &summ_obrat, &summ_twice);
		printf("direct summ = %.8f\nsumm backwards = %.8f\npairwise summ = %.8f\n", summ_pr, summ_obrat, summ_twice);
		printf("standart function cosx = %.8f\n", cosf(x));

		printf("relative error = %.8f%%\n", fabsf(((summ_pr - cosf(x)) / summ_pr) * 100.f));
		printf("relative error = %.8f%%\n", fabsf(((summ_obrat - cosf(x)) / summ_obrat) * 100.f));
		printf("relative error = %.8f%%\n", fabsf(((summ_twice - cosf(x)) / summ_twice) * 100.f));

		printf("absolute error = %.8f\n", fabsf(summ_pr - cosf(x)));
		printf("absolute error = %.8f\n", fabsf(summ_obrat - cosf(x)));
		printf("absolute error = %.8f\n", fabsf(summ_twice - cosf(x)));

	}

	if (choice == expx) {
		create_mas(mas, x, n, next_member_exp);
		summf(mas, n, &summ_pr, &summ_obrat, &summ_twice);
		printf("direct summ = %.8f\nsumm backwards = %.8f\npairwise summ = %.8f\n", summ_pr, summ_obrat, summ_twice);
		printf("standart function exp(x) = %.8f\n", expf(x));

		printf("relative error = %.8f%%\n", fabsf(((summ_pr - expf(x)) / summ_pr) * 100.f));
		printf("relative error = %.8f%%\n", fabsf(((summ_obrat - expf(x)) / summ_obrat) * 100.f));
		printf("relative error = %.8f%%\n", fabsf(((summ_twice - expf(x)) / summ_twice) * 100.f));

		printf("absolute error = %.8f\n", fabsf(summ_pr - expf(x)));
		printf("absolute error = %.8f\n", fabsf(summ_obrat - expf(x)));
		printf("absolute error = % .8f\n", fabsf(summ_twice - expf(x)));

	}

	if (choice == ln) {
		create_mas(mas, x, n, next_member_ln);
		summf(mas, n, &summ_pr, &summ_obrat, &summ_twice);
		printf("direct summ = %.8f\nsumm backwards = %.8f\npairwise summ = %.8f\n", summ_pr, summ_obrat, summ_twice);
		printf("standart function ln(1+x) = %.8f\n", logf(x + 1));

		printf("relative error = %.8f%%\n", fabsf(((summ_pr - logf(x + 1)) / summ_pr) * 100.f));
		printf("relative error = %.8f%%\n", fabsf(((summ_obrat - logf(x + 1)) / summ_obrat) * 100.f));
		printf("relative error = %.8f%%\n", fabsf(((summ_twice - logf(x + 1)) / summ_twice) * 100.f));

		printf("absolute error = %.8f\n", fabsf(summ_pr - logf(x + 1)));
		printf("absolute error = %.8f\n", fabsf(summ_obrat - logf(x + 1)));
		printf("absolute error = %.8f\n", fabsf(summ_twice - logf(x + 1)));

	}
	return 0;
	free(mas);
}