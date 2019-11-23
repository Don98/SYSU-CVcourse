#include <iostream>
#include "../CImg.h"
#include "HomeWork6.h"
#include <string.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <cstring>
#include <vector>
#include <direct.h>
#include <windows.h>
#include <iostream>
using namespace cv;
using namespace std;
using namespace cimg_library;

HomeWork6::HomeWork6(char * name1){
	this->image.load_bmp(name1);
	this->width = image.width();
	this->height = image.height();
	this->depth = image.depth();
	this->gray_num = -1;
	vector<bool> tmp;
	 for(int j=0;j<height;j++){
		tmp.push_back(false);
	 }
	for(int i=0;i<width;i++){
		 this->mapping.push_back(tmp);
	}
}
HomeWork6::HomeWork6(){}
void HomeWork6::show(){
	this->gray.display("abc");
}
void HomeWork6::show1(){
	this->image.display("abc");
}

void HomeWork6::save(char * name){
	this->gray.save(name);
}
void HomeWork6::save1(char * name){
	this->image.save(name);
}

CImg<unsigned char> HomeWork6::get_gray(){
	return this->gray;
}
void HomeWork6::set_gray(CImg<unsigned char> gray1){
	this->gray = gray1;
}

void HomeWork6::change_gray(){
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
void HomeWork6::change_gray3(int num){
	if(this->gray_num == -1)
		this->gray_num = num;
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
	if(this->gray_num >= 0){
		for(int i = 0;i < width;i++){
			for(int j =0;j < height;j++){
				if(gray1(i,j) <= this->gray_num)
					gray1(i,j) = 0;
				else
					gray1(i,j) = 255;
			}
		}
	}
	this->gray = gray1;
}

CImg<unsigned char> HomeWork6::change_gray2(CImg<unsigned char> image1){
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
void HomeWork6::change_gray1(){
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

void HomeWork6::divide_digits(int left1,int right1,int top1,int bottom1,int num){
	// 132 148       428 180
	// 100 140       310 160
	rect t;
	int length,left,right,top,bottom;
	for(int i=left1;i<right1;i++){
		for(int j=top1;j<bottom1;j++){
			if(gray(i,j) == 255 || this->mapping[i][j] == true){
				this->mapping[i][j] = true;
			}
			else{
				left = width;right = 0;top = height;bottom = 0;
				this->mapping[i][j] = true;
				length = find_length(i,j,245,left,right,top,bottom);
				// t.left = left-2;
				// t.right = right+2;
				// t.top = top-2;
				// t.bottom = bottom+2;
				t.left = left;
				t.right = right;
				t.top = top;
				t.bottom = bottom;
				this->to_dic.push_back(t);
			}
			
		}
	}
	if(num == 0){
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
	if(num == 1){
		char name[20] = "digit1/0_0.bmp";
		int the_num = 0;
		for(int i = 0;i < this->to_dic.size();i++){
			CImg<unsigned char> number_image(to_dic[i].right - to_dic[i].left,to_dic[i].bottom - to_dic[i].top,depth,1);
			for(int j = to_dic[i].left;j < to_dic[i].right;j++)
				for(int k = to_dic[i].top;k < to_dic[i].bottom;k++)
					number_image(j - to_dic[i].left,k - to_dic[i].top) = this->gray(j,k);
			// number_image.display();
			number_image.save(name);
			name[9] += 1;
			the_num += 1;
			if(the_num == 5){
				the_num = 0;
				name[9] -= 5;
				name[7] += 1;
			}
		}
	}
	if(num == 2){
		char name[20] = "digit2/0.bmp";
		for(int i = 0;i < this->to_dic.size();i++){
			CImg<unsigned char> number_image(to_dic[i].right - to_dic[i].left,to_dic[i].bottom - to_dic[i].top,depth,1);
			for(int j = to_dic[i].left;j < to_dic[i].right;j++)
				for(int k = to_dic[i].top;k < to_dic[i].bottom;k++)
					number_image(j - to_dic[i].left,k - to_dic[i].top) = this->gray(j,k);
			number_image.save(name);
			name[7] += 1;
		}
	}
}
void HomeWork6::read_digits(){
	char name[20] = "digits/0.bmp";
	for(int i = 0;i < 10;i++){
		CImg<unsigned char> number_image;
		number_image.load_bmp(name);
		this->digits.push_back(change_gray2(number_image));
		name[7] += 1;
	}
}
void HomeWork6::read_digit1(){
	char name[20] = "digit1/0_0.bmp";
	int the_num = 0;
	for(int i = 0;i < 50;i++){
		CImg<unsigned char> number_image;
		number_image.load_bmp(name);
		this->digits.push_back(change_gray2(number_image));
		name[9] += 1;
		the_num += 1;
		if(the_num == 5){
			the_num = 0;
			name[7] += 1;
			name[9] -= 5;
		}
	}
}
void HomeWork6::read_digit2(){
	char name[20] = "digit2/0.bmp";
	for(int i = 0;i < 10;i++){
		CImg<unsigned char> number_image;
		number_image.load_bmp(name);
		this->digits.push_back(change_gray2(number_image));
		name[7] += 1;
	}
}
// 使用阈值法
void HomeWork6::use_thresholds(int threshold){
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			if(this->gray(i,j) > threshold)
				this->gray(i,j) = 255;
			else
				this->gray(i,j) = 0;
		}
	}
}
// 使用大律法
void HomeWork6::use_otsu(){
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
void HomeWork6::delete_bounds(){
	for(int i = 0;i < 10;i++){
		for(int j = 0;j < height;j++){
			if(this->gray(i,j) == 0)
				dispose_T(this->gray,i,j);
			if(this->gray(width - 1 - i,j) == 0)
				dispose_T(this->gray,width - 1 - i,j);
		}
	}
	for(int i = 0;i < width;i++){
		for(int j = 0;j < 10;j++){
			if(this->gray(i,j) == 0)
				dispose_T(this->gray,i,j);
			if(this->gray(i,height - 1 - j) == 0)
				dispose_T(this->gray,i,height - 1 - j);
		}
	}
}

void HomeWork6::delate(){
	int width = this->gray.width();
	int height = this->gray.height();
	int depth = this->gray.depth();
	// delate_part(1,width-1,1,height-1);
	CImg<unsigned char> gray1(width,height,depth,1);
	for(int i = 0;i < width;i++)
		for(int j = 0;j < height;j++)
			gray1(i,j) = 255;
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

void HomeWork6::delate_part(int left,int right,int top,int bottom){
	int width = this->gray.width();
	int height = this->gray.height();
	int depth = this->gray.depth();
	CImg<unsigned char> gray1(width,height,depth,1);
	gray1 = this->gray;
	for(int i=left;i<right;i++){
		for(int j=top;j<bottom;j++){
			if(gray(i,j) == 0 || gray(i-1,j) == 0 || gray(i+1,j) == 0 || gray(i,j-1) == 0 || gray(i,j+1) == 0){
				gray1(i,j) = 0;
			}
			else
				gray1(i,j) = 255;
		}
	}
	gray = gray1;
}

int HomeWork6::find_length(int i,int j,int threshold,int &left,int &right,int &top,int &bottom){
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

void HomeWork6::dispose_T(CImg<unsigned char> &result,int i,int j){
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
					this->mapping[i][j] = false;
				}
			}
		}
	}
}


void HomeWork6::delete_big(int threshold){
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
				if(length >= threshold || length <= 60 || (abs(right - left) < 15 && abs(top - bottom) < 15))
					dispose_T(result,i,j);
				else{//这里存在一个神奇的现象，当使用length大于等于阈值直接返回时，画框会出现画了中断的线的框
					// if(length > 5){
						// if(abs(right - left) <= 25 && abs(top - bottom) <= 25)		
							// this->image.draw_rectangle(left, top,right, bottom,this->red,1,~0U);
					// }
				}
			}
			
		}
	}
	this->gray = result;
}

