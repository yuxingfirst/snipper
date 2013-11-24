#include "queue.h"
#include <stdio.h>

STAILQ_HEAD(mdhr, stuff);

struct stuff {
    int a;
    STAILQ_ENTRY(stuff) next; 
};

int main(void) {
    struct mdhr t_queue; 
    STAILQ_INIT(&t_queue);

    struct stuff s1;
    s1.a = 1;
    STAILQ_INSERT_HEAD(&t_queue, &s1, next);

    struct stuff s2;
    s2.a = 2;
    STAILQ_INSERT_HEAD(&t_queue, &s2, next);

    struct stuff s3;
    s3.a = 3;
    STAILQ_INSERT_HEAD(&t_queue, &s3, next);
    
    struct stuff *pos;
    STAILQ_FOREACH(pos, &t_queue, next) {
        printf("%d\n", pos->a); 
    }
    printf("------------------");
    struct stuff s4;
    s4.a = 4;

    STAILQ_INSERT_AFTER(&t_queue, &s2, &s4, next);

    STAILQ_FOREACH(pos, &t_queue, next) {
        printf("%d\n", pos->a); 
    }

    return 0;
}
