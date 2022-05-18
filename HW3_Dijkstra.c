////선형탐색을 이용한 다익스트라 알고리즘////
#include <stdio.h>
#include <stdbool.h>

#define NUM 6
#define INF 1000000000

// 전체 그래프 초기화
int a[NUM][NUM] = {
    {0,4,2,INF,INF,INF},
    {4,0,INF,4,5,INF},
    {2,INF,0,INF,4,INF},
    {INF,4,INF,0,INF,1},
    {INF,5,4,INF,0,2},
    {INF,INF,INF,1,2,0},
};

bool v[NUM]; 
int d[NUM]; 

// 최소 거리 갖는 노드 얻기
int getSmallIndex() {
    int min = INF;                     
    int index = 0;                    
    // 가장 최소 거리를 갖는 노드를 반환
    for (int i = 0; i < NUM; i++) {
        if (d[i] < min && !v[i]) {      
            min = d[i];                 
            index = i;                 
        }
    }
    return index;  
}

// 다익스트라 수행(최소비용 구하기)
void dijkstra(int start) {
    for (int i = 0; i < NUM; i++) {
        d[i] = a[start][i];           
    }
    v[start] = true;               
    for (int i = 0; i < NUM - 2; i++) {
        int current = getSmallIndex();  
        v[current] = true;            
        for (int j = 0; j < NUM; j++) {           
            if (!v[j]) {                    
                if (d[current] + a[current][j] < d[j]) {  
                                                          
                    d[j] = d[current] + a[current][j];     
                }
            }
        }
    }
}

int main(void) {
    dijkstra(0);
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < NUM; i++) {
        printf("%d \t\t %d\n", i+1, d[i]);
    }
}