int HomeWork6::dic_num(int left,int top,int right,int bottom){
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
int get_circle_num(CImg<unsigned char> the_image,vector<vector<bool> > the_mapping){
	int width = the_image.width();
	int height = the_image.height();
	int depth = the_image.depth();
	int num = 0,x0,y0;
	vector<int> x,y;
	int L[3] = {-1,0,1};
	for(int i = 0;i < width;i++){
		for(int j = 0;j < height;j++){
			if(the_mapping[i][j] == false){
				x.push_back(i);
				y.push_back(j);
				the_mapping[i][j] = true;
				while(x.size() != 0){
					x0 = x[x.size()-1];
					y0 = y[y.size()-1];
					x.pop_back();y.pop_back();
					for(int k = 0;k < 3;k++){
						for(int p = 0;p < 3;p++){
							if(x0 + L[k] >= 0 && x0 + L[k] < width && y0+L[p] >= 0 && y0+L[p] < height && the_mapping[x0+L[k]][y0+L[p]] == false){
								x.push_back(x0+L[k]);
								y.push_back(y0+L[p]);
								the_mapping[x0+L[k]][y0+L[p]] = true;
							}
						}
					}
				}
				num += 1;
			}
		}
	}
	return num;
}

void del_white(int height,int width,int i,int j,vector<vector<bool> > &the_mapping){
	int x0,y0;
	vector<int> x,y;
	int L[3] = {-1,0,1};
	the_mapping[i][j] = true;
	x.push_back(i);
	y.push_back(j);
	while(x.size() != 0){
		// cout << x.size() << endl;
		x0 = x[x.size() - 1];
		y0 = y[y.size() - 1];
		x.pop_back();y.pop_back();
		for(int k = 0;k < 3;k++){
			for(int p = 0;p < 3;p++){
				if(x0 + L[k] >= 0 && x0 + L[k] < width && y0+L[p] >= 0 && y0+L[p] < height && the_mapping[x0+L[k]][y0+L[p]] == false){
					x.push_back(x0+L[k]);
					y.push_back(y0+L[p]);
					the_mapping[x0+L[k]][y0+L[p]] = true;
				}
			}
		}
	}
}

int HomeWork6::dic_num2(CImg<unsigned char> the_image){
	int width = the_image.width();
	int height = the_image.height();
	int depth = the_image.depth();
	
	// the_image.display();
	vector<vector<bool> > the_mapping;
	for(int i = 0;i < width;i++){
		vector<bool> t;
		for(int j = 0;j < height;j++)
			t.push_back(false);
		the_mapping.push_back(t);
	}
	vector<vector<bool> > the_mapping2;
	for(int i = 0;i < width;i++){
		vector<bool> t;
		for(int j = 0;j < height;j++)
			t.push_back(false);
		the_mapping2.push_back(t);
	}
	vector<vector<bool> > the_mapping3;
	for(int i = 0;i < width;i++){
		vector<bool> t;
		for(int j = 0;j < height;j++)
			t.push_back(false);
		the_mapping3.push_back(t);
	}
	for(int j = 0;j < height;j++){
		for(int i = 0;i < width;i++){
			if(the_image(i,j) == 0)
				the_mapping[i][j] = true;
		}
	}
	for(int j = 0;j < height;j++){
		for(int i = 0;i < width;i++){
			if(the_image(i,j) == 0)
				break;
			else
				del_white(height,width,i,j,the_mapping);
		}
		for(int i = width-1;i >= 0;i--){
			if(the_image(i,j) == 0)
				break;
			else
				del_white(height,width,i,j,the_mapping);
		}
	}
	for(int i = 0;i < width;i++){
		for(int j = 0;j < height;j++){
			if(the_image(i,j) == 0)
				break;
			else
				del_white(height,width,i,j,the_mapping);
		}
		for(int j = height - 1;j >= 0;j--){
			if(the_image(i,j) == 0)
				break;
			else
				del_white(height,width,i,j,the_mapping);
		}
	}
	int circle_num = get_circle_num(the_image,the_mapping);
	// cout << "The circle_num is : " << circle_num << endl;
	
	// for(int i = 0;i < width;i++){
		// for(int j = 0;j < height;j++)
			// cout << the_mapping[i][j] << " ";
		// cout << endl;
	// }
	if(circle_num > 0){
		if(circle_num == 2)
			return 8;
		int zero_left = 0,zero_right = 0;
		for(int i = 0;i < width;i++){
			for(int j = 0;j < height/2;j++)
				if(the_mapping[i][j] == false)
					zero_left += 1;
			for(int j = height/2+1;j < height;j++)
				if(the_mapping[i][j] == false)
					zero_right += 1;
		}
		// if(zero_left + zero_right >= height * width / 3)
		// cout << "zero num is :" << zero_left << " " << zero_right << endl;
		if(zero_left + zero_right >= 20)
			return 0;
		if(abs(zero_left - zero_right) <= 3)
			return 4;
		if(zero_left > zero_right)
			return 9;
		else
			return 6;
	}else{             
		/*
		for(int j = 0;j < height;j++){
			for(int i = 0;i < width;i++){
				if(the_image(i,j) == 0){
					the_mapping[i][j] = true;
					the_mapping2[i][j] = true;
					the_mapping3[i][j] = true;
				}
				else{
					the_mapping[i][j] = false;
					the_mapping2[i][j] = false;
					the_mapping3[i][j] = false;
				}	
			}
		}
		int one_left = 0,one_right = 0,vlength = 0,vpos = 0,hlength = 0,hpos = 0,num_all = 0;
		for(int i = 0;i < width;i++){
			num_all = 0;
			for(int j = 0;j < height;j++){
				if(the_mapping[i][j] == true)
					num_all += 1;
				else{
					if(num_all > vlength){
						vlength = num_all;
						vpos = i;
					}
					num_all = 0;
				}
			}
			if(num_all > vlength)
				vlength = num_all;
		}
		for(int i = 0;i < width;i++){
			num_all = 0;
			for(int j = 0;j < height;j++){
				if(the_mapping[i][j] == true)
					num_all += 1;
				else{
					if(vlength - num_all > 1){
						for(int k = j-1;k >= j - num_all;k--){
							the_mapping[i][k] = false;
						}
					}
					num_all = 0;
				}
			}
			if(vlength - num_all > 1){
				for(int k = height-1;k >= height - num_all;k--){
					the_mapping[i][k] = false;
				}
			}
		}
		for(int j = 0;j < height;j++){
			num_all = 0;
			for(int i = 0;i < width;i++){
				if(the_mapping2[i][j] == true)
					num_all += 1;
				else{
					if(num_all > hlength){
						hlength = num_all;
						hpos = j;
					}
					num_all = 0;
				}
			}
			if(num_all > hlength)
				hlength = num_all;
		}
		for(int j = 0;j < height;j++){
			num_all = 0;
			for(int i = 0;i < width;i++){
				if(the_mapping2[i][j] == true)
					num_all += 1;
				else{
					if(vlength - num_all > 1){
						for(int k = i-1;k >= i - num_all;k--){
							the_mapping2[k][j] = false;
						}
					}
					num_all = 0;
				}
			}			
			if(vlength - num_all > 1){
				for(int k = width-1;k >= width - num_all;k--){
					the_mapping2[k][j] = false;
				}
			}
		}
		for(int i = 0;i < width;i++){
			num_all = 0;
			for(int j = 0;j < height/2;j++)
				if(the_mapping3[i][j] == true)
					one_left += 1;
			for(int j = height/2+1;j < height;j++)
				if(the_mapping3[i][j] == true)
					one_right += 1;
		}
		// if(abs(one_left - one_right) <= 7){
			// if(hpos > height / 2)
		// }
		cout << "The result is : " << one_left << " " << one_right << " " << abs(one_left - one_right) << " "<< height * width - one_left - one_right << " " << vlength << " " << hlength << endl;
		*/
		vector<int> min_all;
		vector<int> min_num;
		for(int i = 0;i < 9;i++){
			min_all.push_back(-1);
			min_num.push_back(-1);
		}
		int width1,height1,dis=0,gray_width,gray_height;
		for(int i = 0;i < this->digits.size();i++){
			if(i / 5 == 0 || i / 5 == 4 || i / 5 == 6 || i / 5 == 8 || i / 5 == 9)
				continue;
			CImg<unsigned char> gray1 = this->digits[i];
			// gray1.display();
			gray_width = gray1.width();
			gray_height = gray1.height();
			width1 = gray_width < the_image.width() ? gray_width:the_image.width();
			height1 = gray_height < the_image.height() ? gray_height:the_image.height();
			dis = 0;
			for(int j = 0;j < width1;j++){
				for(int k = 0 ;k < height1;k++){
					dis += (the_image(j,k) - gray1(gray_width-j,gray_height-k)) * (the_image(j,k) - gray1(gray_width-j,gray_height-k));
				}
			}
			// for(int j = 0;j < width1;j++){
				// for(int k = 0 ;k < height1;k++){
					// if((int)the_image(j,k) == 255)
						// cout << 0 << " ";
					// else
						// cout << 1 << " ";
				// }
				// cout << "    ";
				// for(int k = 0 ;k < height1;k++){
					// if((int)gray1(gray_width-j,gray_height-k)==255)
						// cout << 0 << " ";
					// else
						// cout << 1 << " ";
				// }
				// cout << endl;
			// }
			// cout << "==============================================================" << endl;
			// cout << dis << endl;
			if(min_all[0] == -1){
				min_all[0] = dis;
				min_num[0] = i / 5;
			}
			else{
				int pos  = -1;
				for(int j = 0;j < min_all.size()-1;j++){
					if(dis < min_all[j]){
						pos = j;
						break;
					}
				}
				if(pos != -1){
					for(int j = min_all.size() - 1;j > pos;j--){
						min_all[j] = min_all[j-1];
						min_num[j] = min_num[j-1];
					}
					min_all[pos] = dis;
					min_num[pos] = i / 5;
				}
			}
		}
		int all_num[10] = {0};
		for(int i = 0;i < min_num.size();i++)
			all_num[min_num[i]] += 1;
		int pos = -1,max = 0;
		for(int i = 0;i < 10;i++){
			if(all_num[i] > max){
				max = all_num[i];
				pos = i;
			}
		}
		return pos;
		
	}
	/*
	for(int i = 0;i < width;i++){
		for(int j = 0;j < height;j++)
			cout << the_mapping[i][j] << " ";
		cout << "  ";
		for(int j = 0;j < height;j++)
			cout << the_mapping2[i][j] << " ";
		cout << "  ";
		for(int j = 0;j < height;j++)
			cout << the_mapping3[i][j] << " ";
		cout << endl;
	}*/
}
int HomeWork6::dic_num1(int left,int top,int right,int bottom){
	int width,height,dis,num=0,min_length=-1;
	// int min_three[3] = {-1,-1,-1};
	// int min_num[3] = {-1,-1,-1};
	vector<int> min_all;
	vector<int> min_num;
	for(int i = 0;i < 9;i++){
		min_all.push_back(-1);
		min_num.push_back(-1);
	}
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
		// cout << dis << endl;
		if(min_all[0] == -1){
			min_all[0] = dis;
			min_num[0] = i / 5;
		}
		else{
			int pos  = -1;
			for(int j = 0;j < min_all.size()-1;j++){
				if(dis < min_all[j]){
					pos = j;
					break;
				}
			}
			if(pos != -1){
				for(int j = min_all.size() - 1;j > pos;j--){
					min_all[j] = min_all[j-1];
					min_num[j] = min_num[j-1];
				}
				min_all[pos] = dis;
				min_num[pos] = i / 5;
			}
		}
		// if((i+1) % 5 == 0)
			// cout << "==========================" << endl;
	}
	int all_num[10] = {0};
	for(int i = 0;i < min_num.size();i++)
		all_num[min_num[i]] += 1;
	int pos = -1,max = 0;
	for(int i = 0;i < 10;i++){
		if(all_num[i] > max){
			max = all_num[i];
			pos = i;
		}
	}
	// for(int i = 0;i < min_all.size();i++){
		// cout << min_all[i] << " ";
	// }
	// cout << endl;
	// for(int i = 0;i < min_all.size();i++){
		// cout << min_num[i] << " ";
	// }
	// cout << endl;
	return pos;
}

