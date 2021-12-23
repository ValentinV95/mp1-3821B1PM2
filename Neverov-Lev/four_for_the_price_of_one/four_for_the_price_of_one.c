#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

unsigned int count = 0;
const int BUBBLE_SORT = 1, QUICK_SORT = 2, MERGE_SORT = 3, RADIX_SORT = 4;

int choose() {
	int choice;
	do {
		printf("Select sort type. Enter one of the following number.\n");
		printf("\t1. bubble sort\n\t2. quick sort\n\t3. merge sort\n\t4. radix sort\n");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);
	return choice;
}

int swap(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
	return 0;
}

int bubble_sort(double* array, int size) {
	bool flag;
	do {
		flag = false;
		for (int j = 0; j < size - 1; ++j) {
			if (array[j] > array[j + 1]) {
				swap(&array[j], &array[j + 1]);
				++count;
				flag = true;
			}
		}
	} while (flag == true);

	return count;
}

int partition(double* array, int left_iterator, int right_iterator) {
	double q = array[right_iterator];
	int i = left_iterator - 1;
	for (int j = left_iterator; j < right_iterator; ++j) {
		if (array[j] <= q) {
			++i;
			swap(&array[i], &array[j]);
			++count;
		}
	}
	swap(&array[i + 1], &array[right_iterator]);
	++count;
	return (i + 1);
}

int quick_sort(double* array, int  left_iterator, int right_iterator) {
	if (left_iterator < right_iterator) {
		int q = partition(array, left_iterator, right_iterator);
		quick_sort(array, left_iterator, q - 1);
		quick_sort(array, q + 1, right_iterator);
	}
	return count;
}


int merge_sort(double* array, int size) {

	if (size > 1) {
		merge_sort(array, size / 2);
		merge_sort(&array[size / 2], size - size / 2);
		double* temp_array = (double*)malloc(size * sizeof(double));
		int left_iterator = 0, right_iterator = 0;;
		for (int i = 0; i < size; ++i) {
			if (array[left_iterator] < array[size / 2 + right_iterator]) {
				temp_array[i] = array[left_iterator++];
				++count;
			}
			else {
				temp_array[i] = array[size / 2 + right_iterator++];
				++count;
			}
			if (left_iterator == size / 2) {
				while (right_iterator < size - size / 2) {
					temp_array[++i] = array[size / 2 + right_iterator++];
					++count;
				}
			}
			else if (right_iterator == size - size / 2) {
				while (left_iterator < size / 2) {
					temp_array[++i] = array[left_iterator++];
					++count;
				}
			}
		}

		for (int i = 0; i < size; i++) {
			array[i] = temp_array[i];
		}
	}
	return count;
}
void create_counters(double* data, long* counters, long N) {
	unsigned char* bp = (unsigned char*)data;
	unsigned char* dataEnd = (unsigned char*)(data + N);
	unsigned short i;
	memset(counters, 0, 256 * sizeof(double) * sizeof(long));
	while (bp != dataEnd) {
		++count;
		for (i = 0; i < sizeof(double); ++i) {
			++count;
			++counters[256 * i + *(bp++)];
		}
	}
}

void radix_pass(short Offset, long N, double* source, double* dest, long* Count) {
	double* sp;
	long s = 0, c, i, * cp = Count;
	unsigned char* bp;
	for (i = 256; i > 0; --i, ++cp) {
		c = *cp;
		*cp = s;
		s += c;
		++count;
	}
	bp = (unsigned char*)source + Offset;
	sp = source;
	for (i = N; i > 0; --i, bp += sizeof(double), ++sp) {
		cp = Count + *bp;
		dest[*cp] = *sp;
		++(*cp);
		++count;
	}
}

void radix_sort(double* data, double* sorted_data, long* counters, long N) {
	long* Count;
	int numNeg = 0, negCount = 0;
	unsigned short i;
	create_counters(data, counters, N);
	for (i = 0; i < sizeof(double); ++i) {
		++count;
		Count = counters + 256 * i;
		radix_pass(i, N, data, sorted_data, Count);
		for (long j = 0; j < N; ++j) {
			++count;
			data[j] = sorted_data[j];
		}
	}
	i = N - 1;
	while (data[i] < 0) {
		sorted_data[negCount++] = data[i--];
		++count;
		++numNeg;
	}

	for (i = 0; i < N - numNeg; ++i) {
		sorted_data[negCount++] = data[i];
		++count;
	}
	for (long j = 0; j < N; ++j) {
		data[j] = sorted_data[j];
		++count;
	}
}


int main() {
	int i, choice;
	int size;
	printf("Enter size of array: ");
	scanf("%d", &size);
	srand(time(NULL));
	double* nums = (double*)malloc(size * sizeof(double));
	printf("Generated array:\n");
	for (i = 0; i < size; ++i) {
		nums[i] = pow((double)(-1.0), rand() % 2) * ((rand() % 1000) + ((rand() % 100000) / 100000.0));
		printf("%f ", nums[i]);
	}
	putchar('\n');
	choice = choose();
	if (choice == BUBBLE_SORT) {
		count = bubble_sort(nums, size);

	}
	else if (choice == QUICK_SORT) {
		count = quick_sort(nums, 0, size);
	}
	else if (choice == MERGE_SORT) {
		count = merge_sort(nums, size);
	}
	else {
		double* temp = (double*)malloc(size * sizeof(double));
		long counters[sizeof(double) * 256];
		long size2 = (long)size;
		radix_sort(nums, temp, counters, size2);
	}
	for (int i = 0; i < size; ++i) {
		printf("%f ", nums[i]);
	}
	putchar('\n');

	for (int i = 0; i < size - 1; ++i) {
		if (nums[i] > nums[i + 1]) {
			printf("ERROR: Array is not sorted");
			break;
		}
	}
	putchar('\n');
	printf("%u permutations were made\n", count);
	return 0;
}
