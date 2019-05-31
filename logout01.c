//
// Created by ironthrone on 2019/5/30.
//

#include <stdio.h>
#include <unistd.h>
#include <utmp.h>
#include <stdlib.h>
#include <fcntl.h>
#include <memory.h>
#include <time.h>
//#import "utmplib.c"


int main() {

}

int logout_tty(char *line) {
    int fd;
    struct utmp cur;
    int len = sizeof(struct utmp);
    int recval = -1;

    if ((fd = fopen(UTMP_FILE, O_RDONLY)) == -1) {
        perror("cannot to open");
        exit(1);
    }

    while (read(fd, &cur, len) == len) {
        if (strncmp(cur.ut_line, line, sizeof(cur.ut_line)) == 0) {
            cur.ut_type = DEAD_PROCESS;
            if (time(&cur.ut_time) != -1) {
                if (lseek(fd, -len, SEEK_CUR) != -1) {
                    if (write(fd, &cur, len) == len) {
                        recval = 0;
                    }
                }
            }
            break;
        }
    }

    if (close(fd) == -1) {
        recval = 1;
    }
    return recval;
}