void HomeWork6::find_rule(){
	int left1,right1,top1,bottom1;
	int length = 0,max_length = 0;
	// change_gray3(0);
	change_gray();
	// show();
	for(int i = 0; i < width;i++){
		for(int j = 0;j < height;j++){
			// if(this->gray(i,j) != 255)
				// this->gray(i,j) = 0;
			if(this->gray(i,j) <= 160)
				this->gray(i,j) = 0;
			else
				this->gray(i,j) = 255;
				
		}
	}
	delate();
	// show();
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
	if((num_result[2][0].top > top1 && num_result[1][0].top < top1) || (num_result[1][0].top > top1 && num_result[2][0].top > top1 && num_result[2][0].top - top1 < num_result[1][0].top - top1)){
		this->num_result.insert(this->num_result.begin() + 1,this->num_result[2]);
		this->num_result.pop_back();
	}
	rule_pos.left = left1;
	rule_pos.top = top1;
	rule_pos.bottom = bottom1;
	rule_pos.right = right1;
	// this->num_result[1][this->num_result[1].size()-1].right = 1940;
	// this->image.draw_rectangle(left1, top1,right1+1, bottom1+1,this->blue,1,~0U);
	
}
void HomeWork6::divide_all_part(){
	vector<rect> t;
	rect t1;
	int length_between = -1;
	int left,right,top,bottom,length = 0,last_length = -1,flag = 1;
	change_gray();
	use_otsu();
	delate_part(num_result[1][0].left,num_result[1][0].right,num_result[1][0].top,num_result[1][0].bottom);
	// show();
	set_mapping();
	int tmp = 0;
	for(int i = 0;i < this->num_result.size();i++){
		t.clear();
		for(int j = 0;j < this->num_result[i].size();j++){
			for(int p = this->num_result[i][j].left;p < this->num_result[i][j].right;p++){
				for(int k = this->num_result[i][j].top;k < this->num_result[i][j].bottom;k++){
					if(this->gray(p,k) == 0 && this->mapping[p][k] == false){
						left=width;right=0;top=height;bottom=0;
						length = find_length(p,k,200,left,right,top,bottom);
						if((right - left) <= 30 && (bottom - top) <= 30 && length > 40){
							t1.left = left;t1.right = right;t1.top = top;t1.bottom = bottom;
							t.push_back(t1);
						}
					}
				}
			}
		}
		this->every_num.push_back(t);
	}
}

 
bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!
 
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!
 
	return false;    // this is not a directory!
}

