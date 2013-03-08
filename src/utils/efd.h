/*
    Copyright (c) 2012-2013 250bpm s.r.o.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom
    the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#ifndef NN_EFD_INCLUDED
#define NN_EFD_INCLUDED

/*  Defines a type of native file descriptor on the platform. */
#if defined NN_HAVE_WINDOWS
#include "win.h"
typedef SOCKET nn_fd;
#else
typedef int nn_fd;
#endif

/*  Provides a way to send signals via file descriptors. The important part
    is that nn_efd_getfd() returns an actual OS-level file descriptor that
    you can poll on to wait for the event. */

struct nn_efd;

int nn_efd_init (struct nn_efd *self);
void nn_efd_term (struct nn_efd *self);
nn_fd nn_efd_getfd (struct nn_efd *self);
void nn_efd_signal (struct nn_efd *self);
void nn_efd_unsignal (struct nn_efd *self);

#if defined NN_HAVE_WINDOWS

#include "win.h"

struct nn_efd {
    SOCKET r;
    SOCKET w;
};

#elif defined NN_USE_SOCKETPAIR

struct nn_efd {
    int r;
    int w;
};

#elif defined NN_USE_PIPE

struct nn_efd {
    int r;
    int w;
};

#elif defined NN_USE_EVENTFD

struct nn_efd {
    int efd;
};

#endif

#endif
