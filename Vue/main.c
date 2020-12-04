#include "graphics.h"

void deplacement(POINT* p1,POINT* p2,COULEUR clr){
    POINT Pdep = get_arrow();
    draw_fill_rectangle((*p1),(*p2),black);
    (*p1).x += Pdep.x*10; (*p2).x += Pdep.x*10;
    (*p1).y += Pdep.y*10; (*p2).y += Pdep.y*10;
    draw_fill_rectangle((*p1),(*p2),clr);
}

int main(void) {
    
    init_graphics();
    
    POINT carre1,carre2;
    int hauteur,largeur;
    hauteur = largeur = 0;
    carre1.x = carre1.y = 20;
    carre2.x = carre2.y = 40;
    draw_rectangle(carre1,carre2,white);
    write_text("wesh");

    for (int i = 0; i < 10; i++)
    {
        deplacement(&carre1,&carre2,red);
        taille(&hauteur,&largeur);
        printf("hauteur: %d\tlargeur: %d\n",hauteur,largeur);
    }
    
    wait_escape();

    return 0;
}
