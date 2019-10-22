#include <iostream>
#include <math.h>
#include "CImg.h"
using namespace std;
using namespace cimg_library;
#include "canny.h"

Canny::Canny(char *infilename1,char *outfilename1,float sigma1,float tlow1,float thigh1){
	   this->infilename = infilename1;
	   this->outfilename = outfilename1;
	   this->sigma = sigma1;
	   this->tlow = tlow1;
	   this->thigh = thigh1;
	   this->distance = 5;
		}
int Canny::read_bmp_image(){
	image.load_bmp(this->infilename);
	this->rows = image.height();
	this->cols = image.width();
	return 1;
}
int Canny::write_bmp_image(){
	this->image.save(this->outfilename);
	return 1;
}
void Canny::gaussian_smooth(){
	this->image.blur(this->sigma);
}

void Canny::derrivative_x_y(short int **delta_x, short int **delta_y){
   int r, c, pos;
   if(((*delta_x) = (short *) calloc(rows*cols, sizeof(short))) == NULL){
      fprintf(stderr, "Error allocating the delta_x image.\n");
      exit(1);
   }
   if(((*delta_y) = (short *) calloc(rows*cols, sizeof(short))) == NULL){
      fprintf(stderr, "Error allocating the delta_x image.\n");
      exit(1);
   }
   for(r=0;r<rows;r++){
      pos = r * cols;
      (*delta_x)[pos] = image[pos+1] - image[pos];
      pos++;
      for(c=1;c<(cols-1);c++,pos++){
         (*delta_x)[pos] = image[pos+1] - image[pos-1];
      }
      (*delta_x)[pos] = image[pos] - image[pos-1];
   }
   for(c=0;c<cols;c++){
      pos = c;
      (*delta_y)[pos] = image[pos+cols] - image[pos];
      pos += cols;
      for(r=1;r<(rows-1);r++,pos+=cols){
         (*delta_y)[pos] = image[pos+cols] - image[pos-cols];
      }
      (*delta_y)[pos] = image[pos] - image[pos-cols];
	}
}

