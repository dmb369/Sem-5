import cv2
import numpy as np
from matplotlib import pyplot as plt

# 1D Convolution 
def conv1d(signal, kernel):
    sr = signal.reshape(1, -1)  # Shape: (1, n)
    kr = kernel.reshape(1, -1)  # Shape: (1, k)
    res = cv2.filter2D(sr, -1, kr)
    return res.flatten()

# 2D Convolution 
def conv2d(image, kernel):
    result = cv2.filter2D(image, -1, kernel)
    return result

img = cv2.imread( '/Users/devmbandhiya/Desktop/DIP/images.png' , cv2.IMREAD_GRAYSCALE)

# Apply 2D convolution on the full image
k_2d = np.array([[0, 1, 0],
                      [1, -4, 1],
                      [0, 1, 0]], dtype=np.float32)  # Edge detection kernel

o_2d = conv2d(img, k_2d)

# 1D convolution on a specific row of the image 
row = img[50, :]  # Extract row 50
k_1d = np.array([0.2, 0.5, 0.2], dtype=np.float32)

o_1d = conv1d(row, k_1d)

# Display the original and filtered imgs (2D)
plt.figure(figsize=(10, 5))

# Original image
plt.subplot(1, 2, 1)
plt.imshow(img, cmap='gray')
plt.title("Original Image")
plt.axis('off')

# 2D Convolution result
plt.subplot(1, 2, 2)
plt.imshow(o_2d, cmap='gray')
plt.title("2D Convolution (Edge Detection)")
plt.axis('off')

plt.show()

# 1D Convolution result (for row 50)
print("1D Convolution Output (Row 50):", o_1d)

img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)

# 3x3 Mask
low_pass_kernel = np.ones((3, 3), np.float32) / 10
low_pass = cv2.filter2D(img, -1, low_pass_kernel)

# 3x3 Mask
high_pass_kernel = np.array([[0, -1, 0],
                              [-1, 5, -1],
                              [0, -1, 0]])


high_pass = cv2.filter2D(low_pass, -1, high_pass_kernel)

# Display the images
plt.figure(figsize=(12, 6))

plt.subplot(1, 3, 1)
plt.imshow(img)
plt.title('Original Image')
plt.axis('off')

plt.subplot(1, 3, 2)
plt.imshow(low_pass)
plt.title('Low-Pass Filter (Averaging)')
plt.axis('off')

plt.subplot(1, 3, 3)
plt.imshow(high_pass)
plt.title('High-Pass Filter')
plt.axis('off')

plt.show()



'''import cv2
import numpy as np

# 1D Convolution 
def conv1d(signal, kernel):
    signal_reshaped = signal.reshape(1, -1)  # Shape: (1, n)
    kernel_reshaped = kernel.reshape(1, -1)  # Shape: (1, k)
    result = cv2.filter2D(signal_reshaped, -1, kernel_reshaped)
    # Flatten the result to 1D
    return result.flatten()

# 2D Convolution
def conv2d(image, kernel):
    result = cv2.filter2D(image, -1, kernel)
    return result


s_1d = np.array([1, 2, 3, 4, 5, 6], dtype=np.float32)
k_1d = np.array([0.2, 0.5, 0.2], dtype=np.float32)

# Apply 1D convolution
o_1d = conv1d(s_1d, k_1d)
print("1D Convolution Output:", o_1d)

i_2d = np.array([[1, 2, 3],
                     [4, 5, 6],
                     [7, 8, 9]], dtype=np.float32)

k_2d = np.array([[0, 1, 0],
                      [1, -4, 1],
                      [0, 1, 0]], dtype=np.float32)

# Apply 2D convolution
o_2d = conv2d(i_2d, k_2d)
print("2D Convolution Output:\n", o_2d)'''
