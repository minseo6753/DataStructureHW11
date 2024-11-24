#include "subway.h"
#include <stack>

MatrixWGraph::MatrixWGraph(int n = 0) :node(n), vertex(0), count(0) {
	length = new int* [n];
	for (int i = 0; i < n; i++) {
		length[i] = new int[n];
		for (int j = 0; j < n; j++) {
			length[i][j] = MAXLEN;
		}
		length[i][i] = 0;
	}
	s = new bool[n]();
	dist = new pair<int,int>[n];
	stlist = new Station[n];
}

void MatrixWGraph::AddVertex(int num1, string name1, int num2, string name2) {
	vertex++;
	Station station1(num1, name1);
	Station station2(num2, name2);

	int p1 = -1; //station1의 인덱스값
	int p2 = -1; //station2의 인덱스값
	for (int i = 0; i < count; i++) {
		if (stlist[i].num == station1.num && stlist[i].name == station1.name) {
			p1 = i;
		}
		if (stlist[i].num == station2.num && stlist[i].name == station2.name) {
			p2 = i;
		}
	}
	if (p1 < 0) {
		p1 = count;
		stlist[count++] = station1;
	}
	if (p2 < 0) {
		p2 = count;
		stlist[count++] = station2;
	}

	if (station1.name == station2.name) { //환승역
		for (int i = 0; i < transfer.size(); i++) {
			if (stlist[transfer[i][0]].name == station1.name) {
				bool b1 = false, b2 = false;
				for (int j = 0; j < transfer[i].size(); j++) {
					if (p1 != transfer[i][j]) {
						length[p1][transfer[i][j]] = length[transfer[i][j]][p1] = 30;
					}
					else b1 = true;
					if (p2 != transfer[i][j]) {
						length[p2][transfer[i][j]] = length[transfer[i][j]][p2] = 30;
					}
					else b2 = true;
				}
				if (!b1) transfer[i].push_back(p1);
				if (!b2) transfer[i].push_back(p2);
				return;
			}
		}
		transfer.push_back({ p1,p2 });
		length[p1][p2] = length[p2][p1] = 30;
	}
	else {
		length[p1][p2] = length[p2][p1] = 60;
	}
	
}

void MatrixWGraph::Dijkstra(int line1, string src, int line2, string dst) {

	int srcnum, dstnum;
	for (int i = 0; i < node; i++) {
		if (stlist[i].num == line1 && stlist[i].name == src) {
			srcnum = i;
		}
		if (stlist[i].num == line2 && stlist[i].name == dst) {
			dstnum = i;
		}
	}

	for (int i = 0; i < node; i++) {
		dist[i] = make_pair(srcnum, length[srcnum][i]);
	}

	s[srcnum] = true;

	for (int i = 0; i < node - 2; i++) { //시작점과 가장 마지막으로 남은 점을 빼고 n-2번 탐색
		
		int temp = dstnum;
		for (int j = 0; j < node; j++) { //다음으로 방문할 노드 선택
			if (!s[j] && dist[j].second < dist[temp].second) {
				temp = j;
			}
		}

		s[temp] = true;
		for (int j = 0; j < node; j++) {
			if (!s[j] && dist[temp].second + length[temp][j] < dist[j].second) {
				dist[j].second = dist[temp].second + length[temp][j];
				dist[j].first = temp;
			}
		}
	}

	PrintRoute(srcnum, dstnum);
}

void MatrixWGraph::PrintRoute(int srcnum, int dstnum) {
	stack<int> iroute;
	iroute.push(dstnum);

	int midnode=dstnum;
	while (iroute.top() != srcnum) {
		iroute.push(dist[iroute.top()].first);

		int temp = dist[iroute.top()].second - dist[dstnum].second / 2;
		if (temp >= 0 && temp <= 30) {
			midnode = iroute.top();
		}
	}
	int prenode = dstnum;
	while (!iroute.empty()) {
		while (stlist[iroute.top()].name == stlist[prenode].name) {
			iroute.pop();
		}
		cout << stlist[iroute.top()].num<<' '<<stlist[iroute.top()].name <<' '<< dist[iroute.top()].second << endl;
		prenode = iroute.top();
		iroute.pop();
	}
	PrintTime(dist[dstnum].second);
	cout <<stlist[midnode].num<<' ' << stlist[midnode].name << endl;
	PrintTime(dist[midnode].second);
	PrintTime(dist[dstnum].second - dist[midnode].second); 
}

void MatrixWGraph::PrintTime(int time) {
	cout << time / 60 << ':' << (time % 60) / 10 << 0 << endl;
}