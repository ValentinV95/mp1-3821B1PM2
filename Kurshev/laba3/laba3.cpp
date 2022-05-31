#include <iostream>
#include <random>
#include <math.h>

using namespace std;

template <typename T> 
class my_vector
{
private:
    T* arr;
    int size;
    
public:
    my_vector()
    {
        size = 0;
        arr = NULL;
    }

    my_vector(int a)
    {
        size = a;
        arr = new T[size];
    }

    void set_size(int a)
    {
        size = a;
        arr = new T[size];
    }
    
    int get_size() {
        return size;
    }

    T* get_arr() 
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << endl;
        }
        return arr;
    }

    void show_arr()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << endl;
        }
    }

    my_vector(int a, T* m)
    {
        size = a;
        arr = new T[size];
        for (int i = 0; i < a; i++)
        {
            arr[i] = m[i];
        }
    }

    T& operator[](int index)
    {
        return arr[index];
    }

    void operator=(const my_vector<T> &a)
    {
        this->set_size(a.size);
        
        for (int i = 0; i < size; i++)
        {
            arr[i] = a.arr[i];
        }
    }
    
    my_vector(const my_vector<T>& vector)
    {
        size = vector.size;
        if (size != 0)
        {
            arr = new T[size];
            for (int i = 0; i < size; i++)
            {
                arr[i] = vector.arr[i];
            }
        }
        else
        {
            arr = NULL;
        }
    }

    void swap(int a, int b)
    {
        T tmp = NULL;
        tmp = arr[a];
        arr[a] = arr[b];
        arr[b] = tmp;
    }

    T max_element()
    {
        T max_el = abs(arr[0]);
        for (int i = 1; i < size; i++)
        {
            if (abs(arr[i]) > max_el)
            {
                max_el = abs(arr[i]);
            }
        }
        return max_el;
    }
    
    int index(T max_element)
    {
        int index = 0;
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == max_element)
            {
                return i;
            }
        }
    }

    my_vector<T> operator*(T a)
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] = arr[i]*a;
        }
        return *this;
    }

    ~my_vector()
    {
        delete[] arr;
    }
};





template <template <typename > class my_vector ,typename T>
class my_matrix 
{
private:
    int string_size;
    int column_size;
    my_vector<T>* matrix;



public:

    my_matrix()
    {
        string_size = 0;
        column_size = 0;       
    }

    void rematrix(int a, int b)
    {
        string_size = a;
        column_size = b;
        matrix = new my_vector<T>[string_size];
    }

    my_vector<T>& operator[](int index)
    {
        return matrix[index];
    }

    my_matrix(int a, int b)
    {
        string_size = a;
        column_size = b;
        matrix = new my_vector<T>[string_size];
    }
    
    my_matrix(my_vector<T>* vec_mas, int a, int b)
    {
        string_size = a;
        column_size = b;
        matrix = new my_vector<T>[string_size];

        for (int i = 0; i < string_size; i++)
        {
            matrix[i] = vec_mas[i];
        }  
    }

    void swap_string(int a, int b)
    {
        for (int i = 0; i < string_size; i++)
        {
            matrix[i].swap(a, b);
        }
    }

    int get_column_size()
    {
        return column_size;
    }

    int get_string_size()
    {
        return string_size;
    }

    my_vector<T> operator*(my_vector<T> X)
    {
        my_vector<T> res(X.get_size());

        for(int i = 0; i < column_size; i++)
        {
            T sum = 0;
            for (int j = 0; j < string_size; j++)
            {
                sum = sum + matrix[j][i]*X[j];
            }
            res[i] = sum;
        }
        return res;
    }

    void show()
    {
        for (int i = 0; i < column_size; i++)
        {
            for (int j = 0; j < string_size; j++)
            {
                cout << matrix[j][i] << " ";
            }
            cout << "\n";
        }
    }

    T max_element()
    {
        T max_el = matrix[0][0];
        for (int i = 0; i < string_size; i++)
        {
            for (int j = 0; j < column_size; j++)
            {
                if (matrix[i][j] > max_el)
                {
                    max_el = matrix[i][j];
                }
            }
        }
        return max_el;
    }
    
    my_matrix(const my_matrix<my_vector, T>& input_matrix)
    {
        string_size = input_matrix.string_size;
        column_size = input_matrix.column_size;
        if (string_size && column_size)
        {
            matrix = new my_vector<T>[input_matrix.string_size];
            for (int i = 0; i < string_size; i++)
            {
                matrix[i] = input_matrix.matrix[i];
            }
        }
        else
        {
            matrix = NULL;
        }
    }
    void set_column_size(int size)
    {
        column_size = size;
    }

