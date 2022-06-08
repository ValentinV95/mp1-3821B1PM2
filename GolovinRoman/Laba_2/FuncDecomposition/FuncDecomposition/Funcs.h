#pragma once
#include <stdio.h>
#include <math.h>

//������ � ������ - x
//������ � �������� - 1
//������ � ���������� - 1
//������ � ��������� - x

float revSum(float (*nextEl)(float x, float pref, int i), float first, float x);

static float recSum(float (*nextEl)(float x, float pref, int i), float x, float pref, int i);

//����� ����
float straightSum(float (*nextEl)(float x, float pref, int i), float first, float x);

//����� �������� ���������
float nearbySum(float (*nextEl)(float x, float pref, int i), float first, float x);

float nextSin(float x, float pref, int i);

float nextCos(float x, float pref, int i);

float nextExp(float x, float pref, int i);

float nextLn(float x, float pref, int i);

float absoluteDeviation(float value, double standard);

float relativeDeviation(float value, double standard);