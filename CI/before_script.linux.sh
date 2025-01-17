#!/bin/bash

set -xeo pipefail

free -m

if [[ "${BUILD_TESTS_ONLY}" ]]; then
    export GOOGLETEST_DIR="${PWD}/googletest/build/install"
    env GENERATOR='Unix Makefiles' CONFIGURATION=Release CI/build_googletest.sh
fi

declare -a CMAKE_CONF_OPTS=(
    -DCMAKE_C_COMPILER="${CC:-/usr/bin/cc}"
    -DCMAKE_CXX_COMPILER="${CXX:-/usr/bin/c++}"
    -DCMAKE_C_COMPILER_LAUNCHER=ccache
    -DCMAKE_CXX_COMPILER_LAUNCHER=ccache
    -DCMAKE_INSTALL_PREFIX=install
    -DCMAKE_BUILD_TYPE=RelWithDebInfo
    -DBUILD_SHARED_LIBS=OFF
    -DUSE_SYSTEM_TINYXML=ON
    -DCMAKE_INSTALL_PREFIX=install
    -DRakNet_LIBRARY_RELEASE=~/CrabNet/lib/libRakNetLibStatic.a
    -DRakNet_LIBRARY_DEBUG=~/CrabNet/lib/libRakNetLibStatic.a
)

if [[ $CI_OPENMW_USE_STATIC_DEPS ]]; then
    CMAKE_CONF_OPTS+=(
        -DOPENMW_USE_SYSTEM_MYGUI=OFF
        -DOPENMW_USE_SYSTEM_OSG=OFF
        -DOPENMW_USE_SYSTEM_BULLET=OFF
    )
fi

mkdir -p build
cd build

# Set up compilers
if [ ! -z "${MATRIX_CC}" ]; then
    eval "${MATRIX_CC}"
fi

export RAKNET_ROOT=~/CrabNet

if [[ "${BUILD_TESTS_ONLY}" ]]; then
    ${ANALYZE} cmake \
        "${CMAKE_CONF_OPTS[@]}" \
        -DBUILD_OPENMW=OFF \
        -DBUILD_OPENMW_MP=OFF \
        -DBUILD_BSATOOL=OFF \
        -DBUILD_ESMTOOL=OFF \
        -DBUILD_LAUNCHER=OFF \
        -DBUILD_BROWSER=OFF \
        -DBUILD_MWINIIMPORTER=OFF \
        -DBUILD_ESSIMPORTER=OFF \
        -DBUILD_OPENCS=OFF \
        -DBUILD_WIZARD=OFF \
        -DBUILD_UNITTESTS=ON \
        -DGTEST_ROOT="${GOOGLETEST_DIR}" \
        -DGMOCK_ROOT="${GOOGLETEST_DIR}" \
        ..
else
    ${ANALYZE} cmake \
        "${CMAKE_CONF_OPTS[@]}" \
        ..
fi
