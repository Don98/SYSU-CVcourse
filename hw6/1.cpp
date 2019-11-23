#include <iostream>
#include <string.h>
#include <math.h>
#include <cstring>
#include <vector>
#include <io.h>
#include <fstream>
#include <windows.h>
using namespace std;
void GetAllFiles( string path, vector<string>& files, vector<string>& folders)  {
	long   hFile = 0;  
	struct _finddata_t fileinfo;  
	string p;  
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1){  
		do{   
			if((fileinfo.attrib &  _A_SUBDIR)){  
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0){
					// files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					folders.push_back(p.assign(path).append("\\").append(fileinfo.name) );
					GetAllFiles( p.assign(path).append("\\").append(fileinfo.name), files ,folders); 
				}
			}  
			else
				files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
		}while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile); 
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
int main(int argc, char* argv[]){
	vector<string> files,folders;
	GetAllFiles("data/TT035_result",files,folders);
	// for(int i = 0;i < files.size();i++)
		// cout << files[i] << endl;
	// for(int i = 0;i < folders.size();i++)
		// cout << dirExists(folders[i]) << endl;
	
	if (0 != access(argv[1], 0))
		mkdir(argv[1]);
}
// g++ 1.cpp -o b -std=c++11 -IE:\OpenCV-MinGW-Build\include -IE:\xgboost\include -LE:\xgboost -llib\xgboost -LE:\OpenCV-MinGW-Build\x64\mingw\bin -fopenmp -llibopencv_calib3d341 -llibopencv_core341 -llibopencv_dnn341 -llibopencv_features2d341 -llibopencv_flann341 -llibopencv_highgui341 -llibopencv_imgcodecs341 -llibopencv_imgproc341 -llibopencv_ml341 -llibopencv_objdetect341 -llibopencv_photo341 -llibopencv_shape341 -llibopencv_stitching341 -llibopencv_superres341 -llibopencv_video341 -llibopencv_videoio341 -llibopencv_videostab341 -O2 -lgdi32 -lpthread

// g++ 1.cpp -o b -std=c++11 -IE:\xgboost\include -LE:\xgboost -llib\xgboost -fopenmp 