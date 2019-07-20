#include <form.h>

#define STARTX 15
#define STARTY 4
#define WIDTH 25

#define N_FIELDS 3

int main(){
  FIELD *field[N_FIELDS];
  FORM  *my_form;
  int ch, i;

  /* Inicializa curses */
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  /* Inicializa los campos */
  for(i = 0; i < N_FIELDS - 1; ++i)
    field[i] = new_field(1, WIDTH, STARTY + i * 2, STARTX, 0, 0);
  field[N_FIELDS - 1] = NULL;

  /* Establecer las opciones de campo */
  set_field_back(field[1], A_UNDERLINE);    /* Imprime una linea pora la opcion       */

  field_opts_off(field[0], O_ACTIVE);       /* Este campo es una etiqueta estatica    */
  field_opts_off(field[1], O_PUBLIC);       /* Este es un campo estilo contraseña     */
  field_opts_off(field[1], O_AUTOSKIP);     /* Evita entrar en algun otro campo       */
  /* despues de ingresar el ultimo caracter */

  /* Crea el formulario y lo publica */
  my_form = new_form(field);
  post_form(my_form);
  refresh();

  set_field_just(field[0], JUSTIFY_CENTER); /* Justificar al centro                   */
  set_field_buffer(field[0], 0, "Este es un campo estatico");

  /* Inicializa el campo  */
  mvprintw(STARTY, STARTX - 10, "Campo 1:");
  mvprintw(STARTY + 2, STARTX - 10, "Campo 2:");
  refresh();

  /* Ciclo para optener solicitudes del usuario */
  while( (ch = getch()) != KEY_F(1)  ){
    switch( ch  ){
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
