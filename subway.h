#ifndef SUBWAY
#define SUBWAY

#define MAXLEN 45000

#include<iostream>
#include<vector>
using namespace std;

struct Station {
	int num;
	string name;
	Station(int n = 0, string s = "") :num(n), name(s) {};
};

class MatrixWGraph {
	int node;
	int vertex;
	int** length;
	bool* s;
	int* dist; //first는 이전 노드번호 second는 소요시간
	Station* stlist; //역의 배열. 인덱스값이 노드의 번호가 된다
	int count; //stlist에 들어있는 원소의 갯수
	vector<vector<int>> transfer; //이름이 같은 역들의 노드번호가 하나의 배열을 이룸.
	vector<vector<vector<int>>> paths;
public:
	MatrixWGraph(int);
	void AddVertex(int, string, int, string);
	void Dijkstra(int, string, int, string);
	void PrintRoute(int, int);
	void PrintTime(int);
};

#endif // !
