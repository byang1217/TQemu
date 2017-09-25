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
#include "qapi/error.h"
#include "qemu-common.h"
#include "qemu/main-loop.h"
#include "qemu/atomic.h"

/***********************************************************/
/* bottom halves (can be seen as timers which expire ASAP) */

struct QEMUBH {
    QEMUBHFunc *cb;
    void *opaque;
    QEMUBH *next;
    bool scheduled;
    bool idle;
    bool deleted;
};

static struct QEMUBH *first_bh;

QEMUBH *qemu_bh_new(QEMUBHFunc *cb, void *opaque)
{
    QEMUBH *bh;
    bh = g_new(QEMUBH, 1);
    *bh = (QEMUBH){
        .cb = cb,
        .opaque = opaque,
    };
    bh->next = first_bh;
    first_bh = bh;
    return bh;
}

void qemu_bh_cancel(QEMUBH *bh)
{
    bh->scheduled = 0;
}

void qemu_bh_delete(QEMUBH *bh)
{
    bh->scheduled = 0;
    bh->deleted = 1;
}

void qemu_bh_schedule_idle(QEMUBH *bh)
{
    bh->idle = 1;
    atomic_mb_set(&bh->scheduled, 1);
}

void qemu_bh_schedule(QEMUBH *bh)
{
	bh->idle = 0;
	atomic_mb_set(&bh->scheduled, 1);
}

void replay_bh_schedule_event(QEMUBH *bh)
{
	qemu_bh_schedule(bh);
}

/* Multiple occurrences of aio_bh_poll cannot be called concurrently */
int qemu_bh_poll(void)
{
	QEMUBH *bh, **bhp, *next;
	int ret;

	ret = 0;
	for (bh = first_bh; bh; bh = next) {
		next = bh->next;
		if (!bh->deleted && atomic_xchg(&bh->scheduled, 0)) {
			if (!bh->idle) {
				ret = 1;
			}
			bh->idle = 0;
			bh->cb(bh->opaque);
		}
	}

	/* remove deleted bhs */
	bhp = &first_bh;
	while (*bhp) {
		bh = *bhp;
		if (bh->deleted) {
			*bhp = bh->next;
			g_free(bh);
		} else {
			bhp = &bh->next;
		}
	}

	return ret;
}
