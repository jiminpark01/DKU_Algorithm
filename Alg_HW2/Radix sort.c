#include <stdio.h>
#include <stdlib.h>		//rand() 함수 이용
#include <time.h>		//time(), 수행시간

#define MAX 100 //500, 1000, 5000, 10000

void radix_sort(int* arr, int n) {
	int res[MAX], maxValue = 0;
	int exp = 1;
	int i;

	//최대값 구하기
	for (i = 0; i < n; i++) {
		if (arr[i] > maxValue) maxValue = arr[i];
	}

	//1의자리 수 부터 비교
	while (maxValue / exp > 0) {
		int bucket[10] = { 0 };
		for (i = 0; i < n; i++) bucket[arr[i] / exp % 10]++;	//해당 자리 수의 버킷 증가
		for (i = 1; i < 10; i++) bucket[i] += bucket[i - 1];	//누적 합 계산 (결과 배열 만들기 위해)
		for (i = n - 1; i >= 0; i--) res[--bucket[arr[i] / exp % 10]] = arr[i];	//같은 자리 수끼리는 순서 유지
		for (i = 0; i < n; i++) arr[i] = res[i];
		exp *= 10;  //자리 수 올리기
	}
}

int main() {
	int arr[MAX];
	int i;
    double start, end;

    //난수 생성
    srand(time(NULL));
    for (i = 0; i < MAX; i++) {
        arr[i] = rand() % MAX;
    }

    //시작 시간
    start = (double)clock() / CLOCKS_PER_SEC;

    //정렬
    radix_sort(arr, MAX);

    //끝난 시간
    end = (((double)clock()) / CLOCKS_PER_SEC);

    //출력
    printf("------------------Quick Sort (%d)-------------------\n", MAX);
    for (i = 0; i < MAX; i++) {
        if (i % 10 == 0)
            printf("\n");
        printf("%5d ", arr[i]);
    }
    printf("\n프로그램 수행시간: %lf\n", (end - start));
    return 0;
}