#include <stdlib.h>
char *foo(char *);

main() {
    char *a = NULL;
    char *b = NULL;
    a = foo("Hi there, Chris");
    b = foo("Goodbye");
    printf("From main: %s %s\n", a, b);
}

char *foo(char *p){
    char *q = (char *)malloc(strlen(p)+1);
    strcpy(q, p);
    printf("From q: the string is %s\n", q);
    return q;
}