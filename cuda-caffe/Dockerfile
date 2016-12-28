FROM nvidia/cuda:8.0-cudnn5-devel
MAINTAINER Masaki Yano <ruby.yano1995@gmail.com>

RUN apt-get update

# install dependencies
RUN apt-get install -y \
    git \
    wget \
    bc \
    cmake \
    libatlas-base-dev \
    libatlas-dev \
    libboost-all-dev \
    libopencv-dev \
    libprotobuf-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    protobuf-compiler \
    libhdf5-dev \
    libleveldb-dev \
    liblmdb-dev \
    libsnappy-dev \
    python-dev \
    python-pip \
    python-numpy \
    gfortran

# Download caffe code
RUN cd /root/ && \
    git clone https://github.com/BVLC/caffe.git && \
    for req in $(cat ./caffe/python/requirements.txt); do pip install $req; done

# build caffe
WORKDIR /root/caffe

RUN cp Makefile.config.example Makefile.config && \
    sed -i -s "s/# USE_CUDNN/USE_CUDNN/g" Makefile.config && \
    sed -i -s "s/# ALLOW_LMDB_NOLOCK/ALLOW_LMDB_NOLOCK/g" Makefile.config

RUN make -j8 all

RUN make -j8 test

RUN make -j8 pycaffe

# install draw tools
RUN apt-get install -y --no-install-recommends graphviz && \
    pip install pydot

ENV PYTHONPATH=/root/caffe/python:$PYTHONPATH
