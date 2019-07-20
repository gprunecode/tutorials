#include <form.h>

int main(){
  FIELD *field[3];
  FORM  *my_form;
  int ch;

  /* Inicializa curses */
  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Inicializa unos pocos pares de color */
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_WHITE, COLOR_BLUE);

  /* Inicializa los campos */
  field[0] = new_field(1, 10, 4, 18, 0, 0);
  field[1] = new_field(1, 10, 6, 18, 0, 0);
  field[2] = NULL;

  /* Establece las opciones de campo */
  set_field_fore(field[0], COLOR_PAIR(1));     /* Coloca el campo con el fordo azul  */
  set_field_back(field[0], COLOR_PAIR(2));     /* y el frente blanco (los caracteres */
  /* son impresos en BLANCO             */
  field_opts_off(field[0], O_AUTOSKIP);        /* No ir al siguiente campo cuando    */
  /* este campo se llene por completo   */
  set_field_back(field[1], A_UNDERLINE);
  field_opts_off(field[1], O_AUTOSKIP);

  /* Crea el formulario y lo publica */
  my_form = new_form(field);
  post_form(my_form);
  refresh();

  set_current_field(my_form, field[0]);        /* Establece foco en campo coloreado  */
  mvprintw(4, 10, "Valor 1:");
  mvprintw(6, 10, "Valor 2:");
  mvprintw(LINES - 2, 0, "Utilice las teclas de flecha UP, DOWN para cambiar entre campos");
  refresh();

  /* Ciclo para optener solicitudes del usuario */
  while( (ch = getch()) != KEY_F(1)  ){
    switch( ch  ){
      case KEY_DOWN:
        /* Ir al siguiente campo */
        form_driver(my_form, REQ_NEXT_FIELD);
        /* Ir al final del buffer actual  */
        /* Deja en el ultimo caracter     */
        form_driver(my_form, REQ_END_LINE);
        break;
      case KEY_UP:
        /* Ir al campo anterior */
        form_driver(my_form, REQ_PREV_FIELD);
        form_driver(my_form, REQ_END_LINE);
        break;
      default:
        /* Si este es un caracter normal, se optiene */
        /* Imprime                                   */
        form_driver(my_form, ch);
        break;

    }

  }

  /* Remueve el formulario y libera la memoria */
  unpost_form(my_form);
  free_form(my_form);
  free_field(field[0]);
  free_field(field[1]);

  endwin();
  return 0;
}
