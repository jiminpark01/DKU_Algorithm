#include <stdio.h>
#include <stdlib.h>		//rand() �Լ� �̿�
#include <time.h>		//time(), ����ð�


void exchange_sort(int count) {
	int tmp;
	int i, j;
	double start, end;

	int* arr = malloc(sizeof(int) * count);	//�����Ҵ�

	//���� ����
	srand(time(NULL));	//������

	for (i = 0; i < count; i++) {	//���� �迭 �����
		arr[i] = rand() % count;
	}

	//���� �ð�
	start = (double)clock() / CLOCKS_PER_SEC;

	//����
	for (i = 0; i < count; i++) {
		for (j = 0; j < count - 1; j++) {
			if (arr[j] > arr[j + 1]) {	//�� ��Ҹ� ���Ͽ� �� ��Ұ� �� ũ�ٸ�
				tmp = arr[j];			//��ȯ
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}

	//���� �ð�
	end = (((double)clock()) / CLOCKS_PER_SEC);

	//���
	printf("Exchange sort (%d) --------------------", count);
	for (i = 0; i < count; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n ���α׷� ����ð�: %lf\n", (end - start));
	printf("\n\n");
	free(arr);	//�����Ҵ� ����
}


int main() {
	//��ȯ����
	exchange_sort(100);
	exchange_sort(500);
	exchange_sort(1000);
	exchange_sort(5000);
	exchange_sort(10000);
}
