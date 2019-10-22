#ifndef _HOMEWORK4__
#define _HOMEWORK4_
#include <iostream>
#include <string.h>
#include <vector>
#include "../CImg.h"
using namespace std;
using namespace cimg_library;

struct rect{
	int left;
	int right;
	int top;
	int bottom;
};

class HomeWork4{
	private:
		CImg<unsigned char> image;
		CImg<unsigned char> gray;
		vector<vector<bool> > mapping;
		int L[3] = {-1,0,1};
		int height;
		int width;
		int depth;
		const unsigned char
			 red[3]   = { 255, 0, 0 };
		const unsigned char
			 blue[3]   = { 0, 0 ,255};
		 vector<rect> to_dic;
		 rect rule_pos;
		 vector<CImg<unsigned char> > digits;
	public:
		HomeWork4(char *name1);
		void show();
		void show1();
		void save(char * name);
		void save1(char * name);
		void change_gray();
		void change_gray1();
		CImg<unsigned char> change_gray2(CImg<unsigned char> image1);
		void use_thresholds(int threshold);
		void use_two_peaks();
		void use_iter();
		void use_otsu();
		void delate();
		void delete_big(int threshold);
		int find_length(int i,int j,int threshold,int &left,int &right,int &top,int &bottom);
		void dispose_T(CImg<unsigned char> &result,int i,int j);
		CImg<unsigned char> get_gray();
		void set_gray(CImg<unsigned char> gray1);
		void find_rule();
		void divide_digits();
		void read_digits();
		int dic_num(int left,int top,int right,int bottom);
		void recognition_number_by_template();
		void recognition_number_by_tesseract();
};

#endif