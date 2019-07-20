#include <ncurses.h>
#include <string.h>

int main(void)
{
  char mesg[] = "Ingrese una cadena: ";   /* Mensaje a mostrar en pantalla */
  char str[80];
  int row, col;                           /* Para almacenar el numero de filas y
                                           * el numero de columnas de pantalla */
  initscr();                              /* inicia el modo curses */
  getmaxyx(stdscr, row, col);             /* obtiene el numero de filas y columnas */
  mvprintw(row/2, (col - strlen(mesg))/2, "%s", str);
  getch();
  endwin();

  return 0;
}
