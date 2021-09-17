#include"main.h"

using namespace std;

string UTF8ToGB(const char* str) //编码转换utf-8 --> gbk,解决编码不符出现的中文乱码问题。
{
	string result;
	WCHAR* strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}

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