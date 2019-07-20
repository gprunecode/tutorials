#include <stdio.h>
#include <ncurses.h>

#define WIDTH  30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
  "Eleccion 1",
  "Eleccion 2",
  "Eleccion 3",
  "Eleccion 4",
  "Salir",
};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, int highlight);

int main()
{
  WINDOW *menu_win;
  int highlight = 1;
  int choice = 0;
  int c;

  initscr();
  clear();
  noecho();
  cbreak();   /* Buffer de linea desactivado. Pasar de todo */
  startx = (80 - WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;

  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  keypad(menu_win, TRUE);
  mvprintw(0, 0, "Utilice las flechas para ir arriba y abajo, Presione enter para elegir");
  refresh();
  print_menu(menu_win, highlight);

  while(1) {
    c = wgetch(menu_win);
    switch(c) {
      case KEY_UP:
        if(highlight == 1)
          highlight = n_choices;
        else
          --highlight;
        break;
      case KEY_DOWN:
        if(highlight == n_choices)
          highlight = 1;
        else
          ++highlight;
        break;
      case 10:
        choice = highlight;
        break;
      default:
        mvprintw(24, 0, "Caracter presionado = %3d Ojala se imprima como '%c'", c, c);
        refresh();
        break;

    }
    print_menu(menu_win, highlight);
    if(choice != 0) /* El usuario eligio salir del bucle infinito */
      break;
  }
  mvprintw(23, 0, "Elegiste la opcion %d con la cadena %s\n", choice, choices[choice - 1]);
  clrtoeol();
  refresh();
  getch();
  endwin();

  return 0;
}

void print_menu(WINDOW *menu_win, int highlight) {
  int x, y, i;

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for(i = 0; i < n_choices; ++i) {
    if(highlight == i + 1) { /* Resalta lo opcion actual */
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    ++y;
  }
  wrefresh(menu_win);
}
