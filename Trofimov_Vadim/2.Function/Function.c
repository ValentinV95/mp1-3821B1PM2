# include <stdio.h>
# include <math.h>
# include <cfloat>
# include <stdlib.h>

enum Fun { EXIT, SIN, COS, SINCOS, EXP, LN }; enum Sum { DIR = 1, REV, CROSS }; enum Sinorcos { SINV = 1, COSV };

//FILE * rs = fopen("/home/home/Code/mp1-3821B1PM2/Trofimov_Vadim/2.Function/size.txt","w"); FILE * ab = fopen("/home/home/Code/mp1-3821B1PM2/Trofimov_Vadim/2.Function/abs.txt","w");FILE * rel = fopen("/home/home/Code/mp1-3821B1PM2/Trofimov_Vadim/2.Function/relative.txt","w");

//функции суммирования ряда. На вход принимает длину и указатель на
//первый элемент массива. Сумма помещается в первый элемент массива.
//Сложность линейная
void dir(int n, float* a) {
    int i;
    for (i = 1; i < n; ++i)
        a[0] += a[i];
}
void rev(int n, float* a) {
    for (; n > 0; --n)
        a[n - 1] += a[n];
}
void cross(int n, float* a) {
    int i = 1;
    if (n % 2 == 1) {
        a[0] += a[1];
        i++;
    }
    for (; i + 2 < n;) {
        a[i] += a[i + 1];
        a[0] += a[i];
        i += 2;
    }
}
//функция вычисления числа Пи/6 через ряд Маклорена для арксинуса.
float pix() {
    float* a = NULL;
    a = (float*)malloc(100 * sizeof(float));
    if (a == NULL) exit(0);
    int n = 1;
    a[0] = 0.5;
    for (; n<100; ++n) {
        a[n] = a[n - 1] * (a[0] * a[0] + (1.f - 6.f * n) / (2.f * (2.f * n * n + n)) * a[0] * a[0]);
    }
    rev(n-1, a);
    return(a[0]);
    free(a);
}

//функции вычисления ряда Маклорена. На вход принимает аргумент
//вычисляемой функции(для тригонометрических функций в радианах).
//Внутри себя вызывает функцию суммирования.
float sinx(double x) {
    float* a = NULL;
    float d, res;
    int n = 1;
    enum Sum sum;

    res = (float)fmod(x, 12 * pix());
    a = (float*)malloc(101 * sizeof(float));
    if (a == NULL) exit(0);
    a[0] = res;
    for (; n<100 && fabs(a[n - 1]) > FLT_MIN; ++n) {
        d = 4 * n * n + 2 * n;
        a[n] = ((-1) * a[n - 1] * res * res) / d;
//        a = (float*)realloc(a, (n + 2) * sizeof(float));
    }
    //    fprintf(rs,"%0.1f ; %d\n",x,n);
    if (n > 1) {
        printf("Select a type of sum\n1.Dirrect\n2.Reverse\n3.Cross\n");
        scanf_s("%d", &sum);
        switch (sum) {
        case DIR:
            dir(n - 1, a);
            break;
        case REV:
            rev(n - 1, a);
            break;
        case CROSS:
            cross(n - 1, a);
            break;
        default:
            printf("Invalid operation");
            exit(0);
        }
    }
    return(a[0]);
}

float cosx(double x) {
    float* a = NULL;
    float d, res;
    int n = 1;
    enum Sum sum;

    res = (float)fmod((float)x, 12 * pix());
    a = (float*)malloc(101 * sizeof(float));
    if (a == NULL) exit(0);
    a[0] = 1;
    for (; n<100 && fabs(a[n - 1]) > FLT_MIN; ++n) {
        d = 4 * n * n - 2 * n;
        a[n] = ((-1) * a[n - 1] * res * res) / d;
//        a = (float*)realloc(a, (n + 2) * sizeof(float));
    }
    //    fprintf(rs,"%0.1f ; %d\n",x,n);
    if (n > 1) {
        printf("Select a type of sum\n1.Dirrect\n2.Reverse\n3.Cross\n");
        scanf_s("%d", &sum);
        switch (sum) {
        case DIR:
            dir(n - 1, a);
            break;
        case REV:
            rev(n - 1, a);
            break;
        case CROSS:
            cross(n - 1, a);
            break;
        default:
            printf("Invalid operation");
            exit(0);
        }
    }
    return(a[0]);
}

//функция, подсчета тригонометрических функций путем формул приведения. Работает за меньшее кол-во элементов, но требует больше проверок
float sinxcosx(double x) {
    int a = (int)floor(x / (3 * pix()) + 0.5);
    float res;
    int n = 1;
    enum Sinorcos sinorcos;

    printf("1.sin\n2.cos\n");
    scanf_s("%d", &sinorcos);
    res = (float)x - 3 * a * pix();
    a %= 4;
    if (a < 0) {
        a += 4;
        a %= 4;
    }
    switch (sinorcos) {
    case SINV:
        if (a == 1)
            res = cosx(res);
        else if (a == 3)
            res = -cosx(res);
        else if (a == 2)
            res = -sinx(res);
        else
            res = sinx(res);
        printf("sin(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n", sin(x), res, fabs(sin(x) - res), fabs(1 - res / sin(x)));
        //fprintf(rs,"%0.1f ; %d\n",x,n);fprintf(ab,"%0.2lf ; %20.17lf\n",f,abs(res-sin(x))); fprintf(rel,"%0.2lf ; %20.17lf\n",f,abs(1.-res/sin(x)));
        break;
    case COSV:
        if (a == 1)
            res = sinx(-res);
        else if (a == 3)
            res = sinx(res);
        else if (a == 2)
            res = -cosx(res);
        else
            res = cosx(res);
        printf("cos(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n", cos(x), res, fabs(cos(x) - res), fabs(1 - res / cos(x)));
        //fprintf(rs,"%0.1lf ; %d\n",x,n);fprintf(ab,"%0.2lf ; %20.17lf\n",f,abs(res-cos(x))); fprintf(rel,"%0.2lf ; %20.17lf\n",f,abs(1.-res/cos(x)));
        break;
    default:
        printf("Invalid operation");
        exit(0);
        break;
    }
    return(res);
}

