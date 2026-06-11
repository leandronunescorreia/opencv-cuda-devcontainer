ARG CUDA_VERSION=11.8.0
ARG UBUNTU_VERSION=22.04

FROM nvidia/cuda:${CUDA_VERSION}-cudnn8-devel-ubuntu${UBUNTU_VERSION}

ARG PYTHON_VERSION=3.9
ARG OPENCV_VERSION=4.10.0

ENV DEBIAN_FRONTEND=noninteractive
ENV CONDA_DIR=/usr/local/conda
ENV PATH=${CONDA_DIR}/bin:$PATH
ENV WORK_DIR=/home

WORKDIR ${WORK_DIR}

# ------------------------------------------------------------
# Base system packages
# ------------------------------------------------------------

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        wget \
        ca-certificates \
        bzip2 \
        unzip && \
    rm -rf /var/lib/apt/lists/*

# ------------------------------------------------------------
# System dependencies for OpenCV
# ------------------------------------------------------------

# --------------------------
# Install build dependencies
# --------------------------
# Build tools
RUN apt-get update && \
apt-get install -y --no-install-recommends \
        build-essential cmake cmake-qt-gui pkg-config unzip yasm git checkinstall \
        gcc g++ \
        binutils tar lsb-release procps manpages-dev sudo software-properties-common \
        curl wget zip xauth swig \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# Video/Audio
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        ffmpeg sox libsndfile1 libavcodec-dev libavformat-dev libswscale-dev \
        libavutil-dev libavfilter-dev libswresample-dev libpostproc-dev \
        libx264-dev libxvidcore-dev libmp3lame-dev libopus-dev libvorbis-dev \
        libva-dev \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean


# Image libs
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libjpeg-dev libjpeg8-dev libjpeg-turbo8-dev libpng-dev libtiff-dev libtiff5-dev \
        libopenjp2-7-dev libwebp-dev libopenexr-dev openexr \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean


# GUI / OpenGL
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libgtk-3-dev libcanberra-gtk3-module \
        libgl1 libgl1-mesa-glx libgl1-mesa-dev libglvnd-dev libglu1-mesa libglu1-mesa-dev \
        libgl-dev libglew-dev mesa-utils mesa-common-dev libglfw3 libglfw3-dev \
        libx11-dev libxext6 libxfixes-dev libxrender-dev libxrandr-dev libxi-dev \
        libxinerama-dev libxcursor-dev libxmu-dev libfontconfig1-dev \
        dbus-x11 \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean


# Video4Linux / cameras
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libv4l-dev v4l-utils libdc1394-25 libdc1394-dev libxine2-dev qv4l2 \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean


# GStreamer
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev \
        gstreamer1.0-tools gstreamer1.0-plugins-base gstreamer1.0-plugins-good \
        gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean


# Linear algebra / BLAS / LAPACK
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libatlas-base-dev liblapack-dev liblapacke-dev libopenblas-dev libeigen3-dev \
        libtbb-dev libtbb2 \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean


# Logging / flags
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libgoogle-glog-dev libgflags-dev \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# HDF5 / protobuf / optional
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libhdf5-dev libprotobuf-dev protobuf-compiler libgphoto2-dev doxygen \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# Boost
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libboost-python-dev libboost-thread-dev \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# VTK / Qt / extras
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        qtbase5-dev qt5-qmake qtchooser qtbase5-dev-tools qtmultimedia5-dev \
        libqt5x11extras5 \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# PostgreSQL client
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libpq-dev \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# Tesseract OCR
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libtesseract-dev \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean

# X11 session
RUN apt-get update && \
apt-get install -y --no-install-recommends \        
        libsm6 \
        zlib1g-dev \
    && rm -rf /var/lib/apt/lists/* \
    && apt-get clean \
    && ln -s /usr/include/libv4l1-videodev.h /usr/include/linux/videodev.h

# Cleanup
RUN apt-get update && apt-get install -y --no-install-recommends --fix-missing \
    libcurl4-openssl-dev \
 && rm -rf /var/lib/apt/lists/* \
 && apt-get clean

# ------------------------------------------------------------
# Install Miniconda
# ------------------------------------------------------------

RUN wget -q https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -O miniconda.sh && \
    chmod u+x miniconda.sh && \
    bash miniconda.sh -b -p ${CONDA_DIR} && \
    rm -f miniconda.sh
# ------------------------------------------------------------
# Install Python + Conda packages
# ------------------------------------------------------------

ENV CONDA_PLUGINS_AUTO_ACCEPT_TOS=true
RUN conda init bash
RUN conda tos accept
# Conda configuration
RUN conda config --set always_yes yes && \
    conda config --add channels conda-forge && \
    conda config --set channel_priority strict

RUN conda install -y -c conda-forge python=${PYTHON_VERSION}
RUN conda install -y -c conda-forge "numpy>=1.21"
RUN conda install -y -c conda-forge matplotlib=3.3
RUN conda search conda-forge::xeus-cling=0.15.3 --info
RUN conda install -y -c conda-forge xeus-cling=0.15.3

RUN conda install -y notebook jupyterlab ipykernel
RUN conda clean --all --yes

# ------------------------------------------------------------
# Register xeus-cling kernels
# ------------------------------------------------------------

# Explicitly register xeus-cling kernels
# RUN mkdir -p ${CONDA_DIR}/share/jupyter/kernels && \
#     cp -r ${CONDA_DIR}/share/jupyter/kernels/xcpp11 ${CONDA_DIR}/share/jupyter/kernels/ && \
#     cp -r ${CONDA_DIR}/share/jupyter/kernels/xcpp14 ${CONDA_DIR}/share/jupyter/kernels/ && \
#     cp -r ${CONDA_DIR}/share/jupyter/kernels/xcpp17 ${CONDA_DIR}/share/jupyter/kernels/

# ------------------------------------------------------------
# Verify xeus-cling installation
# ------------------------------------------------------------

# RUN /usr/local/conda/bin/xeus-cling --install --sys-prefix --kernel-name xcpp17 --display-name "C++17 (xeus-cling)" && \
#     /usr/local/conda/bin/xeus-cling --install --sys-prefix --kernel-name xcpp14 --display-name "C++14 (xeus-cling)" && \
#     /usr/local/conda/bin/xeus-cling --install --sys-prefix --kernel-name xcpp11 --display-name "C++11 (xeus-cling)"

# ------------------------------------------------------------
# Build OpenCV 4.8.1 from source
# ------------------------------------------------------------
WORKDIR /tmp
RUN wget -q "https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip" -O opencv.zip && \
    unzip -q opencv.zip && mv opencv-${OPENCV_VERSION} /opencv && rm opencv.zip && \
    wget -q "https://github.com/opencv/opencv_contrib/archive/${OPENCV_VERSION}.zip" -O contrib.zip && \
    unzip -q contrib.zip && mv opencv_contrib-${OPENCV_VERSION} /opencv_contrib && rm contrib.zip

# --------------------------
# Build OpenCV
# --------------------------
WORKDIR /opencv
RUN mkdir -p build && cd build && \
    PYTHON_EXEC=$(which python) && \
    PYTHON_INCLUDE=$($PYTHON_EXEC -c "from sysconfig import get_paths as gp; print(gp()['include'])") && \
    PYTHON_LIBFILE=$($PYTHON_EXEC -c "import sysconfig, os; \
        print(os.path.join(sysconfig.get_config_var('LIBDIR'), \
        'libpython' + sysconfig.get_config_var('LDVERSION') + '.so'))") && \
    NUMPY_INCLUDE=$($PYTHON_EXEC -c "import numpy; print(numpy.get_include())") && \
    PYTHON_SITE=$($PYTHON_EXEC -c "import site; print(site.getsitepackages()[0])") && \
    cmake \
        -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D OPENCV_EXTRA_MODULES_PATH=/opencv_contrib/modules \
        -D WITH_OPENGL=ON \
        -D WITH_GLEW=ON \
        -D WITH_FFMPEG=ON \
        -D WITH_LIBV4L=ON \
        -D BUILD_opencv_cvv=OFF \
        -D BUILD_opencv_stereo=OFF \
        -D BUILD_opencv_legacy=OFF \
        # python
        -D BUILD_opencv_python3=ON \
        -D BUILD_opencv_python2=OFF \
        -D PYTHON_VERSION=310 \    
        -D PYTHON3_EXECUTABLE=${PYTHON_EXEC} \
        -D PYTHON3_INCLUDE_DIR=${PYTHON_INCLUDE} \
        -D PYTHON3_LIBRARY=${PYTHON_LIBFILE} \
        -D PYTHON3_NUMPY_INCLUDE_DIRS=${NUMPY_INCLUDE} \
        -D PYTHON3_PACKAGES_PATH=${PYTHON_SITE} \
        -D OPENCV_PYTHON3_INSTALL_PATH=${PYTHON_SITE} \
        #cuda
        -D WITH_CUDA=ON \
        -D WITH_CUDNN=ON \
        -D OPENCV_DNN_CUDA=ON \
        -D CUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda \
        -D CMAKE_LIBRARY_PATH=/usr/local/cuda/lib64/stubs \    
        -D CMAKE_CUDA_ARCHITECTURES="5.3 6.1 7.0 7.5 8.6" \
        -D ENABLE_FAST_MATH=ON \
        -D CUDA_FAST_MATH=ON \
        -D CUDA_ARCH_BIN="5.3 6.1 7.0 7.5 8.6" \
        -D CUDA_ARCH_PTX="5.3 6.1 7.0 7.5 8.6" \
        -D WITH_NVCUVID=ON \        
        -D OPENCV_ENABLE_NONFREE=OFF \
        -D INSTALL_PYTHON_EXAMPLES=OFF \
        -D INSTALL_C_EXAMPLES=OFF \
        -D BUILD_TESTS=OFF \
        -D BUILD_PERF_TESTS=OFF \
        -D BUILD_EXAMPLES=OFF \
        -D BUILD_opencv_viz=OFF \
        -D BUILD_opencv_hdf=OFF \
        -D WITH_QT=OFF \
        -D WITH_IPP=OFF \
        -D BUILD_IPP_IW=OFF \
        -D WITH_OPENEXR=OFF \
        -D CMAKE_CXX_STANDARD=17 \
        -D CMAKE_CXX_STANDARD_REQUIRED=ON \
        -D CMAKE_CXX_FLAGS="-Wno-error -O2" \
        .. && \
    make VERBOSE=1 -j"$(nproc)" && make install && ldconfig

# ------------------------------------------------------------
# Cleanup
# ------------------------------------------------------------

RUN apt-get -qq -y autoremove && \
    apt-get -qq autoclean

RUN conda install -y \
-c pytorch \
-c nvidia \
pytorch=2.5.0 \
torchvision=0.20.0 \
torchaudio=2.5.0 \
pytorch-cuda=11.8 && \
conda clean --all --yes
RUN conda clean --all --yes


# ------------------------------------------------------------
# setup libtorch for C++ development
# ------------------------------------------------------------
RUN wget https://download.pytorch.org/libtorch/cu118/libtorch-cxx11-abi-shared-with-deps-2.5.0%2Bcu118.zip \
 && unzip libtorch*.zip \
 && mkdir -p /work/work/thirdparty \
 && mv libtorch /work/work/thirdparty/libtorch \
 && rm libtorch*.zip


# warning to abi compatibility issues with libtorch and opencv, see 
# conda install -c conda-forge openh264

EXPOSE 8888

RUN mkdir -p /work
WORKDIR /work

RUN jupyter kernelspec list

CMD ["bash"]