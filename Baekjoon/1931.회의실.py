'''
문제
한 개의 회의실이 있는데 이를 사용하고자 하는 N개의 회의들에 대하여 회의실 사용표를 만들려고 한다.
각 회의 I에 대해 시작시간과 끝나는 시간이 주어져 있고, 각 회의가 겹치지 않게 하면서 회의실을 사용할 수 있는 최대수의 회의를 찾아라.
단, 회의는 한번 시작하면 중간에 중단될 수 없으며 한 회의가 끝나는 것과 동시에 다음 회의가 시작될 수 있다.
회의의 시작시간과 끝나는 시간이 같을 수도 있다. 이 경우에는 시작하자마자 끝나는 것으로 생각하면 된다.

입력
첫째 줄에 회의의 수 N(1 ≤ N ≤ 100,000)이 주어진다.
둘째 줄부터 N+1 줄까지 각 회의의 정보가 주어지는데 이것은 공백을 사이에 두고 회의의 시작시간과 끝나는 시간이 주어진다.
시작 시간과 끝나는 시간은 231-1보다 작거나 같은 자연수 또는 0이다.

출력
첫째 줄에 최대 사용할 수 있는 회의 수를 출력하여라.

예제 입력 1
11
1 4
3 5
0 6
5 7
3 8
5 9
6 10
8 11
8 12
2 13
12 14

예제 출력 1
4

힌트
(1,4), (5,7), (8,11), (12,14) 를 이용할 수 있다.
'''

N = int(input())
meetings = []
for _ in range(N):
    meetings.append([int(x) for x in input().split()])
meetings = sorted(meetings, key=lambda lst:lst[1]-lst[0])

answer = 1
times = [t for t in range(meetings[0][0],meetings[0][1])]

for i in range(1,len(meetings)):
    push = True
    tempTimes = [i for i in range(meetings[i][0], meetings[i][1])]
    for t in tempTimes:
        if t in times:
            push = False
            continue

    if push:
        times += tempTimes
        answer += 1
print(answer)