    void set_string_size(int size)
    {
        string_size = size;
    }
    ~my_matrix()
    {
        delete[] matrix;
    }

    void operator=(const my_matrix<my_vector, T> &mat)
    {
        this->set_string_size(mat.string_size);
        this->set_column_size(mat.column_size);
        matrix = new my_vector<T>[string_size];
        for (int i = 0; i < string_size; i++)
        {
            matrix[i] = mat.matrix[i];
        }      
    }
};


template <template <typename> class my_vector,typename T>
class SLAU
{
private:
    my_matrix<my_vector, T> matrix;
    my_matrix<my_vector, T> matrix_copy;
    my_vector<T> res;
    my_vector<T> X;



public:
    SLAU( my_matrix<my_vector, T> input_matrix, my_vector<T> input_vector)
    {
        matrix = input_matrix;
        res = input_vector;
        matrix_copy = input_matrix;
        X.set_size(res.get_size());
    }
    
    SLAU(int size)
    {
        my_vector<T> vec(size);
        matrix.rematrix(size,size);
        res.set_size(size);
        X.set_size(size);
        srand(time(NULL));
        for (int i = 0; i < matrix.get_string_size(); i++)
        {
            for (int j = 0; j < vec.get_size(); j++)
            {
                if (i != j)
                {
                    vec[j] = 0.01 * ((rand() % 100)-50);
                }
                else
                {
                    vec[j] = 10*((rand() % 100)+1);

                }
            }
            res[i] = (rand() % 100)+1;
            matrix[i] = vec;
        }
        matrix_copy = matrix;
    }

    

    void straight()
    {
        double max_element = 0;
        int max_index = 0;
        my_vector<double> vec(4);
        for (int i = 0; i < matrix.get_string_size(); i++)
        {            
            max_element =  matrix[i].max_element();
            max_index = matrix[i].index(max_element);          
            if (max_index >= i)
            {
                matrix.swap_string(max_index, i);
                res.swap(max_index, i);
            }
            else if (max_index < i)
            {
                for (int p = max_index + 1; p< matrix.get_column_size(); p++)
                {
                    max_index = i;
                    if(matrix[i][p]>matrix[i][max_index])
                    {
                        max_index = p;
                    }
                    max_element = matrix[i][max_index];
                    matrix.swap_string(i, max_index);
                    res.swap(max_index, i);
                }
            }          
            vec = matrix[i];
            for (int j = i + 1; j < matrix.get_column_size(); j++)
            {
                for(int k = i; k < matrix.get_string_size(); k++)   
                {         
                   matrix[k][j] = matrix[k][j] -  matrix[k][i]* (vec[j] / ( max_element));
                }
                res[j] = res[j] - res[i] * (vec[j] / (max_element));
            }            
        }   
        cout << "matrix" <<"\n" << endl;
        matrix.show();
        cout << endl;
        cout << "res" <<"\n" << endl;
        res.show_arr();
        cout <<"\n" << endl;
    }
    
    void reverse()
    {
        T sum = 0;        
        X[matrix.get_column_size()-1] = (res[matrix.get_column_size()-1])/(matrix[matrix.get_string_size()-1][ matrix.get_column_size()-1]);       

        for (int i = matrix.get_string_size()-1; i >= 0; i--)
        {           
            sum = (res[i]) / matrix[i][i];
            for (int j = i + 1; j < matrix.get_string_size(); j++)
            {
                sum = sum - ((X[j] * matrix[j][i]) / (matrix[i][i]));
            }
            X[i] = sum;
        }
        cout << "X" <<"\n" << endl;
        X.show_arr();
    }

    void check()
    {
        my_vector<T> res1(X.get_size());
        res1 = matrix_copy * X;
        cout <<"\n" << "res1" <<"\n" << endl;
        res1.show_arr();
    }
    
    my_matrix<my_vector, T> get_matrix()
    {
        return matrix;
    }
    my_vector<T> get_res()
    {
        return res;
    }
    my_vector<T> get_X()
    {
        return X;
    }
    void show_X()
    {
        X.show_arr();
    }
    void show_res()
    {
        res.show_arr();
    }
    void show_matrix()
    {
        matrix.show();
    }
};


int main()
{
    int size;
    cout << "enter matrix size: ";
    cin >> size;
    SLAU<my_vector, double> slau1(size);
    cout << "start matrix" << "\n" << endl;
    slau1.show_matrix();
    cout << " \n" << endl;
    cout << "start res" << endl;
    cout <<endl;
    slau1.show_res();
    cout << "\n" << endl;
    slau1.straight();
    slau1.reverse();
    slau1.check();
}