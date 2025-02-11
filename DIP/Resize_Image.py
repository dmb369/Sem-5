import cv2

img = cv2.imread('/Users/devmbandhiya/Desktop/cat.jpg', cv2.IMREAD_UNCHANGED)

# RESIZE_1
# Set the desired width and height
width = 1600 # OR img.shape[1] #Keep original width
height = 1000 # OR img.shpe[0] #Keep original height
dim = (width, height)
# Resize the image
resized_image = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)

cv2.imshow('Resized Image', resized_image)
cv2.waitKey(0)
cv2.destroyAllWindows()

print("Original Dimensions:", img.shape)


# RESIZE_2
scale_percent = 60 #percent of original size
width = int(img.shape[1]*scale_percent/100)
height = int(img.shape[0]*scale_percent/100)
dim = (width, height)

resized = cv2.resize(img, dim, interpolation = cv2.INTER_AREA)

cv2.imshow('Resized Image', resized)
cv2.waitKey(0)
cv2.destroyAllWindows()

