# Vortex
Vortex is a chess bot written in C++ and powered by libtorch, designed for high performance and accuracy.

# Windows Installation:
1) Make sure you have Python 3.8 or later installed


3) Can be downloaded from here:
   
   https://www.python.org/downloads/
   
4) Go to https://pytorch.org/ and download the latest Libtorch.

   This is the one I downloaded (the release one):
   
![image](https://github.com/user-attachments/assets/ac6a0d50-837d-4ed8-8758-9d9d2666822e)


6) Tested Pytorch: Stable 2.4.1 C++/Java CUDA 12.1 (CUDA is not required)
   
   If you want CUDA, make sure you download CUDA first before installing Pytorch from here:
   
   https://developer.nvidia.com/cuda-toolkit-archive
   
   Download the CUDA version supported by the Pytorch version you want

7) Once downloaded, navigate to libtorch-win-shared-with-deps-2.4.1+cu124.zip\libtorch\lib (your version may be different)

   Copy all of the files ending with .dll (dont copy any of the other files):

   ![image](https://github.com/user-attachments/assets/1891d8e4-1d29-4faa-acae-7ae3d96788ef)

8) Navigate where you want Vortex to be and run: ```git clone```
