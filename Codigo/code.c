#include <stdlib.h>
char *foo(char *);

// compile by running gcc code.c -o executableName
// execute by ./executableName

main() {
    char *a = NULL;
    char *b = NULL;
    a = foo("Hi there, Chris");
    b = foo("Goodbye");
    printf("From main: %s %s\n", a, b);
}


// Ya que aqui foo me devuelve un pointer, pues se tiene q en el heap
//  y por ende cuando termina el execution stack no se pierde la informacion.


char *foo(char *p){
    char *q = (char *)malloc(strlen(p)+1);
    strcpy(q, p);
    printf("From q: the string is %s\n", q);
    return q;
}