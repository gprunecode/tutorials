#include <ncurses.h>

int main(void)
{
  int ch;

  initscr();                    /* Inicia el modo curses */
  raw();                        /* Desactiva buffer de linea */
  noecho();                     /* Sin echo() al hacer getch */

  printw("Pulse cualquier caracter para verlo remarcado\n");
  ch = getch();                 /* Si no ha llamado a raw() tenemos que
                                 * pulsar enter antes que llegue al programa */
  if (ch == KEY_F(1))
    printw("F1 Key pressed");   /* Sin habilitar keypad esto no llegara a nosotros */
                                /* Sin noecho() algunos caracteres feos de escape podrian
                                 * ser impresos */
  else {
    printw("La tecla pulsada es ");
    attron(A_BOLD);
    printw("%c", ch);
    attroff(A_BOLD);
  }
  refresh();                    /* Imprime en la pantalla real */
  getch();                      /* Espera entrada de usuario */
  endwin();                     /* Termina modo curses */

  return 0;
}
