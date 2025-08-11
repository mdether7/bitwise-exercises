/* display.c */
#include "binarotator.h"
#include <ncurses.h>
#include <panel.h>

#define INT_ROW 1
#define SHORT_ROW 3
#define CHAR_ROW 5

static WINDOW* rotator_window;
static WINDOW* info_window;
static PANEL* rotator_panel;
static PANEL* info_panel;

/* prototypes for static funcs */
static void draw_rotator(struct numbers* num, struct selection* sel);
static void draw_info(struct numbers* num, struct selection* sel);
static void draw_bits(struct numbers* num, struct selection* sel);
static void draw_signed_int_bits(int signed_i, struct selection* sel);
static void draw_signed_short_bits(int signed_s, struct selection* sel);
static void draw_signed_char_bits(int signed_c, struct selection* sel);
static void draw_bits_heads_up(struct selection* sel);

int display_init(struct numbers* num, struct selection* sel)
{
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE); /* for arrow keys */
  cbreak();
  rotator_window = newwin(7, 46, 0, 0);
  rotator_panel = new_panel(rotator_window);
  info_window = newwin(7, 20, 0, 46);
  info_panel = new_panel(info_window);
  wclear(rotator_window);
	wclear(info_window);
  wattron(rotator_window, A_BOLD);
  wattron(info_window, A_BOLD);
  display_update(num, sel);
  return 0;
}

int display_shutdown(void)
{
  del_panel(info_panel);
  info_panel = NULL;
  delwin(info_window);
  info_window = NULL;
  del_panel(rotator_panel);
  rotator_panel = NULL;
  delwin(rotator_window);
  rotator_window = NULL;
  endwin();
  return 0;
}

void display_update(struct numbers* num, struct selection* sel)
{
  wclear(rotator_window);
  wclear(info_window);
  draw_rotator(num, sel);
  draw_info(num, sel);
  update_panels();
  doupdate();
}

enum tool_command get_command(void)
{ 
  int ch;
  while (1)
  {
    ch = getch();
    switch (ch)
    {
      case 'w':
      case 's':
      case KEY_UP:
      case KEY_DOWN:
        return TOGGLE_BIT;
      case ' ': /* space */
        return SWITCH_TYPE;
      case 'a':
      case KEY_LEFT:
        return MOVE_LEFT;
      case 'd':
      case KEY_RIGHT:
        return MOVE_RIGHT;
      case '\x1b': /* escape */
        return QUIT;
    }
  }
}

static void draw_rotator(struct numbers* num, struct selection* sel)
{
  box(rotator_window, ACS_VLINE, ACS_HLINE);
  mvwaddstr(rotator_window, 0, 3, "BINAROTATOR"); 
  draw_bits(num, sel);
  draw_bits_heads_up(sel);
}

static void draw_signed_int_bits(int signed_i, struct selection* sel)
{
  int curr_bit = 1;
  int padding = 0;
  for (int i = INT_WIDTH; i > 0; i--)
  {
    int result = binary_is_nth_bit_set(signed_i, curr_bit);
    char bit = result ? '1' : '0';
    chtype ch = bit | A_BOLD;
    if ( curr_bit == sel->selected_bit && sel->selected_type == SIGNED_INT )
    {
      ch |= A_BLINK;
    }
    if ( (i % 8) == 0 ) 
    { /* make spaces every byte */
      padding++;
    }          /* +5 for aligning everything properly */
    mvwaddch(rotator_window, INT_ROW, (i + 5) - padding, ch);
    curr_bit++;
  }
}

static void draw_signed_short_bits(int signed_s, struct selection* sel)
{
  int curr_bit = 1;
  int padding = 0;
  for (int i = SHORT_WIDTH; i > 0; i--)
  {
    int result = binary_is_nth_bit_set(signed_s, curr_bit);
    char bit = result ? '1' : '0';
    chtype ch = bit | A_BOLD;
    if ( curr_bit == sel->selected_bit && sel->selected_type == SIGNED_SHORT )
    {
      ch |= A_BLINK;
    }
    if ( (i % 8) == 0 ) 
    { /* make spaces every byte */
      padding++;
    }                    /* plus SHORT_WIDTH to align displayed bits*/
    mvwaddch(rotator_window, SHORT_ROW, (i + (5 + SHORT_WIDTH)) - padding, ch);
    curr_bit++;
  }
}

static void draw_signed_char_bits(int signed_c, struct selection* sel)
{
  int curr_bit = 1;
  int padding = 0;
  for (int i = CHAR_WIDTH; i > 0; i--)
  {
    int result = binary_is_nth_bit_set(signed_c, curr_bit);
    char bit = result ? '1' : '0';
    chtype ch = bit | A_BOLD;
    if ( curr_bit == sel->selected_bit && sel->selected_type == SIGNED_CHAR )
    {
      ch |= A_BLINK;
    }
    if ( (i % 8) == 0 ) 
    { /* make spaces every byte */
      padding++;
    }                                   /* /\ Same idea as up /\ */
    mvwaddch(rotator_window, CHAR_ROW, (i + (5 + SHORT_WIDTH + CHAR_WIDTH)) - padding, ch); 
    curr_bit++;
  }
}

static void draw_bits(struct numbers* num, struct selection* sel)
{
  draw_signed_int_bits(num->int_value, sel);
  draw_signed_short_bits(num->short_value, sel);
  draw_signed_char_bits(num->char_value, sel);
}

static void draw_bits_heads_up(struct selection* sel)
{
  if ( sel->selected_type == SIGNED_INT ) 
  {
    wattron(rotator_window, A_STANDOUT);
    mvwaddstr(rotator_window, 1, 39, "INT");
    wattroff(rotator_window, A_STANDOUT);
  }
  else
  {
    mvwaddstr(rotator_window, 1, 39, "INT");
  }
  if ( sel->selected_type == SIGNED_SHORT )
  {
    wattron(rotator_window, A_STANDOUT);
    mvwaddstr(rotator_window, 3, 39, "SHORT");
    wattroff(rotator_window, A_STANDOUT); 
  }
  else
  {
    mvwaddstr(rotator_window, 3, 39, "SHORT");
  }
  if ( sel->selected_type == SIGNED_CHAR )
  {
    wattron(rotator_window, A_STANDOUT);
    mvwaddstr(rotator_window, 5, 39, "CHAR");
    wattroff(rotator_window, A_STANDOUT);     
  }
  else
  {
    mvwaddstr(rotator_window, 5, 39, "CHAR");
  }
}

static void draw_info(struct numbers* num, struct selection* sel)
{
  box(info_window, ACS_VLINE, ACS_HLINE);
  mvwaddstr(info_window, 0, 3, "INFO");
  mvwprintw(info_window, 1, 1, "Type: %s", number_type_to_string(sel->selected_type));
  switch (sel->selected_type)
  {
    case SIGNED_INT:
      mvwprintw(info_window, 2, 1, "Decimal: %d (%d-bit)", num->int_value, INT_WIDTH);
      break;
    case SIGNED_SHORT:
      mvwprintw(info_window, 2, 1, "Decimal: %d (%d-bit)", num->short_value, SHORT_WIDTH);
      break;
    case SIGNED_CHAR:
      mvwprintw(info_window, 2, 1, "Decimal: %d (%d-bit)", num->char_value, CHAR_WIDTH);
      break;
    default:
      mvwprintw(info_window, 2, 1, "Decimal: ???");
      break;
  }
  mvwprintw(info_window, 3, 1, "Selected bit: %d", sel->selected_bit);
}

void printmsg(const char* msg)
{
  mvaddstr(20, 10, msg);
}

void wait(void)
{
  getch();
}