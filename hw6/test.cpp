#include <iostream>
#include "../CImg.h"
#include "HomeWork6.cpp"
#include "DigitalRecognition.cpp"
#include <string.h>
using namespace std;
using namespace cimg_library;
//g++ -o a.exe test.cpp -O2 -lgdi32
// g++ test.cpp -std=c++11 -IE:\OpenCV-MinGW-Build\include -IE:\xgboost\include -LE:\xgboost -llib\xgboost -LE:\xgboost -LE:\OpenCV-MinGW-Build\x64\mingw\bin -fopenmp -llibopencv_calib3d341 -llibopencv_core341 -llibopencv_dnn341 -llibopencv_features2d341 -llibopencv_flann341 -llibopencv_highgui341 -llibopencv_imgcodecs341 -llibopencv_imgproc341 -llibopencv_ml341 -llibopencv_objdetect341 -llibopencv_photo341 -llibopencv_shape341 -llibopencv_stitching341 -llibopencv_superres341 -llibopencv_video341 -llibopencv_videoio341 -llibopencv_videostab341 -O2 -lgdi32 -lpthread

// a.exe "data\TT0351\CC -  (1).bmp" 4 800 "data\TT035_result\CC -  (1).txt" "data\TT035_result\CC -  (1)\000.bmp" "data\TT035_result\CC -  (1)"
int get_num(char *name){
	int length1 = 0;
	int i = 0;
	while(true){
		if(name[i] == '\0')
			break;
		length1 = length1 * 10 + name[i++] - '0';
	}
	return length1;
}

void test(char *argv[]){
	HomeWork6 t(argv[1]);
	t.change_gray();
	t.use_otsu();
	int num = get_num(argv[2]);
	int the_num = get_num(argv[3]);
	t.delete_big(the_num);
	for(int i = 0;i < num;i++){
		t.delate();
		t.delete_bounds();
		// t.show();
		if(i == 0)	
			t.delete_big(the_num);
	}
	t.find_num();
	t.find_rule();
	t.find_bracket();
	t.draw_all_bracket();
	// t.draw_three_areas();
	// t.divide_all_part();
	// t.write_result(argv[4],argv[5]);
	// t.draw_every_num();
	t.get_bracket_result();
	t.show1();
	// t.save1(argv[7]);
}


void test1(char *argv[]){
	DigitalRecognition t(argv[4],argv[6]);
	t.knn(5);
	t.svm();
	t.adaboost();
	t.xgboost();
}
int main(int argc, char* argv[]){	
	// test(argv);
	test1(argv);
}