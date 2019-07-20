#include <ncurses.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int ch, prev, row, col;
  prev = EOF;
  FILE *fp;
  int y, x;

  if (argc != 2) {
    printf("Usage: %s <a c file name>\n", argv[0]);
    exit(1);
  }

  fp = fopen(argv[1], "r");

  if (fp == NULL) {
    perror("Cannot open input file");
    exit(1);
  }

  initscr();                        /* inicia el modo curses */
  getmaxyx(stdscr, row, col);       /* obtiene los limites de pantalla */
  while ((ch = fgetc(fp)) != EOF) {
    getyx(stdscr, y, x);            /* obtiene posicion actual del cursor */
    if (y == (row - 1)) {
      printw("<-Press Any Key->");  /* pide una pulsacion al usuario */
      getch();
      clear();                      /* limpia la pantalla */
      move(0, 0);                   /* comienza al inicio de la pantalla */
    }
    if (prev == '/' && ch == '*') { /* solamente cuando es / y *
                                     * cambia a negrita */
      attron(A_BOLD);               /* activa negrita */
      getyx(stdscr, y, x);          /* obtiene posicion actual del cursor */
      move(y, x-1);                 /* retrocede un espacio */
      printw("%c%c", '/', ch);      /* La impresion real sucede aqui */
    }
    else
      printw("%c", ch);
    refresh();
    if (prev == '*' && ch == '/')
      attroff(A_BOLD);              /* apagar una vez se ha alcanzado
                                     * y luego */
    prev = ch;
  }

  printw("<-Press Any Key->");
  getch();

  endwin();                         /* Fin del modo curses */
  fclose(fp);

  return 0;
}
