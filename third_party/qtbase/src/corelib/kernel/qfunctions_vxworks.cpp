// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "qglobal.h"

#ifdef Q_OS_VXWORKS

#include "qplatformdefs.h"
#include "qfunctions_vxworks.h"

#if defined(_WRS_KERNEL)
#include <vmLib.h>
#endif
#include <selectLib.h>
#include <ioLib.h>

QT_USE_NAMESPACE

#ifdef __cplusplus
extern "C" {
#endif

// no lfind() - used by the TIF image format
void *lfind(const void* key, const void* base, size_t* elements, size_t size,
            int (*compare)(const void*, const void*))
{
    const char* current = (char*) base;
    const char* const end = (char*) (current + (*elements) * size);
    while (current != end) {
        if (compare(current, key) == 0)
            return (void*)current;
        current += size;
    }
    return 0;
}


// no rand_r(), but rand()
// NOTE: this implementation is wrong for multi threaded applications,
// but there is no way to get it right on VxWorks (in kernel mode)
#if defined(_WRS_KERNEL)
int rand_r(unsigned int * /*seedp*/)
{
    return rand();
}
#endif

// gettimeofday() is declared, but is missing from the library
// It IS however defined in the Curtis-Wright X11 libraries, so
// we have to make the symbol 'weak'
#if defined(Q_CC_DIAB) && !defined(VXWORKS_DKM) && !defined(VXWORKS_RTP)
#  pragma weak gettimeofday
#endif
int gettimeofday(struct timeval *tv, void /*struct timezone*/ *)
{
    // the compiler will optimize this and will only use one code path
    if (sizeof(struct timeval) == sizeof(struct timespec)) {
        int res = clock_gettime(CLOCK_REALTIME, (struct timespec *) tv);
        if (!res)
            tv->tv_usec /= 1000;
        return res;
    } else {
        struct timespec ts;

        int res = clock_gettime(CLOCK_REALTIME, &ts);
        if (!res) {
            tv->tv_sec = ts.tv_sec;
            tv->tv_usec = ts.tv_nsec / 1000;
        }
        return res;
    }
}

// symlinks are not supported (lstat is now just a call to stat - see qplatformdefs.h)
int symlink(const char *, const char *)
{
    errno = EIO;
    return -1;
}

ssize_t readlink(const char *, char *, size_t)
{
    errno = EIO;
    return -1;
}

// there's no truncate(), but ftruncate() support...
int truncate(const char *path, off_t length)
{
    int fd = open(path, O_WRONLY, 00777);
    if (fd >= 0) {
        int res = ftruncate(fd, length);
        int en = errno;
        close(fd);
        errno = en;
        return res;
    }
    // errno is already set by open
    return -1;
}



// VxWorks doesn't know about passwd & friends.
// in order to avoid patching the unix fs path everywhere
// we introduce some dummy functions that simulate a single
// 'root' user on the system.

uid_t getuid()
{
    return 0;
}

gid_t getgid()
{
    return 0;
}

uid_t geteuid()
{
    return 0;
}

struct group *getgrgid(gid_t gid)
{
    static struct group grbuf = { "root", 0, 0, 0 };

    if (gid == 0) {
        return &grbuf;
    } else {
        errno = ENOENT;
        return 0;
    }
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif // Q_OS_VXWORKS
