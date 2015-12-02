#include "font.h"
#include <stdio.h>
int main(void)
{
    int x,y;
    unsigned short *_bitmap = bitmap + 12 * 'C';
    for(y = 0;y < 12;y++){
        for(x = 0;x < 12;x++){
            printf("%c",(_bitmap[y] >> x & 1) ? '-' : ' ');
        }
        printf("\n");
    }
}
