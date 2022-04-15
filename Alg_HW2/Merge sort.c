#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100 //500, 1000, 5000, 10000


//�����ϴ� �κ�
void merge(int arr[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = left;
	int tmp[MAX];
	while (i <= mid && j <= right) {		//���� ���� ��ġ��
		if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];
	}
	while (i <= mid) tmp[k++] = arr[i++];	//�߰� ���� ��ġ��
	while (j <= right) tmp[k++] = arr[j++];	//������ ���� ��ġ��
	for (int a = left; a <= right; a++)arr[a] = tmp[a];
}

void merge_sort(int arr[], int left, int right) {
	int mid;
	
	if (left < right) {
		mid = (left + right) / 2;

		//����� ȣ��
		merge_sort(arr, left, mid);			//�迭�� ���� ���ҵ��� �ɰ��鼭 ����
		merge_sort(arr, mid + 1, right);	//�迭�� ������ ���ҵ��� �ɰ��鼭 ����
		merge(arr, left, mid, right);		//�ɰ� ���ҵ� ����
	}
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
	merge_sort(arr, 0, MAX-1);

	//���� �ð�
	end = (((double)clock()) / CLOCKS_PER_SEC);

	printf("------------------Merge Sort-------------------\n");
	for (i = 0; i < MAX; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n���α׷� ����ð�: %lf\n", end - start);
	return 0;
}
