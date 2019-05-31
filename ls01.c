//
// Created by ironthrone on 2019/5/31.
//

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

void do_ls(char []);

int main(int ac, char *av[]) {
    if (ac == 1) {
        do_ls(".");
    } else {
        while (--ac) {
            printf("%s:\n", *++av);
            do_ls(*av);
        }
    }
}


void do_ls(char dirname[]) {
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "ls1:cannot open %s\n", dirname);
    } else {
        while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
            printf("%s\n", dirent_ptr->d_name);
        }
        closedir(dir_ptr);
    }
}