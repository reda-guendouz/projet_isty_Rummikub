#include "Vue/graphics2.h"
#include "Modele/modele.h"

int main(int argc, char const *argv[])
{
    init_pioche();
    init_joueurs(2);
    init_graphics();

 
    POINT carre1,carre2,l1,l2;
    carre1.x = carre1.y = 20;
    carre2.x = carre2.y = 40;
    l1.x = 75; l2.x = 0;
    l1.y = 75; l2.y = 0;
    draw_fill_rectangle(carre1,carre2,blanc);
    int i,j;
    for(i=0;i<8;i++){
        for(j=0;j<30;j++){
            load_img("assets/Tuiles/O/13.png",l1,l2);l1.x +=50;
        }
        l1.x=75;
        l1.y+=75;
    }
    affiche_all();


    wait_escape();
    return 0;
}
