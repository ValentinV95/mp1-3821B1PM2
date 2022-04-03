# include <math.h>
# include <stdio.h>
# include <cfloat>
double tau = 6.283185307179586,f;
int choise = 1, n = 1;

FILE * rs = fopen("/home/home/Code/mp1-3821B1PM2/Trofimov_Vadim/2.Function/size.txt","w"); FILE * ab = fopen("/home/home/Code/mp1-3821B1PM2/Trofimov_Vadim/2.Function/abs.txt","w");FILE * rel = fopen("/home/home/Code/mp1-3821B1PM2/Trofimov_Vadim/2.Function/relative.txt","w");

//функции суммирования ряда. На вход принимает длину и указатель на
//первый элемент массива. Сумма помещается в первый элемент массива.
//Сложность линейная
void dir(int n, float* a){
    int i;
    for(i=1;i<n;++i)
        a[0]+=a[i];
}
void rev(int n, float* a){
    for(;n>0;--n)
        a[n-1]+=a[n];
}
void cross(int n, float* a){
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
float pix(){
    float* a = (float*)malloc(504 * sizeof(float));
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
float sinx(float x){
    float* a = NULL;
    float d,res;
    int n = 1;
    res = fmod(x,tau);
    a = (float*)malloc(n * sizeof(float));
    a[0] = res;
    for(;abs(a[n-1]) > FLT_MIN;++n){
        d = 4 * n * n + 2* n;
		a[n] =((-1)*a[n - 1]*res*res)/d;
        a = (float*)realloc(a,(n+2) * sizeof(float));
    }
    fprintf(rs,"%0.1f ; %d\n",x,n);
//    printf("Select a type of sum\n1.Dirrect\n2.Reverse\n3.Cross\n");
//    scanf("%d",&choise);
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

float cosx(float x){
    float* a = NULL;
    float d,res;
    int n = 1;

    res = fmod(x,12*pix());
    a = (float*)malloc(n * sizeof(float));
    a[0] = 1;
    for(;abs(a[n-1]) > FLT_MIN;++n){
        d = 4 * n * n - 2* n;
		a[n] =((-1)*a[n - 1]*res*res)/d;
        a = (float*)realloc(a,(n+2) * sizeof(float));
    }
    fprintf(rs,"%0.1f ; %d\n",x,n);
//    printf("Select a type of sum\n1.Dirrect\n2.Reverse\n3.Cross\n");
//    scanf("%d",&choise);
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
float sinxcosx(float x){
    int a = floor(x/(3*pix())+0.5), sw=1;
    float res;
    int n = 1;

//    printf("1.sin\n2.cos\n");
//    scanf("%d",&sw);
    res = x - 3*a*pix();
    a%=4;
    if (a<0){
        a+=4;
        a%=4;
    }
    switch(sw){
        case 1:
            if(a ==1)
                res=cosx(res);
            else if(a==3)
                res=-cosx(res);
            else if(a==2)
                res=-sinx(res);
            else
                res=sinx(res);
                //printf("sin(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n",sin(x),res,abs(sin(x)-res),abs(1-res/sin(x)));
            fprintf(rs,"%0.1f ; %d\n",x,n);fprintf(ab,"%0.2lf ; %20.17lf\n",f,abs(res-sin(x))); fprintf(rel,"%0.2lf ; %20.17lf\n",f,abs(1.-res/sin(x)));
            break;
        case 2:
            if(a ==1)
                res=sinx(-res);
            else if(a==3)
                res=sinx(res);
            else if(a==2)
                res=-cosx(res);
            else
                res=cosx(res);
            //    printf("cos(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n",cos(x),res,abs(cos(x)-res),abs(1-res/cos(x)));
            fprintf(rs,"%0.1lf ; %d\n",x,n);fprintf(ab,"%0.2lf ; %20.17lf\n",f,abs(res-cos(x))); fprintf(rel,"%0.2lf ; %20.17lf\n",f,abs(1.-res/cos(x)));
            break;
        default:
            printf("Invalid operation");
            exit(0);
            break;
    }
return(res);
}

float expx(float x){
    float* a = NULL;
    int n = 1;

    a = (float*)malloc(n * sizeof(float));
    a[0] = 1;
    for(; abs(a[n-1])>FLT_MIN&&n<1024;++n){
        a[n] =a[n - 1]*x/n;
        a = (float*)realloc(a,(n+2) * sizeof(float));
    }
    fprintf(rs,"%0.1f ; %d\n",x,n);
//    printf("Select a type of sum\n1.Dirrect\n2.Reverse\n");
//    scanf("%d",&choise);
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
// так как ряд 1+1/2+1/3+...+1/n расходится, нет смысла выделять много памяти на его подсчет
float lnx(float x){
    float* a = NULL;
    float d;
    int n = 1;

    if (x<=0)
        exit(-1);
    a = (float*)malloc(1024 * sizeof(float));
    d = (x-1)/(x+1);
    a[0]=d;
    for(;n < 1024&& abs(a[n-1])>FLT_MIN;++n){
		a[n] =a[n - 1]*d*d*((2.*n-1)/(2*n+1));
        }
        fprintf(rs,"%0.1f ; %d\n",x,n);
//    printf("Select a type of sum\n1.Dirrect\n2.Reverse\n");
//    scanf("%d",&choise);
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
    float x,res;
    if (rs==NULL ||ab==NULL||rel==NULL) exit(0);
    for(;;){
        printf("Select a operation:\n1.sin\n2.cos\n3.sincos\n4.exp\n5.log\n0.exit\n");
        scanf("%d",&variant);
        if(variant==0)
            exit(0);
//        printf("Enter a value\n");
//        scanf("%f",&x);
        switch (variant){
            case 1:
                for(x=-100;x<100;x+=0.2){
                res = sinx(x);
                //printf("sin(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n",sin(x),res,abs(sin(x)-res),abs(1-res/sin(x)));
               fprintf(ab,"%0.1lf ; %20.17lf\n",x,abs(res-sin(x)));fprintf(rel,"%0.1lf ; %20.17lf\n",x,abs(1-res/sin(x)));
                }fclose(rs);fclose(ab),fclose(rel);
                break;
            case 2:
                for (x=-100;x<100;x+=0.2){
                res = cosx(x);
                //printf("cos(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n",cos(x),res,abs(cos(x)-res),abs(1-res/cos(x)));
                fprintf(ab,"%0.1lf ; %20.17lf\n",x,abs(res-cos(x)));fprintf(rel,"%0.1lf ; %20.17lf\n",x,abs(1.-res/cos(x)));
                }fclose(rs);fclose(ab);fclose(rel);
                break;
            case 3:
                for (x=-100;x<100;x+=0.2){
                res = sinxcosx(x);
                }fclose(rs);fclose(ab);fclose(rel);
                break;
            case 4:
                for (x=-13;x<13;x+=0.05){
                f = x;
                res = expx(x);
                //printf("exp(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n",exp(x),res,abs(exp(x)-res),abs(1-res/exp(x)));
                fprintf(ab,"%0.2lf ; %20.17lf\n",f,abs(res-exp(x)));fprintf(rel,"%0.2lf ; %20.17lf\n",f,abs(1.-res/exp(x)));
                }fclose(rs);fclose(ab);fclose(rel);
                break;
            case 5:
                for(x=0.1;x<10000;x+=1){
                f = x;
                res = lnx(x);
                //printf("log(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n",log(x),res,abs(log(x)-res),abs(1-res/log(x)));
                fprintf(ab,"%0.1lf ; %20.17lf\n",f,abs(res-log(x)));fprintf(rel,"%0.1lf ; %20.17lf\n",f,abs(1.-res/log(x)));
                }fclose(rs);fclose(ab);fclose(rel);
                break;
            default :
                printf("Invalid variant\n");
                break;
        }
    }

return(0);
}
