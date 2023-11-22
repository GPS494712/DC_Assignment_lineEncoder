#include <iostream>

void input_b8zs(int *arr, int size)
{
    int count = 0;
    int v = 2;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 1)
            count = 0;
        if (arr[i] == 0)
            count++;
        if (count == 8)
        {
            arr[i - count + 1] = 0;
            arr[i - count + 2] = 0;
            arr[i - count + 3] = 0;
            arr[i - count + 4] = v;
            arr[i - count + 5] = 1;
            arr[i - count + 6] = 0;
            arr[i - count + 7] = v;
            arr[i - count + 8] = 1;
            count = 0;
        }
    }
}

void input_hdb3(int *arr, int size)
{
    int count1 = 0;
    int count0 = 0;
    int v = 2;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 1)
        {
            count0 = 0;
            count1++;
        }
        if (arr[i] == 0)
            count0++;

        if (count0 == 4)
        {
            if (count1 % 2 == 0)
            {
                arr[i - count0 + 1] = 1;
                arr[i - count0 + 4] = v;
            }
            if (count1 % 2 == 1)
            {
                arr[i - count0 + 4] = v;
            }
            count0 = 0;
            count1 = 0;
        }
    }
}

