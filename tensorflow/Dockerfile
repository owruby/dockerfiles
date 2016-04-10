FROM nvidia/cuda:7.5-cudnn4-devel

MAINTAINER ruby.yano1995@gmail.com

ENV LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/usr/local/cuda/lib64"
ENV CUDA_HOME=/usr/local/cuda

# install for tensorflow
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    python-pip \
    python-dev \
    git

# install tensorflow
RUN pip install --upgrade https://storage.googleapis.com/tensorflow/linux/gpu/tensorflow-0.7.1-cp27-none-linux_x86_64.whl

# download tensorflow codes
RUN git clone --recurse-submodules https://github.com/tensorflow/tensorflow