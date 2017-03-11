#include"data_calib.h"

//注册的鼠标相应函数
void onmouse(int event, int x, int y, int flag, void *img) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:  //鼠标左键被按下时
		drawing_box = true;
		rect = cv::Rect(x, y, 0, 0);//记录矩形左上角
		break;

	case CV_EVENT_MOUSEMOVE:
		if (drawing_box) {     //鼠标左键按下时的移动
			rect.width = x - rect.x;
			rect.height = y - rect.y;
		}
		break;

	case CV_EVENT_LBUTTONUP:
		drawing_box = false;  //鼠标左键放开时
		if (rect.width < 0) {
			rect.x = rect.x + rect.width;  //如果起始点不是左上角  则相应做出调整
			rect.y = rect.y + rect.height;
		}
		break;

	default:
		break;
	}

}


int main() {
	cout << "**********数据标定Demo**********" << endl << endl;

	while (1) {
		cout << "o键选择图片  q键退出..." << endl;
		cin >> picture_path;
		if(picture_path == "o" || picture_path == "O"){
		//win32
		_tsetlocale(LC_CTYPE, TEXT(""));//让wprintf 支持中文
		TCHAR szPathName[MAX_PATH];
		OPENFILENAME ofn = { OPENFILENAME_SIZE_VERSION_400 };
		ofn.hwndOwner = GetForegroundWindow();// 打开OR保存文件对话框的父窗口
		ofn.lpstrFilter = TEXT("所有文件(*.*)");
		lstrcpy(szPathName, TEXT(""));
		ofn.lpstrFile = szPathName;
		ofn.nMaxFile = sizeof(szPathName);//存放用户选择文件的 路径及文件名 缓冲区
		ofn.lpstrTitle = TEXT("选择图片");//选择文件对话框标题
		TCHAR szCurDir[MAX_PATH];
		GetCurrentDirectory(sizeof(szCurDir), szCurDir);
		ofn.lpstrInitialDir = szCurDir;//设置对话框显示的初始目录
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
		BOOL bOk = GetOpenFileName(&ofn);
		if (bOk) {
			picture_path = (string)szPathName;
		}
		else
			break;

		cout << "载入图片..." << endl << endl;
		cv::Mat tmp;
		cv::Mat img = cv::imread(picture_path);
		_itoa(img.channels(), depth, 10);  //_itoa()将整数转化为char * 预处理器添加_CRT_SECURE_NO_WARNINGS 否则报错
		_itoa(img.cols, width, 10);
		_itoa(img.rows, height, 10);

		cv::namedWindow("src");
		setMouseCallback("src", onmouse, &img); ("src", onmouse, &img);
		imshow("src", img);
		img.copyTo(tmp);
		cout << "开始进行标定！" << endl
			<< "说明：\n"
			<< "1、鼠标选中矩形框后按  enter  键确定" << endl
			<< "2、数字键选择标定类别：\n\t0-机动车（默认）\t1-文字\n\t2-人体\t\t\t3-人脸\n\t4-背包\t\t\t5-行李箱\n\t6-交通信号灯\t\t7-路标\n\t8-道具\t\t\t9-枪支" << endl
			<< "3、标定结束后按esc键结束该图片标定并保存文件" << endl << endl<<"当前类别：机动车\n";
		while (1) {
			if (drawing_box) {
				img.copyTo(tmp);
				rectangle(tmp, cv::Point(rect.x, rect.y), cv::Point(rect.x + rect.width, rect.y + rect.height), cv::Scalar(255, 0, 0), 1.5);//画矩形


			}
			else {
				//确定矩形框
				if (cv::waitKey(10) == 13) {
					rectangle(tmp, cv::Point(rect.x, rect.y), cv::Point(rect.x + rect.width, rect.y + rect.height), cv::Scalar(255, 0, 0), 1.5);
					tmp.copyTo(img); //确定了矩形框
					boxs[coun] = rect;//将矩形保存
					categories[coun] = category;//将类型保存
					coun++;
					cout << "已确定矩形框 x:" << rect.x << "\ty:" << rect.y << "\twidth: " << rect.width << "\theight: " << rect.height << "\t类别为：" << name[category] << endl;
				}

			}
			imshow("src", tmp);

			//退出程序
			char command = cv::waitKey(10);
			if (command == 27) {
				cv::destroyWindow("src");
				string xmlFile_s = picture_path.append(".xml");
				//const char * xmlFile = xmlFile_s.data();
				const char * xmlFile = xmlFile_s.data();
				
				save_file(xmlFile, width, height, depth, name, categories, boxs);

				cout << "已保存\t" << coun << endl << endl;
				coun = 0;
				break;
			}
			//根据按钮设置类别
			else if (command == '0') {
				category = VEHICLE;
				cout << "修改类别为 机动车..." << endl;
			}
			else if (command == '1') {
				category = TEXT;
				cout << "修改类别为 文字..." << endl;
			}
			else if (command == '2') {
				category = PERSON;
				cout << "修改类别为 人体..." << endl;
			}
			else if (command == '3') {
				category = FACE;
				cout << "修改类别为 人脸..." << endl;
			}
			else if (command == '4') {
				category = BAG;
				cout << "修改类别为 背包..." << endl;
			}
			else if (command == '5') {
				category = SUITCASE;
				cout << "修改类别为 行李箱..." << endl;
			}
			else if (command == '6') {
				category = TRAFFIC_SIGNAL_LAMP;
				cout << "修改类别为 交通信号灯..." << endl;
			}
			else if (command == '7') {
				category = ROAD_SIGNAL;
				cout << "修改类别为 路标..." << endl;
			}
			else if (command == '8') {
				category = KNIFE;
				cout << "修改类别为 刀具..." << endl;
			}
			else if (command == '9') {
				category = GUN;
				cout << "修改类别为 枪支..." << endl;
			}

		}

		}
		else
		{
			break;
		}

	}
	return 0;
}