void Canny::non_max_supp(short *mag, short *gradx, short *grady,unsigned char *result){
    int rowcount, colcount,count;
    short *magrowptr,*magptr;
    short *gxrowptr,*gxptr;
    short *gyrowptr,*gyptr,z1,z2;
    short m00,gx,gy;
    float mag1,mag2,xperp,yperp;
    unsigned char *resultrowptr, *resultptr;
    for(count=0,resultrowptr=result,resultptr=result+cols*(rows-1);
        count<cols; resultptr++,resultrowptr++,count++){
        *resultrowptr = *resultptr = (unsigned char) 0;
    }

    for(count=0,resultptr=result,resultrowptr=result+cols-1;
        count<rows; count++,resultptr+=cols,resultrowptr+=cols){
        *resultptr = *resultrowptr = (unsigned char) 0;
    }
   for(rowcount=1,magrowptr=mag+cols+1,gxrowptr=gradx+cols+1,
      gyrowptr=grady+cols+1,resultrowptr=result+cols+1;
      rowcount<rows-2;
      rowcount++,magrowptr+=cols,gyrowptr+=cols,gxrowptr+=cols,
      resultrowptr+=cols){
      for(colcount=1,magptr=magrowptr,gxptr=gxrowptr,gyptr=gyrowptr,
         resultptr=resultrowptr;colcount<cols-2;
         colcount++,magptr++,gxptr++,gyptr++,resultptr++){
         m00 = *magptr;
         if(m00 == 0){
            *resultptr = (unsigned char) NOEDGE;
         }
         else{
            xperp = -(gx = *gxptr)/((float)m00);
            yperp = (gy = *gyptr)/((float)m00);
         }

         if(gx >= 0){
            if(gy >= 0){
                    if (gx >= gy)
                    {
                        /* 111 */
                        /* Left point */
                        z1 = *(magptr - 1);
                        z2 = *(magptr - cols - 1);

                        mag1 = (m00 - z1)*xperp + (z2 - z1)*yperp;

                        /* Right point */
                        z1 = *(magptr + 1);
                        z2 = *(magptr + cols + 1);

                        mag2 = (m00 - z1)*xperp + (z2 - z1)*yperp;
                    }
                    else
                    {
                        /* 110 */
                        /* Left point */
                        z1 = *(magptr - cols);
                        z2 = *(magptr - cols - 1);

                        mag1 = (z1 - z2)*xperp + (z1 - m00)*yperp;

                        /* Right point */
                        z1 = *(magptr + cols);
                        z2 = *(magptr + cols + 1);

                        mag2 = (z1 - z2)*xperp + (z1 - m00)*yperp;
                    }
                }
                else
                {
                    if (gx >= -gy)
                    {
                        /* 101 */
                        /* Left point */
                        z1 = *(magptr - 1);
                        z2 = *(magptr + cols - 1);

                        mag1 = (m00 - z1)*xperp + (z1 - z2)*yperp;

                        /* Right point */
                        z1 = *(magptr + 1);
                        z2 = *(magptr - cols + 1);

                        mag2 = (m00 - z1)*xperp + (z1 - z2)*yperp;
                    }
                    else
                    {
                        /* 100 */
                        /* Left point */
                        z1 = *(magptr + cols);
                        z2 = *(magptr + cols - 1);

                        mag1 = (z1 - z2)*xperp + (m00 - z1)*yperp;

                        /* Right point */
                        z1 = *(magptr - cols);
                        z2 = *(magptr - cols + 1);

                        mag2 = (z1 - z2)*xperp  + (m00 - z1)*yperp;
                    }
                }
            }
            else
            {
                if ((gy = *gyptr) >= 0)
                {
                    if (-gx >= gy)
                    {
                        /* 011 */
                        /* Left point */
                        z1 = *(magptr + 1);
                        z2 = *(magptr - cols + 1);

                        mag1 = (z1 - m00)*xperp + (z2 - z1)*yperp;

                        /* Right point */
                        z1 = *(magptr - 1);
                        z2 = *(magptr + cols - 1);

                        mag2 = (z1 - m00)*xperp + (z2 - z1)*yperp;
                    }
                    else
                    {
                        /* 010 */
                        /* Left point */
                        z1 = *(magptr - cols);
                        z2 = *(magptr - cols + 1);

                        mag1 = (z2 - z1)*xperp + (z1 - m00)*yperp;

                        /* Right point */
                        z1 = *(magptr + cols);
                        z2 = *(magptr + cols - 1);

                        mag2 = (z2 - z1)*xperp + (z1 - m00)*yperp;
                    }
                }
                else
                {
                    if (-gx > -gy)
                    {
                        /* 001 */
                        /* Left point */
                        z1 = *(magptr + 1);
                        z2 = *(magptr + cols + 1);

                        mag1 = (z1 - m00)*xperp + (z1 - z2)*yperp;

                        /* Right point */
                        z1 = *(magptr - 1);
                        z2 = *(magptr - cols - 1);

                        mag2 = (z1 - m00)*xperp + (z1 - z2)*yperp;
                    }
                    else
                    {
                        /* 000 */
                        /* Left point */
                        z1 = *(magptr + cols);
                        z2 = *(magptr + cols + 1);

                        mag1 = (z2 - z1)*xperp + (m00 - z1)*yperp;

                        /* Right point */
                        z1 = *(magptr - cols);
                        z2 = *(magptr - cols - 1);

                        mag2 = (z2 - z1)*xperp + (m00 - z1)*yperp;
                    }
                }
            }

            /* Now determine if the current point is a maximum point */

            if ((mag1 > 0.0) || (mag2 > 0.0))
            {
                *resultptr = (unsigned char) NOEDGE;
            }
            else
            {
                if (mag2 == 0.0)
                    *resultptr = (unsigned char) NOEDGE;
                else
                    *resultptr = (unsigned char) POSSIBLE_EDGE;
            }
        }
    }
}

