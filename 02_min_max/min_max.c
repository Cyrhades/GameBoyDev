#include <stdio.h>
#include <stdlib.h>
#include <gb/gb.h>
#include <gbdk/console.h>  
#include <rand.h>

void clear_line(UINT8 y)
{
    UINT8 x;
    x = 20;
    while (x) {
        x -= 1;
        gotoxy(x, y);
        setchar(' ');
    }
}

void clear_screen(void) {
    UINT8 y = 18;
    while (y) {
        y -= 1;
       clear_line(y);
    }
}

void startGame() {
    // nombre random entre 1 et 100
    UINT8 posCurseur = 1;
    UINT8 key;    
    UINT8 chiffre1 = 0;
    UINT8 chiffre2 = 0;
    UINT8 chiffre3 = 1;
    uint16_t seed = LY_REG;
    seed |= (uint16_t)DIV_REG << 8;
    initrand(seed);
    UINT8 nombre1 = rand()%9;
    UINT8 nombre2 = rand()%9;
    UINT8 nombre3 = rand()%9;
    UINT16 nombre = (nombre1*100)+(nombre2*10)+nombre3;

    // afficher le texte
    gotoxy(1, 2);
    printf("Trouvez le nombre\n\t\tentre 1 et 999");

    gotoxy(7, 8);
    printf("0 0 1");

    gotoxy(7, 9);
    printf("_ _ _");
    gotoxy(7, 10);
    printf(".");

    gotoxy(0, 17);
    printf("Created By Cyrhades");

    // Pour débbugage
    //gotoxy(0, 15); printf("Le nombre est : %u", nombre);
    while (1)
    {    
        key = waitpad(J_LEFT | J_RIGHT | J_UP | J_DOWN | J_A | J_SELECT);
        if(key) {  
            if(key & J_SELECT) {
                reset();
            }
            else if(key & J_A) {
                gotoxy(0, 15);
                printf("                  ");
                if((chiffre1*100)+(chiffre2*10)+chiffre3 == nombre) {
                    gotoxy(0, 5);
                    printf("    VICTOIRE !!!    ");
                } else if((chiffre1*100)+(chiffre2*10)+chiffre3 > nombre) {
                    gotoxy(0, 15);
                    printf("Plus petit      ");
                } else {
                    gotoxy(0, 15);
                    printf("Plus grand     ");
                }
            }
            else if (key & J_LEFT && posCurseur > 1) {
                posCurseur -= 1;
            } 
            else if (key & J_RIGHT && posCurseur < 3) {
                posCurseur += 1;
            }
            else if (key & J_UP) {
                switch(posCurseur)
                {
                    case 1 : 
                        gotoxy(7, 8); 
                        chiffre1 = chiffre1==9 ? 0 : chiffre1+1;
                        printf("%u", chiffre1 ); 
                        break;
                    case 2 : 
                        gotoxy(9, 8);  
                        chiffre2 = chiffre2==9 ? 0 : chiffre2+1;
                        printf("%u", chiffre2); 
                        break;
                    case 3 : 
                        gotoxy(11, 8); 
                        chiffre3 = chiffre3==9 ? 0 : chiffre3+1;
                        printf("%u", chiffre3); 
                        break;
                }
            } 
            else if (key & J_DOWN ) {
                switch(posCurseur)
                {
                    case 1 : 
                        gotoxy(7, 8); 
                        chiffre1 = chiffre1==0 ? 9 : chiffre1-1;
                        printf("%u", chiffre1); 
                        break;
                    case 2 : 
                        gotoxy(9, 8);  
                        chiffre2 = chiffre2==0 ? 9 : chiffre2-1;
                        printf("%u", chiffre2); 
                        break;
                    case 3 : 
                        gotoxy(11, 8); 
                        chiffre3 = chiffre3==0 ? 9 : chiffre3-1;
                        printf("%u", chiffre3);  
                        break;
                }
            }
            gotoxy(7, 10); setchar(' '); 
            gotoxy(9, 10); setchar(' ');
            gotoxy(11, 10); setchar(' ');
            switch(posCurseur)
            {
                case 1 : gotoxy(7, 10);  printf("."); break;
                case 2 : gotoxy(9, 10);  printf("."); break;
                case 3 : gotoxy(11, 10); printf("."); break;
            }
            delay(300);
        }
    }
}

void main(void) {
    // 1. On place le texte au centre de l'écran
    gotoxy(4, 8);
    printf("Press START!");
    // 2. On attend que l'utilisateur clique sur START
    waitpad(J_START);
    // 3. On efface l'écran (donc le Press START)
    clear_screen();

    startGame();
}