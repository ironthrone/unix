#include <iostream>
#include <time.h>
int  fun() {
    std::cout << "you are right" << std::endl;
}

int main() {
//    std::cout << "Hello, World!" << std::endl;
//    int i = 1, *p1;
//    int *p = &i;
//    const int &r = 00;
////    int &r = 00;
//
//    const int *const p3 = &i;
//    const int ci = 10;
//
//    typedef char *pstring;
//    const pstring cstr = "";
//    const char *sp;
//    char *const pp = "";
//
//
//    int it = 42, *p10 = &i;
//    decltype(*p10) d = it;
//    //函数指针
//    int (*funPtr)();
//    funPtr = fun;
//    funPtr();
//    return 0;


    time_t t = time(nullptr);
    printf("%12.16s",ctime(&t)+4);
    return 0;
}


