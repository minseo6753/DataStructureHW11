#include "subway.h"
#include<fstream>
#include<string>

int main(int argc, char* argv[])
{
	int numLine;
	int line1, line2;
	string src, dst;
	if (argc != 3) {
		cerr << "Argument Count is "<< argc << endl << "Argument must be " <<
			argc << endl;
		return 1;
	}
	fstream fin(argv[1]);
	if (!fin) {
		cerr << argv[1] << " open failed" << endl;
		return 1;
	}
	fin >> numLine;
	//데이터 받는 과정
	MatrixWGraph g(numLine);

	int num1, num2;
	string name1, name2;
	
	while (fin >> num1 >> name1 >> num2 >> name2) {
		
		g.AddVertex(num1, name1, num2, name2);
	}
	//…
	fin.close();
	fstream fin2(argv[2]);
	if (!fin2) {
		cerr << argv[2] << " open failed" << endl;
		return 1;
	}
	fin2 >> line1 >> src;
	fin2 >> line2 >> dst;
	fin2.close();
	//결과 출력
	g.Dijkstra(line1, src, line2, dst);
	
	return 0;
}