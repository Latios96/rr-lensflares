# Building

Tested with cmake 3.20.4 and Visual Studio 2019

Prerequisites:
- Visual Studio 2019
- [CUDA](https://developer.nvidia.com/cuda-downloads) 
- [Optix](https://developer.nvidia.com/designworks/optix/download)

Build on Windows:
```
git clone --recursive 
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release "-DOptiX_ROOT_DIR=C:\ProgramData\NVIDIA Corporation\OptiX SDK 7.4.0" .. --build
cmake --build . --config Release -- /M:%NUMBER_OF_PROCESSORS%
```