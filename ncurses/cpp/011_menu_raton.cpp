#include <ncurses.h>
#include <string.h>

#define WIDTH  30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
  "Opcion 1",
  "Opcion 2",
  "Opcion 3",
  "Opcion 4",
  "Salir",
};

int n_choices = sizeof(choices) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);
void report_choice(int mouse_x, int mouse_y, int *p_choice);

int main()
{
  int c, choice = 0;
  WINDOW *menu_win;
  MEVENT event;

  /* Inicializa curses */
  initscr();
  clear();
  noecho();
  cbreak();   // Deshabilitar buffer de linea. Pasar todo

  /* Trata de poner la ventana al centro de la pantalla */
  startx = (80 -  WIDTH) / 2;
  starty = (24 - HEIGHT) / 2;

  attron(A_REVERSE);
  mvprintw(23, 1, "Click en Salir para terminar (Funciona mejor en una consola virtual)");
  refresh();
  attroff(A_REVERSE);

  /* Imprime el menu por primera vez */
  menu_win = newwin(HEIGHT, WIDTH, starty, startx);
  print_menu(menu_win, 1);
  /* necesitamos habilitar las teclas de "funcion",
   *      KEY_MOUSE forma parte de ellas */
  keypad( menu_win, TRUE  );
  /* Optener todos los eventos del raton */
  mousemask(ALL_MOUSE_EVENTS, NULL);

  while(1) {
    c = wgetch(menu_win);
    switch(c) {
      case KEY_MOUSE:
      if(getmouse(&event) == OK) { /* Cuando el usuario presiona el boton izquierdo del mouse */
        if(event.bstate & BUTTON1_PRESSED) {
          report_choice(event.x + 1, event.y + 1, &choice);
          if(choice == -1) // Opcion de salida
            goto end;
          mvprintw(22, 1, "La opcion elegida : %d La cadena elegida es \"%10s\"", choice, choices[choice - 1]);
          refresh();
        }
      }
      print_menu(menu_win, choice);
      break;
    }
  }
  end:
  endwin();
  return 0;
}

void print_menu(WINDOW *menu_win, int highlight) {
  int x, y, i;

  x = 2;
  y = 2;
  box(menu_win, 0, 0);
  for(i = 0; i < n_choices; ++i) {
    if(highlight == i + 1) {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%s", choices[i]);
      wattroff(menu_win, A_REVERSE);
    } else
      mvwprintw(menu_win, y, x, "%s", choices[i]);
    ++y;
  }
  wrefresh(menu_win);
}

/* Informa la opcion de acuerdo a la posicion del mouse */
void report_choice(int mouse_x, int mouse_y, int *p_choice) {
  int i,j, choice;

  i = startx + 2;
  j = starty + 2;

  for(choice = 0; choice < n_choices; ++choice)
    if(mouse_y == j + choice && mouse_x >= i &&
        mouse_x <= i + strlen(choices[choice])) {
      if(choice == n_choices - 1)
        *p_choice = -1;
      else
        *p_choice = choice + 1;
      break;
    }
}
