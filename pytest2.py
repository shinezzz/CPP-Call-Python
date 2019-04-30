import numpy as np
import cv2

def arrayreset(array):
    a = array[:, 0:len(array[0] - 2):3]
    #b = array[:, 1:len(array[0] - 2):3]
    #c = array[:, 2:len(array[0] - 2):3]
    #print(a.shape, b.shape, c.shape)
    #a = a[:, :, None]
    #b = b[:, :, None]
    #c = c[:, :, None]
    #m = np.concatenate((a, b, c), axis=2)

    return a

def load_image(image):
    img = arrayreset(image)
    rgbImg=cv2.cvtColor(img,cv2.COLOR_GRAY2BGR)
    print(rgbImg.shape)
    cv2.imshow("test",rgbImg)
    cv2.waitKey(0)
