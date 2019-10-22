#include<iostream>
#include<math.h>
#include "../CImg.h"
using namespace std;
using namespace cimg_library;
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

#define PI 3.1415926
void display(CImg<unsigned char> image){
	image.display("snkjs");
}

void change_color(CImg<unsigned char> image){
	CImg<unsigned char> new_image = image;
	cimg_forXY(image, x, y) {
		if (new_image(x,y,0) == 255 && new_image(x,y,1) == 255 && new_image(x,y,2) == 255) {
			new_image(x,y,0) = 255;
			new_image(x,y,1) = 0;
			new_image(x,y,2) = 0;
 		}
	}
	cimg_forXY(new_image,x,y){
		if(new_image(x,y,0) == 0 && new_image(x,y,1) == 0 && new_image(x,y,2) == 0){
			new_image(x,y,0) = 0;	
			new_image(x,y,1) = 255;	
			new_image(x,y,2) = 0;	
		}
	}
	// new_image.display("change_color");
	new_image.save("change_color.bmp");
}

void draw_tria_hand(CImg <unsigned char> &image,Point center,double length,Color color){
	CImg<unsigned char> new_image = image;
	int x0,y0,x1,y1,x2,y2;
	x0 = center.x; y0 = center.y + length / 2 / cos(PI / 180 * 30);
	x1 = center.x + length / 2; y1 = center.y - length / 2 * tan(PI / 180 * 30);
	x2 = center.x - length / 2; y2 = center.y - length / 2 * tan(PI / 180 * 30);    
	double tan60 = tan(PI / 180 * 60);
	double tan120 = tan(PI / 180 * 120);
	double b1 = tan(PI / 180 * 60) * x0 - y0;
	double b2 = tan(PI / 180 * 120) * x0 - y0;
	cimg_forXY(new_image,x,y){
		if(y > y1 && y + b1 - tan60 * x < 0 && y + b2 - tan120 * x < 0){
			new_image(x,y,0) = color.a;
			new_image(x,y,1) = color.b;
			new_image(x,y,2) = color.c;
		}
	}
	// new_image.display("draw_triangle_by_hand");
	new_image.save("draw_triangle_by_hand.bmp");
}

void draw_tria_func(CImg <unsigned char> &image,Point center,double length,Color color){
	CImg<unsigned char> new_image = image;
	int x0,y0,x1,y1,x2,y2;
	x0 = center.x; y0 = center.y + length / 2 / cos(PI / 180 * 30);
	x1 = center.x + length / 2; y1 = center.y - length / 2 * tan(PI / 180 * 30);
	x2 = center.x - length / 2; y2 = center.y - length / 2 * tan(PI / 180 * 30);    
	const unsigned char
         color1[]   = { color.a, color.b, color.c };
	new_image.draw_triangle(x0,y0,x1,y1,x2,y2,color1);
	// new_image.display("draw_triangle_by_func");
	new_image.save("draw_triangle_by_func.bmp");
}

void draw_circle_hand(CImg <unsigned char> &image,Point center,double length,Color color){
	CImg<unsigned char> new_image = image;
	cimg_forXY(new_image,x,y){
		if(pow((center.x - x),2) + pow((center.y - y),2) < length * length) {
			new_image(x,y,0) = color.a;
			new_image(x,y,1) = color.b;
			new_image(x,y,2) = color.c;
		}
	}
	// new_image.display("draw_circle_by_hand");
	new_image.save("draw_circle_by_hand.bmp");
}

void draw_circle_func(CImg <unsigned char> &image,Point center,double length,Color color){
	CImg<unsigned char> new_image = image;
	const unsigned char
         color1[]   = { color.a, color.b, color.c };
	new_image.draw_circle(center.x,center.y,length,color1);
	// new_image.display("draw_circle_by_func");
	new_image.save("draw_circle_by_func.bmp");
}

void draw_line_hand(CImg <unsigned char> &image,Point start,double roat,double length,Color color){
	CImg<unsigned char> new_image = image;
	roat = fmod(roat,90.0);
	double tanroat = tan(PI / 180 * roat);
	double b = tanroat * start.x - start.y;
	Point end = Point(int(start.x  + cos(PI / 180 * roat) * length),int(start.y + sin(PI / 180 * roat) * length));
	cimg_forXY(new_image,x,y){
		if(y + int(b) == int(tanroat * x) && pow((start.x - x),2) + pow((start.y - y),2) <= length * length && sqrt(pow((start.x - x),2) + pow((start.y - y),2)) + sqrt((pow((end.x - x),2) + pow((end.y - y),2))) <= length){
			new_image(x,y,0) = color.a; 
			new_image(x,y,1) = color.b;
			new_image(x,y,2) = color.c;
		}
	}
	// new_image.display("draw_line_by_hand");
	new_image.save("draw_line_by_hand.bmp");
}

void draw_line_func(CImg <unsigned char> &image,Point start,double roat,double length,Color color){
	CImg<unsigned char> new_image = image;
	roat = fmod(roat,90.0);
	Point end = Point(int(start.x  + cos(PI / 180 * roat) * length),int(start.y + sin
	(PI / 180 * roat) * length));
	const unsigned char
         color1[]   = { color.a, color.b, color.c };
	new_image.draw_line(start.x,start.y,end.x,end.y,color1);
	// new_image.display("draw_line_by_func");
	new_image.save("draw_line_by_func.bmp");
}

int main(){
	CImg<unsigned char> image;
	image.load_bmp("1.bmp");
	
	Point center = Point(50,50);
	Point start = Point(0,0);
	Color blue = Color(0,0,255);
	Color yellow = Color(200,155,0);
	Color green = Color(0,255,0);
	change_color(image);
	draw_tria_hand(image,center,40,blue);
	draw_tria_func(image,center,40,blue);
	draw_circle_hand(image,center,15,yellow);
	draw_circle_func(image,center,15,yellow);
	draw_line_hand(image,start,135,100,green);
	draw_line_func(image,start,135,100,green);
	// image.save("2.bmp");
}

// -O2 -lgdi32
// g++ -o a.exe 1.cpp -O2 -lgdi32