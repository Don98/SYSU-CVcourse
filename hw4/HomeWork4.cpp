#include <iostream>
#include "../CImg.h"
#include "HomeWork4.h"
#include <string.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <cstring>
using namespace cv;
using namespace std;
using namespace cimg_library;

HomeWork4::HomeWork4(char * name1){
	this->image.load_bmp(name1);
	this->width = image.width();
	this->height = image.height();
	this->depth = image.depth();
	vector<bool> tmp;
	 for(int j=0;j<height;j++){
		tmp.push_back(false);
	 }
	for(int i=0;i<width;i++){
		 this->mapping.push_back(tmp);
	}
}
void HomeWork4::show(){
	this->gray.display("abc");
}
void HomeWork4::show1(){
	this->image.display("abc");
}

void HomeWork4::save(char * name){
	this->gray.save(name);
}
void HomeWork4::save1(char * name){
	this->image.save(name);
}

CImg<unsigned char> HomeWork4::get_gray(){
	return this->gray;
}
void HomeWork4::set_gray(CImg<unsigned char> gray1){
	this->gray = gray1;
}

void HomeWork4::change_gray(){
	CImg<unsigned char> gray1(width,height,depth,1);
	unsigned char r,g,b;
	unsigned char gr1 = 0;
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			r = image(i,j,0,0); // First channel RED
			g = image(i,j,0,1); // Second channel GREEN
			b = image(i,j,0,2); // Third channel BLUE
			gr1 = round(0.299*((double)r) + 0.587*((double)g) + 0.114*((double)b));
			gray1(i,j,0,0) = gr1;
			}
	}
	this->gray = gray1;
}
CImg<unsigned char> HomeWork4::change_gray2(CImg<unsigned char> image1){
	int width1 = image1.width();
	int height1 = image1.height();
	int depth1 = image1.depth();
	CImg<unsigned char> gray1(width1,height1,depth1,1);
	unsigned char r,g,b;
	unsigned char gr1 = 0;
	for(int i=0;i<width1;i++){
		for(int j=0;j<height1;j++){
			r = image1(i,j,0,0); // First channel RED
			g = image1(i,j,0,1); // Second channel GREEN
			b = image1(i,j,0,2); // Third channel BLUE
			gr1 = round(0.299*((double)r) + 0.587*((double)g) + 0.114*((double)b));
			if(gr1 != 255)
				gray1(i,j,0,0) = 0;
			else
				gray1(i,j,0,0) = gr1;
			}
	}
	return gray1;
}
void HomeWork4::change_gray1(){
	CImg<unsigned char> gray1(width,height,depth,1);
	unsigned char r,g,b;
	unsigned char gr1 = 0;
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			r = image(i,j,0,0); // First channel RED
			g = image(i,j,0,1); // Second channel GREEN
			b = image(i,j,0,2); // Third channel BLUE
			gr1 = round(0.299*((double)r) + 0.587*((double)g) + 0.114*((double)b));
			if(gr1 != 255)
				gray1(i,j,0,0) = 0;
			else
				gray1(i,j,0,0) = gr1;
			}
	}
	this->gray = gray1;
}

