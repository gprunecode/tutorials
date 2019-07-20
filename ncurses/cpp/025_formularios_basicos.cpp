#include <form.h>

int main(){
  FIELD *field[3];
  FORM  *my_form;
  int ch;

  /* Inicializar curses */
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Inicializar los campos */
  field[0] = new_field(1, 10, 4, 18, 0, 0);
  field[1] = new_field(1, 10, 6, 18, 0, 0);
  field[2] = NULL;

  /* Establecer las opciones de campo */
  set_field_back(field[0], A_UNDERLINE);  /* Imprime una linea para la opcion */
  field_opts_off(field[0], O_AUTOSKIP);   /* No ir al siguente campo si este  */
  /* campo es llenado                 */
  set_field_back(field[1], A_UNDERLINE);
  field_opts_off(field[1], O_AUTOSKIP);

  /* Crear el formulario y publicarlo */
  my_form = new_form(field);
  post_form(my_form);
  refresh();

  mvprintw(4, 10, "Valor 1:");
  mvprintw(6, 10, "Valor 2:");
  refresh();

  /* Ciclo para optener solicitudes del usuario */
  while((ch = getch()) != KEY_F(1)){
    switch(ch){
      case KEY_DOWN:
        /* Ir al siguiente campo */
        form_driver(my_form, REQ_NEXT_FIELD);
        /* Ir al final del buffer actual */
        /* Deja en el ultimo caracter    */
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
