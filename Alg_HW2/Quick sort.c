#include <stdio.h>
#include <stdlib.h>		//rand() �Լ� �̿�
#include <time.h>		//time(), ����ð�

#define MAX 100 //100, 500, 1000, 5000, 10000

void quick_sort(int arr[], int left, int right) {
    int L = left, R = right;                // L�� ���� ����, R�� ���� ������
    int pivot = arr[(left + right) / 2];    // pivot ���� (�߰���) 
    int tmp;

    while (L <= R) {        //pivot ���� ���� �ʴ� ����. left�� right ���� ���ʿ� �ִ� ���� �ݺ�
        while (arr[L] < pivot)    // L�� pivot���� ū ���� �����ų� pivot�� ���� ������ L ������Ű��
            L++;
        while (arr[R] > pivot)    // R�� pivot���� ���� ���� �����ų� pivot�� ���� ������ R ���ҽ�Ű��
            R--;

        if (L <= R) {    // ã�� �� ���� ��ȯ 
            if (L != R) {
                tmp = arr[L];
                arr[L] = arr[R];
                arr[R] = tmp;
            }
            //L�� ����������, R�� �������� ��ĭ�� �̵�
            L++;
            R--;
        }
    }

    //����Լ� ȣ��
    if (left < R)
        quick_sort(arr, left, R);    // ���� �迭 ��������� �ݺ� 

    if (L < right)
        quick_sort(arr, L, right);    // ������ �迭 ��������� �ݺ�
}

int main() {
    int i;
    int arr[MAX];
    double start, end;

    //���� ����
    srand(time(NULL));
    for (i = 0; i < MAX; i++) {
        arr[i] = rand() % MAX;
    }

    //���� �ð�
    start = (double)clock() / CLOCKS_PER_SEC;

    //����
    quick_sort(arr, 0, MAX - 1);

    //���� �ð�
    end = (((double)clock()) / CLOCKS_PER_SEC);

    //���
    printf("------------------Quick Sort (%d)-------------------\n", MAX);
    for (i = 0; i < MAX; i++) {
        if (i % 10 == 0)
            printf("\n");
        printf("%5d ", arr[i]);
    }
    printf("\n���α׷� ����ð�: %lf\n", (end - start));
    return 0;
}