void Canny::magnitude_x_y(short int *delta_x, short int *delta_y,short int **magnitude){
   int r, c, pos, sq1, sq2;
   if((*magnitude = (short *) calloc(rows*cols, sizeof(short))) == NULL){
      fprintf(stderr, "Error allocating the magnitude image.\n");
      exit(1);
   }

   for(r=0,pos=0;r<rows;r++){
      for(c=0;c<cols;c++,pos++){
         sq1 = (int)delta_x[pos] * (int)delta_x[pos];
         sq2 = (int)delta_y[pos] * (int)delta_y[pos];
         (*magnitude)[pos] = (short)(0.5 + sqrt((float)sq1 + (float)sq2));
      }
   }
}
void Canny::apply_hysteresis(short int *mag, unsigned char *nms,float tlow, float thigh, unsigned char *edge){
   int r, c, pos, numedges, lowcount, highcount, lowthreshold, highthreshold,
       i, hist[32768], rr, cc;
   short int maximum_mag, sumpix;
   for(r=0,pos=0;r<rows;r++){
      for(c=0;c<cols;c++,pos++){
	 if(nms[pos] == POSSIBLE_EDGE) edge[pos] = POSSIBLE_EDGE;
	 else edge[pos] = NOEDGE;
      }
   }

   for(r=0,pos=0;r<rows;r++,pos+=cols){
      edge[pos] = NOEDGE;
      edge[pos+cols-1] = NOEDGE;
   }
   pos = (rows-1) * cols;
   for(c=0;c<cols;c++,pos++){
      edge[c] = NOEDGE;
      edge[pos] = NOEDGE;
   }
   for(r=0;r<32768;r++) hist[r] = 0;
   for(r=0,pos=0;r<rows;r++){
      for(c=0;c<cols;c++,pos++){
	 if(edge[pos] == POSSIBLE_EDGE) hist[mag[pos]]++;
      }
   }
   for(r=1,numedges=0;r<32768;r++){
      if(hist[r] != 0) maximum_mag = r;
      numedges += hist[r];
   }

   highcount = (int)(numedges * thigh + 0.5);
   r = 1;
   numedges = hist[1];
   while((r<(maximum_mag-1)) && (numedges < highcount)){
      r++;
      numedges += hist[r];
   }
   highthreshold = r;
   lowthreshold = (int)(highthreshold * tlow + 0.5);
   for(r=0,pos=0;r<rows;r++){
      for(c=0;c<cols;c++,pos++){
	 if((edge[pos] == POSSIBLE_EDGE) && (mag[pos] >= highthreshold)){
            edge[pos] = EDGE;
            follow_edges((edge+pos), (mag+pos), lowthreshold);
	 }
      }
   }
   for(r=0,pos=0;r<rows;r++){
      for(c=0;c<cols;c++,pos++) if(edge[pos] != EDGE) edge[pos] = NOEDGE;
   }
}
void Canny::follow_edges(unsigned char *edgemapptr, short *edgemagptr, short lowval){
   short *tempmagptr;
   unsigned char *tempmapptr;
   int i;
   float thethresh;
   int x[8] = {1,1,0,-1,-1,-1,0,1},
       y[8] = {0,1,1,1,0,-1,-1,-1};

   for(i=0;i<8;i++){
      tempmapptr = edgemapptr - y[i]*cols + x[i];
      tempmagptr = edgemagptr - y[i]*cols + x[i];

      if((*tempmapptr == POSSIBLE_EDGE) && (*tempmagptr > lowval)){
         *tempmapptr = (unsigned char) EDGE;
         follow_edges(tempmapptr,tempmagptr, lowval);
      }
   }
}


void Canny::change_gray(){
	int width = image.width();
	int height = image.height();
	int depth = image.depth();
	CImg<unsigned char> gray1(width,height,depth,1);
	unsigned char r,g,b;
	unsigned char gr1 = 0;
	/* Convert RGB image to grayscale image */
	for(int i=0;i<width;i++){
	for(int j=0;j<height;j++){
		//Return a pointer to a located pixel value.
		r = image(i,j,0,0); // First channel RED
		g = image(i,j,0,1); // Second channel GREEN
		b = image(i,j,0,2); // Third channel BLUE
		gr1 = round(0.299*((double)r) + 0.587*((double)g) + 0.114*((double)b));
		gray1(i,j,0,0) = gr1;
		}
	}
	image = gray1;
}
void Canny::to_save_edge(unsigned char *edge){
	   for(int r=0,pos=0;r<rows;r++){
      for(int c=0;c<cols;c++,pos++) image(c,r,0) = edge[pos];
   }
}
unsigned char Canny::show(int i, int j , int pos){
	return this->image(i,j,pos);
}

