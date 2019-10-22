#include <iostream>
#include <vector>
#include <string.h>
#include <math.h>
#include "../CImg.h"
using namespace std;
using namespace cimg_library;

// #define abs(x) (x>=0?x:-x)
#define NOEDGE 255
#define EDGE 0
#define POSSIBLE_EDGE 150

double sin_value[180];
double cos_value[180];
double sin_value1[360];
double cos_value1[360];

int L[3] = {-1,0,1};

class Hough_class{
	public:
		Hough_class(){};
		CImg<unsigned char> get_gray(CImg<unsigned char> image){
			int width = image.width();
			int height = image.height();
			int depth = image.depth();
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
			return gray1;
		}

		CImg<unsigned char> eq(CImg<unsigned char> image){
			int width = image.width();
			int height = image.height();
			int depth = image.depth();
			CImg<unsigned char> new_image(width,height,depth,1);
			double bins[256] = {0.0},p[256] = {0.0},c[256] = {0.0};
			int num = 0;
			for(int i=0;i<width;i++){
				for(int j=0;j<height;j++){
					bins[(int) image(i,j)] += 1;
				}
			}
			for(int i = 0;i < 256;i++){
				p[i] = bins[i] / (width * height);
			}
			c[0] = p[0];
			for(int i = 1;i < 256;i++){
				c[i] = c[i-1] + p[i];
			}
			for(int i=0;i<width;i++){
				for(int j=0;j<height;j++){
					num = (int)image(i,j);
					new_image(i,j) = (unsigned char) (255 * c[num]);
				}
			}
			return new_image;
			
		}

		int find_length(CImg<unsigned char> image,int i,int j,int a,int b,vector<vector<int> > &pos,int num){
			int length = 0;
			int width = image.width();
			int height = image.height();
			for(int p = 0;p < 3;p++){
				for(int k = 0;k < 3;k++){
					int x = i + L[p];
					int y = j + L[k];
					// cout << x << " " << y << endl;
					if (x >= 0 && x <= width-1 && y >= 0 && y <= height-1 && (int)image(x,y) == num && pos[x - a + 5][y - b + 5] != 1){
						// cout << x << " " << y << endl;
						pos[x - a + 5][y - b + 5] = 1;
						length += find_length(image,x,y,a,b,pos,num) + 1;
					}
				}
			}
			return length;
		}
		CImg<unsigned char> dispose_one_short(CImg<unsigned char> image){
			int width = image.width();
			int height = image.height();
			int depth = image.depth();
			CImg<unsigned char> new_image(width,height,depth,1);
			int size = 11;
			vector<vector<int> > pos(size,vector<int>(size));
			for(int i=0;i<width;i++){
				for(int j=0;j<height;j++){
					if((int)image(i,j) == 0)
					{
						for(int p = 0;p < size;p++)
							for(int k = 0;k < size; k++)
								pos[p][k] = 0;
						pos[size/2][size/2] = 1;
						cout << i << " " << j << endl;
						int length = find_length(image,i,j,i,j,pos,(int)image(i,j)) + 1;
						if(length < 10){
							for(int p = 0;p < size;p++){
								for(int k = 0;k < size; k++){
									if(pos[p][k] == 1){
										new_image(i - size / 2 + p,j - size/2 + k) = 255;
									}
								}
							}
						}
						else
							new_image(i,j) = image(i,j);
					}
				}
			}
			return new_image;
		}

		int get_x(int x , int pos, double roate){
			if(roate == 0.0 || roate == 180.0)
				return x;
			if(roate == 45.0)
				return x - pos;
			return x + pos;
		}
		int get_y(int y , int pos, double roate){
			if(roate == 90.0)
				return y;
			return y + pos;
		}

