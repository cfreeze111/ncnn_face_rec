# Copyright (C) 2022 The Qt Company Ltd.
# SPDX-License-Identifier: BSD-3-Clause

#####################################################################
## tst_bench_qhash Binary:
#####################################################################

qt_internal_add_benchmark(tst_bench_qhash
    SOURCES
        tst_bench_qhash.cpp
        outofline.cpp
    NO_PCH_SOURCES
        tst_bench_qhash.cpp # undef QT_NO_FOREACH
    INCLUDE_DIRECTORIES
        .
    LIBRARIES
        Qt::Test
)
