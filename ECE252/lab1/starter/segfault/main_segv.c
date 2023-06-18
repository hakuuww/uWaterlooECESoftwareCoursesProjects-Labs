/**
 * @brief: To demonstrate segmentation fault 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct buf {
    size_t size;  /* buffer size */
    char *data ;  /* data */
};

/* To model a point on 2D terminal screen */
struct point
{
    int x;
    int y;
};


int main(void)
{
    struct buf *p, *q;
    struct point pt={1,2};
 
    p = (struct buf *)malloc(sizeof(struct buf));
    q = p;

    p->data = (char *)&pt ;
    p->size = sizeof(struct point); 

    printf("p->x = %d, p->y =%d\n", ((struct point*)(p->data))->x, ((struct point *)(p->data))->y);
    //type casting

    /* remove pointe p */
    p->data = NULL;
    p->size = 0;
    // free(p);

    printf("q->x = %d, q->y =%d\n", ((struct point*)(q->data))->x, ((struct point *)(q->data))->y);
    //Segmentation fault occurs in this line because q points to the same address as p,
    //and in p, data, the member of the original struct object p is now pointing to a null pointer,
    //so calling q->data->x would mean trying to access a null pointer   

    return(0);
}
