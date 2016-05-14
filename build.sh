CV_VERSION=$(python -c "import cv2; print(cv2.__version__.split('.')[0])")
if [ $CV_VERSION="3" ];
then
  echo "Patching files for OpenCV 3"
  patch stasm/MOD_1/facedet.cpp < stasm_build/patches/facedet.cpp.20160514.diff
  patch stasm/misc.h < stasm_build/patches/misc.h.20160514.diff
  patch stasm/misc.cpp < stasm_build/patches/misc.cpp.20160514.diff
  patch stasm/asm.cpp < stasm_build/patches/asm.cpp.20160514.diff
  patch stasm/faceroi.cpp < stasm_build/patches/faceroi.cpp.20160514.diff
  patch stasm/pinstart.cpp < stasm_build/patches/pinstart.cpp.20160514.diff
fi

patch apps/appmisc.cpp < stasm_build/patches/appmisc.cpp.20140201.diff
patch apps/shapefile/shapefile.cpp < stasm_build/patches/shapefile.cpp.20140201.diff

cp stasm_build/CMakeLists.txt .
cp stasm_build/stasm_util.cpp .
cp stasm_build/STASMConfig.cmake.in .
if [ $CV_VERSION="3" ];
then
  patch stasm_util.cpp < stasm_build/patches/stasm_util.cpp.20160514.diff
fi

mkdir build && cd build
cmake ../
make