void HomeWork4::divide_digits(){
	// 132 148       428 180

	rect t;
	int length,left,right,top,bottom;
	for(int i=130;i<430;i++){
		for(int j=148;j<180;j++){
			if(gray(i,j) == 255 || this->mapping[i][j] == true){
				this->mapping[i][j] = true;
			}
			else{
				left = width;right = 0;top = height;bottom = 0;
				this->mapping[i][j] = true;
				length = find_length(i,j,245,left,right,top,bottom);
				t.left = left-2;
				t.right = right+2;
				t.top = top-2;
				t.bottom = bottom+2;
				this->to_dic.push_back(t);
			}
			
		}
	}
	char name[20] = "digits/0.bmp";
	for(int i = 0;i < this->to_dic.size();i++){
		CImg<unsigned char> number_image(to_dic[i].right - to_dic[i].left,to_dic[i].bottom - to_dic[i].top,depth,1);
		for(int j = to_dic[i].left;j < to_dic[i].right;j++)
			for(int k = to_dic[i].top;k < to_dic[i].bottom;k++)
				number_image(j - to_dic[i].left,k - to_dic[i].top) = this->gray(j,k);
		number_image.save(name);
		name[7] += 1;
	}
}
void HomeWork4::read_digits(){
	char name[20] = "digits/0.bmp";
	for(int i = 0;i < 10;i++){
		CImg<unsigned char> number_image;
		number_image.load_bmp(name);
		this->digits.push_back(change_gray2(number_image));
		name[7] += 1;
	}
}
// 使用阈值法
void HomeWork4::use_thresholds(int threshold){
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			if(this->gray(i,j) > threshold)
				this->gray(i,j) = 255;
			else
				this->gray(i,j) = 0;
		}
	}
}
// 使用双峰法
void HomeWork4::use_two_peaks(){
	int new_T = 0,max_one=-1,max_two=-1,pos1 = 0,pos2 = 0,t;
	int bins[256] = {0};
	for(int i=0;i<width;i++)
		for(int j=0;j<height;j++)
				bins[this->gray(i,j)] += 1;
	for(int i = 1;i < 255;i++){
		if(bins[i] > max_one && bins[i] > bins[i + 1] && bins[i] > bins[i - 1]){
			max_one = bins[i];
			pos1 = i;
		}
	}
	for(int i = 1;i < 255;i++){
		if(bins[i] < max_one && bins[i] > max_two && bins[i] > bins[i + 1] && bins[i] > bins[i - 1]){
			max_two = bins[i];
			pos2 = i;
		}
	}
	if(pos2 < pos1){
		t = pos1;
		pos1 = pos2;
		pos2 = t;
	}
	for(int i = pos1;i < pos2;i++){
		if(bins[i] < max_one){
			max_one = bins[i];
			new_T = i;
		}
	}
	// cout << new_T << endl;
	use_thresholds(new_T);
}
// 使用迭代法
void HomeWork4::use_iter(){
	int T = 0,new_T = 100,m1 = 0,m2 = 0,betaT = 2;
	while(abs(new_T - T) > betaT){
		m1 = 0;m2 = 0;
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){
				if(this->gray(i,j) > new_T)
					m1 = (m1 + this->gray(i,j)) / 2;
				else
					m2 = (m2 + this->gray(i,j)) / 2;
			}
		}
		T = new_T;
		new_T = (m1 + m2)/2;
	}
	// cout << new_T << endl;
	use_thresholds(new_T);
}
// 使用大律法
void HomeWork4::use_otsu(){
	int fit_T = 0,MN = width * height;
	double betaB = -1.0,MaxbetaB = -1.0,m,m1,m2,mg,P1,P2;
	int bins[256] = {0};
	for(int i=0;i<width;i++)
		for(int j=0;j<height;j++)
				bins[this->gray(i,j)] += 1;
	double P[256] = {0.0},WC[256] = {0.0},C[256] = {0.0};
	for(int i = 0;i < 256;i++)
		P[i] = bins[i] *  1.0 / MN ;
	C[0] = P[0];
	for(int i = 1;i < 256;i++){
		WC[i] = WC[i-1] + i * P[i];
		C[i] = C[i-1] + P[i];
	}
	mg = WC[255];
	for(int k = 0;k < 256;k++){
		P1 = C[k];
		P2 = 1 - C[k];
		m1 = WC[k] / P1;
		m2 = (WC[255] - WC[k])/ P2;
		m = WC[k];
		betaB = (mg * P1 - m) * (mg * P1 - m) / (P1 * (1-P1));
		// printf("betaB %lf\n",betaB);
		if(betaB > MaxbetaB){
			MaxbetaB = betaB;
			fit_T = k;
		}
	}
	// cout << fit_T << endl;
	use_thresholds(fit_T);
}
void HomeWork4::delate(){
	int width = this->gray.width();
	int height = this->gray.height();
	int depth = this->gray.depth();
	CImg<unsigned char> gray1(width,height,depth,1);
	for(int i=1;i<width-1;i++){
		for(int j=1;j<height-1;j++){
			if(gray(i,j) == 0 || gray(i-1,j) == 0 || gray(i+1,j) == 0 || gray(i,j-1) == 0 || gray(i,j+1) == 0){
				gray1(i,j) = 0;
			}
			else
				gray1(i,j) = 255;
		}
	}
	gray = gray1;
}