		void compute(vector<vector<int> > &magnitude,vector<vector<double> > diretion,int width,int height,int i , int j,vector<vector<int> > &is_sup){
			int L[2] = {0,0};
			int add[2] = {-1,1};
			int a = i ,b = j,x = i,y = j;
			
			x = get_y(i,1,diretion[i][j]);
			y = get_x(j,1,diretion[i][j]);
			
			int max = 0;
			if(x >= 0 && x<= width-1 && y >= 0 && y <= height-1){
				if(magnitude[i][j] < magnitude[x][y]){
					magnitude[i][j] = 0;
					max = 1;
				}
				else
					magnitude[x][y] = 0;
			}
			int x1 = get_y(i,-1,diretion[i][j]);
			int y1 = get_x(j,-1,diretion[i][j]);
			
			if(x1 >= 0 && x1<= width-1 && y1 >= 0 && y1 <= height-1){
				if(max == 1){
					if(magnitude[i][j] < magnitude[x1][y1]){
						magnitude[i][j] = 0;
						max = magnitude[x1][y1];
					}
					else{
						max = magnitude[i][j];
						magnitude[x1][y1] = 0;
					}
				}
				else{
					if(magnitude[x][y] < magnitude[x1][y1])
						magnitude[x][y] = 0;
					else
						magnitude[x1][y1] = 0;
				}
			}
			
			/*
			for(int k = 0;k < 2;k++){
				// while(true){
				for(int p = 0;p < 2;p++){
					x = get_y(i,L[k],diretion[i][j]);
					y = get_x(j,L[k],diretion[i][j]);
					if(x >= 0 && x<= width-1 && y >= 0 && y <= height-1 && diretion[x][y] == diretion[i][j] && L[k] <= 20){				
						// cout << x << " " << y << " ";
						// printf("%lf\n",diretion[x][y]);
						L[k] += add[k];
						is_sup[x][y] = 1;
						if(magnitude[x][y] <= magnitude[a][b])
							magnitude[x][y] = 0;
						else{
							magnitude[a][b] = 0;
							a = x;b = y;
						}
					}
					else{
						// magnitude[a][b] = 255;
						break;
					}
				}
			}
			// cout << a << " && " << b << endl;
			*/
		}

		int nms(vector<vector<int> > magnitude,vector<vector<int> > &diretion,vector<vector<int> > delta_x,vector<vector<int> > delta_y,int width,int height){
			int mag,gx,gy,g1,g2,g3,g4,max = 0;
			double weight,tmp1,tmp2;
			for(int i=1;i<width-1;i++){
				for(int j=1;j<height-1;j++){
					if(magnitude[i][j] == 0)
						continue;
					mag = magnitude[i][j];
					gx = delta_x[i][j];
					gy = delta_y[i][j];
					if(abs(gy) > abs(gx)){
						weight = abs(gx)/abs(gy);
						g2 = magnitude[i][j-1];
						g4 = magnitude[i][j+1];
						if(gx * gy > 0){
							g1 = magnitude[i-1][j-1];
							g3 = magnitude[i+1][j+1];
						}
						else{
							g1 = magnitude[i+1][j-1];
							g3 = magnitude[i-1][j+1];
						}
					}
					else{
						weight = abs(gy) / abs(gx);
						g2 = magnitude[i+1][j];
						g4 = magnitude[i-1][j];
						if(gx * gy > 0){
							g1 = magnitude[i+1][j+1];
							g3 = magnitude[i-1][j-1];
						}
						else{
							g1 = magnitude[i-1][j+1];
							g3 = magnitude[i+1][j-1];
						}
					}
					tmp1 = weight * g1 + (1 - weight) * g2;
					tmp2 = weight * g3 + (1 - weight) * g4;
					if(mag >= tmp1 && mag >= tmp2)
						diretion[i][j] = mag;
					else
						diretion[i][j] = 0;
					if(mag > max)
						max = mag;
				}
			}
			return max;
		}

		void apply_hysteresis(vector<vector<int> > &diretion,int max,int width,int height,double TH,double TL){
			printf("TH : 0.3max : %lf Tl : 0.1max : %lf\n",0.3*max ,0.1*max);
			// double TH = 0.3*max,TL = 0.1*max;
			// double TH = 200,TL = 5;
			int flag123 = 0;
			for(int i=1;i<width-1;i++){
				for(int j=1;j<height-1;j++){
					if(diretion[i][j] >= TH)
						diretion[i][j] = 255;
					else if(diretion[i][j] <= TL)
						diretion[i][j] = 0;
					else{
						flag123 = 0;
						for(int p = 0;p < 2;p++){
							for(int k = 0;k < 2;k++){
								if(!(p != 1 && k != 1) && diretion[i + L[p]][j + L[k]] >= TH){
									flag123 = 1;
									break;
								}
							}
							if(flag123)	break;
						}
						if(flag123)
							diretion[i][j] = 255;
						else
							diretion[i][j] = 0;
					}
				}
			}
		}

