#include <iostream>
// #include "../CImg.h"
#include <string.h>
#include <math.h>
// #include <opencv2/opencv.hpp>
// #include <opencv2/ml.hpp>  
#include <cstring>
#include <vector>
#include <io.h>
#include <fstream>
#include <xgboost/c_api.h>
int main(){
	int cols=3,rows=5;
	float train[rows][cols];
	for (int i=0;i<rows;i++)
		for (int j=0;j<cols;j++)
			train[i][j] = (i+1) * (j+1);

	float train_labels[rows];
	for (int i=0;i<rows;i++)
		train_labels[i] = 1+i*i*i;
	// convert to DMatrix
	DMatrixHandle h_train[1];
	XGDMatrixCreateFromMat((float *) train, rows, cols, -1, &h_train[0]);

	// load the labels
	XGDMatrixSetFloatInfo(h_train[0], "label", train_labels, rows);

	// read back the labels, just a sanity check
	bst_ulong bst_result;
	const float *out_floats;
	XGDMatrixGetFloatInfo(h_train[0], "label" , &bst_result, &out_floats);
	for (unsigned int i=0;i<bst_result;i++)
		std::cout << "label[" << i << "]=" << out_floats[i] << std::endl;

	// create the booster and load some parameters
	BoosterHandle h_booster;
	XGBoosterCreate(h_train, 1, &h_booster);
	XGBoosterSetParam(h_booster, "booster", "gbtree");
	XGBoosterSetParam(h_booster, "objective", "reg:linear");
	XGBoosterSetParam(h_booster, "max_depth", "5");
	XGBoosterSetParam(h_booster, "eta", "0.1");
	XGBoosterSetParam(h_booster, "min_child_weight", "1");
	XGBoosterSetParam(h_booster, "subsample", "0.5");
	XGBoosterSetParam(h_booster, "colsample_bytree", "1");
	XGBoosterSetParam(h_booster, "num_parallel_tree", "1");

	// perform 200 learning iterations
	for (int iter=0; iter<200; iter++)
		XGBoosterUpdateOneIter(h_booster, iter, h_train[0]);

	// predict
	const int sample_rows = 5;
	float test[sample_rows][cols];
	for (int i=0;i<sample_rows;i++)
		for (int j=0;j<cols;j++)
			test[i][j] = (i+1) * (j+1);
	DMatrixHandle h_test;
	XGDMatrixCreateFromMat((float *) test, sample_rows, cols, -1, &h_test);
	bst_ulong out_len;
	const float *f;
	XGBoosterPredict(h_booster, h_test, 0,0,&out_len,&f);

	for (unsigned int i=0;i<out_len;i++)
		std::cout << "prediction[" << i << "]=" << f[i] << std::endl;


	// free xgboost internal structures
	XGDMatrixFree(h_train[0]);
	XGDMatrixFree(h_test);
	XGBoosterFree(h_booster);
}
// g++ 1.cpp -o b -std=c++11 -IE:\OpenCV-MinGW-Build\include -IE:\xgboost\include -LE:\xgboost -llib\xgboost -LE:\OpenCV-MinGW-Build\x64\mingw\bin -fopenmp -llibopencv_calib3d341 -llibopencv_core341 -llibopencv_dnn341 -llibopencv_features2d341 -llibopencv_flann341 -llibopencv_highgui341 -llibopencv_imgcodecs341 -llibopencv_imgproc341 -llibopencv_ml341 -llibopencv_objdetect341 -llibopencv_photo341 -llibopencv_shape341 -llibopencv_stitching341 -llibopencv_superres341 -llibopencv_video341 -llibopencv_videoio341 -llibopencv_videostab341 -O2 -lgdi32 -lpthread

// g++ 1.cpp -o b -std=c++11 -IE:\xgboost\include -LE:\xgboost -llib\xgboost -fopenmp 