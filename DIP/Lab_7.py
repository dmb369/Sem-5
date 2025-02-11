import cv2
import numpy as np
from scipy.signal import wiener

# Read the input image
image_sp = cv2.imread('/Users/devmbandhiya/Desktop/DIP/Salt_And_Pepper.png')
image_gb = cv2.imread('/Users/devmbandhiya/Desktop/DIP/Gaussian_Blur.png')

# 1. Median Filter
median_filtered = cv2.medianBlur(image_sp, 9)  

# 2. Apply Wiener filter to each color channel
# Split the image into B, G, R channels
b_channel, g_channel, r_channel = cv2.split(image_gb)

# Apply Wiener filter to each channel
b_filtered = wiener(b_channel, (1, 1))
g_filtered = wiener(g_channel, (9, 9))
r_filtered = wiener(r_channel, (9, 9))


b_filtered = np.uint8(b_filtered)
g_filtered = np.uint8(g_filtered)
r_filtered = np.uint8(r_filtered)

# Merge
wiener_filtered_color = cv2.merge([b_filtered, g_filtered, r_filtered])

# Results
cv2.imshow("Original Noisy Salt and Pepper Image", image_sp)
cv2.waitKey(0)
cv2.destroyAllWindows()

cv2.imshow("Median Filtered (Salt and Pepper Noise Reduced)", median_filtered)
cv2.waitKey(0)
cv2.destroyAllWindows()

cv2.imshow("Original Noisy Gaussian Image", image_gb)
cv2.waitKey(0)
cv2.destroyAllWindows()

cv2.imshow("Wiener Filtered (Gaussian Noise Reduced)", wiener_filtered_color)
cv2.waitKey(0)
cv2.destroyAllWindows()
