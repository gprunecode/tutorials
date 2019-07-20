#include <panel.h>

int main()
{ WINDOW *my_wins[3];
  PANEL  *my_panels[3];
  int lines = 10, cols = 40, y = 2, x = 4, i;

  initscr();
  cbreak();
  noecho();

  /* Creacion de ventanas para los paneles */
  my_wins[0] = newwin(lines, cols, y, x);
  my_wins[1] = newwin(lines, cols, y + 1, x + 5);
  my_wins[2] = newwin(lines, cols, y + 2, x + 10);

  /*
   *    * Creacion de bordes alrededor de las ventanas para ver el efecto
   *       * de los paneles
   *          */
  for(i = 0; i < 3; ++i)
    box(my_wins[i], 0, 0);

  /* Unir un panel a cada ventana */      /* ordenar de abajo hacia arriba  */
  my_panels[0] = new_panel(my_wins[0]);   /* agregar 0, orden: stdscr-0     */
  my_panels[1] = new_panel(my_wins[1]);   /* agregar 1, orden: stdscr-0-1   */
  my_panels[2] = new_panel(my_wins[2]);   /* agregar 2, orden: stdscr-0-1-2 */

  /* Actualizar en orden de apilamiento. El 2nd panel estara en la cima     */
  update_panels();

  /* Mostrar en la pantalla */
  doupdate();

  getch();
  endwin();
}
