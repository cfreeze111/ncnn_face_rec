#!/bin/bash
SCRIPT_HOME=$(cd $(dirname $0); pwd)
LOG_FILE=$SCRIPT_HOME/../build.log
source $SCRIPT_HOME/log.sh
set -e

function build_qt()
{
    THIRD_PARTY_DIR="$SCRIPT_HOME/../third_party"

    if [ -d "$THIRD_PARTY_DIR/qtbase-release" ]; then
        log "qtbase is already build! skip..." WARN
        return
    fi

    cmake --version | head -1
    log "Ninja $(ninja --version)" INFO
    { ninja --help || true; } 2>&1 | grep "run N jobs in parallel"

    QT_DIR="$THIRD_PARTY_DIR/qtbase"
    QT_TMP="$SCRIPT_HOME/../cmake-build-release/build_qt"
    QT_DST="$THIRD_PARTY_DIR/qtbase-release"

    log "QT_DIR=${QT_DIR}" WARN
    log "QT_TMP=${QT_TMP}" WARN
    log "QT_DST=${QT_DST}" WARN

    rm -rf ${QT_TMP}
    mkdir -p ${QT_TMP}
    cd ${QT_TMP}

    ${QT_DIR}/configure \
        -release \
        -static \
        -opensource \
        -confirm-license \
        -make libs \
        -nomake tests \
        -nomake examples \
        -prefix ${QT_DST} \
        ${@}
    # -xcb \
    # -system-sqlite \
    # -system-pcre \
    # -system-zlib \
    # -system-freetype \
    # -system-libpng \
    # -system-libjpeg \
    # -system-harfbuzz \
    # -system-libb2 \
    # -system-doubleconversion
    # -system-libmd4c # C markdown parser

    ninja install
}
build_qt
