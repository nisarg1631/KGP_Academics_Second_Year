from PIL import Image, ImageFilter
import numpy as np
from my_package.data.transforms import CropImage
import json
import matplotlib.pyplot as plt


def main():
    image1 = Image.open("./data/imgs/1.jpg")
    image2 = Image.open("./data/imgs/2.jpg")
    print(CropImage((200, 100), 'center')(image1).size)
    # h w 3 old
    # 3 h w new
    # pypi-AgENdGVzdC5weXBpLm9yZwIkNzcxYTBlYjUtODg3Zi00OTg2LTg0NDMtZWEyMDFjYzQ2ZDEyAAIleyJwZXJtaXNzaW9ucyI6ICJ1c2VyIiwgInZlcnNpb24iOiAxfQAABiDgYnRnh0buH2yRJwhIEzYbVj5t82OZcqL6nUZihZErow


if __name__ == '__main__':
    main()
