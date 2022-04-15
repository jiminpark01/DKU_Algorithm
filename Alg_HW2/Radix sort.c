#include <stdio.h>
#include <stdlib.h>		//rand() �Լ� �̿�
#include <time.h>		//time(), ����ð�

#define MAX 100 //500, 1000, 5000, 10000

void radix_sort(int* arr, int n) {
	int res[MAX], maxValue = 0;
	int exp = 1;
	int i;

	//�ִ밪 ���ϱ�
	for (i = 0; i < n; i++) {
		if (arr[i] > maxValue) maxValue = arr[i];
	}

	//1���ڸ� �� ���� ��
	while (maxValue / exp > 0) {
		int bucket[10] = { 0 };
		for (i = 0; i < n; i++) bucket[arr[i] / exp % 10]++;	//�ش� �ڸ� ���� ��Ŷ ����
		for (i = 1; i < 10; i++) bucket[i] += bucket[i - 1];	//���� �� ��� (��� �迭 ����� ����)
		for (i = n - 1; i >= 0; i--) res[--bucket[arr[i] / exp % 10]] = arr[i];	//���� �ڸ� �������� ���� ����
		for (i = 0; i < n; i++) arr[i] = res[i];
		exp *= 10;  //�ڸ� �� �ø���
	}
}

int main() {
	int arr[MAX];
	int i;
    double start, end;

    //���� ����
    srand(time(NULL));
    for (i = 0; i < MAX; i++) {
        arr[i] = rand() % MAX;
    }

    //���� �ð�
    start = (double)clock() / CLOCKS_PER_SEC;

    //����
    radix_sort(arr, MAX);

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