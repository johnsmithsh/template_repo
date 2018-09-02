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

/*改进冒泡排序: 每次外层循环,没有交换发生,说明已经完成排序*/
void BubbleSort2(SqList *L)
{
    int i,j;
    bool bSwaped=true;
    for(i=0; i<L->length && bSwaped; ++i)//bSwaped=false,说明没有发生交换,顺序已经满足要求
    {
        bSwaped=false;
        for(j=L->length-1; j>i; --j)
        {
            if(L->r[j-1] > L->r[j])
            {
                swap(L->r[j-1], L->r[j]);
                bSwaped = true;
            }
        }
    }
}

/*改进冒泡排序: 记录上次交换发生地点,如果本次循环,交换地点没有发现变化,则排序完成*/
void BubbleSort3(SqList *L)
{
    int i,j;
    int lastSwapPos = 0,lastSwapPosTmp=0;//bool bSwaped=true;
    for(i=0; i<L->length ; ++i)//bSwaped=false,说明没有发生交换,顺序已经满足要求
    {
        lastSwapPos =lastSwapPosTmp;
        for(j=L->length-1; j>lastSwapPos; --j)
        {
            if(L->r[j-1] > L->r[j])
            {
                swap(L->r[j-1], L->r[j]);
                lastSwapPosTmp=j;
            }
        }

        if(lastSwapPos ==lastSwapPosTmp)
            break;
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

    BubbleSort3(&L);//BubbleSort2(&L);//BubbleSort(&L);
    printf("冒泡排序:");
    for(int i = 0; i<L.length; ++i)
    {
        printf("%d,", L.r[i]);
    }
    printf("\n");


    return 0;
}
