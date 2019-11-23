# coding=utf-8 
from PIL import Image
import os
import glob
 
# filelist = os.listdir("作业6")
# for i in filelist:
    # filelist1 = os.listdir("作业6/" + i)
    # for j in filelist1:
        # if j.endswith(".png"):
            # jpg = Image.open("作业6/" + i + "/" + j)
            # jpg.save("作业6/" + i + "1/" + j[:-4] + ".bmp")
# os.chdir("data/TT035_result/")
# for i in range(3,8):
    # os.mkdir("CC -  (" + str(i + 1) + ")")
    
for i in range(1,17):
    print('a.exe "data\TT0351\CC -  (' + str(i) + ').bmp" "data\TT035_result\CC -  (' + str(i) + ').txt" "data\TT035_result\CC -  (' + str(i) + ')\\000.bmp" "data\TT035_result\CC -  (' + str(i) + ')"')