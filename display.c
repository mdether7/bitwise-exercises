/* display.c */
#include "binarotator.h"
#include <ncurses.h>
#include <panel.h>

static WINDOW* binary_window;
static WINDOW* result_window;
static PANEL* binary_panel;
static PANEL* result_panel;

/* prototypes for static funcs */
static void draw_binary(struct number* num, struct selection* sel);
static void draw_result(struct number* num, struct selection* sel);

int display_init(void)
{
  initscr();
  noecho();
  curs_set(0);
  cbreak();
  binary_window = newwin(7, 40, 0, 0);
  binary_panel = new_panel(binary_window);
  result_window = newwin(7, 20, 0, 40);
  result_panel = new_panel(result_window);
  wclear(binary_window);
	wclear(result_window);
  update_panels();
	doupdate();
  return 0;
}

int display_shutdown(void)
{
  del_panel(result_panel);
  delwin(result_window);
  del_panel(binary_panel);
  delwin(binary_window);
  endwin();
  return 0;
}

void display_update(struct number* num, struct selection* sel)
{
  draw_binary(num, sel);
  draw_result(num, sel);
  update_panels();
  doupdate();
}

UNUSED static const char* number_type_to_string(enum number_type type)
{
  switch(type)
  {
    case SCHAR:
      return "Char";
    case SSHORT:
      return "Short";
    case SINT:
      return "Int";
    default:
      return "???";
  }
}

static void draw_binary(struct number* num, struct selection* sel)
{
  box(binary_window, ACS_VLINE, ACS_HLINE);
  mvwaddstr(binary_window, 0, 3, "Binarotator");

}

static void draw_result(struct number* num, struct selection* sel)
{
  box(result_window, ACS_VLINE, ACS_HLINE);
  mvwaddstr(result_window, 0, 3, "Info");
  mvwprintw(result_window, 1, 1, "Type: %s", number_type_to_string(sel->selected_type));
  mvwprintw(result_window, 2, 1, "Value: %d", num->i);
  mvwprintw(result_window, 3, 1, "Selected bit: %d", sel->selected_bit);
}

void wait(void)
{
  getch();
}