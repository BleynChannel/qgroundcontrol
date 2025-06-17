# Maintainer: acxz <akashpatel2008@yahoo.com>
# Contributor: K. Morton <pryre.dev@outlook.com>
# Contributor: Anselmo L. S. Melo <anselmo.melo@intel.com>
pkgname=qgroundcontrol
pkgver=4.4.3
pkgrel=1
pkgdesc="Micro air vehicle ground control station."
arch=('x86_64')
url="https://github.com/BleynChannel/qgroundcontrol"
license=('GPL3')

depends=('bzip2'
         'dbus'
         'flac'
         'gst-plugins-base-libs'
         'libasyncns'
         'libffi'
         'libgcrypt'
         'libgpg-error'
         'libogg'
         'libsndfile'
         'libsystemd'
         'libunwind'
         'libx11'
         'libxau'
         'libxcb'
         'libxdmcp'
         'libxext'
         'lz4'
         'orc'
         'pcre'
         'sdl2'
         'xz'
         'zlib'
         'icu'
         'qt6-connectivity'
         'qt6-charts'
         'qt6-5compat'
         'qt6-location'
         'qt6-multimedia-gstreamer'
         'qt6-multimedia'
         'qt6-sensors'
         'qt6-speech'
         'qt6-serialport'
         'qt6-tools'
         'qt6-wayland'
         'qt6-quick3d'
        #  'qt6-quickcontrols'
        #  'qt6-quickcontrols2'
        #  'qt6-svg'
        #  'qt6-graphicaleffects'
        #  'qt6-x11extras'
         'qt6-mqtt'
         'speech-dispatcher'
)

makedepends=('git' 'qt6-base' 'patchelf' 'cmake' 'ninja')

source=("${pkgname}-${pkgver}::git+file:///home/devel/qgroundcontrol"
        # "${pkgname}-${pkgver}::git+https://github.com/BleynChannel/qgroundcontrol.git#branch=dev"
        "${pkgname}-GpsDrivers::git+https://github.com/PX4/GpsDrivers.git"
        "${pkgname}-c_library_v2::git+https://github.com/mavlink/c_library_v2.git"
        "${pkgname}-android_openssl::git+https://github.com/KDAB/android_openssl.git"
        "${pkgname}-gst-plugins-good::git+https://github.com/mavlink/gst-plugins-good.git"
        "${pkgname}-xz-embedded::git+https://github.com/Auterion/xz-embedded.git"
        "${pkgname}-libevents::git+https://github.com/mavlink/libevents.git"
        "${pkgname}-eigen::git+https://gitlab.com/libeigen/eigen.git"
        "${pkgname}-qmdnsengine::git+https://github.com/patrickelectric/qmdnsengine.git"
        "${pkgname}-shapelib::git+https://github.com/OSGeo/shapelib.git"
        "${pkgname}-ArduPilot-Parameter-Repository::git+https://github.com/ArduPilot/ArduPilot-Parameter-Repository.git"
        # "${pkgname}-qtmqtt::git+https://github.com/qt/qtmqtt.git#tag=6.6.3"
        "${pkgname}-libssh::git+https://git.libssh.org/projects/libssh.git"
)

sha256sums=('SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            'SKIP'
            # 'SKIP'
            'SKIP'
)

prepare() {
  cd "$srcdir/${pkgname}-${pkgver}"

  # git submodule init

  # git config submodule."src/GPS/Drivers".url "${srcdir}/${pkgname}"-GpsDrivers
  # git config submodule."libs/mavlink/include/mavlink/v2.0".url "${srcdir}/${pkgname}"-c_library_v2
  # git config submodule."libs/OpenSSL/android_openssl".url "${srcdir}/${pkgname}"-android_openssl
  # git config submodule."libs/qmlglsink/gst-plugins-good".url "${srcdir}/${pkgname}"-gst-plugins-good
  # git config submodule."libs/xz-embedded".url "${srcdir}/${pkgname}"-xz-embedded
  # git config submodule."libs/libevents/libevents".url "${srcdir}/${pkgname}"-libevents
  # git config submodule."libs/eigen".url "${srcdir}/${pkgname}"-eigen
  # git config submodule."libs/qmdnsengine".url "${srcdir}/${pkgname}"-qmdnsengine
  # git config submodule."libs/shapelib".url "${srcdir}/${pkgname}"-shapelib
  # # git config submodule."libs/qtmqtt".url "${srcdir}/${pkgname}"-qtmqtt
  # git config submodule."libs/libssh".url "${srcdir}/${pkgname}"-libssh
  # git config submodule."src/FirmwarePlugin/APM/ArduPilot-Parameter-Repository".url "${srcdir}/${pkgname}"-ArduPilot-Parameter-Repository

  # git -c protocol.file.allow=always submodule update --init --recursive

  # git config --global --add safe.directory "${srcdir}/${pkgname}-${pkgver}"
}

build() {
  mkdir -p "${srcdir}/${pkgname}-${pkgver}/build"
  cd "$srcdir/${pkgname}-${pkgver}/build"
  
  cmake -S "${srcdir}/${pkgname}-${pkgver}" -B . -G Ninja -DCMAKE_BUILD_TYPE=Debug ;
	cmake --build . --target all --config Debug ;
	# cmake --install . --config Debug
}

package() {
  echo "Skipping package creation for now"

#   mkdir -p "${pkgdir}/opt" "${pkgdir}/usr/bin" "${pkgdir}/usr/share/applications"
#   cp -r "${srcdir}/${pkgname}-${pkgver}/build/staging" "${pkgdir}/opt/${pkgname}"
#   cp "${srcdir}/${pkgname}-${pkgver}/resources/icons/qgroundcontrol.png" "${pkgdir}/opt/${pkgname}"
#   cp "${srcdir}/${pkgname}-${pkgver}/deploy/qgroundcontrol-start.sh" "${pkgdir}/opt/${pkgname}"

#   # Use our own desktop file and remove the default one

#   echo "[Desktop Entry]
# Type=Application
# Name=QGroundControl Release
# Comment=Ground control for unmanned vehicles
# Path=/opt/${pkgname}/
# Exec=/usr/bin/${pkgname}
# Icon=/opt/${pkgname}/qgroundcontrol.png
# Terminal=false
# Categories=Qt;Utility;" > "$srcdir/${pkgname}.desktop"

#   rm "${pkgdir}/opt/${pkgname}/${pkgname}.desktop"
#   cp "${srcdir}/${pkgname}.desktop" "${pkgdir}/opt/${pkgname}"

#   ln -s "/opt/${pkgname}/QGroundControl" "${pkgdir}/usr/bin/${pkgname}"
#   ln -s "/opt/${pkgname}/${pkgname}.desktop" "${pkgdir}/usr/share/applications/${pkgname}.desktop"
}

# vim:set ts=2 sw=2 et: