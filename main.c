#include <stdio.h>
// #include <util.h>
#include <logger.h>
#include <unistd.h>

void test_print()
{
    log("booooom");
}

int main()
{
    log("test");
    test_print();
    test_print();
    sleep(4);
    test_print();
    log("test");
    log("test");
    log("test");
    log("test");
    log("test");
    log("test");
    log("test");
}