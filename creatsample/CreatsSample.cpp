// CreatsSample.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <cv.h>
#include <highgui.h>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <io.h>

using namespace std;

#define SAMPLENUM /*2848*/300
#define POSPATH		"F:\\测试素材\\MIT_standard_person\\pedstrian_bmp\\"
#define POSPATH2	"F:\\测试素材\\MIT_standard_person\\pedstrian_bmp\\*.bmp"
#define POSMRPATH		"F:\\测试素材\\MIT_standard_person\\pedstrain_mirror\\"
#define POSMRPATH2	"F:\\测试素材\\MIT_standard_person\\pedstrain_mirror\\*.bmp"
#define NEGPATH		"F:\\测试素材\\CVC-CER-01\\not_pedestrain_bmp\\"
#define NEGPATH2	"F:\\测试素材\\CVC-CER-01\\not_pedestrain_bmp\\*.bmp"

int _tmain(int argc, _TCHAR* argv[])
{
	struct _finddata_t bmp_file;
	long hFile;
	ofstream f;
	string strPrefix;
	string strPostfix;
	int index = 0;
	IplImage* image=0;
	IplImage* ResizeImage=0;
	IplImage* temp=0;


	//	get *.bmp files in directory
	hFile=_findfirst(POSPATH2, &bmp_file);
	if(hFile == -1L)
	{
		printf("no *.bmp files in such directory .\n");
		return 0;
	}

	f.open("pedestrian.dat",  ios::out| ios::binary);
	f<<SAMPLENUM<<'\n';
	//f<<24<<" "<<24<<'\n';
	ResizeImage = cvCreateImage(cvSize(24, 48), IPL_DEPTH_8U, 1);
	
	
	//cvNamedWindow("window_name", 0);

	//读取正样本
	do 
	{
		strPostfix="";
		strPrefix=POSPATH;
		strPrefix+=bmp_file.name;
		
		image = cvLoadImage(strPrefix.c_str(),0);
		//temp = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
		//cvCvtColor(image, temp, CV_RGB2GRAY);
		cvResize(image, ResizeImage, CV_INTER_CUBIC );
		f<<1<<'\n'<<48<<' '<<24<<'\n';
		f.write(ResizeImage->imageData, 48*24);
		f<<'\n';
		//cvReleaseImage(&temp);
		//cvShowImage("window_name", ResizeImage);
		//cvWaitKey(0);
		index++;
	} while(_findnext(hFile,&bmp_file)==0 && index < 100/*924*/);

	////读取正样本镜像
	//hFile=_findfirst(POSMRPATH2, &bmp_file);
	//if(hFile == -1L)
	//{
	//	printf("no *.bmp files in such directory .\n");
	//	return 0;
	//}
	////cvNamedWindow("window_name", 0);
	//index = 0;
	//do 
	//{
	//	strPostfix="";
	//	strPrefix=POSMRPATH;
	//	strPrefix+=bmp_file.name;
	//	cvReleaseImage(&image);
	//	image = cvLoadImage(strPrefix.c_str(),0);
	//	//temp = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
	//	//cvCvtColor(image, temp, CV_RGB2GRAY);
	//	cvResize(image, ResizeImage, CV_INTER_CUBIC );
	//	f<<1<<'\n'<<48<<' '<<24<<'\n';
	//	f.write(ResizeImage->imageData, 48*24);
	//	f<<'\n';
	//	//cvReleaseImage(&temp);
	//	//cvShowImage("window_name", ResizeImage);
	//	//cvWaitKey(0);
	//	index++;
	//} while(_findnext(hFile,&bmp_file)==0 && index < 100/*924*/);

	//读取负样本
	hFile=_findfirst(NEGPATH2, &bmp_file);
	if(hFile == -1L)
	{
		printf("no *.bmp files in such directory .\n");
		return 0;
	}
	//cvNamedWindow("window_name", 0);
	index = 0;
	do 
	{
		strPostfix="";
		strPrefix=NEGPATH;
		strPrefix+=bmp_file.name;
		cvReleaseImage(&image);
		image = cvLoadImage(strPrefix.c_str(),0);
		//temp = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
		//cvCvtColor(image, temp, CV_RGB2GRAY);
		cvResize(image, ResizeImage, CV_INTER_CUBIC );
		f<<0<<'\n'<<48<<' '<<24<<'\n';
		f.write(ResizeImage->imageData, 48*24);
		f<<'\n';
		//cvReleaseImage(&temp);
		//cvShowImage("window_name", ResizeImage);
		//cvWaitKey(0);
		index++;
	} while(_findnext(hFile,&bmp_file)==0 && index < 200/*1000*/);

	f.close();
	if (0 != image)
		cvReleaseImage(&image);
	if (0 != ResizeImage)
		cvReleaseImage(&ResizeImage);
	if (0 != temp)
		cvReleaseImage(&temp);
	return 0;
}

