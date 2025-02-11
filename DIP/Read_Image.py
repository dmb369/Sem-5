import cv2

img = cv2.imread('/Users/devmbandhiya/Desktop/cat.jpg', cv2.IMREAD_UNCHANGED)
cv2.imshow("Cat", img)

cv2.waitKey(0) 
cv2.destroyAllWindows()