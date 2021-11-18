# Fourier Transform for Image Processing
## Basic Information
* GitHub repository: https://github.com/crystal0523/Fourier-Transform-for-Image-Processing
## Problem to Solve
  
The Fourier Transform is an important image processing tool which is used to decompose an image into its sine and cosine components. The output of the transformation represents the image in frequency domain, while the input image is the spatial domain equivalent. 

The Fourier Transform is used in a wide range of image applications, such as image analysis, image filtering, image reconstruction and image compression. This project use pybind to wrap the c++ based FFT-related function to provide high-level API in python.



The formula of 2-D Discrete Fourier Transform for an M*N image:
> $\dfrac{1}{M*N}\sum_{x=0}^{M-1}\sum_{y=0}^{N-1}f(x,y)e^{-i2\pi[\dfrac{ux}{M}+\dfrac{vy}{N}]}$, for u = 0..M-1, v = 0..N-1
## Prospective Users
People who would like to do image processing tricks which are based on frequency domain.
## System Architecture
![](https://i.imgur.com/KtVQwGY.png)

## API Description
* Python
    * getParam(): parser
    * getResult()
* C++ 
    * FFT()
    * InverseFFT()
    * VagueProcess(): LowPassFilter
    * EdgeDetection(): HighPassFilter
    * HybridImage(): LowPassFilter+HighPassFilter
    
## Engineering Infrastructure
* Build System: Makefile
    * make
    * make test
    * make clean
* Version Control: Git
## Schedule
* Week 1: setup Python and c++ environment & domain knowledge study
* Week 2: implement **getParam()**
* Week 3: implement **FFT()** and **InverseFFT()**
* Week 4: implememt **VagueProcess()** and **EdgeDetection()**
* Week 5: implement **HybridImage()** and **getResult()**
* Week 6: Testing
* Week 7: Project presentation
* Week 8: Project presentation
## References
https://homepages.inf.ed.ac.uk/rbf/HIPR2/fourier.htm
https://zh.wikipedia.org/wiki/%E4%BA%8C%E7%B6%AD%E5%82%85%E7%AB%8B%E8%91%89%E8%AE%8A%E6%8F%9B
