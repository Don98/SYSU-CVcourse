# coding=utf-8 
from PIL import Image
import os.path
import glob
 
jpg = Image.open( "lena.jpg" )
# name = "lena.pgm"
# jpg.save( name )

jpg.save( "lean.bmp" )