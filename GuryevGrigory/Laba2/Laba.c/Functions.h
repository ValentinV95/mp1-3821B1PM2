#pragma once
#include <stdio.h>
#include <math.h>

float next_element(char func_type, float x, float prev_element, int i);

float sum(char func_type, float x, float first_element);

static float recursion_sum(char func_type, float prev_elem, float x, int i);

float invers_sum(char func_type, float first_elem, float x);

float pairwise_sum(char func_type, float first_elem, float x);