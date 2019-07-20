#include <ncurses.h>

int main(int argc, const char *argv[])
{
  initscr();                  /* Inicia el modo curses */
  start_color();              /* Inicia la funcionalidad de color */

  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  printw("Una gran cadena en la que no importa que escribir ");
  mvchgat(0, 0, -1, A_BLINK, 1, NULL);
  /*
   * Los primeros dos parametros especifican la posicion para empezar
   * El tercer parametro es el numero de caracteres a actualizar, -1
   * quiere decir hasta fin de linea
   * El cuarto parametro es el attributo para el caracter
   * El quinto parametro es el indice de color. Este indice se obtiene
   * con init_pair() utilice 0 si no quiere ningun color
   * El sexto es para siempre NULL
   */
  refresh();
  getch();
  endwin();                   /* Fin del modo curses */

  return 0;
}
