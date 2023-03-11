from matplotlib import pyplot as plt
from PIL import Image
import cv2
import numpy as np


img = cv2.imread("C:\\Users\\blasz\\work\\studia\\sem6\\psio\\stinkbug.png", cv2.IMREAD_COLOR)
img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

cv2.imshow("gray", img)
cv2.moveWindow("gray", 500, 0)
cv2.waitKey(0)
cv2.destroyWindow("gray")

img = np.asanyarray(Image.open("C:\\Users\\blasz\\work\\studia\\sem6\\psio\\stinkbug.png"))

imgplot = plt.imshow(img)

# print(cv2.__version__)

plt.title('pic')
plt.show