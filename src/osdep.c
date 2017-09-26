/*
 *
 * Copyright (c) 2017 Bin Yang <byang1217@gmail.com>
 * Copyright (c) 2003-2008 Fabrice Bellard
 * Copyright (c) 2010 Red Hat, Inc.
 *
 * QEMU library functions on POSIX which are shared between QEMU and
 * the QEMU tools.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "qemu/osdep.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <termios.h>

FILE *qemu_logfile;
int qemu_loglevel = -1;
static const char *hw_version = "2.5+";

bool id_wellformed(const char *id)
{
    int i;

    if (!qemu_isalpha(id[0])) {
        return false;
    }
    for (i = 1; id[i]; i++) {
        if (!qemu_isalnum(id[i]) && !strchr("-._", id[i])) {
            return false;
        }
    }
    return true;
}

void qemu_set_hw_version(const char *version)
{
    hw_version = version;
}

const char *qemu_hw_version(void)
{
    return hw_version;
}

Monitor *cur_mon;

bool monitor_cur_is_qmp(void)
{
    return 0;
}

void monitor_vprintf(Monitor *mon, const char *fmt, va_list ap)
{
    vfprintf(qemu_logfile, fmt, ap);
}

void monitor_printf(Monitor *mon, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(qemu_logfile, fmt, ap);
    va_end(ap);
}

void qemu_log(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(qemu_logfile, fmt, ap);
    fflush(qemu_logfile);
    va_end(ap);
}

void qemu_log_flush(void)
{
    fflush(qemu_logfile);
}

bool qemu_log_in_addr_range(uint64_t addr)
{
//	return false;
	return true;
}

void *qemu_try_memalign(size_t alignment, size_t size)
{
	void *mem;
	void **ptr;

	if (alignment < sizeof(void*)) {
		alignment = sizeof(void*);
	}
	mem = malloc(size + alignment - 1 + sizeof(void *));
	ptr = (void**)((unsigned long)(mem + alignment - 1 + sizeof(void *)) & ~(alignment - 1));
	ptr[-1] = mem;
	return ptr;
}

void *qemu_memalign(size_t alignment, size_t size)
{
	return qemu_try_memalign(alignment, size);
}

void *qemu_anon_ram_alloc(size_t size, uint64_t *alignment)
{
	*alignment = QEMU_VMALLOC_ALIGN;
	return qemu_try_memalign(*alignment, size);
}

void qemu_vfree(void *ptr)
{
	free(((void**)ptr)[-1]);
}

void qemu_anon_ram_free(void *ptr, size_t size)
{
	(void)size;
	qemu_vfree(ptr);
}

void qemu_set_block(int fd)
{
    int f;
    f = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, f & ~O_NONBLOCK);
}

void qemu_set_nonblock(int fd)
{
    int f;
    f = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, f | O_NONBLOCK);
}

int socket_set_fast_reuse(int fd)
{
    int val = 1, ret;

    ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
                     (const char *)&val, sizeof(val));

    assert(ret == 0);

    return ret;
}

void qemu_set_cloexec(int fd)
{
    int f;
    f = fcntl(fd, F_GETFD);
    fcntl(fd, F_SETFD, f | FD_CLOEXEC);
}

void qemu_set_tty_echo(int fd, bool echo)
{
    struct termios tty;

    tcgetattr(fd, &tty);

    if (echo) {
        tty.c_lflag |= ECHO | ECHONL | ICANON | IEXTEN;
    } else {
        tty.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
    }

    tcsetattr(fd, TCSANOW, &tty);
}

static struct termios oldtty;

static void term_exit(void)
{
    tcsetattr(0, TCSANOW, &oldtty);
}

static void term_init(void)
{
    struct termios tty;

    tcgetattr(0, &tty);
    oldtty = tty;

    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP
                          |INLCR|IGNCR|ICRNL|IXON);
    tty.c_oflag |= OPOST;
    tty.c_lflag &= ~(ECHO|ECHONL|ICANON|IEXTEN);
    tty.c_cflag &= ~(CSIZE|PARENB);
    tty.c_cflag |= CS8;
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &tty);

    atexit(term_exit);
}
