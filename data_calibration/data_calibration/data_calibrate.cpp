#include"data_calibrate.h"



void help() {
	cout << "\t\t°ïÖú"<<endl;
	cout << "°´¼üo£º´ò¿ªÍ¼Æ¬" << endl;
}

void open_img(string img_path) {

	Mat img = imread(img_path);
	imshow("src", img);
	waitKey();
	
}

void mark() {



}