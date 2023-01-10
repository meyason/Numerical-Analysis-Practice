#include <stdio.h>
#include <math.h>

/*
以下の連立一次方程式を、二つの配列vectorAとarrayBに分離し、ガウスの消去法により解析する

2x - 3y + z + 10w = 29.7
8x - y -3z + w = 5.5
x + 2y - 8z + w = -3.7
3x - 9y + 2z + 3w = -2.1

*/

//プロトタイプ宣言
void ArraySet();
void ForwardElimination();
void BackwardSubstitution();

double vectorA[4][4];
double arrayB[4];
double arrayE[4][5];
double answer[4];

int main(void){

    //配列定義
    ArraySet();

    //前進消去
    for(int i = 0; i < 4; i++){
        ForwardElimination(4, i);
    }

    //後退代入
    BackwardSubstitution();

    printf("x:");
    printf("%.2f\n", answer[0]);
    printf("y:");
    printf("%.2f\n", answer[1]);
    printf("z:");
    printf("%.2f\n", answer[2]);
    printf("w:");
    printf("%.2f\n", answer[3]);
    
    return 0;
}

void ArraySet(){
    vectorA[0][0] = 2.00;
    vectorA[0][1] = -3.00;
    vectorA[0][2] = 1.00;
    vectorA[0][3] = 10.00;

    vectorA[1][0] = 8.00;
    vectorA[1][1] = -1.00;
    vectorA[1][2] = -3.00;
    vectorA[1][3] = 1.00;

    vectorA[2][0] = 1.00;
    vectorA[2][1] = 2.00;
    vectorA[2][2] = -8.00;
    vectorA[2][3] = 1.00;

    vectorA[3][0] = 3.00;
    vectorA[3][1] = -9,00;
    vectorA[3][2] = 2.00;
    vectorA[3][3] = 3.00;


    arrayB[0] = 29.70;
    arrayB[1] = 5.50;
    arrayB[2] = -3.70;
    arrayB[3] = -2.10;
}

void ForwardElimination(int n, int k){

    //前進消去したい列k、行列の個数n

    /*
    前進
    */

    //検査対象行を取り出し
    double arrayK[4];
    for(int i = 0; i < 4; i++){
        arrayK[i] = vectorA[k][i];
    }
    double biggestB = arrayB[k];

    //最大値初期化
    double biggestNumber = vectorA[k][k];
    int biggestArrayNumber = k;
  
    //k+1 ~ n番目で検査対象より大きいものの中で、一番大きな数字を選ぶ
    for(int i = k+1; i < n; i++){
        //絶対値で比較
        if(fabsf(biggestNumber) < fabsf(vectorA[i][k])){
            biggestNumber = vectorA[i][k];
            biggestArrayNumber = i;
        }
    }

    //最大値行を取り出し
    double arrayBiggest[3];
    for(int i = 0; i < 4; i++){
        arrayBiggest[i] = vectorA[biggestArrayNumber][i];
    }

    //代入
    for(int i = 0; i < 4; i++){
        //k行目に最大値行代入
        vectorA[k][i] = arrayBiggest[i];
        //検査対象を代入
        vectorA[biggestArrayNumber][i] = arrayK[i];
    }
    arrayB[k] = arrayB[biggestArrayNumber];
    arrayB[biggestArrayNumber] = biggestB;

    /*
    消去
    */
    
    //k行k列目をピボットとする
    double pivot = vectorA[k][k];
    for(int i = k+1; i < n; i++){
        //係数coef
        double coef = (double)vectorA[i][k] / (double)pivot;
        //対象から引く配列
        double arrayCo[4];
        for(int j = 0; j < n; j++){
            arrayCo[j] = vectorA[k][j] * coef;
            vectorA[i][j] = vectorA[i][j] - arrayCo[j];
        }
        arrayB[i] = arrayB[i] - (coef * arrayB[k]);
    }
}

void BackwardSubstitution(){
    for(int i = 0; i < 4; i++){
        int l = 3 - i;
        double pivot = vectorA[l][l];
        if(l != 4){
            for(int j = 0; j < 4 - l; j++){
                int k = 4 - j;
                arrayB[l] = arrayB[l] - (answer[k] * vectorA[l][k]);
            }
        }
        answer[l] = arrayB[l] / pivot;
    }
}