int HomeWork4::find_length(int i,int j,int threshold,int &left,int &right,int &top,int &bottom){
	this->mapping[i][j] = true;
	int length = 0;
	int x,y;
	vector<int> x_point,y_point;
	x_point.push_back(i);
	y_point.push_back(j);
	int now;
	while(x_point.size() != 0){
		now = x_point.size() - 1;
		i = x_point[now];
		j = y_point[now];
		length += 1;
		if(i < left)
			left = i;
		if(i > right)
			right = i;
		if(j > bottom)
			bottom = j;
		if(j < top)
			top = j;
		// if(length >= threshold)
			// return threshold;
		x_point.pop_back();
		y_point.pop_back();
		for(int p = 0;p < 3;p++){
			for(int k = 0;k < 3;k++){
				x = i + L[p];
				y = j + L[k];
				if(x >= 0 && x <= width-1 && y >= 0 && y <= height-1 && this->gray(x,y) == 0 && this->mapping[x][y] == false){
					this->mapping[x][y] = true;
					x_point.push_back(x);
					y_point.push_back(y);
				}
			}
		}
	}
	return length;
	
}

void HomeWork4::dispose_T(CImg<unsigned char> &result,int i,int j){
	int x,y;
	vector<int> x_point;
	vector<int> y_point;
	x_point.push_back(i);
	y_point.push_back(j);
	int now;
	while(x_point.size() != 0){
		now = x_point.size() - 1;
		i = x_point[now];
		j = y_point[now];
		x_point.pop_back();
		y_point.pop_back();
		for(int p = 0;p < 3;p++){
			for(int k = 0;k < 3;k++){
				x = i + L[p];
				y = j + L[k];
				if(x >= 0 && x <= width-1 && y >= 0 && y <= height-1 && result(x,y) == 0){
					result(x,y) = 255;
					x_point.push_back(x);
					y_point.push_back(y);
				}
			}
		}
	}
}


void HomeWork4::delete_big(int threshold){
	CImg<unsigned char> result(width,height,depth,1);
	result = this->gray;
	int length = 0;
	
	int left,right,top,bottom;
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			if(gray(i,j) == 255 || this->mapping[i][j] == true){
				this->mapping[i][j] = true;
			}
			else{
				left = width;right = 0;top = height;bottom = 0;
				this->mapping[i][j] = true;
				length = find_length(i,j,threshold,left,right,top,bottom);
				if(length >= threshold)
					dispose_T(result,i,j);
				else{//这里存在一个神奇的现象，当使用length大于等于阈值直接返回时，画框会出现画了中断的线的框
					if(length > 5){
						if(abs(right - left) <= 25 && abs(top - bottom) <= 25)		
							this->image.draw_rectangle(left, top,right, bottom,this->red,1,~0U);
					}
				}
			}
			
		}
	}
	this->gray = result;
}

int HomeWork4::dic_num(int left,int top,int right,int bottom){
	int width,height,dis,num=0,min_length=-1;
	for(int i = 0;i < this->digits.size();i++){
		CImg<unsigned char> gray1 = this->digits[i];
		width = gray1.width() < right - left ? gray1.width():right - left;
		height = gray1.height() < bottom - top ? gray1.height():bottom - top;
		dis = 0;
		for(int j = 0;j < width;j++){
			for(int k = 0 ;k < height;k++){
				dis += (this->gray(left + j, top + k) - gray1(j,k)) * (this->gray(left + j, top + k) - gray1(j,k));
			}
		}
		if(min_length == -1)
			min_length = dis;
		if(min_length > dis){
			min_length = dis;
			num = i;
		}
	}
	return num;
}

