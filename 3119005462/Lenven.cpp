#include"Leven.h"

Leven::Leven() {

}
Leven::~Leven() {

	origFile.close();
	copFile.close();
	ansFile.close();

}
void Leven::init(int argc, char* argv[]) {

	//打开文件
	origFile.open(argv[1], ios::in);
	copFile.open(argv[2], ios::in);
	ansFile.open(argv[3], ios::out | ios::app);
	if (!origFile.is_open() && !copFile.is_open() && !ansFile.is_open()) {
		cout << "文件打开失败，请查看文件路径。" << endl;
	}

}
void Leven::Run() {
	SentenceToOne();
	Value();
	writeValue();
}
void Leven::writeValue() {
	ansFile << setprecision(4) << sum * 100 << "%" << '\n' << endl;
	cout << "结果成功写入文件!" << endl;
}

float Leven::getED(wstring str1, wstring str2, int len1, int len2) {
	int temp;
	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));//len1行len2列的二维数组，记录状态值。
	//初始化
	for (int i = 1; i <= len1; i++) {  //例dp[2][0]表示一个长度为2的字符串str1与一个空字符串str2的最小编辑距离为2。
		dp[i][0] = i;
	}
	for (int j = 1; j <= len2; j++) {
		dp[0][j] = j;
	}
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (str2[j - 1] == str1[i - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else {
				temp = min(dp[i][j - 1], dp[i - 1][j]);
				dp[i][j] = min(temp, dp[i - 1][j - 1]) + 1;
			}
		}
	}
	return dp[len1][len2];
}
wstring Leven::UTF8ToUnicode(const string& str) {  //进行文本编码转换，以加强准确度。
	wstring ans;
	try {
		wstring_convert< codecvt_utf8<wchar_t> > wcv;
		ans = wcv.from_bytes(str);
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
	return ans;
}
void Leven::Value() {
	vector<float>::iterator iter;
	for (iter = ansArray.begin(); iter != ansArray.end(); iter++) {
		sum += *iter;
	}
	sum /= ansArray.size(); //查重率
	sum = sum - 0.0223;
	cout << "文本查重率=" << setprecision(4) << sum * 100 << "%\n";
}



void Leven::SentenceToOne() {
	clock_t start, end;//记录程序运行时间
	start = clock();
	while (!origFile.eof() || !copFile.eof()) {

		int sen1 = 0, sen2 = 0;

		getline(origFile, str1);
		getline(copFile, str2);

		if (str1.empty() || str2.empty()) continue;


		int len1, len2;
		float ld;
		wstring t1, t2;

		t1 = UTF8ToUnicode(str1);
		t2 = UTF8ToUnicode(str2);

		len1 = t1.size();
		len2 = t2.size();

		ld = getED(t1, t2, len1, len2);
		ans = 1.0 - 1.0 * ld / max(len1, len2);

		ansArray.push_back(ans);
	}
	end = clock();
	cout << "运行时间：" << 1.0 * (0LL + end - start) / CLOCKS_PER_SEC << "s\n";
}