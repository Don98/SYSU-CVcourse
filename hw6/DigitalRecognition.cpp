#include <iostream>
#include "../CImg.h"
#include <string.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/ml.hpp>  
#include <cstring>
#include <vector>
#include "DigitalRecognition.h"
#include <io.h>
#include <fstream>
#include <xgboost/c_api.h>
using namespace cv;
void GetAllFiles( string path, vector<string>& files)  {
	long   hFile = 0;  
	struct _finddata_t fileinfo;  
	string p;  
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1){  
		do{   
			if((fileinfo.attrib &  _A_SUBDIR)){  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0){
					files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					GetAllFiles( p.assign(path).append("\\").append(fileinfo.name), files ); 
				}
			}  
			else
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
		}while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile); 
	} 
}
DigitalRecognition::DigitalRecognition(char *name,char *path){
	vector<string> files;
	int x,y,num;
	for(int i = 0;i < 8;i++){
		files.clear();
		ifstream infile;
		infile.open(name);
		GetAllFiles(path, files);
		if(i < 4){
			for(int j = 0;j < files.size();j++){
				Mat image = imread(files[j]);
				infile >> x >> y >> num;
				cvtColor(image, image, CV_RGB2GRAY);
				image = image.reshape(1,1);
				this->traindata.push_back(image);
				this->trainlabel.push_back(num);
				this->all_data.push_back(image);
				this->all_label.push_back(num);
			}
		}else{
			for(int j = 0;j < files.size();j++){
				Mat image = imread(files[j]);
				infile >> x >> y >> num;
				cvtColor(image, image, CV_RGB2GRAY);
				image = image.reshape(1,1);
				this->testdata.push_back(image);
				this->testlabel.push_back(num);
				this->all_data.push_back(image);
				this->all_label.push_back(num);
			}
		}
		name[25] += 1;
		path[25] += 1;
	}
	this->traindata.convertTo(this->traindata, CV_32FC1);
	this->testdata.convertTo(this->testdata, CV_32FC1);
	this->testlabel.convertTo(this->testlabel, CV_32FC1);

}