void Canny::set_distance(float new_distance){
	this->distance = new_distance;
}
void Canny::connect_edge(unsigned char *edge){
   unsigned char *tempmapptr;
   int x[8] = {1,1,0,-1,-1,-1,0,1},
       y[8] = {0,1,1,1,0,-1,-1,-1};
   	int num = 0,now_pos = 0,i;
    unsigned char *new_edge;
	new_edge = (unsigned char *)calloc(rows*cols,sizeof(unsigned char));
	bool flag = true;
	for(int r=0,pos=0;r<rows;r++){
		for(int c=0;c<cols;c++,pos++){
			new_edge[pos] = NOEDGE;
			if(edge[pos] == EDGE){
				flag = true;
				for(i=0;i<8;i++){
					tempmapptr = edge + pos - y[i]*cols + x[i];
					if(*tempmapptr == EDGE){
						flag = false;
						break;
					}
				}
				if(flag)
					edge[pos] = NOEDGE;
			}
		}
	}
	int temp = 0;
	for(int r=0,pos=0;r<rows;r++){
		for(int c=0;c<cols;c++,pos++){
			if(edge[pos] == EDGE){
				now_pos = 0;
				new_edge[pos] = EDGE;
			   for(i=0;i<8;i++){
					tempmapptr = edge + pos - y[i]*cols + x[i];
					if(*tempmapptr == EDGE){
						num = 2;
						while(*tempmapptr != EDGE){
							temp = pos - num * y[i]*cols + num * x[i];
							if(temp >= 0 && temp % cols < rows && temp / rows < cols)
								tempmapptr = edge + temp;
							else break;
							num++;
						}
						now_pos = num;
						num++;
						while(num - now_pos < distance){
							temp = pos - num * y[i]*cols + num * x[i];
							if(temp >= 0 && temp % cols < rows && temp / rows < cols){
								tempmapptr = edge + temp;
								if(*tempmapptr == EDGE){
									int has_num = 0;
									for(int j = 1;j < 5;j++){
										temp = pos - (num + j)* y[i]*cols + (num + j) * x[i];
										if(!(temp >= 0 && temp % cols < rows && temp / rows < cols))	break;
										tempmapptr = edge + temp;
										if(*tempmapptr == EDGE)	has_num += 1;
									}
									if(has_num >= 3)	break;
								}
								num++;
							}
							else
							{
								temp = -1;
								break;
							}
						}
						if(num - now_pos != distance && temp >= 0){
							for(int j = now_pos;j <= num;j++)
								new_edge[pos - j * y[i]*cols + j * x[i]] = EDGE;
						}
					}
				}
    	  }    	  
  		}
  	}
	for(int r=0,pos=0;r<rows;r++){
		for(int c=0;c<cols;c++,pos++){
			edge[pos] = new_edge[pos];
		}
	}
}
int Canny::find_length(unsigned char *edge,int pos,int *flag,int *num){
   unsigned char *tempmapptr;
   int x[8] = {1,1,0,-1,-1,-1,0,1},
       y[8] = {0,1,1,1,0,-1,-1,-1};
   tempmapptr = edge + pos;
   int length = 0;
   bool notIn = true;
   int temp;
   for(int i = 0;i < 8;i++){
   		// cout << i << endl;
   		temp = pos - y[i]*cols + x[i];
   		tempmapptr = edge + temp;
   		if(*(tempmapptr) == EDGE){
	   		notIn = true;
	   		for(int j = 1;j <= *num;j++){
	   			if(*(flag + j) == temp)
	   			{
	   				notIn = false;
	   				break;
	   			}
	   		}
	   		if(notIn){
	   			*num += 1;
	   			*(flag + *num) = temp;
	   			length += find_length(edge,temp,flag,num) + 1;
	   		}
	   	}
   }
   // cout << length << endl;
   return length;
}

void Canny::delete_line(unsigned char *edge){
	int length = 0;
	int *flag,*num;
	num = (int *)calloc(1,sizeof(int));
	flag = (int *)calloc(cols*rows,sizeof(int));
	for(int r=0,pos=0;r<rows;r++){
		for(int c=0;c<cols;c++,pos++){
			// cout << c << " " << r << endl;
			if(edge[pos] == EDGE){
				length = 0;
				*(flag + 1) = pos;
				*num = 1;
				for(int i = 0;i < 8;i++){
					length += find_length(edge,pos,flag,num);
				}
				if(length < 20){
					for(int i = 1;i <= *num;i++)	edge[*(flag + i)] = NOEDGE;
				}
			}
		}
	}
}
void Canny::canny(){
	unsigned char *nms;        /* Points that are local maximal magnitude. */
	short int *delta_x,        /* The first devivative image, x-direction. */
			*delta_y,        /* The first derivative image, y-direction. */
			*magnitude;      /* The magnitude of the gadient image.      */
	change_gray();
	gaussian_smooth();
	derrivative_x_y( &delta_x, &delta_y);
	magnitude_x_y(delta_x, delta_y,&magnitude);
	if((nms = (unsigned char *) calloc(rows*cols,sizeof(unsigned char)))==NULL){
		fprintf(stderr, "Error allocating the nms image.\n");
		exit(1);
	}
	non_max_supp(magnitude, delta_x, delta_y, nms);
	unsigned char *edge; 
	if((edge=(unsigned char *)calloc(rows*cols,sizeof(unsigned char))) ==NULL){
		fprintf(stderr, "Error allocating the edge image.\n");
		exit(1);
	}
	
	apply_hysteresis(magnitude, nms, tlow, thigh, edge);
	connect_edge(edge);
	delete_line(edge);
	to_save_edge(edge);
	free(delta_x);
	free(delta_y);
	free(magnitude);
	free(nms);
}