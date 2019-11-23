#ifndef _HomeWork6__
#define _HomeWork6_
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

class HomeWork6{
	private:
		CImg<unsigned char> image;
		CImg<unsigned char> gray;
		vector<vector<bool> > mapping;
		int gray_num;
		int L[3] = {-1,0,1};
		int height;
		int width;
		int depth;
		const unsigned char
			 red[3]   = { 255, 0, 0 };
		const unsigned char
			 blue[3]   = { 0, 0 ,255};
		const unsigned char
			 green[3]   = { 0, 255 ,0};
		 vector<rect> to_dic;
		 vector<vector<rect> > num_result;
		 vector<vector<rect> > every_num;
		 vector<rect> all_bracket;
		 rect rule_pos;
		 vector<CImg<unsigned char> > digits;
		 int bracket_pos;
		 int start;
		 double between;
	public:
		HomeWork6(char *name1);
		HomeWork6();
		void show();
		void show1();
		void save(char * name);
		void save1(char * name);
		void change_gray();
		void change_gray1();
		void change_gray3(int num);
		CImg<unsigned char> change_gray2(CImg<unsigned char> image1);
		void use_thresholds(int threshold);
		void use_otsu();
		void delate();
		void delate_part(int left,int right,int top,int bottom);
		void delete_big(int threshold);
		void delete_bounds();
		int find_length(int i,int j,int threshold,int &left,int &right,int &top,int &bottom);
		void dispose_T(CImg<unsigned char> &result,int i,int j);
		CImg<unsigned char> get_gray();
		void set_gray(CImg<unsigned char> gray1);
		void find_rule();
		void find_bracket();
		void find_bracket1();
		void draw_three_areas();
		void set_mapping();
		void draw_every_num();
		void draw_all_bracket();
		void divide_all_part();
		void find_num();
		void divide_digits(int left,int right,int top,int bottom,int num);
		void read_digits();
		void read_digit1();
		void read_digit2();
		void get_bracket_result();
		int dic_num(int left,int top,int right,int bottom);
		int dic_num1(int left,int top,int right,int bottom);
		int dic_num2(CImg<unsigned char> the_image);
		void recognition_number_by_template(int num1,int num2);
		void recognition_number_by_template1(int num1,int num2);
		void recognition_number_by_re(int num1,int num2);
		void write_result(char * name,char * name1,char * name2);
};

#endif