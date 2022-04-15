#include <stdio.h>
#include <stdlib.h>		//rand() 함수 이용
#include <time.h>		//time(), 수행시간


void exchange_sort(int count) {
	int tmp;
	int i, j;
	double start, end;

	int* arr = malloc(sizeof(int) * count);	//동적할당

	//난수 생성
	srand(time(NULL));	//무작위

	for (i = 0; i < count; i++) {	//랜덤 배열 만들기
		arr[i] = rand() % count;
	}

	//시작 시간
	start = (double)clock() / CLOCKS_PER_SEC;

	//정렬
	for (i = 0; i < count; i++) {
		for (j = 0; j < count - 1; j++) {
			if (arr[j] > arr[j + 1]) {	//두 요소를 비교하여 앞 요소가 더 크다면
				tmp = arr[j];			//교환
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}

	//끝난 시간
	end = (((double)clock()) / CLOCKS_PER_SEC);

	//출력
	printf("Exchange sort (%d) --------------------", count);
	for (i = 0; i < count; i++) {
		if (i % 10 == 0)
			printf("\n");
		printf("%5d ", arr[i]);
	}
	printf("\n 프로그램 수행시간: %lf\n", (end - start));
	printf("\n\n");
	free(arr);	//동적할당 해제
}


int main() {
	//교환정렬
	exchange_sort(100);
	exchange_sort(500);
	exchange_sort(1000);
	exchange_sort(5000);
	exchange_sort(10000);
}
