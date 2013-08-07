#!/bin/sh

#Change to executable.
#"sudo ./install_linux_dep.sh

#Linux:
mkdir -p /opt/dev/boost
cd /opt/dev/boost
wget -c http://sourceforge.net/projects/boost/files/boost/1.54.0/boost_1_54_0.tar.bz2 && tar xjvf boost_1_54_0.tar.bz2 && rm boost_1_54_0.tar.bz2
cd boost_1_54_0
./bootstrap.sh --with-libraries=regex --prefix=/opt/dev/boost
./b2 install variant=release link=static threading=multi runtime-link=static

#Set ~/.bashrc export BOOST_ROOT=/opt/dev/boost/boost_1_54_0/
#curl http://sourceforge.net/projects/boost/files/boost/1.54.0/boost_1_54_0.tar.bz2 | tar xjv
