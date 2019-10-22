# coding=utf-8 
from PIL import Image
import os.path
import glob

file_list = glob.glob("*.jpg")
for i in file_list:
    jpg = Image.open(i)
    jpg.save( i[:-3] + "bmp")
 