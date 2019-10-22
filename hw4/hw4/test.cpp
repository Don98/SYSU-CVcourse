#include <iostream>
#include "../CImg.h"
#include "HomeWork4.cpp"
#include <string.h>
using namespace std;
using namespace cimg_library;
//g++ -o a.exe test.cpp -O2 -lgdi32
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

void use_two_peaks(char *argv[]){
	char name[50] = "test_data/A.bmp";
	char name1[50] = "use_two_peaks/resultA.bmp";
	int num = get_num(argv[6]);
	for(int i = 0;i < num;i++){
		HomeWork4 t1(name);
		t1.change_gray();
		t1.use_two_peaks();
		t1.save(name1);
		name[10] += 1;
		name1[20] += 1;
	}
}

void use_iter(char *argv[]){
	char name[50] = "test_data/A.bmp";
	char name1[50] = "use_iter/resultA.bmp";
	int num = get_num(argv[6]);
	for(int i = 0;i < num;i++){
		HomeWork4 t1(name);
		t1.change_gray();
		t1.use_iter();
		t1.save(name1);
		name[10] += 1;
		name1[15] += 1;
	}
}

void use_otsu(char *argv[]){
	char name[50] = "test_data/A.bmp";
	char name1[50] = "otsu_method/resultA.bmp";
	int num = get_num(argv[6]);
	for(int i = 0;i < num;i++){
		HomeWork4 t1(name);
		t1.change_gray();
		t1.use_otsu();
		t1.save(name1);
		name[10] += 1;
		name1[18] += 1;
	}
}

void task2(char *argv[]){
	HomeWork4 t(argv[1]);
	t.change_gray();
	t.show();
	int num = get_num(argv[2]);
	for(int i = 0;i < num;i++)
		t.delate();
	t.show();
	t.delete_big(get_num(argv[3]));
	t.show();
	t.save1(argv[4]);
}

void recognition_number_by_tesseract(char *argv[]){	
	HomeWork4 t(argv[1]);
	t.change_gray();
	int num = get_num(argv[2]);
	for(int i = 0;i < num;i++)
		t.delate();
	t.find_rule();
	t.recognition_number_by_tesseract();
}

void recognition_number_by_template(char *argv[]){
	HomeWork4 t1(argv[5]);
	t1.change_gray1();
	t1.divide_digits();
	
	HomeWork4 t(argv[1]);
	t.change_gray();
	t.read_digits();
	int num = get_num(argv[2]);
	for(int i = 0;i < num;i++)
		t.delate();
	t.find_rule();
	t.recognition_number_by_template();
}

int main(int argc, char* argv[]){	
	// task2(argv);
	// recognition_number_by_tesseract(argv);
	// recognition_number_by_template(argv);
	// use_two_peaks(argv);
	// use_iter(argv);
	use_otsu(argv);
}