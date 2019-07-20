#include <curses.h>
#include <menu.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD   4

char *choices[] = {
  "Opcion 1",
  "Opcion 2",
  "Opcion 3",
  "Opcion 4",
  "Opcion 5",
  "Opcion 6",
  "Opcion 7",
  "Salir",

};

void func(char *name);

int main(){
  ITEM **my_items;
  int c;
  MENU *my_menu;
  int n_choices, i;
  ITEM *cur_item;

  /* Inicializa curses */
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

  /* Inicializa los elementos */
  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
  for(i = 0; i < n_choices; ++i){
    my_items[i] = new_item(choices[i], choices[i]);
    /* Establece el puntero de usuario */
    set_item_userptr(my_items[i], func);

  }
  my_items[n_choices] = (ITEM *)NULL;

  /* Crea el menu */
  my_menu = new_menu((ITEM **)my_items);

  /* Publica el menu */
  mvprintw(LINES - 3, 0, "Presione <ENTER> para ver la opcion seleccionada");
  mvprintw(LINES - 2, 0, "Flechas Arriba y Abajo para navegar (F1 para Salir)");
  post_menu(my_menu);
  refresh();

  while((c = getch()) != KEY_F(1)){
    switch(c){
      case KEY_DOWN:
        menu_driver(my_menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(my_menu, REQ_UP_ITEM);
        break;
      case 10: /* Enter */
        { ITEM *cur;
          void (*p)(char *);

          cur = current_item(my_menu);
          p = item_userptr(cur);
          p((char *)item_name(cur));
          pos_menu_cursor(my_menu);
          break;
        }
        break;

    }

  }

  unpost_menu(my_menu);
  for(i = 0; i < n_choices; ++i)
    free_item(my_items[i]);
  free_menu(my_menu);
  endwin();

}

void func(char *name){
  move(20, 0);
  clrtoeol();
  mvprintw(20, 0, "El elemento seleccionado es : %s", name);

}
