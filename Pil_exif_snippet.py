from PIL import Image
from PIL. from PIL.ExifTags import TAGS

img = Image.open('test.jpg')

exif = img.getexif()

for k, v in exif.items():
    print('{}: {}'.format(TAGS[k], v))
