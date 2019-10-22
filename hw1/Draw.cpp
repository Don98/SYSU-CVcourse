#include<iostream>
#include<math.h>
#include "../CImg.h"
using namespace std;
using namespace cimg_library;

#define PI 3.1415926


// g++ -o a.exe Draw.cpp -O2 -lgdi32

struct Point{
	double x;
	double y;
	Point(double x1, double y1){
		x = x1;
		y = y1;
	}
};

struct Color{
	int a,b,c;
	Color(int a1, int b1, int c1){
		a = a1;
		b = b1;
		c = c1;
	}
};

class Draw{
	private:
		CImg<unsigned char> image;
	public:
		Draw(CImg<unsigned char> image1){
			this->image = image1;
		}
		// 展示image
		void display(){
		image.display("display");
		}
		// 将白色区域变成红色，黑色区域变成绿色,display表示是否展示，save表示是否保存
		void change_color(int display,int save){
			cimg_forXY(image, x, y) {
				if (image(x,y,0) == 255 && image(x,y,1) == 255 && image(x,y,2) == 255) {
					image(x,y,0) = 255;
					image(x,y,1) = 0;
					image(x,y,2) = 0;
				}
			}
			cimg_forXY(image,x,y){
				if(image(x,y,0) == 0 && image(x,y,1) == 0 && image(x,y,2) == 0){
					image(x,y,0) = 0;	
					image(x,y,1) = 255;	
					image(x,y,2) = 0;	
				}
			}
			if(display)
				image.display("change_color");
			if(save)
				image.save("draw_triangle_by_hand.bmp");
		}
		// 手动绘制等边三角形,display表示是否展示，save表示是否保存,center为中心点,length为等边三角形边长,color为填充颜色
		void draw_tria_hand(int display, int save,Point center,double length,Color color){
			int x0,y0,x1,y1,x2,y2;
			x0 = center.x; y0 = center.y + length / 2 / cos(PI / 180 * 30);
			x1 = center.x + length / 2; y1 = center.y - length / 2 * tan(PI / 180 * 30);
			x2 = center.x - length / 2; y2 = center.y - length / 2 * tan(PI / 180 * 30);
			double tan60 = tan(PI / 180 * 60);
			double tan120 = tan(PI / 180 * 120);
			double b1 = tan(PI / 180 * 60) * x0 - y0;
			double b2 = tan(PI / 180 * 120) * x0 - y0;
			cimg_forXY(image,x,y){
				if(y >= y1 && y + b1 - tan60 * x <= 0 && y + b2 - tan120 * x <= 0){
					image(x,y,0) = color.a;
					image(x,y,1) = color.b;
					image(x,y,2) = color.c;
				}
			}
			if(display)
				image.display("draw_triangle_by_hand");
			if(save)
				image.save("draw_triangle_by_hand.bmp");
		}
		// 调用函数画等边三角形,display表示是否展示，save表示是否保存,center为中心点,length为等边三角形边长,color为填充颜色
		void draw_tria_func(int display, int save,Point center,double length,Color color){
			int x0,y0,x1,y1,x2,y2;
			x0 = center.x; y0 = center.y + length / 2 / cos(PI / 180 * 30);
			x1 = center.x + length / 2; y1 = center.y - length / 2 * tan(PI / 180 * 30);
			x2 = center.x - length / 2; y2 = center.y - length / 2 * tan(PI / 180 * 30);
			const unsigned char
				 color1[]   = { color.a, color.b, color.c };
			image.draw_triangle(x0,y0,x1,y1,x2,y2,color1);
			if(display)
				image.display("draw_triangle_by_func");
			if(save)
				image.save("draw_triangle_by_func.bmp");
		}
		// 手动画圆,display表示是否展示，save表示是否保存,center为中心点,length为半径,color为填充颜色
		void draw_circle_hand(int display, int save,Point center,double length,Color color){
			cimg_forXY(image,x,y){
				if(pow((center.x - x),2) + pow((center.y - y),2) < length * length) {
					image(x,y,0) = color.a;
					image(x,y,1) = color.b;
					image(x,y,2) = color.c;
				}
			}
			if(display)
				image.display("draw_circle_by_hand");
			if(save)
				image.save("draw_circle_by_hand.bmp");
		}
		// 调用函数直接画圆,display表示是否展示，save表示是否保存,center为中心点,length为半径,color为填充颜色
		void draw_circle_func(int display, int save,Point center,double length,Color color){
			const unsigned char
				 color1[]   = { color.a, color.b, color.c };
			image.draw_circle(center.x,center.y,length,color1);
			if(display)
				image.display("draw_circle_by_func");
			if(save)
				image.save("draw_circle_by_func.bmp");
		}
		// 手动画线,display表示是否展示，save表示是否保存,start为起始点,roat为角度,length为长度,color为填充颜色
		void draw_line_hand(int display, int save,Point start,double roat,double length,Color color){
			roat = fmod(roat,90.0);
			double tanroat = tan(PI / 180 * roat);
			double b = tanroat * start.x - start.y;
			Point end = Point(int(start.x  + cos(PI / 180 * roat) * length),int(start.y + sin(PI / 180 * roat) * length));
			cimg_forXY(image,x,y){
				if(y + int(b) == int(tanroat * x) && pow((start.x - x),2) + pow((start.y - y),2) < length * length && sqrt(pow((start.x - x),2) + pow((start.y - y),2)) + sqrt((pow((end.x - x),2) + pow((end.y - y),2))) < length){
					image(x,y,0) = color.a; 
					image(x,y,1) = color.b;
					image(x,y,2) = color.c;
				}
			}
			if(display)
				image.display("draw_line_by_hand");
			if(save)
				image.save("draw_line_by_hand.bmp");
		}
		// 通过调用CImg直接画线,display表示是否展示，save表示是否保存,start为起始点,roat为角度,length为长度,color为填充颜色
		void draw_line_func(int display, int save,Point start,double roat,double length,Color color){
			roat = fmod(roat,90.0);
			Point end = Point(round(start.x  + cos(PI / 180 * roat) * length),round(start.y + sin
			(PI / 180 * roat) * length));
			const unsigned char
				 color1[]   = { color.a, color.b, color.c };
			image.draw_line(start.x,start.y,end.x,end.y,color1);
			if(display)
				image.display("draw_line_by_func");
			if(save)
				image.save("draw_line_by_func.bmp");
		}
		//保存操作过后的图片
		void save_image(){
			image.save("2.bmp");
		}
};
// 测试函数
void test()
{
	CImg<unsigned char> image;
	// image.load_bmp("1.bmp");
	image.load_bmp("untitled.bmp");
	
	Draw t = Draw(image);
	t.display();
	// Point center = Point(50,50);
	// Point start = Point(0,0);
	// Color blue = Color(0,0,255);
	// Color yellow = Color(200,155,0);
	// Color green = Color(0,255,0);
	// int display = 0;
	// int save = 0;
	
	// t.change_color(display,save);
	// t.draw_tria_hand(display,save,center,40,blue);
	// t.draw_tria_func(display,save,center,40,blue);
	// t.draw_circle_hand(display,save,center,15,yellow);
	// t.draw_circle_func(display,save,center,15,yellow);
	// t.draw_line_hand(display,save,start,135,100,green);
	// t.draw_line_func(display,save,start,135,100,green);
	// t.save_image();
}

int main(){
	test();
}
