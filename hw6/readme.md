## 对于测试代码的编译

g++ test.cpp -std=c++11 -IE:\OpenCV-MinGW-Build\include -IE:\xgboost\include -LE:\xgboost -llib\xgboost -LE:\xgboost -LE:\OpenCV-MinGW-Build\x64\mingw\bin -fopenmp -llibopencv_calib3d341 -llibopencv_core341 -llibopencv_dnn341 -llibopencv_features2d341 -llibopencv_flann341 -llibopencv_highgui341 -llibopencv_imgcodecs341 -llibopencv_imgproc341 -llibopencv_ml341 -llibopencv_objdetect341 -llibopencv_photo341 -llibopencv_shape341 -llibopencv_stitching341 -llibopencv_superres341 -llibopencv_video341 -llibopencv_videoio341 -llibopencv_videostab341 -O2 -lgdi32 -lpthread

（修改你的OpenCV库以及xgboost所在的位置即可）

## 运行代码所需要的几个参数

第一个参数: 读入的图像的H-image.bmp
第二个参数：第一个数字数据的txt
第三个参数：第一个数字数据的图片名
第四个参数：第一个数字数据所在的路径

## 运行代码所需要的几个文件夹以及文件

- 文件夹
	- TT035_result 保存分割好的数字数据
	- TT0351 原始图像数据

## 温馨提示

a.exe "data\TT0351\CC -  (1).bmp" "data\TT035_result\CC -  (1).txt" "data\TT035_result\CC -  (1)\000.bmp" "data\TT035_result"

地址 https://github.com/Don98/SYSU-CVcourse