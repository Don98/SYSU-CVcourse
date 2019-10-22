## 对于测试代码的编译

g++ test.cpp -IE:\OpenCV-MinGW-Build\include -LE:\OpenCV-MinGW-Build\x64\mingw\bin -llibopencv_calib3d341 -llibopencv_core341 -llibopencv_dnn341 -llibopencv_features2d341 -llibopencv_flann341 -llibopencv_highgui341 -llibopencv_imgcodecs341 -llibopencv_imgproc341 -llibopencv_ml341 -llibopencv_objdetect341 -llibopencv_photo341 -llibopencv_shape341 -llibopencv_stitching341 -llibopencv_superres341 -llibopencv_video341 -llibopencv_videoio341 -llibopencv_videostab341 -O2 -lgdi32

（修改你的OpenCV库所在的位置即可）

## 运行代码所需要的几个参数

第一个参数: 读入的图像的H-image.bmp
第二个参数: 膨胀的次数
第三个参数：删除联通块的阈值大小
第四个参数：任务二的结果保存图片名字
第五个参数: 模板数字图片的名字
第六个参数: test_data中文件的数量

## 运行代码所需要的几个文件夹以及文件

- 文件夹
	- digits 保存分割好的模板数字
	- otsu_method 用来保存使用大律法的到的结果
	- tesseract_recognition 保存使用tesseract识别的结果
	- test_data 用来测试阈值法的数据集
	- use_iter 使用迭代法得到的结果
	- use_two_peaks 使用双峰法得到的结果

## 温馨提示

使用tesseract的时候，自己的电脑上必须装有tesseract，否则将无法运行。

test_data的数据集被我统一命名为A.bmp B.bmp等等，可以使用我提供的change_name.py一键修改文件夹内文件的名字。


地址 https://github.com/Don98/SYSU-CVcourse/hw4/