#pragma once

#include"Vector.h"

double danger_posability = 0.0000000001; //�������� �� ������� ���������� �������� (����������� ����������)
							  


template<class T>class Matrix : public Vector<Vector<T>>
{
public:



	bool manyXs;

	void set() // ������������ ������ �������� �������
	{
		for (int i = 0; i < this->size; i++)
		{
			if(i==2) cout << "        > ������� �������� ��������� �� " << i + 1 << "-�� ������ \n";
			else cout << "        > ������� �������� ��������� �� " << i + 1 << "-�� ������ \n";
			for (int j = 0; j < this->size; j++)
			{
				cin >> this->array[i].array[j];
			}
		}
		
	}


	Matrix(int n) :Vector<Vector<T>>(n) // ������ ������� �������
	{
		
		for (int i = 0; i < n; i++)
		{
			this->array[i].change_size(n);
		}

		set();


	}


	Matrix(int n,Matrix<T>& M) :Vector<Vector<T>>(n) // ������ ������� ��� ���������, ����������
	{
		
		for (int i = 0; i < n; i++)
		{
			this->array[i].change_size(n);
		}

		for (int i = 0; i < this->size; i++)
			for (int j = 0; j < this->size; j++)
				this->array[i].array[j] = M.array[i].array[j];




	}



		



};