void HomeWork4::find_rule(){
	int left1,right1,top1,bottom1;
	int left,right,top,bottom;
	int length = 0,max_length = 0;
	for(int i=1;i<width-1;i++){
		for(int j=1;j<height-1;j++){
			if(this->gray(i,j) == 0){
				length = 0;
				for(int p = i + 1; p < width; p++){
					if(this->gray(p,j) == 0)
						length += 1;
					else
						break;
				}
				if(length > max_length){
					left1 = i;
					right1 = i + length;
					top1 = j;
					bottom1 = j;
					max_length = length;
				}
			}
		}
	}
	this->image.draw_rectangle(left1-10, top1-20,right1+10, bottom1+50,this->blue,1,~0U);
	
	for(int i=1;i<width-1;i++){
		for(int j=1;j<height-1;j++){
			this->mapping[i][j] = false;
		}
	}
	rect t;
	for(int i=left1;i<right1;i++){
		for(int j=top1;j<bottom1+50;j++){
			if(gray(i,j) == 255 || this->mapping[i][j] == true){
				this->mapping[i][j] = true;
			}
			else{
				left = width;right = 0;top = height;bottom = 0;
				this->mapping[i][j] = true;
				length = find_length(i,j,245,left,right,top,bottom);
				if(length < 245 && length > 100){		
					t.left = left;
					t.right = right;
					t.top = top;
					t.bottom = bottom;
					this->to_dic.push_back(t);
				}
			}
			
		}
	}
	for(int i = 0;i < 3;i++)
		this->to_dic.pop_back();
	this->rule_pos.left = left1;
	this->rule_pos.right = right1;
	this->rule_pos.top = top1;
	this->rule_pos.bottom = bottom1;
}

void HomeWork4::recognition_number_by_template(){
	change_gray();
	cout << "The result of recognition numbers !" << endl;
	for(int i = 0;i < this->to_dic.size();i++){
		this->image.draw_rectangle(to_dic[i].left, to_dic[i].top,to_dic[i].right, to_dic[i].bottom,this->red,1,~0U);
		cout << dic_num(to_dic[i].left, to_dic[i].top,to_dic[i].right, to_dic[i].bottom) << " ";
		if((i + 1) % 2 == 0)
			cout << endl;
	}
}
void HomeWork4::recognition_number_by_tesseract(){
	change_gray();
	char name[150] = "tesseract tesseract_recognition/resultA.bmp tesseract_recognition/resultA digits";
	char pic_name[100] = "tesseract_recognition/resultA.bmp";
	for(int i = 0;i < this->to_dic.size();i++){
		this->image.draw_rectangle(to_dic[i].left, to_dic[i].top,to_dic[i].right, to_dic[i].bottom,this->red,1,~0U);
		CImg<unsigned char> number_image(to_dic[i].right - to_dic[i].left,to_dic[i].bottom - to_dic[i].top,depth,1);
		cout << to_dic[i].left << " " << to_dic[i].right << " " << to_dic[i].top << " " << to_dic[i].bottom << endl;
		for(int j = to_dic[i].left;j < to_dic[i].right;j++){
			for(int k = to_dic[i].top;k < to_dic[i].bottom;k++){
				number_image(j - to_dic[i].left,k - to_dic[i].top) = this->gray(j,k);
			}
		}
		number_image.save("123.bmp");
		Mat src_color = imread("123.bmp");  
		int c=src_color.cols/2;
		int r=src_color.rows/2;  
		Mat src_gray;
		Mat src_gray_resize; 
		cvtColor(src_color, src_gray, COLOR_BGR2GRAY);
		resize(src_gray, src_gray_resize, Size(512, 512), 0, 0, INTER_LINEAR);
		imwrite(pic_name, src_gray_resize);
		system(name);
		name[38] += 1;
		name[72] += 1;
		pic_name[28] += 1;
	}
	system("del 123.bmp");
}