void HomeWork6::write_result(char * name,char * name1,char *name2){
	change_gray();
	use_otsu();
	ofstream outfile;
	outfile.open(name);
	int num,the_num = 0,the_num1 = 0,the_num2 = 0;
	for(int i = 0;i < every_num.size();i++){
	   for(int j = 0 ;j < every_num[i].size();j++){		   
			if (0 != access(name2, 0))
				mkdir(name2);
			// cout << name1 << endl;
			if((every_num[i][j].right - every_num[i][j].left) < (every_num[i][j].bottom - every_num[i][j].top)){
				CImg<unsigned char> number_image(every_num[i][j].right - every_num[i][j].left + 2,every_num[i][j].bottom - every_num[i][j].top + 2,depth,1);
				for(int p = every_num[i][j].left - 1;p < every_num[i][j].right + 1;p++){
					for(int k = every_num[i][j].top - 1;k < every_num[i][j].bottom + 1;k++){
						number_image(p - every_num[i][j].left + 1,k - every_num[i][j].top + 1) = this->gray(p,k);
					}
				}
				// cout << name1 << endl;
				number_image.resize(15,25).save(name1);
				// name1[30] += 1;
				name1[31] += 1;
				the_num++;
				// if(the_num == 10 || i == 1)
					// number_image.display("asd");
			}else{
				CImg<unsigned char> number_image(every_num[i][j].bottom - every_num[i][j].top + 2,every_num[i][j].right - every_num[i][j].left + 2,depth,1);
				for(int p = every_num[i][j].left - 1;p < every_num[i][j].right + 1;p++){
					for(int k = every_num[i][j].bottom + 1;k > every_num[i][j].top - 1;k--){
						number_image(every_num[i][j].bottom + 1 - k,p - every_num[i][j].left + 1) = this->gray(p,k);
					}
				}
				number_image.resize(15,25).save(name1);
				// cout << name1 << endl;
				// name1[30] += 1;
				name1[31] += 1;
				the_num++;
				// if(the_num == 10 || i == 1)
					// number_image.display("asd");
			}
			if(the_num == 10){
				name1[31] -= 10;
				name1[30] += 1;
				the_num1 += 1;
				the_num = 0;
				if(the_num1 == 10){
					name1[30] -= 10;
					name1[29] += 1;
					the_num1  = 0;
				}
			}
			// cout << "The num is : ";
			// cin >> num;
			// outfile << (every_num[i][j].right + every_num[i][j].left) / 2 << " " << (every_num[i][j].bottom + every_num[i][j].top) / 2 << " " << num << endl;
			outfile << (every_num[i][j].right + every_num[i][j].left) / 2 << " " << (every_num[i][j].bottom + every_num[i][j].top) / 2 << " " << endl;
	   }
	}

	outfile.close();
}
void HomeWork6::find_num(){
	set_mapping();
	for(int i = 0;i < width;i++)
		for(int j = height / 8;j < height * 4 / 5;j++)
			this->gray(i,j) = 0;
	// delate();
	// show();
	int left,right,top,bottom,length;
	rect t;
	for(int i=0;i<width;i++){
		for(int j=0;j<height;j++){
			if(gray(i,j) == 255 || this->mapping[i][j] == true){
				this->mapping[i][j] = true;
			}
			else{
				left = width;right = 0;top = height;bottom = 0;
				this->mapping[i][j] = true;
				length = find_length(i,j,200,left,right,top,bottom);
				if(length > 20 && !((right - left) >= width/2 && (bottom - top) >= height/2)){		
					t.left = left;
					t.right = right;
					t.top = top+5;
					t.bottom = bottom-5;
					this->to_dic.push_back(t);
					// this->image.draw_rectangle(left, top,right, bottom,this->red,1,~0U);
				}
			}
		}
	}
	vector<vector<rect> > tmp;
	vector<vector<rect> > result;
	vector<int> pos_num;
	for(int i = 0;i < this->to_dic.size();i++){
		if(pos_num.size() == 0){
			pos_num.push_back((to_dic[i].bottom + to_dic[i].top) / 2);
			vector<rect> t;
			t.push_back(to_dic[i]);
			tmp.push_back(t);
		}
		else{
			int pos = -1;
			for(int j = 0;j < pos_num.size();j++){
				if(abs((to_dic[i].bottom + to_dic[i].top) / 2 - pos_num[j]) <= 30 || (this->gray_num >= 0 && abs((to_dic[i].bottom + to_dic[i].top) / 2 - pos_num[j]) <= 62)){
					tmp[j].push_back(to_dic[i]);
					pos = j;
				}
			}
			if(pos == -1){
				pos_num.push_back((to_dic[i].bottom + to_dic[i].top) / 2);
				vector<rect> t;
				t.push_back(to_dic[i]);
				tmp.push_back(t);
			}
		}
	}
	for(int i = 0;i < width;i++)
		for(int j = 0;j < height;j++)
			mapping[i][j] = false;
	CImg<unsigned char> divide_gray = this->gray;
	change_gray3(0);
	for(int i = 0;i < tmp.size();i++){
		left = width;right = 0;top = height;bottom = 0;
		if(tmp[i].size() <= 1){
			continue;
		}
		vector<rect> t1;
		result.push_back(t1);
		int num = result.size() - 1;
		for(int j = 0;j < tmp[i].size();j++){
			if(j > 0){
				int min_top,max_bottom;
				if(tmp[i][j-1].top > tmp[i][j].top)
					min_top = tmp[i][j-1].top;
				else
					min_top = tmp[i][j].top;
				if(tmp[i][j-1].bottom < tmp[i][j].bottom)
					max_bottom = tmp[i][j-1].bottom;
				else
					max_bottom = tmp[i][j].bottom;
				int lefta=width,righta=0,topa=height,bottoma=0,lengtha = 0;
				int num_between = 0;
				for(int p = tmp[i][j-1].right; p < tmp[i][j].left;p++){
					for(int k = min_top;k < max_bottom;k++){
						if(this->gray(p,k) == 0)
							// num_between += 1;
							num_between += find_length(p,k,200,lefta,righta,topa,bottoma);
					}
				}
				// cout << tmp[i][j-1].right << " " << tmp[i][j].left << " " << num_between << endl;	
				
				if(num_between >= 500){					
					rect t;t.left = left;t.right = right;t.top = top;t.bottom = bottom;
					result[num].push_back(t);
					left = width;right = 0;top = height;bottom = 0;
				}
					
			}
			if(tmp[i][j].left < left)
				left = tmp[i][j].left;
			if(tmp[i][j].right > right)
				right = tmp[i][j].right;
			if(tmp[i][j].top < top)
				top = tmp[i][j].top;
			if(tmp[i][j].bottom > bottom)
				bottom = tmp[i][j].bottom;
		}					
		rect t;
		t.left = left;
		t.right = right;
		t.top = top;
		t.bottom = bottom;
		result[num].push_back(t);
		int pos = -1;
		for(int j = 0;j < result.size();j++){
			if(top + bottom < result[j][0].top + result[j][0].bottom){
				pos = j;
				break;
			}
		}
		if(pos != -1){
			result.insert(result.begin() + pos,result[num]);
			result.pop_back();
		}
	}
	this->num_result = result;
	for(int i = 0;i < width;i++)
		for(int j = 0;j < height;j++)
			mapping[i][j] = false;
	change_gray();
	use_otsu();
	for(int i = 0;i < result.size();i++){
		for(int j = 0;j < result[i].size();j++){
			for(int p = result[i][j].right + 1;p < width;p++){
				for(int k = result[i][j].top; k < result[i][j].bottom;k++){
					if(this->gray(p,k) == 0){
						left = width;right = 0;top = height;bottom = 0;
						find_length(p,k,200,left,right,top,bottom);
						if(top >= this->num_result[i][j].top && bottom < this->num_result[i][j].bottom){
							this->num_result[i][j].right = right + 1;
						}
					}
				}
			}
		}
	}
}

