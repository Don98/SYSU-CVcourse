import cv2
import os
if __name__ == "__main__":
    filelist = os.listdir("test_data")
    for i in range(len(filelist)):
        os.rename("test_data/" + filelist[i], "test_data/" + chr(i + 65) + ".bmp")
        # os.rename("test_data/" + filelist[i], "test_data/" + chr(i + ord('a')) + ".bmp")