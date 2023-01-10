#include <stdio.h>
#include <math.h>

//プロトタイプ宣言
double DifY();
double RungeKutta();

/*
常微分方程式dy/dx = y/2x を、ルンゲクッタ法により解析する
y(1) = 1
1 <= x <= 2
*/


//10等分
int step = 10;
double h = (2.0 - 1.0) / 10.0;

int main(void){

    //初期値
    double x = 1.0;
    double y = 1.0;

    for(int i = 0; i <= step; i++){
        
        printf("y");
        printf("%d", i);
        printf("=");
        printf("%.4f\n", y);
        
        y = RungeKutta(x, y);
        x += h;
    }

    return 0;
}

//導関数計算
double DifY(double x, double y){
    return y / (2.0 * x);
}

//ルンゲクッタ
double RungeKutta(double x, double y){
    
    double k1 = h * DifY(x , y);
    double k2 = h * DifY(x + (h / 2.0), y + (k1 / 2.0));
    double k3 = h * DifY(x + (h / 2.0), y + (k2 / 2.0));
    double k4 = h * DifY(x + h, y + k3);

    double yn = y + (k1 + 2.0*k2 + 2.0*k3 + k4) / 6.0;
    
    return yn;
}