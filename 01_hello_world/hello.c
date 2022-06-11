#include <stdio.h>
#include <gb/gb.h>          // utiliser pour la gestion des boutons
#include <gbdk/console.h>  // utiliser pour la gestion des boutons

#include "cyrhades.c"


void main(void) {
    // 1. On place le texte au centre de l'écran
    gotoxy(4, 8);
    printf("Press START!");
    // 2. On attend que l'utilisateur clique sur START
    waitpad(J_START);
    // 3. On efface l'écran (donc le Press START)
    clear_screen();

    credits();
}