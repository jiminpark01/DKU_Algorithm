#include <stdio.h>
#include <stdlib.h>		//rand() 함수 이용
#include <time.h>		//time(), 수행시간

#define MAX 100 //100, 500, 1000, 5000, 10000

void quick_sort(int arr[], int left, int right) {
    int L = left, R = right;                // L은 가장 왼쪽, R은 가장 오른쪽
    int pivot = arr[(left + right) / 2];    // pivot 설정 (중간값) 
    int tmp;

    while (L <= R) {        //pivot 값을 넘지 않는 동안. left가 right 보다 왼쪽에 있는 동안 반복
        while (arr[L] < pivot)    // L이 pivot보다 큰 값을 만나거나 pivot을 만날 때까지 L 증가시키기
            L++;
        while (arr[R] > pivot)    // R이 pivot보다 작은 값을 만나거나 pivot을 만날 때까지 R 감소시키기
            R--;

        if (L <= R) {    // 찾은 두 원소 교환 
            if (L != R) {
                tmp = arr[L];
                arr[L] = arr[R];
                arr[R] = tmp;
            }
            //L는 오른쪽으로, R는 왼쪽으로 한칸씩 이동
            L++;
            R--;
        }
    }

    //재귀함수 호출
    if (left < R)
        quick_sort(arr, left, R);    // 왼쪽 배열 재귀적으로 반복 

    if (L < right)
        quick_sort(arr, L, right);    // 오른쪽 배열 재귀적으로 반복
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
    quick_sort(arr, 0, MAX - 1);

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