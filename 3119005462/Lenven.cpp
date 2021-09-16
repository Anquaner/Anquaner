#include"Leven.h"

Leven::Leven() {

}
Leven::~Leven() {

	origFile.close();
	copFile.close();
	ansFile.close();

}
void Leven::init(int argc, char* argv[]) {

	//���ļ�
	origFile.open(argv[1], ios::in);
	copFile.open(argv[2], ios::in);
	ansFile.open(argv[3], ios::out | ios::app);
	if (!origFile.is_open() && !copFile.is_open() && !ansFile.is_open()) {
		cout << "�ļ���ʧ�ܣ���鿴�ļ�·����" << endl;
	}

}
void Leven::Run() {
	SentenceToOne();
	Value();
	writeValue();
}
void Leven::writeValue() {
	ansFile << setprecision(4) << sum * 100 << "%" << '\n' << endl;
	cout << "����ɹ�д���ļ�!" << endl;
}

float Leven::getLD(string str1, string str2, int len1, int len2) {
	int temp;
	vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1));//len1��len2�еĶ�ά���飬��¼״ֵ̬��
	//��ʼ��
	for (int i = 1; i <= len1; i++) {  //��dp[2][0]��ʾһ������Ϊ2���ַ���str1��һ�����ַ���str2����С�༭����Ϊ2��
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
void Leven::Value() {
	vector<float>::iterator iter;
	for (iter = ansArray.begin(); iter != ansArray.end(); iter++) {
		sum += *iter;
	}
	sum /= ansArray.size(); //������

	cout << "�ı�������=" << setprecision(4) << sum * 100 << "%\n";
}



void Leven::SentenceToOne() {
	clock_t start, end;//��¼��������ʱ��
	start = clock();
	while (!origFile.eof() || !copFile.eof()) {

		int sen1 = 0, sen2 = 0;

		getline(origFile, str1);
		getline(copFile, str2);

		if (str1.empty() || str2.empty()) continue;


		int len1, len2;
		float ld;
		len1 = str1.size();
		len2 = str2.size();

		ld = getLD(str1, str2, len1, len2);
		ans = 1.0 - 1.0 * ld / max(len1, len2);

		ansArray.push_back(ans);
	}
	end = clock();
	cout << "����ʱ�䣺" << 1.0 * (0LL + end - start) / CLOCKS_PER_SEC << "s\n";
}