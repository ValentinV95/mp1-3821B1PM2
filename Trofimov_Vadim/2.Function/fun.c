# include <math.h>
# include <stdio.h>
# include <cfloat>
double tau = 6.283185307179586;
int choise = 1;
//функции суммирования ряда. На вход принимает длину и указатель на
//первый элемент массива. Сумма помещается в первый элемент массива.
//Сложность линейная
void dir(int n, double* a){
    int i;
    for(i=1;i<n;++i)
        a[0]+=a[i];
}
void rev(int n, double* a){
    for(;n>0;--n)
        a[n-1]+=a[n];
}
void cross(int n, double* a){
    int i=1;
    if (n % 2 == 1){
        a[0]+=a[1];
        i++;
    }
    for(;i+2<n;){
        a[i]+=a[i+1];
        a[0]+=a[i];
        i+=2;
    }
}
//функция вычисления числа Пи/6 через ряд Маклорена для арксинуса. Сходится при 504 элементах.
double pix(){
    double* a = (double*)malloc(504 * sizeof(double));
    int n = 1;
    a[0] = 0.5;
    for(;a[n-1] > DBL_MIN;++n){
		a[n] =a[n - 1]*(a[0]*a[0]+(1-6*n)/(2.0*(2*n*n+n))*a[0]*a[0]);
    }
    rev(n,a);
    return(a[0]);
    free(a);
}

//функции вычисления ряда Маклорена. На вход принимает аргумент
//вычисляемой функции(для тригонометрических функций в радианах).
//Внутри себя вызывает функцию суммирования.
double sinx(double x){
    double* a = NULL;
    int n = 1;
    double d;

    a = (double*)malloc(n * sizeof(double));
    x = fmod(x,tau);
    a[0] = x;
    for(;abs(a[n-1]) > DBL_MIN;++n){
        d = 4 * n * n + 2* n;
		a[n] =((-1)*a[n - 1]*x*x)/d;
        a = (double*)realloc(a,(n+2) * sizeof(double));
    }
    printf("number %d",n);
    //printf("Select a type of sum\n1.Dirrect\n2.Reverse\n3.Cross\n");
    //scanf("%d",&choise);
    switch (choise){
        case 1:
            dir(n,a);
            break;
        case 2:
            rev(n,a);
            break;
        case 3:
            cross(n,a);
            break;
        default:
            printf("Invalid operation");
            exit(0);
    }
    return(a[0]);
    free(a);
}

double cosx(double x){
    double* a = NULL;
    int n = 1;
    double d;

    a = (double*)malloc(n * sizeof(double));
    x = fmod(x,tau);
    a[0] = 1;
    for(;abs(a[n-1]) > DBL_MIN;++n){
        d = 4 * n * n - 2* n;
		a[n] =((-1)*a[n - 1]*x*x)/d;
        a = (double*)realloc(a,(n+2) * sizeof(double));
    }
    printf("number %d",n);
    //printf("Select a type of sum\n1.Dirrect\n2.Reverse\n3.Cross\n");
    //scanf("%d",&choise);
    switch (choise){
        case 1:
            dir(n,a);
            break;
        case 2:
            rev(n,a);
            break;
        case 3:
            cross(n,a);
            break;
        default:
            printf("Invalid operation");
            exit(0);
    }return(a[0]);
    free(a);
}

//функция, подсчета тригонометрических функций путем формул приведения. Работает за меньшее кол-во элементов, но требует больше проверок
double sinxcosx(double x){
    int a = floor(x/(3*pix())+0.5),n;
    double res;
    printf("1.sin\n2.cos\n");
    scanf("%d",&n);
    res = x - 3*a*pix();
    a%=4;
    if (a<0){
        a+=4;
        a%=4;
    }
    switch(n){
        case 1:
            if(a ==1)
                res=cosx(res);
            else if(a==3)
                res=-cos(res);
            else if(a==2)
                res=-sinx(res);
            else
                res=sinx(res);
            printf("res = %.16lf\nsin = %.16lf\nabs err=%.16lf\nrel err=%.16lf\n",res,sin(x),abs(res-sin(x)),abs(1.-res/sin(x)));
            break;
        case 2:
            if(a ==1)
                res=sinx(res);
            else if(a==3)
                res=-sin(res);
            else if(a==2)
                res=-cosx(res);
            else
                res=cosx(res);
            printf("res = %.16lf\ncos = %.16lf\nabs err=%.16lf\nrel err=%.16lf\n",res,cos(x),abs(res-cos(x)),abs(1.-res/cos(x)));
            break;
        default:
            printf("Invalid operation");
            exit(0);
            break;
    }
return(res);
}

