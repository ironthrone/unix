//
// Created by ironthrone on 2019/5/28.
//
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void show_info(struct utmp *);

void show_time(long);

int main() {
    struct utmp current_record;
    int utmpfd;
    size_t reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }
    while (read(utmpfd, &current_record, reclen) == reclen) {
        if (current_record.ut_type != USER_PROCESS) {
            continue;
        }
        show_info(&current_record);
    }
    close(utmpfd);
    return 0;
}

void show_info(struct utmp *utbufp) {
    printf("%8.8s", utbufp->ut_name);
    printf(" ");
    printf("%8d", utbufp->ut_pid);
    printf(" ");
    printf("%8.8s", utbufp->ut_line);
    printf(" ");
    printf("%15s", utbufp->ut_id);
    printf(" ");
    show_time(utbufp->ut_tv.tv_sec);
#ifdef SHOWHOST
    printf("{%s}",utbufp->ut_host);
#endif
    printf("\n");
}

void show_time(long time) {
    char *cp;
    cp = ctime(&time);
    printf("%16.16s", cp + 4);
}