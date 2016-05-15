# Camintra
Get to know your camera!

* Intrinsics pinhole parameters
	* Focal length
	* Aspect ratio
	* Principal point
	* Field of view
* Extrinsic parameters
	* Camera center
	* Attitude matrix
* Lense distortion
* Camera response function
* Point spread function
* Noise estimation
* Sharpness estimation

Dependencies
------------

* OpenCV 3.1
* Xcode 7
* OS X 10.11.4

Installation
------------

### OpenCV
```
export CFLAGS="-I /usr/local/lib/python2.7/site-packages/numpy/core/include $CFLAGS"
export CFLAGS="-I /System/Library/Frameworks/Python.framework/Versions/2.7/Extras/lib/python/numpy/core/include $CFLAGS"

cmake -D CMAKE_BUILD_TYPE=RELEASE \
    -D CMAKE_INSTALL_PREFIX=/usr/local \
    -D BUILD_opencv_python2=ON \
    -D BUILD_opencv_python3=OFF \
    -D WITH_CUDA=OFF \
    -D WITH_FFMPEG=OFF \
    -D PYTHON_LIBRARY=/usr/lib/libpython2.7.dylib \
	-D PYTHON2_PACKAGES_PATH=/usr/local/lib/python2.7/site-packages \
    -D PYTHON2_NUMPY_INCLUDE_DIRS=/usr/local/lib/python2.7/site-packages/numpy/core/include \
	-D PYTHON2_INCLUDE_DIR=/usr/local/Frameworks/Python.framework/Headers \
	-D INSTALL_C_EXAMPLES=OFF \
    -D INSTALL_PYTHON_EXAMPLES=OFF \
	-D BUILD_EXAMPLES=ON \
	-D OPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
```