double expx(double x){
    double* a = NULL;
    int n = 1;

    a = (double*)malloc(n * sizeof(double));
    a[0] = 1;
    for(; abs(a[n-1])>DBL_MIN&&n<1024;++n){
        a[n] =a[n - 1]*x/n;
        a = (double*)realloc(a,(n+2) * sizeof(double));
    }
    printf("number %d",n);
    //printf("Select a type of sum\n1.Dirrect\n2.Reverse\n");
    //scanf("%d",&choise);
    switch (choise){
        case 1:
            dir(n,a);
            break;
        case 2:
            rev(n,a);
            break;
        default:
            printf("Invalid operation");
            exit(0);
    }
    return(a[0]);
    free(a);
}

double lnx(double x){
    double* a = NULL;
    int n = 1;
    double d;

    if (x<=0)
        exit(-1);
    if (x==1)
        return (0);
    a = (double*)malloc(n * sizeof(double));
    d = (x-1)/(x+1);
    a[0]=d;
    for(;n < 1024&& abs(a[n-1])>DBL_MIN;++n){
		a[n] =a[n - 1]*d*d*((2.*n-1)/(2*n+1));
        a = (double*)realloc(a,(n+2) * sizeof(double));
    }
    printf("number %d",n);
    //printf("Select a type of sum\n1.Dirrect\n2.Reverse\n");
    //scanf("%d",&choise);
    switch (choise){
        case 1:
            dir(n,a);
            break;
        case 2:
            rev(n,a);
            break;
        default:
            printf("Invalid operation");
            exit(0);
    }
    return(2*a[0]);
    free(a);
}

int main(){
    int variant;
    double x,res;
    FILE * rs = fopen("/home/home/Code/2.Function/result.txt","w");FILE * rf = fopen("/home/home/Code/2.Function/reference.txt","w");FILE * ab = fopen("/home/home/Code/2.Function/abs.txt","w");FILE * rel = fopen("/home/home/Code/2.Function/relative.txt","w");
    if (rs==NULL|| rf==NULL|| ab==NULL||rel==NULL) exit(0);
    for(;;){
        printf("Select a operation:\n1.sin\n2.cos\n3.sincos\n4.exp\n5.log\n0.exit\n");
        scanf("%d",&variant);
        if(variant==0)
            exit(0);
        printf("Enter a value\n");
        scanf("%lf",&x);
        switch (variant){
            case 1:
                for(x=-10;x<10;x+=0.1){
                res = sinx(x);
                fprintf(rs,"%.1lf %.16lf\n",x,res);fprintf(rf,"%.1lf %.16lf\n",x,sin(x));fprintf(ab,"(%.1lf) (%.16lf)\n",x,abs(res-sin(x)));fprintf(rel,"%.1lf %.16lf\n",x,abs(1-sinx(x)/sin(x)));
                }fclose(rs),fclose(rf),fclose(ab),fclose(rel);
                //printf("res = %.16lf\nsin = %.16lf\nabs err=%.16lf\nrel err=%.16lf\n",res,sin(x),abs(res-sin(x)),abs(1.-res/sin(x)));
                break;
            case 2:
                res = cosx(x);
                printf("res = %.16lf\ncos = %.16lf\nabs err=%.16lf\nrel err=%.16lf\n",res,cos(x),abs(res-cos(x)),abs(1.-res/cos(x)));
                break;
            case 3:
                res = sinxcosx(x);
                break;
            case 4:
                res = expx(x);
                printf("res = %.16lf\nexp = %.16lf\nabs err=%.16lf\nrel err=%.16lf\n",res,exp(x),abs(res-exp(x)),abs(1.-res/exp(x)));
                break;
            case 5:
                res = lnx(x);
                printf("res = %.16lf\nlog = %.16lf\nabs err=%.16lf\nrel err=%.16lf\n",res,log(x),abs(res-log(x)),abs(1.-res/log(x)));
                break;
            default :
                printf("Invalid variant\n");
                break;
        }
    }

return(0);
}
