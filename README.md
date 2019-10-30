# archiver

ideally, all the operations get performed on the raw data, then the information will be extracted;
To ensure best possible recognition results:

* remove alpha channel
* white balance
* rotate
* deskew
* crop to uniform whitespace
* thresholding (otsu) - binarization
  * testCase: 4 corners are white?
* noise removal
* gaussian blur slightly


## integration archiver

1. remove initial comments in libraries
2. upgrade to opencv4.0.1
3. switch to nieblack-alg implementations


## implementation concerns

class ImgObject has:
