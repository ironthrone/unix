//
// Created by ironthrone on 2019/5/31.
//

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void do_ls(char []);
void dostat(char *filename);
void show_stat_info(char *filename, struct stat *info);
void mode_to_letters(int mode, char str[]);
char *uid_to_name(uid_t uid);
char *gid_to_name(gid_t gid);


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
            dostat(dirent_ptr->d_name);
        }
        closedir(dir_ptr);
    }
}

void dostat(char *filename) {
    struct stat buf;

    if (stat(filename, &buf) == 0) {
        show_stat_info(filename, &buf);
    } else {
        perror("can not read file");
        exit(1);
    }
}


void show_stat_info(char *filename, struct stat *info) {
//    char *uid_to_name(),*ctime(),*gid_to_name(),*filemode();
//    void mode_to_letters();
    char modestr[11];
    mode_to_letters(info->st_mode, modestr);

    printf("%s ", modestr);
    printf("%4ld ", info->st_nlink);
    printf("%-15s ", uid_to_name(info->st_uid));
    printf("%-15s ", gid_to_name(info->st_gid));
    printf("%8ld ", info->st_size);
    printf("%.12s ", 4 + ctime(&info->st_mtime));
    printf("%s\n", filename);
}

void mode_to_letters(int mode, char str[]) {
    strcpy(str, "----------");

    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (S_IRUSR & mode) str[1] = 'r';
    if (S_IWUSR & mode) str[2] = 'w';
    if (S_IXUSR & mode) str[3] = 'x';

    if (S_IRGRP & mode) str[4] = 'r';
    if (S_IWGRP & mode) str[5] = 'w';
    if (S_IXGRP & mode) str[6] = 'x';

    if (S_IROTH & mode) str[7] = 'r';
    if (S_IWOTH & mode) str[8] = 'w';
    if (S_IXOTH & mode) str[9] = 'x';
}


char *uid_to_name(uid_t uid) {
    struct passwd *pwd = getpwuid(uid);
    static char name[10];
    if (pwd != NULL) {
        return pwd->pw_name;

    } else {
        sprintf(name, "%d", uid);
        return name;
    }
}



char *gid_to_name(gid_t gid) {
    struct group *grp = getgrgid(gid);
    static char name[10];
    if (grp != NULL) {
        return getgrgid(gid)->gr_name;

    } else {
        sprintf(name, "%d", gid);
        return name;
    }
}