#include <iostream>
#include "canny.h"
#include "canny.cpp"
using namespace std;

// g++ -O3 -o a 1.cpp -lm -lpthread -lX11
//./a lena.bmp result.bmp 2 0.9 0.8
int main(int argc, char *argv[]){		
	char *infilename = NULL; 
	char *outfilename = NULL;
	float sigma,tlow,thigh;
	if(argc != 6){
		cout << "Please input the right parameters!\n";
		exit(1);
	}
	infilename = argv[1];
	outfilename = argv[2];
	sigma = atof(argv[3]);
	tlow = atof(argv[4]);
	thigh = atof(argv[5]);
	Canny t(infilename,outfilename,sigma,tlow,thigh);
	t.read_bmp_image();
	t.canny();
	t.write_bmp_image();
}