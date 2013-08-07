#!/bin/sh

#Change to executable.
#Usage: sudo ./install_linux_dep.sh

#Linux (GCC)
mkdir -p /opt/dev/boost
cd /opt/dev/boost
wget -c http://sourceforge.net/projects/boost/files/boost/1.54.0/boost_1_54_0.tar.bz2 && tar xjvf boost_1_54_0.tar.bz2 && rm boost_1_54_0.tar.bz2
cd boost_1_54_0
./bootstrap.sh --with-libraries=regex --prefix=/opt/dev/boost
./b2 install variant=release link=static threading=multi runtime-link=static

#Add to ~/.bashrc : export BOOST_ROOT=/opt/dev/boost/boost_1_54_0/
cd /opt/dev/
git clone git://code.opencv.org/opencv.git
cd opencv
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE ..
make
#Add to ~/.bashrc : export OpenCV_DIR=/opt/dev/opencv/release/

# Cross-compile Windows (MinGW)
cd /opt/dev/
git clone https://github.com/mxe/mxe.git 
cd mxe
make gcc mignw-64 boost opencv

#Add to ~/.bashrc: export PATH=/opt/dev/mxe/usr/bin:$PATH
#compile: cmake -DCMAKE_TOOLCHAIN_FILE=/opt/dev/mxe/usr/i686-pc-mingw32/share/cmake/mxe-conf.cmake ..