void HomeWork6::draw_three_areas(){
	for(int i = 0;i < this->num_result[0].size();i++)
		this->image.draw_rectangle(this->num_result[0][i].left, this->num_result[0][i].top,this->num_result[0][i].right, this->num_result[0][i].bottom,this->red,1,~0U);
	for(int i = 0;i < this->num_result[1].size();i++)
		this->image.draw_rectangle(this->num_result[1][i].left, this->num_result[1][i].top,this->num_result[1][i].right, this->num_result[1][i].bottom,this->blue,1,~0U);
	for(int i = 0;i < this->num_result[2].size();i++)
		this->image.draw_rectangle(this->num_result[2][i].left, this->num_result[2][i].top,this->num_result[2][i].right, this->num_result[2][i].bottom,this->green,1,~0U);
}
void HomeWork6::draw_all_bracket(){	
	for(int i = 0;i < this->all_bracket.size();i++){
		this->image.draw_rectangle(this->all_bracket[i].left, this->bracket_pos,this->all_bracket[i].right, rule_pos.top,this->blue,1,~0U);
		this->image.draw_rectangle(this->all_bracket[i].top, this->bracket_pos,this->all_bracket[i].top, rule_pos.top,this->red,1,~0U);
	}
}
void HomeWork6::draw_every_num(){
	for(int i = 0;i < this->every_num[0].size();i++)
		this->image.draw_rectangle(this->every_num[0][i].left, this->every_num[0][i].top,this->every_num[0][i].right, this->every_num[0][i].bottom,this->red,1,~0U);
	for(int i = 0;i < this->every_num[1].size();i++)
		this->image.draw_rectangle(this->every_num[1][i].left, this->every_num[1][i].top,this->every_num[1][i].right, this->every_num[1][i].bottom,this->blue,1,~0U);
	for(int i = 0;i < this->every_num[2].size();i++)
		this->image.draw_rectangle(this->every_num[2][i].left, this->every_num[2][i].top,this->every_num[2][i].right, this->every_num[2][i].bottom,this->green,1,~0U);
	// cout << this->every_num.size() << endl;
	// for(int i = 0;i < this->every_num.size();i++){
		// for(int j = 0;j < this->every_num[i].size();j++){
			// this->image.draw_rectangle(this->every_num[i][j].left, this->every_num[i][j].top,this->every_num[i][j].right, this->every_num[i][j].bottom,this->blue,1,~0U);
		// }
	// }
}
void HomeWork6::set_mapping(){
	for(int i = 0;i < width;i++){
		for(int j = 0;j < height;j++)
			this->mapping[i][j] = false;
	}
}

