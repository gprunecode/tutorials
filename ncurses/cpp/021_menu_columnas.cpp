#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD   4

char *choices[] = {
  "Opcion 1",  "Opcion 2",  "Opcion 3",  "Opcion 4",  "Opcion 5",
  "Opcion 6",  "Opcion 7",  "Opcion 8",  "Opcion 9",  "Opcion 10",
  "Opcion 11", "Opcion 12", "Opcion 13", "Opcion 14", "Opcion 15",
  "Opcion 16", "Opcion 17", "Opcion 18", "Opcion 19", "Opcion 20",
  "Salir",
  (char *)NULL,

};

int main(){
  ITEM **my_items;
  int c;
  MENU *my_menu;
  WINDOW *my_menu_win;
  int n_choices, i;

  /* Tnicializa curses */
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);

  /* Crea los elementos */
  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
  for(i = 0; i < n_choices; ++i)
    my_items[i] = new_item(choices[i], choices[i]);

  /* Crea el menu */
  my_menu = new_menu((ITEM **)my_items);

  /* Configura la opcion del menu para no mostar la descripcion */
  menu_opts_off(my_menu, O_SHOWDESC);

  /* Crea la ventana que sera asociada al menu */
  my_menu_win = newwin(10, 70, 4, 4);
  keypad(my_menu_win, TRUE);

  /* Establece la vetana principal y la subventana */
  set_menu_win(my_menu, my_menu_win);
  set_menu_sub(my_menu, derwin(my_menu_win, 6, 68, 3, 1));
  set_menu_format(my_menu, 5, 3);
  set_menu_mark(my_menu, " * ");

  /* Imprime un margen alrededor de la ventana pricipal e imprime el titulo */
  box(my_menu_win, 0, 0);

  attron(COLOR_PAIR(2));
  mvprintw(LINES - 3, 0, "Use PageUp y PageDown para el desplazamiento");
  mvprintw(LINES - 2, 0, "Use Las flechas para navegar (F1 Para Salir)");
  attroff(COLOR_PAIR(2));
  refresh();

  /* Publica el menu */
  post_menu(my_menu);
  wrefresh(my_menu_win);

  while((c = wgetch(my_menu_win)) != KEY_F(1)){
    switch(c){
      case KEY_DOWN:
        menu_driver(my_menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(my_menu, REQ_UP_ITEM);
        break;
      case KEY_LEFT:
        menu_driver(my_menu, REQ_LEFT_ITEM);
        break;
      case KEY_RIGHT:
        menu_driver(my_menu, REQ_RIGHT_ITEM);
        break;
      case KEY_NPAGE:
        menu_driver(my_menu, REQ_SCR_DPAGE);
        break;
      case KEY_PPAGE:
        menu_driver(my_menu, REQ_SCR_UPAGE);
        break;

    }
    wrefresh(my_menu_win);

  }

  /* Remueve el menu y libera toda la memoria tomada */
  unpost_menu(my_menu);
  free_menu(my_menu);
  for(i = 0; i < n_choices; ++i)
    free_item(my_items[i]);
  endwin();

}