		void Hough(vector<vector<int> > diretion,CImg<unsigned char> &hough_image,vector<vector<int> > &is_sup,char * num_length,int width,int height){
			int tp;
			int min = 9999,max = 0;
			for(int i=0;i<width;i++){
				for(int j=0;j<height;j++){
					if(diretion[i][j] != 255)
						continue;
					for(int k = 0;k < 180;k++){
						tp = (int)(i*sin_value[k] + j*cos_value[k]) + width + height;
						is_sup[tp][k] += 1;
						if(max < tp)	max = tp;
						if(min > tp)	min = tp;
					}
				}
			}
			int length = max - min;
			// cout << min << " " << max << endl;

			for(int i = 0;i < (width + height)*2;i++){
				for(int j = 0;j < 180;j++){
					hough_image(i,j) = (unsigned char) ((is_sup[i][j] - min) * 255 / length);
				}
			}
		}

		void Hough_circle(vector<vector<vector<int> > > &circle,vector<vector<int> > diretion,int width,int height,int R1,int R2){
			int x0 = 0,y0 = 0;
			int max = 0;
			for(int k = R1;k < R2;k++){
				for(int i = 0;i < width;i++){
					for(int j = 0;j < height;j++){
						// if(diretion[i][j] != 255){
							for(int p = 0;p < 360;p++){
								// cout << x0 << " " << y0 << endl;
								x0 = (int)(j - k * cos_value1[p]);
								y0 = (int)(i - k * sin_value1[p]);
								// cout << k << " " << i << " " << j << " " << p << " " << x0 << " " << y0 << endl;
								if(x0 >= 0 && x0 < width && y0 >= 0 && y0 < height){	
									circle[k][x0][y0] += 1;
									if(circle[k][x0][y0] > max)
										max = circle[k][x0][y0];
								}
							}
						// }
					}
				}
			}
			cout << "max : " << max << endl;
		}

		int find_best(CImg<unsigned char> image,int tp,int k){
			int width = image.width();
			int height = image.height();
			
			int num = 0;
			for(int i = 0;i < width;i++){
				for(int j = 0;j < height;j++){
					if(tp == (int)(i*sin_value[k] + j*cos_value[k]) + width + height && image(i,j,0) == 255 && image(i,j,1) == 255 && image(i,j,2) == 255)
						num += 1;
				}
			}
			return num;
		}

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

