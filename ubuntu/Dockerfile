
FROM ubuntu:14.04

MAINTAINER ruby.yano1995@gmail.com

WORKDIR /root

# install python3, pip3 python3-numpy, python3-scipy, git
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libblas-dev \
    liblapack-dev \ 
    gfortran \
    git \
    wget \
    curl \
    make \
    python3 \
    python3-pip \
    python3-numpy \
    python3-scipy \
    python3-matplotlib

# install pyenv
RUN git clone https://github.com/yyuu/pyenv.git ~/.pyenv && \
    echo 'export PYENV_ROOT="$HOME/.pyenv"' >> ~/.bash_profile && \
    echo 'export PATH="$PYENV_ROOT/bin:$PATH"' >> ~/.bash_profile && \
    echo 'eval "$(pyenv init -)"' >> ~/.bash_profile

# install pyenv-virtualenv
RUN git clone https://github.com/yyuu/pyenv-virtualenv.git ~/.pyenv/plugins/pyenv-virtualenv && \
    echo 'eval "$(pyenv virtualenv-init -)"' >> ~/.bash_profile        

# reload .bash_profile
RUN /bin/bash -c 'source ~/.bash_profile'
RUN apt-get install -y --no-install-recommends libssl-dev openssl
RUN ["/bin/bash", "-c", "/root/.pyenv/bin/pyenv install 3.5.1"]
RUN ["/bin/bash", "-c", "/root/.pyenv/bin/pyenv global 3.5.1"]
