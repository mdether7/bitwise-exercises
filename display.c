/* display.c */
#include "display.h"
#include <ncurses.h>
#include <panel.h>

WINDOW* binary_window;
WINDOW* option_window;
WINDOW* tooltip_window;
PANEL* binary_panel;
PANEL* option_panel;
PANEL* tooltip_panel;

int display_shutdown(void)
{
  del_panel(tooltip_panel);
  delwin(tooltip_window);
  del_panel(option_panel);
  delwin(option_window);
  del_panel(binary_panel);
  delwin(binary_window);
  endwin();
  return 0;
}

int display_init(void)
{
  initscr();
  noecho();
  curs_set(0);
  cbreak();
  binary_window = newwin(7, 40, 0, 0);
  binary_panel = new_panel(binary_window);
  option_window = newwin(7, 40, 0, 0);
  option_panel = new_panel(option_window);
  tooltip_window = newwin(7, 40, 0, 0);
  tooltip_panel = new_panel(tooltip_window);
  wclear(binary_window);
	wclear(option_window);
	wclear(tooltip_window);
  update_panels();
	doupdate();
  return 0;
}