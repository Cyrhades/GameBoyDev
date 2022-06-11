void clear_screen(void) {
    UINT8 x;
    UINT8 y = 18;
    while (y) {
        y -= 1;
        x = 20;
        while (x) {
            x -= 1;
            gotoxy(x, y);
            setchar(' ');
        }
    }
}


/* Fonction pour printer le texte */
void credits() {
    gotoxy(4, 4);
    printf("Hello world!");
    gotoxy(0, 17);
    printf("Created By Cyrhades");
}
