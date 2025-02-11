import numpy as np
import cv2

# Draw a rectangle
rectangle = np.zeros((300, 300), dtype="uint8")
cv2.rectangle(rectangle, (25, 25), (275, 275), 255, -1)
cv2.imshow("Rectangle", rectangle)
cv2.waitKey(0)

# Draw a circle
circle = np.zeros((300, 300), dtype = "uint8")
cv2.circle(circle, (150, 150), 150, 255, -1)
cv2.imshow("Circle", circle)
cv2.waitKey(0)

# AND Operation
bitwiseAnd = cv2.bitwise_and(rectangle, circle)
cv2.imshow("AND", bitwiseAnd)
cv2.waitKey(0)

# OR Operation
bitwiseOr = cv2.bitwise_or(rectangle, circle)
cv2.imshow("OR", bitwiseOr)
cv2.waitKey(0)

# XOR Operation
bitwiseXor = cv2.bitwise_xor(rectangle, circle)
cv2.imshow("XOR", bitwiseXor)
cv2.waitKey(0)

# NOT Operation
bitwiseNot = cv2.bitwise_not(circle)
cv2.imshow("NOT", bitwiseNot)
cv2.waitKey(0)

# Watermarking
  
# calculating dimensions 
# height and width of the Watermark 
h_logo, w_logo = circle.shape 
  
# height and width of the image 
h_img, w_img = rectangle.shape 
  
# calculating coordinates of center 
# calculating center, where we are going to  
# place our watermark 
center_y = int(h_img/2) 
center_x = int(w_img/2) 
  
# calculating from top, bottom, right and left 
top_y = center_y - int(h_logo/2) 
left_x = center_x - int(w_logo/2) 
bottom_y = top_y + h_logo 
right_x = left_x + w_logo 
  
# adding watermark to the image 
destination = rectangle[top_y:bottom_y, left_x:right_x] 
result = cv2.addWeighted(destination, 1, circle, 0.5, 0) 
  
# displaying and saving image 
rectangle[top_y:bottom_y, left_x:right_x] = result 
cv2.imwrite("watermarked.jpg", rectangle) 
cv2.imshow("Watermarked Image", rectangle) 
cv2.waitKey(0) 

