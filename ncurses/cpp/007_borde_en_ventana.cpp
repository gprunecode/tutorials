#include <ncurses.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);

int main(int argc, const char *argv[])
{
  WINDOW *my_win;
  int startx, starty, width, height;
  int ch;

  initscr();          /* Inicia el modo curses */
  cbreak();           /* Desactivar el buffer de linea
                       * pasarme todo el control a mi */
  keypad(stdscr, TRUE); /* Para habilitar F1 */

  height = 3;
  width = 10;
  starty = (LINES - height) / 2;    /* Calculo para colorcar al centro */
  startx = (COLS - width) / 2;      /* de la ventana */
  printw("Pulse F1 para salir");
  refresh();
  my_win = create_newwin(height, width, starty, startx);

  while ((ch = getch()) != KEY_F(1)) {
    switch (ch) {
      case KEY_LEFT:
        destroy_win(my_win);
        my_win = create_newwin(height, width, starty, --startx);
        break;
      case KEY_RIGHT:
        destroy_win(my_win);
        my_win = create_newwin(height, width, starty, ++startx);
        break;
      case KEY_UP:
        destroy_win(my_win);
        my_win = create_newwin(height, width, --starty, startx);
        break;
      case KEY_DOWN:
        destroy_win(my_win);
        my_win = create_newwin(height, width, ++starty, startx);
        break;
    }
  }

  endwin();         /* Fin del modo curses */

  return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
  WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);
  box(local_win, 0, 0);           /* 0, 0 pone los caracteres por defecto
                                   * para las lineas vertical y horizontal */
  wrefresh(local_win);            /* Muestra la caja */

  return local_win;
}

void destroy_win(WINDOW *local_win) {
  /* box(local_win, ' ', ' ');    : Esto no produce el resultado deseado
   * de borrar la ventana. Deja las cuatro esquinas como un feo residuo de la ventana.
   */
  wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  /* Los parametros tomados son
   * 1. win: la ventana sobre la que operar
   * 2. ls: caracter a utilizar para el lado izquierdo de la ventada
   * 3. rs: caracter a utilizar para el lado derecho de la ventana
   * 4. ts: caracter a utilizar para el lado superior de la ventana
   * 5. bs: caracter a utilizar para el lado inferior de la ventana
   * 6. tl: caracter a utilizar para la esquina superior izquierda de la ventana
   * 7. tr: caracter a utilizar para la esquina superior derecha de la ventana
   * 8. bl: caracter a utilizar para la esquina inferior izquierda de la ventana
   * 9. br: caracter a utilizar para la esquina inferior derecha de la ventana
   */
  wrefresh(local_win);
  delwin(local_win);
}
