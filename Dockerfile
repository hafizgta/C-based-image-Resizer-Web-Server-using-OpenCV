FROM ubuntu:focal
RUN apt-get update --fix-missing \
  && apt-get install -y git g++ make wget build-essential

RUN export DEBIAN_FRONTEND=noninteractive \
	&& apt-get install -y tzdata \
	&& ln -fs /usr/share/zoneinfo/Asia/Jakarta /etc/localtime \
	&& dpkg-reconfigure --frontend noninteractive tzdata

RUN apt install -y cmake git pkg-config libgtk-3-dev \
  libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
  libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
  gfortran openexr libatlas-base-dev python3-dev python3-numpy \
  libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
  libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev

WORKDIR /opt/app 
RUN mkdir ./opencv_build && cd ./opencv_build\
  && git clone https://github.com/opencv/opencv.git\
  && git clone https://github.com/opencv/opencv_contrib.git

RUN cd ./opencv_build/opencv\
  && mkdir -p build

RUN cd ./opencv_build/opencv/build \
  && cmake -D CMAKE_BUILD_TYPE=RELEASE \
  -D CMAKE_INSTALL_PREFIX=/usr/local \
  -D INSTALL_C_EXAMPLES=ON \
  -D INSTALL_PYTHON_EXAMPLES=ON \
  -D OPENCV_GENERATE_PKGCONFIG=ON \
  -D OPENCV_EXTRA_MODULES_PATH=/opt/app/opencv_build/opencv_contrib/modules \
  -D BUILD_EXAMPLES=ON .. \
  && make -j8 \
  && make install

RUN pkg-config --modversion opencv4


RUN wget https://dl.bintray.com/boostorg/release/1.69.0/source/boost_1_69_0.tar.gz \
  && tar xfz boost_1_69_0.tar.gz \
  && rm boost_1_69_0.tar.gz \
  && cd boost_1_69_0 \
  && ./bootstrap.sh --prefix=/usr/local --with-libraries=program_options \
  && ./b2 install 


RUN rm -rf boost_1_69_0 \
    && rm -rf opencv_build\
    && rm -rf /var/lib/apt/lists/*

ADD *.h /
ADD *.cpp /
ADD CMakeLists.txt /

RUN cmake . \
  && make

EXPOSE 8080

ENTRYPOINT ["/bin/bash"]
# ENTRYPOINT ["./tf_detect_crow"]