void HomeWork6::find_bracket(){
	int bra_pos = this->num_result[2][0].top;
	int bra_left = this->num_result[2][0].left;
	int bra_right = this->num_result[2][0].right;
	for(int i = 0;i < this->num_result[2].size();i++){
		if(this->num_result[2][i].top < bra_pos)
			bra_pos = this->num_result[2][i].top;
		if(this->num_result[2][i].left < bra_left)
			bra_left = this->num_result[2][i].left;
		if(this->num_result[2][i].right > bra_right)
			bra_right = this->num_result[2][i].right;
	}
	int max_length = 0;
	int pos = 0;
	for(int j = bra_pos;j < bra_pos + 15;j++){
		int num = 0;
		for(int i = bra_left;i < bra_right;i++){
			if(this->gray(i,j) == 0)
				num += 1;
		}
		if(num > max_length){
			max_length = num;
			pos = j;
		}
	}
	int num = 0;
	change_gray();
	for(int i = 0;i < width;i++){
		for(int j = 0;j < height;j++)
			if(this->gray(i,j) != 255)
				this->gray(i,j) = 0;
	}
	int left_pos = -1,right_pos = -1,num1 = 0;
	rect t;t.top = pos;t.bottom = pos;int middle_pos = -1;
	for(int i = 20;i < width;i++){
		num = 0;num1 = 0;
		for(int j = 0;j < 10;j++){
			if(this->gray(i,pos-j) == 0)
				num += 1;
		}
		for(int j = -10;j < 0;j++){
			if(this->gray(i,pos-j) == 0)
				num1 += 1;
		}
		if(num >= 3){
			num = i;
			for(int j = i+1;j < width;j++){
				if(this->gray(j,pos-2) == 255){
					i = j;
					break;
				}
			}
			if(i - num - 1 == 1){
				if(left_pos == -1)
					num = i-1;
			}
			else if(i - num - 1 > 1)
				num = (num + i - 1) / 2;
			if(left_pos == -1){
				left_pos = num;
				if(middle_pos != -1){
					t.right = num;
					t.left = all_bracket[all_bracket.size()-1].right;
					t.top = middle_pos;
					all_bracket.push_back(t);
					left_pos = -1;right_pos = -1;middle_pos = -1;
				}
			}
			else{
				right_pos = num;
				t.left = left_pos;
				t.right = right_pos;
				if(middle_pos != -1)
					t.top = middle_pos;
				else
					t.top = (left_pos + right_pos) / 2;
				all_bracket.push_back(t);
				left_pos = -1;right_pos = -1;middle_pos = -1;
			}
			// this->image.draw_rectangle(num, pos-5,num, pos,this->blue,1,~0U);
		}
		else{
			if(num1 >= 5){
				num1 = i;
				for(int j = i+1;j < width;j++){
					if(this->gray(j,pos+3) == 255){
						i = j;
						break;
					}
				}
				if(i - num1 - 1 != 1)
					num1 = (num1 + i - 1) / 2;
				// this->image.draw_rectangle(num1, pos,num1, pos+5,this->red,1,~0U);
				middle_pos = num1;
			}
		}
	}
	set_mapping();
	int left = width,right = 0,top = height,bottom = 0,max_bottom = 0;
	for(int i = 0 ;i < this->all_bracket.size();i++){
		if(this->gray(this->all_bracket[i].left,pos) == 0){
			left = width;right = 0;top = height;bottom = 0;
			find_length(this->all_bracket[i].left,pos,200,left,right,top,bottom);
			if(bottom > max_bottom)
				max_bottom = bottom;
		}
	}
	for(int i = 0;i < this->num_result[2].size();i++)
		this->num_result[2][i].top = max_bottom + 1;
	this->bracket_pos = pos;
}
void HomeWork6::find_bracket1(){
	change_gray3(0);
	// show();
	rect t;
	int num_left = 0,num_right = 0;
	int pos = height;
	for(int i = 0 ;i < this->every_num[2].size();i++)
		if(this->every_num[2][i].top < pos)
			pos = this->every_num[2][i].top;
	for(int i = 0;i < this->every_num[2].size();i++){
		num_left = -1;num_right = -1;
		// this->image.draw_rectangle(this->every_num[2][i].left - 10, pos,this->every_num[2][i].right + 10, pos,this->red,1,~0U);
		for(int j = 0;j < 10;j++){
			if(this->gray(this->every_num[2][i].left - j,pos) == 0 && num_left < 0)
				num_left = this->every_num[2][i].left - j;
			if(this->gray(this->every_num[2][i].right + j,pos) == 0 && num_right < 0)
				num_right = this->every_num[2][i].right + j;
			if(num_left >= 0 && num_right >= 0)
				break;
		}
		if(num_left >= 0 && num_right >= 0){
			t.left = num_left;
			t.right = num_right;
			t.top = (num_left + num_right) / 2;
			t.bottom = pos;
			all_bracket.push_back(t);
		}
	}
	this->bracket_pos = pos;
	// cout << all_bracket.size() << endl;
}

