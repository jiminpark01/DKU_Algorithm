#include <stdio.h>
#include <stdlib.h>		//rand() 함수 이용
#include <time.h>		//time(), 수행시간

#define MAX 100 //500, 1000, 5000, 10000

//교환
void swap(int arr[], int a, int b) {
	int tmp;
	tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}

//힙 만들기
void heapify(int arr[], int n, int i) {
	int parent = i;		//부모 노드
	int L = 2 * i + 1;	//왼쪽 자식노드
	int R = 2 * i + 2;	//오른쪽 자식노드

	//왼쪽 자식 노드 존재 여부 체크, 부모 노드와 값 비교
	if (L < n && arr[parent] < arr[L])	//왼쪽 자식노드가 부모보다 클 경우
		parent = L;
	//오른쪽 자식 노드 존재 여부 체크, 부모 노드와 값 비교
	if (R < n && arr[parent] < arr[R])
		parent = R;
	//왼쪽이나 오른쪽 자식 노드 중 부모 노드보다 큰 값이 존재하는 경우
	if (i != parent) {
		swap(arr, parent, i);
		heapify(arr, n, parent);	//초기 부모 노드가 맨 끝 노드를 찾아갈 때까지 내려감
	}
}
void heap_sort(int arr[]) {
	//최대 힙 구성
	for (int i = (MAX / 2) - 1; i >= 0; i--)
		heapify(arr, MAX, i);

	for (int i = MAX - 1; i >= 0; i--) {
		if (arr[0] > arr[i]) {
			swap(arr, 0, i);	//가장 큰 값을 맨 뒤로 보냄(최상단, 최하단 교체)
			heapify(arr, i, 0);	//힙으로 만듦
		}
	}
}


int main() {
	int i;
	double start, end;
	int arr[MAX];

	//난수 생성
	srand(time(NULL));
	for (int i = 0; i < MAX; i++) {
		arr[i] = rand() % MAX;
	}

	//시작 시간
	start = (double)clock() / CLOCKS_PER_SEC;

	//정렬
	heap_sort(arr);

	//끝난 시간
	end = (((double)clock()) / CLOCKS_PER_SEC);

	printf("------------------Heap Sort-------------------\n");
	for (i = 0; i < MAX; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n프로그램 수행시간: %lf\n", end - start);
	return 0;
}