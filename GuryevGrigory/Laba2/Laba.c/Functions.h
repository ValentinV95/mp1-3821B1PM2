#pragma once
#include <stdio.h>
#include <math.h>

double next_element(char func_type, double x, double prev_element, int i);

double sum(char func_type, double x, double first_element);

static double recursion_sum(char func_type, double prev_elem, double x, int i);

double invers_sum(char func_type, double first_elem, double x);

double pairwise_sum(char func_type, double first_elem, double x);