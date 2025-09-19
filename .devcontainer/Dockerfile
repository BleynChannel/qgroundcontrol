FROM ubuntu:22.04

ARG QT_VERSION=6.8.3
ARG QT_MODULES="qtcharts qtlocation qtpositioning qtspeech qt5compat qtmultimedia qtserialport qtimageformats qtshadertools qtconnectivity qtquick3d qtsensors"

ENV DEBIAN_FRONTEND noninteractive

ENV DISPLAY :99

ENV QT_PATH /opt/Qt
ENV QT_DESKTOP $QT_PATH/${QT_VERSION}/gcc_64

ENV PATH /usr/lib/ccache:$QT_DESKTOP/bin:$PATH

COPY tools/setup/install-dependencies-debian.sh /tmp/qt/
RUN /tmp/qt/install-dependencies-debian.sh

COPY tools/setup/install-qt-debian.sh /tmp/qt/
RUN /tmp/qt/install-qt-debian.sh

RUN locale-gen en_US.UTF-8 && dpkg-reconfigure locales

RUN apt-get update && apt-get install -y sudo
RUN apt install gstreamer1.0-plugins-bad gstreamer1.0-libav gstreamer1.0-gl -y
RUN apt install libfuse2 -y
RUN apt install libxcb-xinerama0 libxkbcommon-x11-0 libxcb-cursor-dev -y

RUN useradd -m -s /bin/bash myuser
RUN usermod -aG sudo myuser
RUN echo "%sudo ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/sudo-group

USER myuser

WORKDIR /home/myuser