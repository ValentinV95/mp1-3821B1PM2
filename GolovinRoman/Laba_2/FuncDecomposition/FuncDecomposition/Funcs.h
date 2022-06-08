#pragma once
#include <stdio.h>
#include <math.h>

//Первый у синуса - x
//Первый у косинуса - 1
//Первый у экспоненты - 1
//Первый у логорифма - x

float revSum(float (*nextEl)(float x, float pref, int i), float first, float x);

static float recSum(float (*nextEl)(float x, float pref, int i), float x, float pref, int i);

//Сумма влоб
float straightSum(float (*nextEl)(float x, float pref, int i), float first, float x);

//Сумма соседних элементов
float nearbySum(float (*nextEl)(float x, float pref, int i), float first, float x);

float nextSin(float x, float pref, int i);

float nextCos(float x, float pref, int i);

float nextExp(float x, float pref, int i);

float nextLn(float x, float pref, int i);

float absoluteDeviation(float value, double standard);

float relativeDeviation(float value, double standard);