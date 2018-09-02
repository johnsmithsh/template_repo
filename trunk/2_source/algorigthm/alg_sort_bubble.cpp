#include <string.h>
#include <stdio.h>

/*冒泡排序算法*/

#define MAXSIZE 10
typedef struct{
    int r[MAXSIZE+1];//!<存储要排序的数组
    int length;//!<记录顺序表长度
}SqList;

void swap(int &a, int &b)
{
    int t=a;
    a=b;
    b=t;
}

void BubbleSort(SqList *L)
{
    int i,j;
    for(i=0; i<L->length; ++i)
    {
        for(j=L->length-2; j>=i; --j)
        {
            if(L->r[j] > L->r[j+1])
                swap(L->r[j], L->r[j+1]);
        }
    }
}

/*改进冒泡排序*/
void BubbleSort2(SqList *L)
{
    int i,j;
    bool bSwaped=true;
    for(i=0; i<L->length && bSwaped; ++i)//bSwaped=false,说明没有发生交换,顺序已经满足要求
    {
        for(j=L->length-1; j>i; --j)
        {
            bSwaped=false;
            if(L->r[j-1] > L->r[j])
            {
                swap(L->r[j-1], L->r[j]);
                bSwaped = true;
            }
        }
    }
}


int main(int argc, char **argv)
{
    SqList L;
    L.r[0]=9;
    L.r[1]=1;
    L.r[2]=5;
    L.r[3]=8;
    L.r[4]=3;
    L.r[5]=7;
    L.r[6]=4;
    L.r[7]=6;
    L.r[8]=2;
    L.length = 9;

    BubbleSort2(&L);//BubbleSort(&L);
    printf("冒泡排序:");
    for(int i = 0; i<L.length; ++i)
    {
        printf("%d,", L.r[i]);
    }
    printf("\n");


    return 0;
}
