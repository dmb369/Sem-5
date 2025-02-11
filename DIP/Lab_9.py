import cv2
import numpy as np
import matplotlib.pyplot as plt

def fft_image(image):
    image_float = np.float32(image)
    dft = cv2.dft(image_float, flags=cv2.DFT_COMPLEX_OUTPUT)
    dft_shift = np.fft.fftshift(dft)
    return dft_shift

def ifft_image(dft_shift):

    dft_ishift = np.fft.ifftshift(dft_shift)
    img_back = cv2.idft(dft_ishift)
    img_back = cv2.magnitude(img_back[:, :, 0], img_back[:, :, 1])
    return img_back

def low_pass_filter(dft_shift, cutoff):
    rows, cols = dft_shift.shape[0:2]
    crow, ccol = rows // 2, cols // 2

    mask = np.zeros((rows, cols, 2), np.uint8)
    center = (crow, ccol)
    cv2.circle(mask, center, cutoff, (1, 1), thickness=-1)
    
    filtered_dft = dft_shift * mask
    return filtered_dft

def high_pass_filter(dft_shift, cutoff):
    rows, cols = dft_shift.shape[0:2]
    crow, ccol = rows // 2, cols // 2
    
    mask = np.ones((rows, cols, 2), np.uint8)
    cv2.circle(mask, (crow, ccol), cutoff, (0, 0), thickness=-1)

    filtered_dft = dft_shift * mask
    return filtered_dft


image = cv2.imread('download.jpg', cv2.IMREAD_GRAYSCALE)

dft_shift = fft_image(image)

#low-pass filtering
cutoff = 30  
low_pass_dft = low_pass_filter(dft_shift, cutoff)
low_pass_reconstructed = ifft_image(low_pass_dft)

# High-pass filtering
high_pass_dft = high_pass_filter(dft_shift, cutoff)
high_pass_reconstructed = ifft_image(high_pass_dft)

# Display results
plt.figure(figsize=(12, 8))
plt.subplot(2, 3, 1)
plt.title('Original Image')
plt.imshow(image, cmap='gray')
plt.axis('off')

plt.subplot(2, 3, 2)
plt.title('Low-pass Filtered Image')
plt.imshow(low_pass_reconstructed, cmap='gray')
plt.axis('off')

plt.subplot(2, 3, 3)
plt.title('High-pass Filtered Image')
plt.imshow(high_pass_reconstructed, cmap='gray')
plt.axis('off')

plt.subplot(2, 3, 4)
plt.title('Magnitude Spectrum')
magnitude_spectrum = np.log(cv2.magnitude(dft_shift[:, :, 0], dft_shift[:, :, 1]) + 1)
plt.imshow(magnitude_spectrum, cmap='gray')
plt.axis('off')

plt.show()