#pragma once
#include <stdio.h>
#include <math.h>

static double recSum(double (*nextEl)(double x, double pref, int i), double first, double x);

double revSum(double (*nextEl)(double x, double pref, int i), double x);

double straightSum(double (*nextEl)(double x, double pref, int i), double x);

double nextSin(double x, double pref, int i);

double nextCos(double x, double pref, int i);

double nextExp(double x, double pref, int i);

double nextLn(double x, double pref, int i);