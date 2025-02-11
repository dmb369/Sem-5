import cv2
import numpy as np

a=cv2.imread("/content/jpg_44-2.jpg")

# Negative of an image
negative= cv2.bitwise_not(a)

cv2.imshow("original image",a)
cv2.imshow("negative image",negative)
cv2.waitKey(0)

#flipping an image
flip=cv2.flip(a,1) # 1:horizontal, 0: vertical flip

cv2.imshow("flipped image",flip)
cv2.waitKey(0)

#thresholding
grey=cv2.cvtColor(a,cv2.COLOR_BGR2GRAY)
_, threshhold= cv2.threshold(grey,90,255,cv2.THRESH_BINARY)

cv2.imshow("threshold",threshhold)
cv2.waitKey(0)

#contrast stretching
min,max=np.min(grey),np.max(grey)

contrast_st=(grey-min)*(255/(max-min))
contrast_st=np.clip(contrast_st,0,255).astype(np.uint8)

cv2.imshow("original greyscale",grey)
cv2.imshow("contrast image",contrast_st)
cv2.waitKey(0)


'''
img1 = dip.imread("C:/Users/HP/Downloads/download.png")
img2 = dip.imread("C:/Users/HP/Downloads/download (2).jpeg")

img1 = dip.resize(img1,(300,300))  
img2 = dip.resize(img2,(300,300))

dip.imshow("img1",img1)
dip.waitKey(0)
dip.imshow("img2",img2)
dip.waitKey(0)

mixed = dip.add(img1,img2)

dip.imshow("mixed",mixed)
dip.waitKey(0)

deducted = dip.subtract(img1,img2)

dip.imshow("deducted",deducted)
dip.waitKey(0)

greyscale = dip.cvtColor(img1,dip.COLOR_BGR2GRAY)

mean = np.mean(greyscale)
print(mean)

brightness = 150
bright_image = dip.add(img1,np.ones_like(img1)*brightness)

dip.imshow("bright", bright_image)
dip.waitKey(0)
'''