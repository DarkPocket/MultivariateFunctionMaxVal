#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>



#define X_MAX_NUM  50

#define Pmin 0
#define Pmax 20
const double absError = 0.0001;

int debug = 0;
void douInit(double n[], int m);

double fxCalculate( double X[], int amout ) ; //函数表达式

void  bubble_sort (double a[][X_MAX_NUM], int n);
void xCarry(double X[], int amout );
double adjustmentInterval(   double deltaY, double y );


//进位carry

void douInit(double n[], int m)
{
        int i = 0;
        n[i] = 0;
        for (i = 0; i <= m; i++)
        {
                n[i] = Pmin;
                //     cout << n[i] << endl;
                if (i >= X_MAX_NUM)
                {
                        break;
                }
        }
}

void  bubble_sort (double a[][X_MAX_NUM], int n)
{
        int i, j;
        double  t[10];
        //        cout << " bubble_sort  " << endl;
        printf("  bubble_sort  ");
        int k = 0;
        for (i = 1; i < n; i++)
        {
                for (j = 0; j < n - i; j++)
                {

                        if (a[j][0] < a[j + 1][0])
                        {

                                for (k = 0; k < 10; k++)
                                {
                                        t[k] = a[j][k];
                                }

                                for (k = 0; k < 10; k++)
                                {
                                        a[j][k] = a[j + 1][k];
                                }

                                for (k = 0; k < 10; k++)
                                {
                                        a[j + 1][k] = t[k];
                                }

                        }
                }
        }

}

double fxCalculate( double x[], int amout )
{
        //函数表达式
        int i = 0;
        double y = 0;


        y = -(x[1] - 2) * (x[1] - 2) + 10 - (x[2] - 10) * (x[2] - 10) + 2  - (x[3] - 5) * (x[3] - 5) + 12   - (x[4] - 7) * (x[4] - 7) + 8  ;
        x[0] = y;

        return y;
}

void xCarry(double x[], int amout )
{
        //处理x累加进位的问题
        //从x1开始  ，x0存y值
        int i = 0, j = 0;
        for (i = 1; i <= amout ; i++)
        {
                if ( ( x[i] < Pmin) || (x[i] > Pmax))
                {
                        x[i + 1] = x[i + 1] + absError;
                        for (j = 1; j <= i; j++)
                        {
                                // doubInit(x[i]);
                                x[j] = Pmin;
                        }
                }
        }


}

double adjustmentInterval(   double deltaY, double y)
{
        //调整x累加间隔
        double deltaT = 0;
        double k = 10;
        double a = 0;

        deltaT = k * exp(deltaY / y) * absError;

        if (deltaT < absError)
        {
                deltaT = absError; getchar( );
        }


        if (debug )
        {

                printf("y=%lf deltaY=%lf  deltaT=%lf\n", y, deltaY, deltaT);
        }

        return deltaT;
}


void showArray( double P[], int n)
{
        int i = 0;
        printf("\n   showArray\n");

        printf(" y=%0.9lf " , P[i]);
        for (i = 1; i <= n; i++)
        {
                printf(" P[%d]=%0.6lf ", i, P[i]);

        }

        printf("\n");
}
//interval 间隔
//Multivariate function

double  calculateMultivariateFunction ( FILE * fp  )
{
        int i = 0;
        double  Result[X_MAX_NUM] = {0};
        double x[X_MAX_NUM] = {0};
        //从x1开始  ，x0存y值
        int xAmount = 4;
        // Δ δ delta delt 德尔塔
        double deltaT = absError;
        double tempY = 0, maxY = 0;
        long int times = 0;

        douInit(x, xAmount);

        showArray(x, xAmount);
        maxY = fxCalculate(  x,  xAmount  );


        //   for (; x[xAmount ] < Pmax ; x[1] = x[1] + deltaT)
        for (; x[xAmount + 1] < absError ; x[1] = x[1] + deltaT)
        {
                //控制循环次数

                //x累加进位
                xCarry(  x,  xAmount  );

                //函数计算
                tempY = fxCalculate(  x,  xAmount  );

                if (tempY >= maxY)
                {

                        deltaT = absError;

                        for (i = 0; i <= xAmount; i++)
                        {
                                Result[i] = x[i];
                        }
                        if (times % 10000== 0)
                        {
                              //  printf("  上升 \n");
                                printf("  tempY  \n Result  \n");
                                showArray(Result, xAmount);

                                //  printf("  xx \n");
                                //  showArray(x, xAmount);
                                debug = 1;
                               //  getchar( );
                        }

                        deltaT = adjustmentInterval(  (maxY - tempY), maxY );
                         maxY = tempY;
                        debug = 0;
                  //      getchar( );
                }
                else
                {
                        //   printf("  下降 \n");
                        deltaT = adjustmentInterval(  (maxY - tempY), tempY  );

                }
                //
                times++;

                /*
                //    if ( 2 - Result[1] < absError)
                if ( (2 - x[1] < absError) && ( x[1] - 2 < absError))
                {
                        showArray(Result, xAmount);
                        //    getchar();
                        printf(" 2 - Result[1]   xx \n");
                        showArray(x, xAmount);
                }
                if (times % 1000000 == 0)
                {
                        printf(" Result[1]   xx \n");
                        showArray(x, xAmount);
                        //    getchar();
                }*/
        }



        printf("  fx 最大值 \n Result  \n");
        showArray(Result, xAmount);

        return 0;

        //  absError


}


int test ( )
{
        FILE * fp = NULL;

        calculateMultivariateFunction (  fp  );
        return 0;
}








int main()
{


        test ( );
        printf("Hello world!\n");
        return 0;
}
