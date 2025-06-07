//
// Created by Bartek on 07.06.2025.
//

#include "utils.h"
#include <stdio.h>

void hello_world() {
    struct util hello;
    hello.a = "from";
    hello.b = "util";

    printf("Hello world, %s %s", hello.a, hello.b);
}