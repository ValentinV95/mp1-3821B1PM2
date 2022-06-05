#include"Functions.h"
#include <windows.h>



void main()
{

	setlocale(LC_ALL, "Rus");

	int choice = 4;

	int work = 1;

	float badX, x;

	int x1, i = 1;

	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	/* ����������� ������ */	float errorFactSin, errorFactCos, errorFactExp, errorFactLn;		 float recursiveErrorFactSin, recursiveErrorFactCos, recursiveErrorFactExp, recursiveErrorFactLn;				float pairErrorFactSin, pairErrorFactCos, pairErrorFactExp, pairErrorFactLn;
	/* ���������� ������ */		float errorAbsSin, errorAbsCos, errorAbsExp, errorAbsLn;			 float recursiveErrorAbsSin, recursiveErrorAbsCos, recursiveErrorAbsExp, recursiveErrorAbsLn;					float pairErrorAbsSin, pairErrorAbsCos, pairErrorAbsExp, pairErrorAbsLn;
	//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



	while (work == 1)
	{

		printf("\n\n [��������!!!] ��-�� �������� ������ ������ ������������� ������� � <������������� �����> ");
		printf("\n\n      ������� x = ");
		scanf_s("%f", &x);


		system("cls");

		badX = x;
		float strangeX = x;



		//--------
		x = x_period(x);
		//--------



		

		float rsinx, rcosx, rlnx, rexpx, psinx, pcosx, plnx, pexpx;

		float PredElLn = badX, PredElSin = x, PredElCos = 1, PredElExp = 1, expx = 1, cosx = 1, sinx = x, lnx = badX;

		//----------------------------------------------------------

		float Array_for_sin[100];
		float Array_for_cos[100];
		float Array_for_exp[100];
		float Array_for_ln[100];


		Array_for_sin[0] = PredElSin;   //������ ������� sin
		Array_for_cos[0] = PredElCos;   //������ ������� cos
		Array_for_exp[0] = PredElExp;   //������ ������� exp
		Array_for_ln[0] = PredElLn;     //������ ������� ln

	//----------------------------------------------------------

		for (i = 1; i < 100; i++)
		{
			if (i % 2 == 0) x1 = 1;
			else x1 = -1;

			PredElSin = next_element_sin(PredElSin, x, i);
			PredElCos = next_element_cos(PredElCos, x, i);
			PredElExp = next_element_exp(PredElExp, badX, i);
			PredElLn = next_element_lnx(PredElLn, badX, i);

			Array_for_sin[i] = x1 * PredElSin;
			Array_for_cos[i] = x1 * PredElCos;
			Array_for_exp[i] = PredElExp;
			Array_for_ln[i] = x1 * PredElLn;
		}





		sinx = direct_summ(Array_for_sin);
		cosx = direct_summ(Array_for_cos);
		expx = direct_summ(Array_for_exp);
		lnx = direct_summ(Array_for_ln);

		rsinx = reverse_summ(Array_for_sin);
		rcosx = reverse_summ(Array_for_cos);
		rexpx = reverse_summ(Array_for_exp);
		rlnx = reverse_summ(Array_for_ln);

		psinx = pair_summ(Array_for_sin);
		pcosx = pair_summ(Array_for_cos);
		pexpx = pair_summ(Array_for_exp);
		plnx = pair_summ(Array_for_ln);





		//--------------------- ����� ������ -----------------------

		errorFactSin = ((sin(strangeX) - sinx) / sin(strangeX)) * 100;
		errorAbsSin = sinx - sin(strangeX);
		if (errorFactSin < 0) { errorFactSin *= (-1); }



		errorFactCos = ((cos(strangeX) - cosx) / cos(strangeX)) * 100;
		errorAbsCos = cosx - cos(strangeX);
		if (errorFactCos < 0) { errorFactCos *= (-1); }


		errorFactExp = ((exp(strangeX) - expx) / exp(strangeX)) * 100;
		errorAbsExp = expx - exp(strangeX);
		if (errorFactExp < 0) { errorFactExp *= (-1); }


		errorFactLn = ((log(strangeX + 1) - lnx) / log(strangeX + 1)) * 100;
		errorAbsLn = lnx - log(strangeX + 1);
		if (errorFactLn < 0) { errorFactLn *= (-1); }

		//-------------| 

		recursiveErrorFactSin = ((sin(strangeX) - rsinx) / sin(strangeX)) * 100;
		recursiveErrorAbsSin = rsinx - sin(strangeX);
		if (recursiveErrorFactSin < 0) { recursiveErrorFactSin *= (-1); }



		recursiveErrorFactCos = ((cos(strangeX) - rcosx) / cos(strangeX)) * 100;
		recursiveErrorAbsCos = rcosx - cos(strangeX);
		if (recursiveErrorFactCos < 0) { recursiveErrorFactCos *= (-1); }


		recursiveErrorFactExp = ((exp(strangeX) - rexpx) / exp(strangeX)) * 100;
		recursiveErrorAbsExp = rexpx - exp(strangeX);
		if (recursiveErrorFactExp < 0) { recursiveErrorFactExp *= (-1); }


		recursiveErrorFactLn = ((log(strangeX + 1) - rlnx) / log(strangeX + 1)) * 100;
		recursiveErrorAbsLn = rlnx - log(strangeX + 1);
		if (recursiveErrorFactLn < 0) { recursiveErrorFactLn *= (-1); }

		//-------------| 

		pairErrorFactSin = ((sin(strangeX) - psinx) / sin(strangeX)) * 100;
		pairErrorAbsSin = psinx - sin(strangeX);
		if (pairErrorFactSin < 0) { pairErrorFactSin *= (-1); }



		pairErrorFactCos = ((cos(strangeX) - pcosx) / cos(strangeX)) * 100;
		pairErrorAbsCos = pcosx - cos(strangeX);
		if (pairErrorFactCos < 0) { pairErrorFactCos *= (-1); }


		pairErrorFactExp = ((exp(strangeX) - pexpx) / exp(strangeX)) * 100;
		pairErrorAbsExp = pexpx - exp(strangeX);
		if (pairErrorFactExp < 0) { pairErrorFactExp *= (-1); }


		pairErrorFactLn = ((log(strangeX + 1) - plnx) / log(strangeX + 1)) * 100;
		pairErrorAbsLn = plnx - log(strangeX + 1);
		if (pairErrorFactLn < 0) { pairErrorFactLn *= (-1); }


		//-------------------------------------------------------------------------------



		printf("\n ��� x = %f\n\n----------- [ ����� ������� ������������ ] -------------------------", badX);
		printf("\n");
		printf("\n");
		printf(" ������������ sinx = %f         ��������� sinx = %f \n", sinx, sin(strangeX));
		printf(" ( ����������� ������ = %f <        ���������� ������ = %.8f )\n", errorFactSin, errorAbsSin);
		printf("\n");
		printf(" ������������ cosx = %f          ��������� cosx = %f \n", cosx, cos(strangeX));
		printf(" ( ����������� ������ = %f <         ���������� ������ = %.8f )\n", errorFactCos, errorAbsCos);
		printf("\n");
		printf(" ������������ expx = %f          ��������� expx = %f \n", expx, exp(strangeX));
		printf(" ( ����������� ������ = %f <         ���������� ������ = %.8f )\n", errorFactExp, errorAbsExp);
		printf("\n");
		printf(" ������������ ln(1+x)= %f          ��������� ln(1+x)= %f \n", lnx, log(strangeX + 1));
		printf(" ( ����������� ������ = %f <         ���������� ������ = %.8f )\n", errorFactLn, errorAbsLn);
		printf("\n");


		printf("\n----------- [ ����� �������� (�������� ������������)] -------------------------");
		printf("\n");
		printf("\n");
		printf(" ������������ sinx = %f         ��������� sinx = %f \n", rsinx, sin(strangeX));
		printf(" ( ����������� ������ = %f <        ���������� ������ = %.8f )\n", recursiveErrorFactSin, recursiveErrorAbsSin);
		printf("\n");
		printf(" ������������ cosx = %f         ��������� cosx = %f\n", rcosx, cos(strangeX));
		printf(" ( ����������� ������ = %f <         ���������� ������ = %.8f )\n", recursiveErrorFactCos, recursiveErrorAbsCos);
		printf("\n");
		printf(" ������������ expx = %f         ��������� expx = %f\n", rexpx, exp(strangeX));
		printf(" ( ����������� ������ = %f <        ���������� ������ = %.8f )\n", recursiveErrorFactExp, recursiveErrorAbsExp);
		printf("\n");
		printf(" ������������ ln(1+x)= %f         ��������� ln(1+x)= %f \n", rlnx, log(strangeX + 1));
		printf(" ( ����������� ������ = %f <        ���������� ������ = %.8f )\n", recursiveErrorFactLn, recursiveErrorAbsLn);
		printf("\n");



		printf("\n----------- [ ����� ��������� ������������ ] -------------------------");
		printf("\n");
		printf("\n");
		printf(" ������������ sinx = %f         ��������� sinx = %f \n", psinx, sin(strangeX));
		printf(" ( ����������� ������ = %f <         ���������� ������ = %.8f )\n", pairErrorFactSin, pairErrorAbsSin);
		printf("\n");
		printf(" ������������ cosx = %f         ��������� cosx = %f\n", pcosx, cos(strangeX));
		printf(" ( ����������� ������ = %f <         ���������� ������ = %.8f )\n", pairErrorFactCos, pairErrorAbsCos);
		printf("\n");
		printf(" ������������ expx = %f         ��������� expx = %f\n", pexpx, exp(strangeX));
		printf(" ( ����������� ������ = %f <         ���������� ������ = %.8f )\n", pairErrorFactExp, pairErrorAbsExp);
		printf("\n");
		printf(" ������������ ln(1+x)= %f         ��������� ln(1+x)= %f \n", plnx, log(strangeX + 1));
		printf(" ( ����������� ������ = %f <         ���������� ������ = %.8f )\n", pairErrorFactLn, pairErrorAbsLn);
		printf("\n");





	}

	
}