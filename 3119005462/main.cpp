#include"main.h"

using namespace std;



bool check(int argc, char* argv[]) {  //检查命令函参数
	if (argc != 4) {
		cout << "ERROR:参数错误！\n";
		return false;
	}
	if (_access(argv[1], 00) == -1 || _access(argv[2], 00) == -1) {
		if (_access(argv[1], 00) == -1) cout << "Refer Adress Error\n";
		if (_access(argv[2], 00) == -1) cout << "Test Adress Error\n";
		return false;
	}
	return true;
}

int main(int argc,char* argv[]) {

	if (check(argc, argv)) {
		Leven leven;
		leven.init(argc,argv);
		leven.Run();
	}
	system("pause");
	return 0;
}