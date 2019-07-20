#include <ncurses.h>
#include <string.h>

int main(void)
{
  char mesg[] = "Solo una cadena"; /* Mensaje que aparecera en la pantalla */
  int row, col;                    /* Para guardar el numero de filas y 
                                    * el numero de columnas de la pantalla */
  initscr();                       /* Inicia el modo curses */
  getmaxyx(stdscr, row, col);      /* Obtiene el numero de filas y columnas */
  mvprintw(row/2, (col-strlen(mesg))/2, "%s", mesg);
                                   /* imprime el mensaje en el centro de la pantalla */
  mvprintw(row-2,0, "Esta pantalla tiene %d filas y %d columnas\n", row, col);
  printw("Prueba redimencionar la ventana (si es posible) y corre el programa nuevamente");
  refresh();
  getch();
  endwin();

  return 0;
}
