#include "graphics2.h"

int main(void) {
    
    init_graphics();
    
    POINT carre1,carre2;
    carre1.x = carre1.y = 20;
    carre2.x = carre2.y = 40;
    draw_rectangle(carre1,carre2,white);
   
    wait_escape();
    return 0;
}