void HomeWork6::get_bracket_result(){
	change_gray();
	use_otsu();
	int num = 0;
	vector<int> the_place;
	for(int i = 0;i < width-5;i++){
		num = 0;
		for(int j = 0;j < 15;j++){
			if(this->gray(i,rule_pos.top + j) == 0)
				num += 1;
		}
		if(num >= 10){
			for(int j = i + 1;j < i + 5;j++){
				num = 0;
				for(int k = 0;k < 15;k++){
					if(this->gray(j,rule_pos.top + k) == 0)
						num += 1;
				}
				if(num < 10){
					num = (i + j - 1) / 2;
					break;
				}
				else
					num = i;
			}
			the_place.push_back(num);
			i = num + 1;
			// this->image.draw_rectangle(num, rule_pos.top,num, rule_pos.top + 10,this->blue,1,~0U);
		}
	}
	
	this->between = 0.5 / (the_place[the_place.size() - 1] - the_place[the_place.size() - 2]);
	this->start = the_place[the_place.size() - 1];
	double bais = -0.5;
	for(int i = 0;i < this->all_bracket.size();i++){
		printf("%lf %lf\n",(this->start - all_bracket[i].right) * this->between + bais,(this->start - all_bracket[i].left) * this->between + bais);
	}
}

void HomeWork6::recognition_number_by_template(int num1,int num2){
	change_gray();
	cout << "The result of recognition numbers !" << endl;
	for(int i = 0;i < this->to_dic.size();i++){
		this->image.draw_rectangle(to_dic[i].left, to_dic[i].top,to_dic[i].right, to_dic[i].bottom,this->red,1,~0U);
		cout << dic_num(to_dic[i].left, to_dic[i].top,to_dic[i].right, to_dic[i].bottom) << " ";
		if((i + 1) % num2 == 0)
			cout << endl;
		if((i + 1) % num2 == num1)
			cout << " . ";
	}
}
void HomeWork6::recognition_number_by_re(int num1,int num2){
	change_gray();
	cout << "The result of recognition numbers !" << endl;
	for(int i = 0;i < this->to_dic.size();i++){
	// for(int i = 32;i < this->to_dic.size();i++){
	// for(int i = 14*4;i < this->to_dic.size();i++){
	// for(int i = 24*4;i < this->to_dic.size();i++){
		// this->image.draw_rectangle(to_dic[i].left, to_dic[i].top,to_dic[i].right, to_dic[i].bottom,this->red,1,~0U);
		if((to_dic[i].right - to_dic[i].left) < (to_dic[i].bottom - to_dic[i].top)){
			CImg<unsigned char> number_image(to_dic[i].right - to_dic[i].left,to_dic[i].bottom - to_dic[i].top,depth,1);
			for(int j = to_dic[i].left;j < to_dic[i].right;j++){
				for(int k = to_dic[i].top;k < to_dic[i].bottom;k++){
					number_image(j - to_dic[i].left,k - to_dic[i].top) = this->gray(j,k);
				}
			}
			cout << dic_num2(number_image) << " ";
		}else{
			CImg<unsigned char> number_image(to_dic[i].bottom - to_dic[i].top,to_dic[i].right - to_dic[i].left,depth,1);
			for(int j = to_dic[i].left;j < to_dic[i].right;j++){
				for(int k = to_dic[i].top;k < to_dic[i].bottom;k++){
					number_image(k - to_dic[i].top,j - to_dic[i].left) = this->gray(j,to_dic[i].bottom - 1 - k + to_dic[i].top);
				}
			}
			cout << dic_num2(number_image) << " ";
		}
		if((i + 1) % num2 == 0)
			cout << endl;
		if((i + 1) % num2 == num1)
			cout << " . ";
	}
}
void HomeWork6::recognition_number_by_template1(int num1,int num2){
	change_gray();
	cout << "The result of recognition numbers !" << endl;
	for(int i = 0;i < this->to_dic.size();i++){
	// for(int i = 0;i < 4;i++){
		this->image.draw_rectangle(to_dic[i].left, to_dic[i].top,to_dic[i].right, to_dic[i].bottom,this->red,1,~0U);
		cout << dic_num1(to_dic[i].left, to_dic[i].top,to_dic[i].right, to_dic[i].bottom) << " ";
		if((i + 1) % num2 == 0)
			cout << endl;
		if((i + 1) % num2 == num1)
			cout << " . ";
	}
}