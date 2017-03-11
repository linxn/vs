#pragma once
#include<opencv2/core/core.hpp> //包含程序所使用的头文件和命名空间  
#include<opencv2/highgui/highgui.hpp>  
#include "opencv2/imgproc/imgproc.hpp"  //不加入该头文件 rectangle函数找不到


#include"tinyxml.h"

#include "stdlib.h" 
#include<string>
#include<iostream>
using namespace std;

//win32
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <locale.h>
#include <ShlObj.h>//选择文件夹 用到

cv::Rect rect;//矩形类 画出的矩形
bool drawing_box;//用于判断是否正在画矩形
				 //    机动车   文字   人体  人脸  背包   行李箱        交通信号灯       路标       刀具   枪支      
enum { VEHICLE, TEXT, PERSON, FACE, BAG, SUITCASE, TRAFFIC_SIGNAL_LAMP, ROAD_SIGNAL, KNIFE, GUN };
string name[10] = { "vehicle","text","person","face","bag","suitcase","traffic_signal_lamp" ,"road_signal" ,"knife", "gun" };//对应上面的类别
int categories[20];//用于存储每个矩形的类别
cv::Rect boxs[20];//用于存储画出的矩形
string picture_path;//图片路径
int category = 0;//当前类别
int coun = 0;//矩形个数
char width[2], height[2], depth[2], x1[2], x2[2], y11[2], y2[2];//tinyxml保存时需要转化为 char*类型 分别为图片长、宽、通道、矩形左上角xy、右下角xy

void save_file(const char* fileName, char* width, char* height, char* depth, string name[], int categories[], cv::Rect boxs[]) {
	TiXmlDocument doc;
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	TiXmlElement * annotationElement = new TiXmlElement("annotation");
	TiXmlElement * folderElement = new TiXmlElement("folder");
	folderElement->LinkEndChild(new TiXmlText("VOC2012"));
	TiXmlElement * sizeElement = new TiXmlElement("size");
	TiXmlElement * widthElement = new TiXmlElement("width");
	widthElement->LinkEndChild(new TiXmlText(width));
	TiXmlElement * heightElement = new TiXmlElement("height");
	heightElement->LinkEndChild(new TiXmlText(height));
	TiXmlElement * depthElement = new TiXmlElement("depth");
	depthElement->LinkEndChild(new TiXmlText(depth));
	annotationElement->LinkEndChild(folderElement);
	annotationElement->LinkEndChild(sizeElement);
	sizeElement->LinkEndChild(widthElement);
	sizeElement->LinkEndChild(heightElement);
	sizeElement->LinkEndChild(depthElement);
	doc.LinkEndChild(decl);
	doc.LinkEndChild(annotationElement);

	for (int i = 0; i < coun; i++) {
		TiXmlElement * objectElement = new TiXmlElement("object");
		TiXmlElement * nameElement = new TiXmlElement("name");
		nameElement->LinkEndChild(new TiXmlText(name[categories[i]].data()));
		TiXmlElement * bndboxElement = new TiXmlElement("bndbox");
		_itoa(boxs[i].x, x1, 10);
		_itoa(boxs[i].y, y11, 10);
		_itoa(boxs[i].x + boxs[i].width, x2, 10);
		_itoa(boxs[i].y + boxs[i].height, y2, 10);
		TiXmlElement * xminElement = new TiXmlElement("xmin");
		xminElement->LinkEndChild(new TiXmlText(x1));
		TiXmlElement * yminElement = new TiXmlElement("ymin");
		yminElement->LinkEndChild(new TiXmlText(y11));
		TiXmlElement * xmaxElement = new TiXmlElement("xmax");
		xmaxElement->LinkEndChild(new TiXmlText(x2));
		TiXmlElement * ymaxElement = new TiXmlElement("ymax");
		ymaxElement->LinkEndChild(new TiXmlText(y2));
		bndboxElement->LinkEndChild(xminElement);
		bndboxElement->LinkEndChild(yminElement);
		bndboxElement->LinkEndChild(xmaxElement);
		bndboxElement->LinkEndChild(ymaxElement);
		objectElement->LinkEndChild(nameElement);
		objectElement->LinkEndChild(bndboxElement);
		annotationElement->LinkEndChild(objectElement);
	}



	doc.SaveFile(fileName);




}