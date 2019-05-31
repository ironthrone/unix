//
// Created by ironthrone on 2019/5/29.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

void oops(char *, char *);

void oops(char *s, char *f) {
    fprintf(stderr, "error: %s", s);
    perror(f);
    exit(1);
}


int main(int ac, char *av[]) {
    if (ac < 3) {
        fprintf(stderr, "argument count is not enough\n");
        exit(1);
    }
    int sfd;
    int tfd;
    ssize_t read_c;
    size_t buffer_size = 2048;
    char buffer[buffer_size];

    if ((sfd = open(av[1], O_RDONLY)) == -1) {
        oops("Can not open", av[1]);
    }
    if ((tfd = creat(av[2], 644)) == -1) {
        oops("Can not open", av[2]);
    }

    while ((read_c = read(sfd, &buffer, buffer_size)) > 0) {
        if (write(tfd, &buffer, read_c) != read_c) {
            oops("Error happens when write ", av[2]);
        }
    }
    if (read_c == -1) {
        oops("Error occur when read", av[1]);
    }

    if (close(sfd) == -1 || close(tfd) == -1) {
        oops("Error occur when close", "");
    }
    return 0;

}

