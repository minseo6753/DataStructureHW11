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
	int node; //����� ����
	int** length; //�� �� ���� �ҿ�ð�
	bool* s; //�湮 ó��
	pair<int, int>* dist; //first�� ���� ����ȣ second�� �ҿ�ð�
	Station* stlist; //���� �迭. �ε������� ����� ��ȣ�� �ȴ�
	int count; //stlist�� ����ִ� ������ ����
	vector<vector<int>> transfer; //�̸��� ���� ������ ����ȣ�� �ϳ��� �迭�� �̷�.

public:
	MatrixWGraph(int);
	void AddVertex(int, string, int, string);
	void Dijkstra(int, string, int, string);
	void PrintRoute(int, int);
	void PrintTime(int);
};

#endif // !
