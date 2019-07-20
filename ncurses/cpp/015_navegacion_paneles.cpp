#include <panel.h>
#include <string.h>

#define NLINES 10
#define NCOLS 40

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

int main()
{ WINDOW *my_wins[3];
  PANEL  *my_panels[3];
  PANEL  *top;
  int ch;

  /* Inicializa curses */
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Inicializa todos los colores */
  init_pair(1, COLOR_RED,   COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE,  COLOR_BLACK);
  init_pair(4, COLOR_CYAN,  COLOR_BLACK);

  init_wins(my_wins, 3);

  /* Unir un panel a cada ventana */      /* Ordenar de abajo hacia arriba  */
  my_panels[0] = new_panel(my_wins[0]);   /* Agregar 0, orden: stdscr-0     */
  my_panels[1] = new_panel(my_wins[1]);   /* Agregar 1, orden: stdscr-0-1   */
  my_panels[2] = new_panel(my_wins[2]);   /* Agregar 2, orden: stdscr-0-1-2 */

  /* Crear el puntero de usuario al siguiente panel */
  set_panel_userptr(my_panels[0], my_panels[1]);
  set_panel_userptr(my_panels[1], my_panels[2]);
  set_panel_userptr(my_panels[2], my_panels[0]);

  /* Actualizar el orden de apilamiento. El 2nd panel estara en la parte superior */
  update_panels();

  /* Mostrar en la pantalla */
  attron(COLOR_PAIR(4));
  mvprintw(LINES - 2, 0, "Utilice tab para navegar a traves de las ventanas (F1 para Salir)");
  attroff(COLOR_PAIR(4));
  doupdate();

  top = my_panels[2];
  while((ch = getch()) != KEY_F(1))
  {   switch(ch)
    {   case 9:
      top = (PANEL *)panel_userptr(top);
      top_panel(top);
      break;
    }
    update_panels();
    doupdate();
  }
  endwin();
  return 0;
}

/* Coloca todas las ventanas */
void init_wins(WINDOW **wins, int n)
{ int x, y, i;
  char label[80];

  y = 2;
  x = 10;
  for(i = 0; i < n; ++i)
  { wins[i] = newwin(NLINES, NCOLS, y, x);
    sprintf(label, "Ventana Numero %d", i + 1);
    win_show(wins[i], label, i + 1);
    y += 3;
    x += 7;
  }
}

/* Muestra la ventana con un borde y una etiqueta */
void win_show(WINDOW *win, char *label, int label_color)
{ int startx, starty, height, width;

  getbegyx(win, starty, startx);
  getmaxyx(win, height, width);

  box(win, 0, 0);
  mvwaddch(win, 2, 0, ACS_LTEE);
  mvwhline(win, 2, 1, ACS_HLINE, width - 2);
  mvwaddch(win, 2, width - 1, ACS_RTEE);

  print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{ int length, x, y;
  float temp;

  if(win == NULL)
    win = stdscr;
  getyx(win, y, x);
  if(startx != 0)
    x = startx;
  if(starty != 0)
    y = starty;
  if(width == 0)
    width = 80;

  length = strlen(string);
  temp = (width - length)/ 2;
  x = startx + (int)temp;
  wattron(win, color);
  mvwprintw(win, y, x, "%s", string);
  wattroff(win, color);
  refresh();
}
