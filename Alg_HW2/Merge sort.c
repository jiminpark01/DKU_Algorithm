#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100 //500, 1000, 5000, 10000


//병합하는 부분
void merge(int arr[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = left;
	int tmp[MAX];
	while (i <= mid && j <= right) {		//왼쪽 원소 합치기
		if (arr[i] <= arr[j]) tmp[k++] = arr[i++];
		else tmp[k++] = arr[j++];
	}
	while (i <= mid) tmp[k++] = arr[i++];	//중간 원소 합치기
	while (j <= right) tmp[k++] = arr[j++];	//오른쪽 원소 합치기
	for (int a = left; a <= right; a++)arr[a] = tmp[a];
}

void merge_sort(int arr[], int left, int right) {
	int mid;
	
	if (left < right) {
		mid = (left + right) / 2;

		//재귀적 호출
		merge_sort(arr, left, mid);			//배열의 왼쪽 원소들을 쪼개면서 정렬
		merge_sort(arr, mid + 1, right);	//배열의 오른쪽 원소들을 쪼개면서 정렬
		merge(arr, left, mid, right);		//쪼갠 원소들 병합
	}
}



int main() {
	int i;
	int arr[MAX];
	double start, end;

	//난수 생성
	srand(time(NULL));
	for (i = 0; i < MAX; i++) {
		arr[i] = rand() % MAX;
	}

	//시작 시간
	start = (double)clock() / CLOCKS_PER_SEC;

	//정렬
	merge_sort(arr, 0, MAX-1);

	//끝난 시간
	end = (((double)clock()) / CLOCKS_PER_SEC);

	printf("------------------Merge Sort-------------------\n");
	for (i = 0; i < MAX; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n프로그램 수행시간: %lf\n", end - start);
	return 0;
}
