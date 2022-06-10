////우선순위 큐(힙구조) 이용한 다익스트라 알고리즘////
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int num = 5;
int INF = 1000000000;

vector<pair<int, int> > a[7];	
int d[7];	

// 다익스트라
void dijkstra(int start) {
	d[start] = 0;		
	priority_queue<pair<int, int> > pq;	
	pq.push(make_pair(start, 0));
	while (!pq.empty()) {			
		int current = pq.top().first;	
		int dist = -pq.top().second;
		pq.pop();								
		if (d[current] < dist) continue;	
		for (int i = 0; i < a[current].size(); i++) {	
			int next = a[current][i].first;				
			int nextDist = dist + a[current][i].second;	
			if (nextDist < d[next]) {			
				d[next] = nextDist;
				pq.push(make_pair(next, -nextDist));
			}
		}
	}
}

int main(void) {
	for (int i = 1; i <= num; i++) {
		d[i] = INF;				
	}

	// 1번 노드와 연결된 노드까지의 비용
	a[1].push_back(make_pair(2, 3));
	a[1].push_back(make_pair(3, 6));
	a[1].push_back(make_pair(4, 3));

	// 2번 노드와 연결된 노드까지의 비용
	a[2].push_back(make_pair(1, 3));
	a[2].push_back(make_pair(4, 1));
	a[2].push_back(make_pair(5, 4));

	// 3번 노드와 연결된 노드까지의 비용
	a[3].push_back(make_pair(1, 6));
	a[3].push_back(make_pair(4, 1));

	// 4번 노드와 연결된 노드까지의 비용
	a[4].push_back(make_pair(1, 3));
	a[4].push_back(make_pair(2, 1));
	a[4].push_back(make_pair(3, 1));
	a[4].push_back(make_pair(5, 1));

	// 5번 노드와 연결된 노드까지의 비용
	a[5].push_back(make_pair(2, 4));
	a[5].push_back(make_pair(4, 2));


	// 다익스트라 알고리즘 수행
	dijkstra(1);
	printf("Vertex   Distance from Source\n");
	for (int i = 1; i <= num; i++) {
		printf("%d \t\t %d\n", i, d[i]);
	}
}
