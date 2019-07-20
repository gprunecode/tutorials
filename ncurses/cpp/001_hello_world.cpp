#include <ncurses.h>

int main(void)
{
  initscr();                  /* Inicia el modo curses */
  printw("Hello World!!!");   /* Imprime Hello World */
  refresh();                  /* Imprimirlo en la pantalla real */
  getch();                    /* Esperar entrada de usuario */
  endwin();                   /* Terminar el modo curses */

  return 0;
}
