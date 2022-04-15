#include <stdio.h>
#include <stdlib.h>		//rand() �Լ� �̿�
#include <time.h>		//time(), ����ð�

#define MAX 100 //500, 1000, 5000, 10000

//��ȯ
void swap(int arr[], int a, int b) {
	int tmp;
	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

//�� �����
void heapify(int arr[], int n, int i) {
	int parent = i;		//�θ� ���
	int L = 2 * i + 1;	//���� �ڽĳ��
	int R = 2 * i + 2;	//������ �ڽĳ��

	//���� �ڽ� ��� ���� ���� üũ, �θ� ���� �� ��
	if (L < n && arr[parent] < arr[L])	//���� �ڽĳ�尡 �θ𺸴� Ŭ ���
		parent = L;
	//������ �ڽ� ��� ���� ���� üũ, �θ� ���� �� ��
	if (R < n && arr[parent] < arr[R])
		parent = R;
	//�����̳� ������ �ڽ� ��� �� �θ� ��庸�� ū ���� �����ϴ� ���
	if (i != parent) {
		swap(arr, parent, i);
		heapify(arr, n, parent);	//�ʱ� �θ� ��尡 �� �� ��带 ã�ư� ������ ������
	}
}
void heap_sort(int arr[]) {
	//�ִ� �� ����
	for (int i = (MAX / 2) - 1; i >= 0; i--)
		heapify(arr, MAX, i);

	for (int i = MAX - 1; i >= 0; i--) {
		if (arr[0] > arr[i]) {
			swap(arr, 0, i);	//���� ū ���� �� �ڷ� ����(�ֻ��, ���ϴ� ��ü)
			heapify(arr, i, 0);	//������ ����
		}
	}
}


int main() {
	int i;
	double start, end;
	int arr[MAX];

	//���� ����
	srand(time(NULL));
	for (int i = 0; i < MAX; i++) {
		arr[i] = rand() % MAX;
	}

	//���� �ð�
	start = (double)clock() / CLOCKS_PER_SEC;

	//����
	heap_sort(arr);

	//���� �ð�
	end = (((double)clock()) / CLOCKS_PER_SEC);

	printf("------------------Heap Sort-------------------\n");
	for (i = 0; i < MAX; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n���α׷� ����ð�: %lf\n", end - start);
	return 0;
}