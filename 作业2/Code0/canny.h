#ifndef _CANNY_
#define _CANNY_
#include <iostream>
#include <math.h>
#include "CImg.h"
using namespace std;
using namespace cimg_library;

#define NOEDGE 255
#define POSSIBLE_EDGE 128
#define EDGE 0

class Canny {
	private:
		CImg<unsigned char> image;
		char *infilename = NULL;  /* Name of the input image */
		char *outfilename = NULL;    /* Name of the output "edge" image */
   		int rows, cols;           /* The dimensions of the image. */
   		float sigma,              /* Standard deviation of the gaussian kernel. */
	 		tlow,               /* Fraction of the high threshold in hysteresis. */
	 		thigh;              /* High hysteresis threshold control. The actual
			        threshold is the (100 * thigh) percentage point
			        in the histogram of the magnitude of the
			        gradient image that passes non-maximal
			        suppression. */
		float distance;
	public:
		Canny(char *infilename1,char *outfilename,float sigma1,float tlow1,float thigh1);
		unsigned char show(int i, int j , int pos);
		void change_gray();
		int read_bmp_image();
		int write_bmp_image();
		void delete_line(unsigned char *edge);
		int find_length(unsigned char *edge,int pos,int *flag,int *num);
		void canny();
		void gaussian_smooth();
		void derrivative_x_y(short int **delta_x, short int **delta_y);
		void magnitude_x_y(short int *delta_x, short int *delta_y,short int **magnitude);
		void non_max_supp(short *mag, short *gradx, short *grady,unsigned char *result);
		void apply_hysteresis(short int *mag, unsigned char *nms,float tlow, float thigh, unsigned char *edge);
		void follow_edges(unsigned char *edgemapptr, short *edgemagptr, short lowval);
		void to_save_edge(unsigned char *edge);
		void connect_edge(unsigned char *edge);
		void set_distance(float new_distance);
};
#endif
