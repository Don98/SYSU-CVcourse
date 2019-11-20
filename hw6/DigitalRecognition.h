#ifndef DIGITALRECONGNITION_
#define DIGITALRECONGNITION
#include <iostream>
#include <string.h>
#include <vector>
#include "../CImg.h"
#include <opencv2/opencv.hpp>
#include <opencv2/ml/ml.hpp>  
using namespace std;
using namespace cimg_library;

class DigitalRecognition{
	private:
		Mat traindata ,trainlabel,testdata ,testlabel,all_data,all_label;
	public:
		DigitalRecognition(char *name,char *path);
		void knn(int k);
		void svm();
		void adaboost();
		void xgboost();
		// void use_knn(int k);
};

#endif