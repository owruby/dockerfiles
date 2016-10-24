
FROM owruby/ubuntu:14.04

MAINTAINER ruby.yano1995@gmail.com

WORKDIR /root

# Install reuiqred package
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    libgtk2.0-dev \
    pkg-config \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    python-dev \
    python-numpy \
    libtbb2 \
    libtbb-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libjasper-dev \
    libdc1394-22-dev \
    wget \
    unzip

# Download opencv
RUN wget https://github.com/Itseez/opencv/archive/3.1.0.zip && \
    unzip 3.1.0.zip

# Build opencv
RUN cd opencv-3.1.0 && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D BUILD_opencv_java=OFF -D WITH_IPP=OFF -D WITH_1394=OFF -D WITH_FFMPEG=OFF -D BUILD_EXAMPLES=OFF -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_DOCS=OFF -D BUILD_opencv_python2=ON -D BUILD_opencv_python3=ON -D BUILD_opencv_video=OFF -D BUILD_opencv_videoio=OFF -D BUILD_opencv_videostab=OFF -D PYTHON_EXECUTABLE=$(which python) .. && \
    make -j10 && \
    make install
