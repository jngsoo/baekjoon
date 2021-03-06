// baek7576 토마토
/*
문제
철수의 토마토 농장에서는 토마토를 보관하는 큰 창고를 가지고 있다. 토마토는 아래의 그림과 같이 격자 모양 상자의 칸에 하나씩 넣어서 창고에 보관한다. 

창고에 보관되는 토마토들 중에는 잘 익은 것도 있지만, 아직 익지 않은 토마토들도 있을 수 있다. 보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받아 익게 된다. 하나의 토마토의 인접한 곳은 왼쪽, 오른쪽, 앞, 뒤 네 방향에 있는 토마토를 의미한다. 대각선 방향에 있는 토마토들에게는 영향을 주지 못하며, 토마토가 혼자 저절로 익는 경우는 없다고 가정한다. 철수는 창고에 보관된 토마토들이 며칠이 지나면 다 익게 되는지, 그 최소 일수를 알고 싶어 한다.

토마토를 창고에 보관하는 격자모양의 상자들의 크기와 익은 토마토들과 익지 않은 토마토들의 정보가 주어졌을 때, 며칠이 지나면 토마토들이 모두 익는지, 그 최소 일수를 구하는 프로그램을 작성하라. 단, 상자의 일부 칸에는 토마토가 들어있지 않을 수도 있다.

입력
첫 줄에는 상자의 크기를 나타내는 두 정수 M,N이 주어진다. M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다. 단, 2 ≤ M,N ≤ 1,000 이다. 둘째 줄부터는 하나의 상자에 저장된 토마토들의 정보가 주어진다. 즉, 둘째 줄부터 N개의 줄에는 상자에 담긴 토마토의 정보가 주어진다. 하나의 줄에는 상자 가로줄에 들어있는 토마토의 상태가 M개의 정수로 주어진다. 정수 1은 익은 토마토, 정수 0은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다. 

출력
여러분은 토마토가 모두 익을 때까지의 최소 날짜를 출력해야 한다. 만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.

예제 입력 1 
6 4
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 1
예제 출력 1 
8
예제 입력 2 
6 4
0 -1 0 0 0 0
-1 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 1
예제 출력 2 
-1
예제 입력 3 
6 4
1 -1 0 0 0 0
0 -1 0 0 0 0
0 0 0 0 -1 0
0 0 0 0 -1 1
예제 출력 3 
6
예제 입력 4 
5 5
-1 1 0 0 0
0 -1 -1 -1 0
0 -1 -1 -1 0
0 -1 -1 -1 0
0 0 0 0 0
예제 출력 4 
14
예제 입력 5 
2 2
1 -1
-1 1
예제 출력 5 
0
*/

#include <iostream>
#include <queue>

using namespace std;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int tomato[1001][1001];
int day[1001][1001];
int n, m;

void print_day(int m, int n) {
    
    printf("Print day\n");
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++) {
            printf("%d ",day[i][j]);
        }
        printf("\n");
    }
}

int main() {
    
    // 토마토 판 입력받으면서 익/안익 에 따라 day 판 설정
    scanf("%d %d", &m, &n);
    queue<pair<int, int> > q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &tomato[i][j]);
            day[i][j] = -1;               // day의 디폴트값 = -1
            if (tomato[i][j] == 1) {        // 익은 토마토의 칸을 큐에 push, day값 0으로 설정 (0일)
                q.push({i, j});
                day[i][j] = 0;
            }
        }
    }
    
    //BFS
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (tomato[nx][ny] == 0 && day[nx][ny] == -1) {  // 익지 않은 토마토 이면서 방문하지 않은 곳
                    day[nx][ny] = day[x][y] + 1;               // 을 day값 기존 토마토가 익은 곳(전 날 익은 토마토) + 1 (1일 추가)
                    q.push({nx, ny});                              // 해당 구역의 토마토가 익은 상태로 변했으므로 큐에 push
                }
            }
        }
    }
//    print_day(m, n);
    
    // day판 순회하면서 max 값을 result로 (마지막 토마토가 익기까지의 걸리는 날짜)
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result = max(result,day[i][j]);
        }
    }
    
    // tomato판 순회하면서 아직 익지 않고 day판에 방문하지 않은 노드있으면 result = -1 (토마토가 모두 익지 못하는 상황)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (tomato[i][j] == 0 && day[i][j] == -1) {
                result = -1;
            }
        }
    }
    
    cout << result;
}

