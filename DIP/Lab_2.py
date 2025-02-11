import cv2 as dip

img = dip.imread("C:/Users/HP/Downloads/Salaar.jpg")
img2 = dip.imread("C:/Users/HP/Downloads/download.jpeg")

img = dip.resize(img, (img2.shape[1], img2.shape[0]))

bitwise_xor = dip.bitwise_xor(img, img2)

watermarked_xor = bitwise_xor.copy()
dip.putText(watermarked_xor, 'Mummy Hero', (50, 50), dip.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2, dip.LINE_AA)

dip.imshow("Bitwise XOR with Watermark", watermarked_xor)
dip.waitKey(0)
dip.destroyAllWindows()