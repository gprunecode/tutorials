#include <ncurses.h>
#include <stdlib.h>

int main()
{
  initscr();                      /* Iniciar el modo curses                 */
  printw("Hola mundo !!!\n");     /* Imprime Hola mundo                     */
  refresh();                      /* Imprimir en la pantalla real           */
  getch();                        /* Esperar                                */
  def_prog_mode();                /* Guardar los modos tty                  */
  endwin();                       /* Finalizar curnes temporalmente         */
  system("/bin/sh");              /* Realizar cualquier cosa en modo cooked */
  reset_prog_mode();              /* Regresar al modo tty previo            */
                                  /* almacenado por def_prog_mode()         */
  refresh();                      /* refresh() restaura los contenidos      */
                                  /* en pantalla                            */
  printw("Otra Cadena\n");        /* De nuevo utilizar curses al maximo     */
  refresh();                      /* de sus capacidades                     */
  getch();                        /* Esperar                                */
  endwin();                       /* Finalizar el modo curses               */

  return 0;

}
