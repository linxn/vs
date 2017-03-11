#pragma once
#include<opencv2/core/core.hpp> //����������ʹ�õ�ͷ�ļ��������ռ�  
#include<opencv2/highgui/highgui.hpp>  
#include "opencv2/imgproc/imgproc.hpp"  //�������ͷ�ļ� rectangle�����Ҳ���


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
#include <ShlObj.h>//ѡ���ļ��� �õ�

cv::Rect rect;//������ �����ľ���
bool drawing_box;//�����ж��Ƿ����ڻ�����
				 //    ������   ����   ����  ����  ����   ������        ��ͨ�źŵ�       ·��       ����   ǹ֧      
enum { VEHICLE, TEXT, PERSON, FACE, BAG, SUITCASE, TRAFFIC_SIGNAL_LAMP, ROAD_SIGNAL, KNIFE, GUN };
string name[10] = { "vehicle","text","person","face","bag","suitcase","traffic_signal_lamp" ,"road_signal" ,"knife", "gun" };//��Ӧ��������
int categories[20];//���ڴ洢ÿ�����ε����
cv::Rect boxs[20];//���ڴ洢�����ľ���
string picture_path;//ͼƬ·��
int category = 0;//��ǰ���
int coun = 0;//���θ���
char width[2], height[2], depth[2], x1[2], x2[2], y11[2], y2[2];//tinyxml����ʱ��Ҫת��Ϊ char*���� �ֱ�ΪͼƬ������ͨ�����������Ͻ�xy�����½�xy

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