#include"data_calibrate.h"



void help() {
	cout << "\t\t����"<<endl;
	cout << "����o����ͼƬ" << endl;
}

void open_img(string img_path) {

	Mat img = imread(img_path);
	imshow("src", img);
	waitKey();
	
}

void mark() {



}