float expx(double x) {
    float* a = NULL;
    int n = 1;
    enum Sum sum;

    a = (float*)malloc(101 * sizeof(float));
    if (a == NULL) exit(0);
    a[0] = 1.f;
    for (; n < 100 && fabs(a[n - 1]) > FLT_MIN && n < 1024  ; ++n) {
        a[n] = (a[n - 1] * (float)x) / n;
//        a = (float*)realloc(a, (n + 2) * sizeof(float));
    }
    //    fprintf(rs,"%0.1f ; %d\n",x,n);
    if (n > 1) {
        printf("Select a type of sum\n1.Dirrect\n2.Reverse\n");
        scanf_s("%d", &sum);
        switch (sum) {
        case DIR:
            dir(n - 1, a);
            break;
        case REV:
            rev(n - 1, a);
            break;
        default:
            printf("Invalid operation");
            exit(0);
        }
    }
    return(a[0]);
}
// так как ряд 1+1/2+1/3+...+1/n расходится, нет смысла выделять много памяти на его подсчет
float lnx(double x) {
    float* a = NULL;
    float d;
    int n = 1;
    enum Sum sum;

    if (x <= 0)
        exit(-1);
    a = (float*)malloc(1024 * sizeof(float));
    if (a == NULL) exit(0);
    d = ((float)x - 1) / ((float)x + 1);
    a[0] = d;
    for (; n < 1024; ++n) {
        a[n] = a[n - 1] * d * d * ((2.f * n - 1) / (2 * n + 1));
    }
    //        fprintf(rs,"%0.1f ; %d\n",x,n);
    if (n > 1) {
        printf("Select a type of sum\n1.Dirrect\n2.Reverse\n");
        scanf_s("%d", &sum);
        switch (sum) {
        case DIR:
            dir(n - 1, a);
            break;
        case REV:
            rev(n - 1, a);
            break;
        default:
            printf("Invalid operation");
            exit(0);
        }
    }
    return(2 * a[0]);
}

int main() {
    double x;
    float res;
    enum Fun fun;
    //    if (rs==NULL ||ab==NULL||rel==NULL) exit(0);
    for (;;) {
        printf("Select a operation:\n1.sin\n2.cos\n3.sincos\n4.exp\n5.log\n0.exit\n");
        scanf_s("%d", &fun);
        if (fun == EXIT)
            exit(0);
        printf("Enter a value\n");
        scanf_s("%lf", &x);
        switch (fun) {
        case SIN:
            //                for(x=-100;x<100;x+=0.2){
            res = sinx(x);
            printf("sin(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n", sin(x), res, fabs(sin(x) - res), fabs(1 - res / sin(x)));
            //               fprintf(ab,"%0.1lf ; %20.17lf\n",x,abs(res-sin(x)));fprintf(rel,"%0.1lf ; %20.17lf\n",x,abs(1-res/sin(x)));
            //                }fclose(rs);fclose(ab),fclose(rel);
            break;
        case COS:
            //                for (x=-100;x<100;x+=0.2){
            res = cosx(x);
            printf("cos(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n", cos(x), res, fabs(cos(x) - res), fabs(1 - res / cos(x)));
            //                fprintf(ab,"%0.1lf ; %20.17lf\n",x,abs(res-cos(x)));fprintf(rel,"%0.1lf ; %20.17lf\n",x,abs(1.-res/cos(x)));
            //                }fclose(rs);fclose(ab);fclose(rel);
            break;
        case SINCOS:
            //                for (x=-100;x<100;x+=0.2){
            res = sinxcosx(x);
            //                }fclose(rs);fclose(ab);fclose(rel);
            break;
        case EXP:
            //                for (x=-13;x<13;x+=0.05){
            res = expx(x);
            printf("exp(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n", exp(x), res, fabs(exp(x) - res), fabs(1 - res / exp(x)));
            //                fprintf(ab,"%0.2lf ; %20.17lf\n",f,abs(res-exp(x)));fprintf(rel,"%0.2lf ; %20.17lf\n",f,abs(1.-res/exp(x)));
            //                }fclose(rs);fclose(ab);fclose(rel);
            break;
        case LN:
            //                for(x=0.1;x<10000;x+=1){
            res = lnx(x);
            printf("log(x) = %.16lf ~ %.16f ; abs = %.16lf ; rel = %.16lf\n", log(x), res, fabs(log(x) - res), fabs(1 - res / log(x)));
            //                fprintf(ab,"%0.1lf ; %20.17lf\n",f,abs(res-log(x)));fprintf(rel,"%0.1lf ; %20.17lf\n",f,abs(1.-res/log(x)));
            //                }fclose(rs);fclose(ab);fclose(rel);
            break;
        default:
            printf("Invalid variant\n");
            break;
        }
    }

    return(0);
}