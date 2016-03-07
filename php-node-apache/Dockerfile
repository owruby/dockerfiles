
FROM php:5.6-apache

MAINTAINER ruby.yano1995@gmail.com

VOLUME /app

# Update apt-get
RUN apt-get update

# Install nodebrew
RUN cd  && \
    apt-get -y install wget && \
    wget git.io/nodebrew && \
    perl nodebrew setup
ENV PATH $HOME/.nodebrew/current/bin:$PATH

# Install Node 
RUN export PATH=$HOME/.nodebrew/current/bin:$PATH && \
    nodebrew install v4.3.2 && \
    nodebrew install-binary v4.3.2&& \
    nodebrew use v4.3.2

# Install gulp
RUN export PATH=$HOME/.nodebrew/current/bin:$PATH && \
    npm install -g gulp

RUN echo export PATH=$HOME/.nodebrew/current/bin:$PATH >> ~/.bashrc && \
    rm -fR /var/www/html
