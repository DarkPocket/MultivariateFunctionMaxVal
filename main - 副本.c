#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>






#define N  50
#define Pmin 1
#define Pmax 6
#define  ValNum   9

int solutionNum = 20; //保留搜索解的个数

double StepNUm = 5;
double absError = 0.000001;

void douInit(double n[]);


void showArray( double P[], int n);

double calculate( double P[], int amout );

void showArrayDimens(double P[N][10],  int n, int amout);
int PartOptimalSearvh(FILE *fp  );
double DetailedSearh( FILE *fp, double PartResult[N][10], double MinStep, int amout  ) ;

void  bubble_sort (double a[][10], int n);
double u(double x[]);
double v(double x[]);




void  bubble_sort (double a[][10], int n)
{
        int i, j;
        double  t[10];
        cout << " bubble_sort  " << endl;
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

double u(double x[])
{
        double y = 0;

        double a, b, c, d, e, f, g, h, j, i;

        a = x[1] ;
        b = x[2] ;
        c = x[3] ;
        d = x[4] ;
        e = x[5] ;
        f = x[6] ;
        g = x[7] ;
        h = x[8] ;
        i = x[9] ;
        y = (13.5 * a * b * c * d * e * f * g * h * i + 3 * a * b * c * d * e * f * g * h - 3.5 * a * b * c * d * e * f * g + 20 * a * b * c * d * e * f - 17 * a * b * c * d * e - 7 * a * b * c * d + 77.5 * a * b * c - 140.5 * a * b - 89.5 * a - 951.5);
        return y;

}

double v(double x[])
{
        double a, b, c, d, e, f, g, h, j, i;
        double y = 0;


        a = x[1] ;
        b = x[2] ;
        c = x[3] ;
        d = x[4] ;
        e = x[5] ;
        f = x[6] ;
        g = x[7] ;
        h = x[8] ;
        i = x[9] ;

        y = (5 * a * b * c * d * e * f * g * h * i + 5 * a * b * c * d * e * f * g * h + 5 * a * b * c * d * e * f * g + 5 * a * b * c * d * e * f + 5 * a * b * c * d * e + 5 * a * b * c * d + 5 * a * b * c + 5 * a * b + 5 * a + 5);
        return y;
}



double DetailedSearh( FILE *fp, double PartResult[N][10], double MinStep, int amout  )
{
        double DetailedResult[N][10] = { 0 };
        double result[N] = { 0 }, P[N] = {0} , temp[N] = {0};
        double yMax = 0, yTemp = 0;
        int i = 0, j = 0, k = 0;
        long long int counts = 0;
        double step = 0;

        cout << "DetailedSearh\n";
        step = MinStep / 10;

        //   MinStep = MinStep / 2;

        yMax = PartResult[i][0];

        cout << " 间隔  " <<     step << "  \n";


        for (j = 0; j < solutionNum; j++)
        {
                cout << " 粗解 " << j << ", 开始详细搜索 \n";
                i = 0;

                P[i] = 0;
                cout << " Y " << i << "= " << PartResult[j][i ]   ;
                for (i = 0; i < amout; i++)
                {
                        if (i > 0)
                        {
                                // P[i] = PartResult[j][i ]  - StepNUm * MinStep;

                                P[i] = PartResult[j][i ]  -  MinStep ;
                        }
                        else
                        {
                                P[i] = 0;
                        }
                        cout << "  X" << i << "= " << PartResult[j][i ]    ;

                        DetailedResult[j][i] = PartResult[j][i ];
                }

                yMax = 0;
                cout << endl;



                i = 0;

                for (; P[amout - 1] < PartResult[j][amout - 1] +  MinStep / 2 ; P[1] = P[1] + step)
                {

                        for (i = 1; i < amout ; i++)
                        {
                                if ((P[i] > PartResult[j][i ] +  MinStep / 2) || ( P[i] < Pmin -  absError) || ( P[i] > Pmax +  absError))
                                {
                                        if (i >= amout - 1)
                                        {
                                                //  P[i] = PartResult[j][i ] - StepNUm * MinStep;
                                                break;
                                        }
                                        else
                                        {
                                                P[i + 1] = P[i + 1] + step;

                                                P[i] = PartResult[j][i ] - MinStep ;
                                                if ( P[i] < Pmin - absError)
                                                {
                                                        P[i] = Pmin;
                                                }
                                        }

                                }
                        }

                        if ( P[amout - 1] > Pmax +  absError)
                        {
                                break;
                        }


                        counts++;
                        yTemp = u(P) / v(P) ;


                        //      cout << "computer u(P) / v(P)  " << yTemp << endl;
                        //      showArray(P, amout);
                        //      getchar();

                        P[0] = yTemp;

                        if (yTemp > yMax  )
                        {
                                yMax = yTemp;

                                //   cout << "computer u(P) / v(P)  " << yTemp << endl;
                                DetailedResult[j][0] = yMax;
                                P[0] = yMax;
                                for (i = 0; i < amout; i++)
                                {
                                        DetailedResult[j][i] = P[i];
                                }




                        }

                }
                cout << " counts = " << counts << endl;
                cout << "computer u(P) / v(P) yMax= " << yMax << endl;
                showArray(DetailedResult[j], amout);

        }

        cout << " all = " << counts << endl;


        //  showArrayDimens(PartResult, N, amout);
        showArrayDimens(DetailedResult, N, amout );

        for (j = 0; j < solutionNum; j++)
        {
                for (i = 0; i < amout ; i++)
                {

                        PartResult[j][i] = DetailedResult[j][i];
                }
        }
        bubble_sort(PartResult, N);


        showArrayDimens(PartResult, 10, amout);


        MinStep = MinStep / 10;
        return MinStep;
}

int PartOptimalSearvh(FILE * fp  )
{


        double x[11] = {0};
        double y = -100000, temp;
        double MinStep = 1;
        int i, j;
        int keyNum = 0;
        int amout = ValNum + 1;
        //amout   10
        double  PartResult[N][10] = {0};
        long long int counts = 0;
        douInit(x);

        cout << " 输入间隔大小 : (0.5)\n";

        cin >> MinStep;


        //   scanf("%d", &amout);



        cout << "x0= " << x[0] << endl;
        showArray(x, amout);


        for (; x[amout - 1] <= Pmax ; x[1] = x[1] + MinStep) //MaxVal
        {
                //控制循环次数
                for (i = 0; i < amout - 1 ; i++)
                {
                        if ( ( x[i] < Pmin) || (x[i] > Pmax))
                        {
                                x[i + 1] = x[i + 1] + MinStep;
                                for (j = 1; j <= i; j++)
                                {
                                        // doubInit(x[i]);
                                        x[j] = Pmin;
                                }
                        }
                }

                //      showArray(x, amout);
                //函数计算


                temp = u(x) / v(x) ;
                if (temp > y)
                {
                        y = temp;
                        PartResult[keyNum][0] = y;
                        for (i = 1; i < amout; i++)
                        {
                                PartResult[keyNum][i] = x[i];
                        }
                        //     cout << "keyNum  " << keyNum << endl;
                        keyNum++;

                        if (keyNum > N - 1)
                        {
                                keyNum = 0;
                        }

                        showArray( PartResult[keyNum], amout);


                }


                counts++;

        }

        bubble_sort(PartResult, N);

        showArrayDimens(PartResult, N, amout);
        cout << "次数  " << counts << endl;
        //   showArray(x, amout);

        int k = 0;
        k = 0;
        do
        {
                fprintf(fp, "  第 %d 轮计算  \n", ++k );
                for  (i = 0; i < amout; i++)
                {
                        for (j = 0; j < amout; j++)
                        {
                                if (j > 0)
                                {
                                        fprintf(fp, " x%d=%lf", j, PartResult[i][j]);
                                }
                                else
                                {
                                        fprintf(fp, " Y=%0.9lf ", PartResult[i][j]);
                                }
                        }
                        fprintf(fp, "\n");
                }



                cout << "第 " << k << "轮计算 " << endl;
                MinStep = DetailedSearh(fp, PartResult, MinStep, amout);
        }
        while (MinStep >  absError );


        return 0;
}

double calculate( double P[], int amout )
{
        int i = 0;
        double y = 0;


        y = u(P) / v(P) ;


        return y;
}


void douInit(double n[])
{
        int i;
        for (i = 0; i <= ValNum; i++)
        {
                n[i] = Pmin;
                //     cout << n[i] << endl;
        }
}





void showArray( double P[], int n)
{
        int i = 0;
        printf("\n   showArray\n");

        printf(" y=%0.9lf " , P[i]);
        for (i = 1; i < n; i++)
        {
                //   printf(" P[%d]=%0.3lf ", i, P[i]);
                //   cout << "x[" << i << "]= " << P[i] << endl;
                cout << "  x[" << i << "]= " << P[i]  ;
        }
        cout << endl;
}

void showArrayDimens(double P[N][10], int n, int amout)
{
        int i, j;
        printf("\n  showArrayDimens\n");

        for (j = 0; j < n; j++)
        {
                if (P[j][0] != 0)
                {

                        for (i = 0; i < amout; i++)
                        {

                                if (i == 0)
                                {
                                        printf("  Y%d=%0.9lf  ", j, P[j][i]);
                                }
                                else
                                {
                                        cout << "  P[" << i << "]= " << P[j][i]  ;
                                        //   printf(" P[%d]=%0.3lf  ", i, P[j][i]);  // [%d]  , j
                                }
                        }
                        printf("\n");
                }
        }
        printf("\n");
}



int  test1( )
{
        FILE *fp;
        char TxtName[PATH_MAX] = {0};
        strcpy(TxtName, "answer.txt");
        if ((fp = fopen(TxtName, "w+")) == NULL)
        {
                printf("%s open error !\n", TxtName);
                getchar();

                return -1;
        }


        PartOptimalSearvh(  fp  );



        if (fclose(fp))
        {
                printf("Can not close the  %s \n", TxtName);
                return -1;
        }
        return 0;


}
int main()
{
        int amout;
        amout = 9;
        int t = 0;
        int i;
        time_t start, finish;
        double mint, sec;
        char TxtName[N * 3] = {0};
        mint = sec = 0;



        printf(" start \n");
        struct timing * timeSTR;

        timeSTR =  Timing_start();


        test1();


        Timing_finish(timeSTR);
        Timing_show(timeSTR);
        Timing_destroy(timeSTR);
        /*
        start = time(NULL);


        finish = time(NULL);
        mint = (int)(finish - start) / 60;
        sec = (finish - start) % 60;


        printf("\n time is %0.lf : %0.1lf seconds\n", mint, sec);*/
        /*
          i = 0;

        amout = 3;
        start = time(NULL);
        fun(amout);
        printf(" %d 台机组\n", amout);
        finish = time(NULL);
        mint = (int)(finish - start) / 60;
        sec = (finish - start) % 60;


        printf("\n time is %0.lf : %0.1lf seconds\n", mint, sec);

                  for (t = 1; t < 7; t++)
                  {


                          start = time(NULL);
                          fprintf(fp, " %d 台机组  P=%0.lf\n", amout, TotalPower( amout, t));
                          PartOptimalSearvh(fp, amout, t );

                          finish = time(NULL);
                          mint = (int)(finish - start) / 60;
                          sec = (finish - start) % 60;


                          printf("\n time is %0.lf : %0.1lf seconds\n", mint, sec);
                          fprintf(fp, "\n time is %0.lf : %0.1lf seconds\n", mint, sec);
                          for (i = 0; i < 60; i++)
                          {
                                  fprintf(fp, "-");
                          }
                          fprintf(fp, "\n");
                          if (amout > 5)
                          {
                                  break ;
                          }
                  }
        */

        /*
                if (fclose(fp))
                {
                        printf("Can not close the  %s \n", TxtName);
                        return -1;
                }
                system("answer.txt");
                //11
        */
        getchar();
        getchar();
        printf("\n over \n ");
        return 0;
}

int test(int amout)
{
        double P[N] = { 0 };
        double bn;
        int i = 0;
        P[0] = 420.3;
        P[1] = 388.9;
        P[2] = 390.8;
        //        bn = calculate(P, amout);

        printf("  bn =%0.9lf \n", bn);

        for (i = 0; i < amout; i++)
        {
                //    result[i] = P[i];
                printf(" P[%d]=%0.3lf ", i, P[i]);

        }
        return 0;
}



int main()
{
    printf("Hello world!\n");
    return 0;
}
