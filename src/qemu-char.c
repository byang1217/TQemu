/*
 * QEMU System Emulator
 *
 * Copyright (c) 2003-2008 Fabrice Bellard
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
#include "qemu-common.h"
#include "qemu/error-report.h"
#include "qemu/timer.h"
#include "sysemu/char.h"
#include "sysemu/sysemu.h"

#include <sys/times.h>
#include <sys/wait.h>
#include <termios.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/select.h>
#include "qemu/sockets.h"

CharDriverState *serial_hds[MAX_SERIAL_PORTS];

/* Get a character (serial) device interface.  */
CharDriverState *qemu_char_get_next_serial(void)
{
    static int next_serial;
    CharDriverState *chr;

    /* FIXME: This function needs to go away: use chardev properties!  */

    while (next_serial < MAX_SERIAL_PORTS && serial_hds[next_serial]) {
        chr = serial_hds[next_serial++];
        qemu_chr_fe_claim_no_fail(chr);
        return chr;
    }
    return NULL;
}

int qemu_chr_fe_claim(CharDriverState *s)
{
    if (s->avail_connections < 1) {
        return -1;
    }
    s->avail_connections--;
    return 0;
}

void qemu_chr_fe_claim_no_fail(CharDriverState *s)
{
    if (qemu_chr_fe_claim(s) != 0) {
        fprintf(stderr, "%s: error chardev \"%s\" already used\n",
                __func__, s->label);
        exit(1);
    }
}

void qemu_chr_fe_release(CharDriverState *s)
{
    s->avail_connections++;
}

CharDriverState *qemu_chr_alloc(ChardevCommon *backend, Error **errp)
{
    CharDriverState *chr = g_malloc0(sizeof(CharDriverState));
    return chr;
}

void qemu_chr_be_event(CharDriverState *s, int event)
{
    /* Keep track if the char device is open */
    switch (event) {
        case CHR_EVENT_OPENED:
            s->be_open = 1;
            break;
        case CHR_EVENT_CLOSED:
            s->be_open = 0;
            break;
    }

    if (!s->chr_event)
        return;
    s->chr_event(s->handler_opaque, event);
}

void qemu_chr_be_generic_open(CharDriverState *s)
{
    qemu_chr_be_event(s, CHR_EVENT_OPENED);
}

int qemu_chr_fe_write(CharDriverState *s, const uint8_t *buf, int len)
{
	return s->chr_write(s, buf, len);
}

int qemu_chr_fe_write_all(CharDriverState *s, const uint8_t *buf, int len)
{
	return s->chr_write(s, buf, len);
}

int qemu_chr_fe_read_all(CharDriverState *s, uint8_t *buf, int len)
{
	return s->chr_sync_read(s, buf, len);
}

int qemu_chr_fe_ioctl(CharDriverState *s, int cmd, void *arg)
{
    int res;
    if (!s->chr_ioctl || s->replay) {
        res = -ENOTSUP;
    } else {
        res = s->chr_ioctl(s, cmd, arg);
    }

    return res;
}

int qemu_chr_be_can_write(CharDriverState *s)
{
    if (!s->chr_can_read)
        return 0;
    return s->chr_can_read(s->handler_opaque);
}

void qemu_chr_be_write_impl(CharDriverState *s, uint8_t *buf, int len)
{
    if (s->chr_read) {
        s->chr_read(s->handler_opaque, buf, len);
    }
}

void qemu_chr_be_write(CharDriverState *s, uint8_t *buf, int len)
{
	qemu_chr_be_write_impl(s, buf, len);
}

int qemu_chr_fe_get_msgfd(CharDriverState *s)
{
    int fd;
    int res = (qemu_chr_fe_get_msgfds(s, &fd, 1) == 1) ? fd : -1;
    return res;
}

int qemu_chr_fe_get_msgfds(CharDriverState *s, int *fds, int len)
{
    return s->get_msgfds ? s->get_msgfds(s, fds, len) : -1;
}

int qemu_chr_fe_set_msgfds(CharDriverState *s, int *fds, int num)
{
    return s->set_msgfds ? s->set_msgfds(s, fds, num) : -1;
}

int qemu_chr_add_client(CharDriverState *s, int fd)
{
    return s->chr_add_client ? s->chr_add_client(s, fd) : -1;
}

void qemu_chr_accept_input(CharDriverState *s)
{
    if (s->chr_accept_input)
        s->chr_accept_input(s);
//    qemu_notify_event();
}

static int null_chr_write(CharDriverState *chr, const uint8_t *buf, int len)
{
    return len;
}

static CharDriverState *qemu_chr_open_null(const char *id,
                                           ChardevBackend *backend,
                                           ChardevReturn *ret,
                                           Error **errp)
{
    CharDriverState *chr;
    ChardevCommon *common = backend->u.null.data;

    chr = qemu_chr_alloc(common, errp);
    if (!chr) {
        return NULL;
    }
    chr->chr_write = null_chr_write;
    chr->explicit_be_open = true;
    return chr;
}

