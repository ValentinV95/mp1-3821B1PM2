#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//1 - sinx, 2 - cosx, 3 - e(x), 4 - ln(1+x)
typedef double(*function)(double, int, double);

void first(double x, int choice_func, double* mas) {
	if (choice_func == 1) {
		mas[0] = x;
	}
	if (choice_func == 2) {
		mas[0] = 1;
	}
	if (choice_func == 3) {
		mas[0] = 1;
	}
	if (choice_func == 4) {
		mas[0] = x;
	}
}

double next_member_sin(double prev, int i, double x) {
	return (prev * (-1) * x * x) / (2 * (double)i * (2 * (double)i + 1));
}


double next_member_cos(double prev, int i, double x) {
	return (prev * (-1) * x * x) / (2 * (double)i * (2 * (double)i - 1));
}


double next_member_exp(double prev, int i, double x) {
	return (prev * x) / ((double)i);
}


double next_member_ln(double prev, int i, double x) {
	return (prev * (-1) * x * i) / ((double)i + 1);
}


void summf(double* mas, int n, double * summ_pr, double * summ_obrat, double * summ_twice) {

	int i, k = 0;

	for (i = 0; i < n; i++) {       //pryamaya
		*summ_pr = *summ_pr + mas[i];
	}

	for (i = n - 1; i >= 0; i--) {    //obratnaya
		*summ_obrat = *summ_obrat + mas[i];
	}

	for (; n > 0; n = n / 2) {
		for (i = 0, k = 0; i < n - 1; i = i + 2, k++) {     //poparnaya
			mas[k] = mas[i] + mas[i + 1];
		}
	}
	*summ_twice = mas[k];
	//printf("direct summ = %.16lf\nsumm backwards = %.16lf\npairwise summ = %.16lf\n", summ_pr, summ_obrat, summ_twice);
}

void create_mas(double* mas, double x, int n, function next) {
	int i;
	for (i = 1; i < n; i++)
		mas[i] = next(mas[i - 1], i, x);
}

int main() {
	double* mas;
	int n = 100;
	int i = 0, choice = 0;
	double x = 0, summ_pr = 0, summ_obrat = 0, summ_twice = 0;
	mas = (double*)malloc(n * sizeof(double));

	printf("enter the number of series:\n1 - sinx\n2 - cosx\n3 - e(x)\n4 - ln(1+x):\n");
	scanf_s("%d", &choice);
	printf("enter x: ");
	scanf_s("%lf", &x);

	first(x, choice, mas);

	if (choice == 1) {

		create_mas(mas, x, n, next_member_sin);
		summf(mas, n, &summ_pr, &summ_obrat, &summ_twice);	
		printf("direct summ = %.16lf\nsumm backwards = %.16lf\npairwise summ = %.16lf\n", summ_pr, summ_obrat, summ_twice);
		printf("standart function sinx = %.16lf\n", sin(x));
		
		printf("relative error = %.16lf%%\n", fabs(((summ_pr - sin(x)) / summ_pr) * 100.0));
		printf("relative error = %.16lf%%\n", fabs(((summ_obrat - sin(x)) / summ_obrat) * 100));
		printf("relative error = %.16lf%%\n", fabs(((summ_twice - sin(x)) / summ_twice) * 100));

		printf("absolute error = %.16lf\n", fabs(summ_pr - sin(x)));
		printf("rabsolute error = %.16lf\n", fabs(summ_obrat - sin(x)));
		printf("absolute error = %.16lf\n", fabs(summ_twice - sin(x)));
	}
	if (choice == 2) {

		create_mas(mas, x, n, next_member_cos);
		summf(mas, n, &summ_pr, &summ_obrat, &summ_twice);
		printf("direct summ = %.16lf\nsumm backwards = %.16lf\npairwise summ = %.16lf\n", summ_pr, summ_obrat, summ_twice);
		printf("standart function cosx = %.16lf\n", cos(x));

		printf("relative error = %.16lf%%\n", fabs(((summ_pr - cos(x)) / summ_pr) * 100.0));
		printf("relative error = %.16lf%%\n", fabs(((summ_obrat - cos(x)) / summ_obrat) * 100));
		printf("relative error = %.16lf%%\n", fabs(((summ_twice - cos(x)) / summ_twice) * 100));

		printf("absolute error = %.16lf\n", fabs(summ_pr - cos(x)));
		printf("rabsolute error = %.16lf\n", fabs(summ_obrat - cos(x)));
		printf("absolute error = %.16lf\n", fabs(summ_twice - cos(x)));
	}
	if (choice == 3) {

		create_mas(mas, x, n, next_member_exp);
		summf(mas, n, &summ_pr, &summ_obrat, &summ_twice);
		printf("direct summ = %.16lf\nsumm backwards = %.16lf\npairwise summ = %.16lf\n", summ_pr, summ_obrat, summ_twice);
		printf("standart function exp(x) = %.16lf\n", exp(x));
		
		printf("relative error = %.16lf%%\n", fabs(((summ_pr - exp(x)) / summ_pr) * 100.0));
		printf("relative error = %.16lf%%\n", fabs(((summ_obrat - exp(x)) / summ_obrat) * 100));
		printf("relative error = %.16lf%%\n", fabs(((summ_twice - exp(x)) / summ_twice) * 100));

		printf("absolute error = %.16lf\n", fabs(summ_pr - exp(x)));
		printf("rabsolute error = %.16lf\n", fabs(summ_obrat - exp(x)));
		printf("absolute error = % .16lf\n", fabs(summ_twice - exp(x)));

	}
	if (choice == 4) {

		create_mas(mas, x, n, next_member_ln);
		summf(mas, n, &summ_pr, &summ_obrat, &summ_twice);
		printf("direct summ = %.16lf\nsumm backwards = %.16lf\npairwise summ = %.16lf\n", summ_pr, summ_obrat, summ_twice);
		printf("standart function ln(1+x) = %.16lf\n", log(x+1));

		printf("relative error = %.16lf%%\n", fabs(((summ_pr - log(x+1)) / summ_pr) * 100.0));
		printf("relative error = %.16lf%%\n", fabs(((summ_obrat - log(x+1)) / summ_obrat) * 100));
		printf("relative error = %.16lf%%\n", fabs(((summ_twice - log(x+1)) / summ_twice) * 100));

		printf("absolute error = %.16lf\n", fabs(summ_pr - log(x+1)));
		printf("rabsolute error = %.16lf\n", fabs(summ_obrat - log(x+1)));
		printf("absolute error = %.16lf\n", fabs(summ_twice - log(x+1)));
	}
	return 0;
	free(mas);
}