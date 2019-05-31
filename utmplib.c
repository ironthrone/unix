//
// Created by ironthrone on 2019/5/29.
//

//#ifndef UTMP_LIB
//#define UTMP_LIB

#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

#define NULLUT ((struct utmp*)NULL)
#define NRECS 16
#define UTSIZE (sizeof(struct utmp))

static char utmpbuf[NRECS * UTSIZE];
static int fd_utmp = -1;
static int num_recs;
static int cur_rec;

//struct utmp *utmp_next();

int utmp_open(char *f) {
    fd_utmp = open(f, O_RDONLY);
    num_recs = 0;
    return fd_utmp;
}

void utmp_close() {
    if (fd_utmp != -1) {
        close(fd_utmp);
    }
}


int utmp_reload() {
    int amt_read;
    amt_read = read(fd_utmp, utmpbuf, NRECS * UTSIZE);
    num_recs = amt_read / UTSIZE;
    cur_rec = 0;
    return num_recs;
}


struct utmp *utmp_next() {
    struct utmp *recp;
    if (fd_utmp == -1) {
        return NULLUT;
    }
    if (cur_rec == num_recs && utmp_reload() == 0) {
        return NULLUT;
    }
    recp = (struct utmp *) &utmpbuf[cur_rec * UTSIZE];
    cur_rec++;
    return recp;
}

//#endif



