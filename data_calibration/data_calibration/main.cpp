#include"data_calib.h"

//ע��������Ӧ����
void onmouse(int event, int x, int y, int flag, void *img) {
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:  //������������ʱ
		drawing_box = true;
		rect = cv::Rect(x, y, 0, 0);//��¼�������Ͻ�
		break;

	case CV_EVENT_MOUSEMOVE:
		if (drawing_box) {     //����������ʱ���ƶ�
			rect.width = x - rect.x;
			rect.height = y - rect.y;
		}
		break;

	case CV_EVENT_LBUTTONUP:
		drawing_box = false;  //�������ſ�ʱ
		if (rect.width < 0) {
			rect.x = rect.x + rect.width;  //�����ʼ�㲻�����Ͻ�  ����Ӧ��������
			rect.y = rect.y + rect.height;
		}
		break;

	default:
		break;
	}

}


int main() {
	cout << "**********���ݱ궨Demo**********" << endl << endl;

	while (1) {
		cout << "o��ѡ��ͼƬ  q���˳�..." << endl;
		cin >> picture_path;
		if(picture_path == "o" || picture_path == "O"){
		//win32
		_tsetlocale(LC_CTYPE, TEXT(""));//��wprintf ֧������
		TCHAR szPathName[MAX_PATH];
		OPENFILENAME ofn = { OPENFILENAME_SIZE_VERSION_400 };
		ofn.hwndOwner = GetForegroundWindow();// ��OR�����ļ��Ի���ĸ�����
		ofn.lpstrFilter = TEXT("�����ļ�(*.*)");
		lstrcpy(szPathName, TEXT(""));
		ofn.lpstrFile = szPathName;
		ofn.nMaxFile = sizeof(szPathName);//����û�ѡ���ļ��� ·�����ļ��� ������
		ofn.lpstrTitle = TEXT("ѡ��ͼƬ");//ѡ���ļ��Ի������
		TCHAR szCurDir[MAX_PATH];
		GetCurrentDirectory(sizeof(szCurDir), szCurDir);
		ofn.lpstrInitialDir = szCurDir;//���öԻ�����ʾ�ĳ�ʼĿ¼
		ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
		BOOL bOk = GetOpenFileName(&ofn);
		if (bOk) {
			picture_path = (string)szPathName;
		}
		else
			break;

		cout << "����ͼƬ..." << endl << endl;
		cv::Mat tmp;
		cv::Mat img = cv::imread(picture_path);
		_itoa(img.channels(), depth, 10);  //_itoa()������ת��Ϊchar * Ԥ���������_CRT_SECURE_NO_WARNINGS ���򱨴�
		_itoa(img.cols, width, 10);
		_itoa(img.rows, height, 10);

		cv::namedWindow("src");
		setMouseCallback("src", onmouse, &img); ("src", onmouse, &img);
		imshow("src", img);
		img.copyTo(tmp);
		cout << "��ʼ���б궨��" << endl
			<< "˵����\n"
			<< "1�����ѡ�о��ο��  enter  ��ȷ��" << endl
			<< "2�����ּ�ѡ��궨���\n\t0-��������Ĭ�ϣ�\t1-����\n\t2-����\t\t\t3-����\n\t4-����\t\t\t5-������\n\t6-��ͨ�źŵ�\t\t7-·��\n\t8-����\t\t\t9-ǹ֧" << endl
			<< "3���궨������esc��������ͼƬ�궨�������ļ�" << endl << endl<<"��ǰ��𣺻�����\n";
		while (1) {
			if (drawing_box) {
				img.copyTo(tmp);
				rectangle(tmp, cv::Point(rect.x, rect.y), cv::Point(rect.x + rect.width, rect.y + rect.height), cv::Scalar(255, 0, 0), 1.5);//������


			}
			else {
				//ȷ�����ο�
				if (cv::waitKey(10) == 13) {
					rectangle(tmp, cv::Point(rect.x, rect.y), cv::Point(rect.x + rect.width, rect.y + rect.height), cv::Scalar(255, 0, 0), 1.5);
					tmp.copyTo(img); //ȷ���˾��ο�
					boxs[coun] = rect;//�����α���
					categories[coun] = category;//�����ͱ���
					coun++;
					cout << "��ȷ�����ο� x:" << rect.x << "\ty:" << rect.y << "\twidth: " << rect.width << "\theight: " << rect.height << "\t���Ϊ��" << name[category] << endl;
				}

			}
			imshow("src", tmp);

			//�˳�����
			char command = cv::waitKey(10);
			if (command == 27) {
				cv::destroyWindow("src");
				string xmlFile_s = picture_path.append(".xml");
				//const char * xmlFile = xmlFile_s.data();
				const char * xmlFile = xmlFile_s.data();
				
				save_file(xmlFile, width, height, depth, name, categories, boxs);

				cout << "�ѱ���\t" << coun << endl << endl;
				coun = 0;
				break;
			}
			//���ݰ�ť�������
			else if (command == '0') {
				category = VEHICLE;
				cout << "�޸����Ϊ ������..." << endl;
			}
			else if (command == '1') {
				category = TEXT;
				cout << "�޸����Ϊ ����..." << endl;
			}
			else if (command == '2') {
				category = PERSON;
				cout << "�޸����Ϊ ����..." << endl;
			}
			else if (command == '3') {
				category = FACE;
				cout << "�޸����Ϊ ����..." << endl;
			}
			else if (command == '4') {
				category = BAG;
				cout << "�޸����Ϊ ����..." << endl;
			}
			else if (command == '5') {
				category = SUITCASE;
				cout << "�޸����Ϊ ������..." << endl;
			}
			else if (command == '6') {
				category = TRAFFIC_SIGNAL_LAMP;
				cout << "�޸����Ϊ ��ͨ�źŵ�..." << endl;
			}
			else if (command == '7') {
				category = ROAD_SIGNAL;
				cout << "�޸����Ϊ ·��..." << endl;
			}
			else if (command == '8') {
				category = KNIFE;
				cout << "�޸����Ϊ ����..." << endl;
			}
			else if (command == '9') {
				category = GUN;
				cout << "�޸����Ϊ ǹ֧..." << endl;
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