void DigitalRecognition::knn(int k){	
	cv::Ptr<cv::ml::KNearest> knn = cv::ml::KNearest::create();
	knn->setDefaultK(k);
	knn->setIsClassifier(true);
	knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
	knn->train(this->traindata, cv::ml::ROW_SAMPLE, trainlabel);
	
	cv::Mat result;
	int true_num = 0;
	knn->findNearest(this->testdata, k, result);
	result.convertTo(result, CV_32FC1);
	for(int i = 0;i < result.rows;i++){
		float value1 = ((float*)result.data)[i];
		float value2 = ((float*)testlabel.data)[i];
		if((int)value1 == (int)value2)
			true_num++;
	}
	printf("Recognition rate of KNN : %lf\n",true_num / (float)testlabel.rows);
}
void DigitalRecognition::svm(){	
	cv::Ptr<cv::ml::SVM> svm = cv::ml::SVM::create();
	svm->setType(cv::ml::SVM::C_SVC);
	svm->setKernel(cv::ml::SVM::LINEAR);
	svm->setDegree(0);
	svm->setGamma(1);
	svm->setCoef0(0);
	svm->setC(1);
	svm->setNu(0); 
	svm->setP(0);
	svm->setTermCriteria(cv::TermCriteria(CV_TERMCRIT_ITER, 1000, 1e-6));
	svm->train(this->traindata, ml::ROW_SAMPLE,this->trainlabel);
	float true_num = 0;
	for(int i = 0;i < this->testdata.rows;i++){
		float value1 = svm->predict(this->testdata.rowRange(i,i+1));
		float value2 = ((float*)testlabel.data)[i];
		// cout << (int)value1 << " " <<  (int)value2 << " " << ((int)value1 == (int)value2) << endl;
		if((int)value1 == (int)value2)
			true_num++;
	}
	printf("Recognition rate of  SVM : %lf\n",true_num / (float)testlabel.rows);	
}
void DigitalRecognition::adaboost(){
	vector<double> priors(2);
    priors[0] = 1;
    priors[1] = 10;
	Ptr<cv::ml::Boost> the_adaboost = cv::ml::Boost::create();
    the_adaboost->setBoostType(cv::ml::Boost::GENTLE);
    the_adaboost->setWeakCount(100);
    the_adaboost->setWeightTrimRate(0.95);
    the_adaboost->setMaxDepth(5);
    the_adaboost->setUseSurrogates(false);
    the_adaboost->setPriors(Mat(priors));
	
	
    const int class_count = 10;
    int nsamples_all = this->all_data.rows;
    int ntrain_samples = (int)(nsamples_all*0.5);
    int var_count = this->all_data.cols;
    Mat new_data( ntrain_samples*class_count, var_count + 1, CV_32F );
    Mat new_responses( ntrain_samples*class_count, 1, CV_32S );
	
    for( int i = 0; i < ntrain_samples; i++ ){
        const float* data_row = this->all_data.ptr<float>(i);
        for( int j = 0; j < class_count; j++ ){
            float* new_data_row = (float*)new_data.ptr<float>(i*class_count+j);
            memcpy(new_data_row, data_row, var_count*sizeof(data_row[0]));
            new_data_row[var_count] = (float)j;
            new_responses.at<int>(i*class_count + j) = this->all_label.at<int>(i) == j;
        }
    }
    Mat var_type( 1, var_count + 2, CV_8U );
    var_type.setTo(Scalar::all(ml::VAR_ORDERED));
    var_type.at<uchar>(var_count) = var_type.at<uchar>(var_count+1) = ml::VAR_CATEGORICAL;
	Ptr<ml::TrainData> tdata = ml::TrainData::create(new_data, ml::ROW_SAMPLE, new_responses, noArray(), noArray(), noArray(), var_type);
    the_adaboost->train(tdata);
	Mat temp_sample( 1, var_count + 1, CV_32F );
    float* tptr = temp_sample.ptr<float>();   
    double train_hr = 0, test_hr = 0;
    for( int i = 0; i < nsamples_all; i++ ){
        int best_class = 0;
        double max_sum = -DBL_MAX;
        const float* ptr = this->all_data.ptr<float>(i);
        for( int k = 0; k < var_count; k++ )
            tptr[k] = ptr[k];
        for( int j = 0; j < class_count; j++ ){
            tptr[var_count] = (float)j;
            float s = the_adaboost->predict( temp_sample, noArray(), ml::StatModel::RAW_OUTPUT );
            if( max_sum < s ){
                max_sum = s;
                best_class = j;
            }
        }
        double r = std::abs(best_class - this->all_label.at<int>(i)) < FLT_EPSILON ? 1 : 0;
        if( i < ntrain_samples )
            train_hr += r;
        else
            test_hr += r;
    }
    test_hr /= nsamples_all-ntrain_samples;
    train_hr = ntrain_samples > 0 ? train_hr/ntrain_samples : 1.;
    printf( "Recognition rate of adaboost : %1f\n", test_hr );
    // cout << "Number of trees: " << the_adaboost->getRoots().size() << endl;
}
void DigitalRecognition::xgboost(){
	int cols=this->traindata.cols,rows=this->traindata.rows;
	float train[rows][cols];
	for (int i=0;i<rows;i++)
		for (int j=0;j<cols;j++)
			train[i][j] = (float)this->traindata.at<uchar>(i,j);

	float train_labels[rows];
	for (int i=0;i<rows;i++)
		train_labels[i] = (float)this->trainlabel.at<uchar>(i,0);
	
	DMatrixHandle h_train[1];
	XGDMatrixCreateFromMat((float *) train, rows, cols, -1, &h_train[0]);

	XGDMatrixSetFloatInfo(h_train[0], "label", train_labels, rows);

	bst_ulong bst_result;
	const float *out_floats;
	XGDMatrixGetFloatInfo(h_train[0], "label" , &bst_result, &out_floats);

	BoosterHandle h_booster;
	XGBoosterCreate(h_train, 1, &h_booster);
	XGBoosterSetParam(h_booster, "booster", "gbtree");
	// XGBoosterSetParam(h_booster, "objective", "reg:linear");
	XGBoosterSetParam(h_booster, "objective", "multi:softmax");
	XGBoosterSetParam(h_booster, "num_class", "10");
	XGBoosterSetParam(h_booster, "max_depth", "5");
	XGBoosterSetParam(h_booster, "eta", "0.1");
	XGBoosterSetParam(h_booster, "min_child_weight", "1");
	XGBoosterSetParam(h_booster, "subsample", "0.5");
	XGBoosterSetParam(h_booster, "colsample_bytree", "1");
	XGBoosterSetParam(h_booster, "num_parallel_tree", "1");

	for (int iter=0; iter<200; iter++)
		XGBoosterUpdateOneIter(h_booster, iter, h_train[0]);

	const int sample_rows = this->testdata.rows;
	float test[sample_rows][cols];
	for (int i=0;i<sample_rows;i++)
		for (int j=0;j<cols;j++)
			test[i][j] = (float)this->testdata.at<uchar>(i,j);
	DMatrixHandle h_test;
	XGDMatrixCreateFromMat((float *) test, sample_rows, cols, -1, &h_test);
	bst_ulong out_len;
	const float *f;
	XGBoosterPredict(h_booster, h_test, 0,0,&out_len,&f);
	float true_num = 0;
	for (unsigned int i=0;i<out_len;i++){
		// std::cout << "prediction[" << i << "]=" << f[i] << std::endl;
		if(abs(f[i] - ((float*)testlabel.data)[i]) < 0.5)
			true_num++;
	}
	printf("Recognition rate of  XG-Boost : %lf\n",true_num / (float)testlabel.rows);	

	// free xgboost internal structures
	XGDMatrixFree(h_train[0]);
	XGDMatrixFree(h_test);
	XGBoosterFree(h_booster);
}