		CImg<unsigned char> conlove(CImg<unsigned char> image,char * name, char * num_length , char * num_min, char * num_max, char * the_flag, char * R1,char *R2){
			int width = image.width();
			int height = image.height();
			int depth = image.depth();
			CImg<unsigned char> conlove_image(width,height,depth,3);
			image.blur(1.5);
			// return image;
			vector<vector<int> > delta_x(width,vector<int>(height));
			for(int i=0;i<width;i++){
				 for(int j=0;j<height;j++){
					delta_x[i][j] = 0;
				 }
			}
			vector<vector<int> > delta_y(width,vector<int>(height));
			for(int i=0;i<width;i++){
				 for(int j=0;j<height;j++){
					delta_y[i][j] = 0;
				 }
			}
			vector<vector<int> > magnitude(width,vector<int>(height));
			for(int i=0;i<width;i++){
				 for(int j=0;j<height;j++){
					magnitude[i][j] = 0;
				 }
			}
			vector<vector<int> > is_sup((width + height)*2,vector<int>(180));
			for(int i=0;i<(width + height)*2;i++){
				 for(int j=0;j<180;j++){
					is_sup[i][j] = 0;
				 }
			}
			vector<vector<int> > record((width + height)*2,vector<int>(180));
			for(int i=0;i<(width + height)*2;i++){
				 for(int j=0;j<180;j++){
					record[i][j] = 0;
				 }
			}
			
			CImg<unsigned char> hough_image((width+height)*2,180,depth,1);
			
			
			vector<vector<int> > diretion(width,vector<int>(height));
			for(int i=0;i<width;i++){
				 for(int j=0;j<height;j++){
					diretion[i][j] = 0;
				 }
			}
			vector<vector<int> > tmp(width,vector<int>(height));
			vector<vector<vector<int> > > circle;
			for(int i=0;i<width;i++){
				 for(int j=0;j<height;j++){
					tmp[i][j] = 0;
				 }
			}
			for(int i = 0;i < 360;i++){
				circle.push_back(tmp);
			}
			// image = eq(image);
			// return image;
			// int kernel[3][3] = {{1,1,1},{1,-8,1},{1,1,1}};
			int kernelx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
			int kernely[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
			double four_min;
			int find_min;
			for(int i=0;i<width;i++){
				for(int j=0;j<height;j++){
					if (i == 0 || j == 0 || i == width - 1 || j == height - 1){
						delta_x[i][j] = (int)image(i,j);
						delta_y[i][j] = (int)image(i,j);
					}
					else{
						for(int p = 0;p < 3;p++){
							for(int k = 0;k < 3;k++){
								delta_x[i][j] += kernelx[p][k] * (int)image(i + L[p],j + L[k]);
								delta_y[i][j] += kernely[p][k] * (int)image(i + L[p],j + L[k]);
							}
						}
						magnitude[i][j] = sqrt(delta_x[i][j] * delta_x[i][j] + delta_y[i][j] * delta_y[i][j]);
					}
				}
			}
			int max = nms(magnitude,diretion,delta_x,delta_y,width,height);
			// cout << max << endl;
			// printf("%lf %lf \n",1.0*get_num(num_min),1.0*get_num(num_max));
			apply_hysteresis(diretion,max,width,height,1.0*get_num(num_min),1.0*get_num(num_max));
			
			for(int i=0;i<width;i++){
				for(int j=0;j<height;j++){
					conlove_image(i,j,0) = (unsigned char) diretion[i][j];
					conlove_image(i,j,1) = (unsigned char) diretion[i][j];
					conlove_image(i,j,2) = (unsigned char) diretion[i][j];
				}
			}	
			conlove_image.save(name);
			int length1 = get_num(num_length);
			
			if(*the_flag == '0'){
				Hough(diretion,hough_image,is_sup,num_length,width,height);
				vector<int> hough_result_x;
				vector<int> hough_result_y;
				vector<int> new_hough_result_x;
				vector<int> new_hough_result_y;
				int tp,flag;
				for(int i=0;i<width;i++){
					for(int j=0;j<height;j++){
						for(int k = 0;k < 180;k++){
							tp = (int)(i*sin_value[k] + j*cos_value[k]) + width + height;
							if(is_sup[tp][k] >= length1){
								flag = 0;
								if(new_hough_result_x.size() != 0){
									for(int p = 0;p < new_hough_result_x.size();p++){
										if(new_hough_result_x[p] == tp && new_hough_result_y[p] == k){
											flag = 1;
											break;
										}
										if(abs(new_hough_result_x[p] - tp) <= 100 && abs(new_hough_result_y[p] - k) <=2){
											if(record[tp][k] == 0){
												record[tp][k] = find_best(conlove_image,tp,k);
											}
											if(record[tp][k] >= record[new_hough_result_x[p]][new_hough_result_y[p]]){
												new_hough_result_x[p] = tp;
												new_hough_result_y[p] = k;
											}
											flag = 1;
											break;
										}
									}
									if(flag != 1){
										new_hough_result_x.push_back(tp);
										new_hough_result_y.push_back(k);
									}
								}
								else{
									record[tp][k] = find_best(conlove_image,tp,k);
									new_hough_result_x.push_back(tp);
									new_hough_result_y.push_back(k);
								}
							}
						}
					}
				}
				for(int i = 0;i < new_hough_result_x.size();i++){
					flag = 0;
					for(int j = 0;j < new_hough_result_x.size();j++){
						if(abs(abs(new_hough_result_y[i] - new_hough_result_y[j]) - 90) <= 2){
							flag = 1;
							break;
						}
					}
					if(flag == 1){
						hough_result_x.push_back(new_hough_result_x[i]);
						hough_result_y.push_back(new_hough_result_y[i]);
					}
				}
				cout << hough_result_x.size() << " " << hough_result_y.size() << endl;
				cout << width << " " << height << endl;
				int R[11] = {-5,-4,-3,-2,-1,0,1,2,3,4,5};
				for(int i=5;i<width-5;i++){
					for(int j=5;j<height-5;j++){
						if(conlove_image(i,j,0) == 220 && conlove_image(i,j,1) == 20 && conlove_image(i,j,2) == 60)
							continue;
						for(int k = 0;k < hough_result_x.size();k++){
							if(hough_result_x[k] == (int)(i*sin_value[hough_result_y[k]] + j*cos_value[hough_result_y[k]]) + width + height){
								if(conlove_image(i,j,0) == 0 && conlove_image(i,j,1) == 0 && conlove_image(i,j,2) == 255){
									for(int p = 0;p < 11;p++){
										for(int p1 = 0;p1 < 11;p1++){
											conlove_image(i + R[p],j + R[p1],0) = 220;
											conlove_image(i + R[p],j + R[p1],1) = 20;
											conlove_image(i + R[p],j + R[p1],2) = 60;
										}
									}
								}
								else{
									conlove_image(i,j,0) = 0;
									conlove_image(i,j,1) = 0;
									conlove_image(i,j,2) = 255;
								}	
							}
						}
					}
				}
				cout << hough_result_x.size() << endl;
				for(int p = 0;p < hough_result_x.size();p++){
					cout << hough_result_x[p] << " " << hough_result_y[p] << endl;
				}
			}
			else{
				vector<int> hough_result_x;
				vector<int> hough_result_y;
				vector<int> hough_result_z;
				Hough_circle(circle,diretion,width,height,get_num(R1),get_num(R2));
				
				for(int k = get_num(R1);k < get_num(R2);k++){
					for(int i = 0;i < width;i++){
						for(int j = 0;j < height;j++){
							if(circle[k][i][j] >= length1){
								hough_result_x.push_back(i);
								hough_result_y.push_back(j);
								hough_result_z.push_back(k);
							}
						}
					}
				}
				// cout << hough_result_x[0] << " " << hough_result_y[0] << " " << hough_result_z[0] << endl;
				cout << hough_result_x.size() << endl;
				for(int i = 0;i < width;i++){
					for(int j = 0;j < height;j++){
						for(int k = 0;k < hough_result_x.size();k++){
						// for(int k = 0;k < 1;k++){
							if(abs((i-hough_result_x[k]) * (i - hough_result_x[k]) + (j - hough_result_y[k]) * (j - hough_result_y[k]) - hough_result_z[k] * hough_result_z[k]) <= 50){
									conlove_image(i,j,0) = 0;
									conlove_image(i,j,1) = 0;
									conlove_image(i,j,2) = 255;
							}
						}
					}
				}
			}
			// return hough_image;
			return conlove_image;
			// return conlove_image;
		}
		CImg<unsigned char> change_edge(CImg<unsigned char> image){
			int width = image.width();
			int height = image.height();
			int depth = image.depth();
			CImg<unsigned char> new_image(width,height,depth,1);
			int flag = 0;
			for(int i=1;i<width-1;i++){
				for(int j=1;j<height-1;j++){
					flag = 0;
					for(int p = 0;p < 3;p++){
						for(int k = 0;k < 3;k++){
							flag += (int) image(i + L[p],j + L[k]);
						}
					}
					if(!(flag == 0 || flag == 255*9))
						new_image(i,j) = 0;
					else
						new_image(i,j) = 255;
				}
			}
			return new_image;
		}
};

int main(int argc, char* argv[]){	
	for(int i=-90; i<90; i++){
		sin_value[i+90] = sin(i*3.1415926/180);
		cos_value[i+90] = cos(i*3.1415926/180);
	}
	for(int i=0; i<360; i++){
		sin_value1[i] = sin(i*3.1415926/180);
		cos_value1[i] = cos(i*3.1415926/180);
	}
	Hough_class t = Hough_class();
	CImg<unsigned char> image;
	// image.load_bmp("Dataset-EX3/Dataset1/IMG_20150320_143133.bmp");1 2 30
	// image.load_bmp("Dataset-EX3/Dataset2/1.bmp");1 2 60
	image.load_bmp(argv[1]);
	// cout << argv[0] << " " << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] << endl;
	CImg<unsigned char> gray = t.get_gray(image);
	gray = t.conlove(gray,argv[3],argv[4],argv[5],argv[6],argv[7],argv[8],argv[9]);
	
	
	
	// gray = change_edge(gray);
	// gray = dispose_one_short(gray);
	
	gray.display("2123");
	// gray.save("Dataset-EX3/Result_Dataset1/IMG_20150320_143133.bmp");
	gray.save(argv[2]);
}