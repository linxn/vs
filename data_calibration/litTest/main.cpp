/*
*y����������Ŀ�Ĳ���
*
*/


#include<opencv2/core/core.hpp> //����������ʹ�õ�ͷ�ļ��������ռ�  
#include<opencv2/highgui/highgui.hpp>  
using namespace cv;

#include<iostream>
using namespace std;

int main() {
	namedWindow("ser");
	int a = waitKey();
	cout << a;
	system("pause");
	return 0;

}