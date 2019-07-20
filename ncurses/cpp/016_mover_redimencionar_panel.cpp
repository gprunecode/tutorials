#include <panel.h>
#include <stdlib.h>
#include <string.h>

typedef struct _PANEL_DATA {
  int x, y, w, h;
  char label[80];
  int label_color;
  PANEL *next;

} PANEL_DATA;

#define NLINES 10
#define NCOLS 40

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
void set_user_ptrs(PANEL **panels, int n);

int main()
{ WINDOW *my_wins[3];
  PANEL  *my_panels[3];
  PANEL_DATA  *top;
  PANEL *stack_top;
  WINDOW *temp_win, *old_win;
  int ch;
  int newx, newy, neww, newh;
  int size = FALSE, move = FALSE;

  /* Inicializar curses */
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Inicializar todos los colores */
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);

  init_wins(my_wins, 3);

  /* Unir un panel a cada ventana */      /* Ordenar de abajo hacia arriba  */
  my_panels[0] = new_panel(my_wins[0]);   /* Agregar 0, orden: stdscr-0     */
  my_panels[1] = new_panel(my_wins[1]);   /* Agregar 1, orden: stdscr-0-1   */
  my_panels[2] = new_panel(my_wins[2]);   /* Agregar 2, orden: stdscr-0-1-2 */

  set_user_ptrs(my_panels, 3);

  /* Actualizar el orden de apilamiento. El 2nd panel estara en la parte superior */
  update_panels();

  /* Mostrar en la pantalla */
  attron(COLOR_PAIR(4));
  mvprintw(LINES - 3, 0, "Use 'm' para mover, 'r' para redimencionar");
  mvprintw(LINES - 2, 0, "Use tab para navegar a traves de las ventanas (F1 para Salir)");
  attroff(COLOR_PAIR(4));
  doupdate();

  stack_top = my_panels[2];
  top = (PANEL_DATA *)panel_userptr(stack_top);
  newx = top->x;
  newy = top->y;
  neww = top->w;
  newh = top->h;
  while((ch = getch()) != KEY_F(1))
  {   switch(ch)
    {   case 9:     /* Tab */
      top = (PANEL_DATA *)panel_userptr(stack_top);
      top_panel(top->next);
      stack_top = top->next;
      top = (PANEL_DATA *)panel_userptr(stack_top);
      newx = top->x;
      newy = top->y;
      neww = top->w;
      newh = top->h;
      break;
      case 'r':   /* Redimencion */
      size = TRUE;
      attron(COLOR_PAIR(4));
      mvprintw(LINES - 4, 0, "Ingrese dimencion: Use las teclas de flecha y pulse <ENTER> para redimencionar");
      refresh();
      attroff(COLOR_PAIR(4));
      break;
      case 'm':   /* Movimiento  */
      attron(COLOR_PAIR(4));
      mvprintw(LINES - 4, 0, "Ingrese movimiento: Use las teclas de flecha y pulse <ENTER> para mover");
      refresh();
      attroff(COLOR_PAIR(4));
      move = TRUE;
      break;
      case KEY_LEFT:
      if(size == TRUE)
      { --newx;
        ++neww;
      }
      if(move == TRUE)
        --newx;
      break;
      case KEY_RIGHT:
      if(size == TRUE)
      { ++newx;
        --neww;
      }
      if(move == TRUE)
        ++newx;
      break;
      case KEY_UP:
      if(size == TRUE)
      { --newy;
        ++newh;
      }
      if(move == TRUE)
        --newy;
      break;
      case KEY_DOWN:
      if(size == TRUE)
      { ++newy;
        --newh;
      }
      if(move == TRUE)
        ++newy;
      break;
      case 10:    /* Enter */
      move(LINES - 4, 0);
      clrtoeol();
      refresh();
      if(size == TRUE)
      { old_win = panel_window(stack_top);
        temp_win = newwin(newh, neww, newy, newx);
        replace_panel(stack_top, temp_win);
        win_show(temp_win, top->label, top->label_color);
        delwin(old_win);
        size = FALSE;
      }
      if(move == TRUE)
      { move_panel(stack_top, newy, newx);
        move = FALSE;
      }
      break;

    }
    attron(COLOR_PAIR(4));
    mvprintw(LINES - 3, 0, "Use 'm' para mover, 'r' para redimencionar");
    mvprintw(LINES - 2, 0, "Use tab para navegar a traves de las ventanas (F1 para Salir)");
    attroff(COLOR_PAIR(4));
    refresh();
    update_panels();
    doupdate();
  }
  endwin();
  return 0;
}

/* Colocar todas las ventanas */
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

/* Establece la estructura PANEL_DATA para paneneles individualmente */
void set_user_ptrs(PANEL **panels, int n)
{ PANEL_DATA *ptrs;
  WINDOW *win;
  int x, y, w, h, i;
  char temp[80];

  ptrs = (PANEL_DATA *)calloc(n, sizeof(PANEL_DATA));

  for(i = 0;i < n; ++i)
  { win = panel_window(panels[i]);
    getbegyx(win, y, x);
    getmaxyx(win, h, w);
    ptrs[i].x = x;
    ptrs[i].y = y;
    ptrs[i].w = w;
    ptrs[i].h = h;
    sprintf(temp, "Ventana numero %d", i + 1);
    strcpy(ptrs[i].label, temp);
    ptrs[i].label_color = i + 1;
    if(i + 1 == n)
      ptrs[i].next = panels[0];
    else
      ptrs[i].next = panels[i + 1];
    set_panel_userptr(panels[i], &ptrs[i]);
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
