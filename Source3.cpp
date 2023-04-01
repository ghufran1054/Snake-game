//#include<iostream>
//#include<cmath>
//#include<string>
//
//using namespace std;
//
//void print(bool** h, int len)
//{
//	char block = char(219);
//	char patrn = char(176);
//	for (int j = 0; j < len; j++) {
//		for (int k = 0; k < len; k++) {
//			if (h[j][k])
//				cout << patrn << patrn;
//			else
//				cout << block << block;
//		}
//		cout << endl;
//	}
//
//}
//void repeat(bool** h, int  len)
//{
//	for (int j = 0; j < len; j++)
//		for (int k = 0; k < len; k++)
//			h[j][len + k] = h[j][k];
//	for (int j = 0; j < len; j++)
//		for (int k = 0; k < len; k++)
//			h[len + j][k] = h[j][k];
//	for (int j = 0; j < len; j++)
//		for (int k = 0; k < len; k++)
//			h[len + j][len + k] = !(h[j][k]);
//}
//
//
//void hadamard(int n)
//{
//	int N = int(pow(2, n - 1));
//	bool** h = new bool*[N];
//	for (int j = 0; j < N; j++)
//		h[j] = new bool[N];
//
//	h[0][0] = true;
//	for (int x = 1; x < N; x += x) {
//		for (int i = 0; i < x; i++) {
//			for (int j = 0; j < x; j++) {
//				h[i + x][j] = h[i][j];
//				h[i][j + x] = h[i][j];
//				h[i + x][j + x] = !h[i][j];
//			}
//		}
//
//	}
//
//
//
//
//	print(h, N);
//
//	for (int j = 0; j < N; j++)
//		delete[] h[j];
//	delete[] h;
//}
//
//int main()
//{
//	cout << "n? ";
//	int n;
//	cin >> n;
//	hadamard(n);
//	return 0;
//}