
mkdir -p build
cp utils/CMakeLists.header.txt  build/CMakeLists.txt
set -x
COCOS_ENGINE_DEV=0 cmake -Sbuild -Bbuild -DCC_USE_GLES2=ON -DCC_USE_VULKAN=ON -DCC_USE_GLES3=ON \
    -G"Visual Studio 16 2019" -DCMAKE_CXX_STANDARD=20
