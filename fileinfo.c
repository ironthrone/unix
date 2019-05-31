//
// Created by ironthrone on 2019/5/31.
//

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void show_stat_info(char *, struct stat *);

int main(int ac, char *av[]) {
//    if (ac < 2) {
//        printf("need a file provided");
//        exit(1);
//    }
//
//    struct stat result_buf;
//    struct stat *buf_ptr;
//    printf("%s\n", *(av + 1));
//    printf("%s\n", *(av + 1));
//    printf("%s\n", *(av + 1));
//
//    if (stat(av[1], buf_ptr) == 0) {
//
//    }
//
//    if (stat(av[1], &result_buf) == 0) {
//        printf("%10o", result_buf.st_mode);
//        printf("%10d", result_buf.st_uid);
//        printf("%10d", result_buf.st_gid);
//        printf("%10ld", result_buf.st_size);
//        printf("%15ld", result_buf.st_mtim.tv_sec);
//        printf("\n");
//        return 0;
//    } else {
//        perror("can not read file info");
//        exit(1);
//    }
//    return 1;
    struct stat info;
    if (ac > 1) {
        if (stat(av[1], &info) != -1) {
            show_stat_info(av[1], &info);
            return 0;
        } else {
            perror(av[1]);
        }
    }
    return 1;
}

void show_stat_info(char *filename, struct stat *info) {
    printf("mode:%o\n", info->st_mode);
    printf("links:%ld\n", info->st_nlink);
    printf("user:%d\n", info->st_uid);
    printf("group:%d\n", info->st_gid);
    printf("size:%ld\n", info->st_size);
    printf("modtime:%ld\n", info->st_mtim.tv_sec);
    printf("name:%s\n", filename);
}