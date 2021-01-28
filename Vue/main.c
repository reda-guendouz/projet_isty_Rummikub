#include "graphics2.h"
/*
void hexatorgb(Uint32 hexa,int *r, int *g, int *b){
    *r = ((hexa >> 16) & 0xFF);
	*g = ((hexa >> 8) & 0xFF);
	*b = ((hexa) & 0xFF) ;
}
*/
int main(void) {
    
    init_graphics();
    
    POINT carre1,carre2,l1,l2;
    carre1.x = carre1.y = 20;
    carre2.x = carre2.y = 40;
    l1.x = 100; l2.x = 150;
    l1.y = l2.y = 200;
    draw_fill_rectangle(carre1,carre2,blanc);
    //draw_line(l1,l2,rouge);

    /*
    /// test fonction hexatorgb
    int rr,gg,bb;
    int *a=&rr;
    int *b=&gg;
    int *c=&bb;

    COULEUR clr = couleur_RGB(152,0,255);
    hexatorgb(clr,a,b,c);
    printf("rr: (%d) gg : (%d) bb:(%d)\n",rr,gg,bb);
    /// fin test
    */
 
    wait_escape();
    return 0;
}
