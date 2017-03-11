/*
*y用于其他项目的测试
*
*/


#include<opencv2/core/core.hpp> //包含程序所使用的头文件和命名空间  
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