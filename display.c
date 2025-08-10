/* display.c */
#include "binarotator.h"
#include <ncurses.h>
#include <panel.h>

static WINDOW* rotator_window;
static WINDOW* info_window;
static PANEL* rotator_panel;
static PANEL* info_panel;

/* prototypes for static funcs */
static void draw_rotator(struct number* num, struct selection* sel);
static void draw_info(struct number* num, struct selection* sel);
static void draw_bits(struct number* num, struct selection* sel);
static void draw_signed_int_bits(int signed_i, struct selection* sel);
static void draw_signed_short_bits(int signed_s, struct selection* sel);
static void draw_bits_heads_up(struct selection* sel);
static const char* number_type_to_string(enum number_type type);

int display_init(void)
{
  initscr();
  noecho();
  curs_set(0);
  cbreak();
  rotator_window = newwin(7, 46, 0, 0);
  rotator_panel = new_panel(rotator_window);
  info_window = newwin(7, 20, 0, 46);
  info_panel = new_panel(info_window);
  wclear(rotator_window);
	wclear(info_window);
  update_panels();
	doupdate();
  return 0;
}

int display_shutdown(void)
{
  del_panel(info_panel);
  delwin(info_window);
  del_panel(rotator_panel);
  delwin(rotator_window);
  endwin();
  return 0;
}

void display_update(struct number* num, struct selection* sel)
{
  draw_rotator(num, sel);
  draw_info(num, sel);
  update_panels();
  doupdate();
}

static const char* number_type_to_string(enum number_type type)
{
  switch(type)
  {
    case SIGNED_CHAR:
      return "Char";
    case SIGNED_SHORT:
      return "Short";
    case SIGNED_INT:
      return "Int";
    default:
      return "???";
  }
}

static void draw_rotator(struct number* num, struct selection* sel)
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
    {
      padding++; /* make spaces every byte */
    }
    mvwaddch(rotator_window, 1, (i + 5) - padding, ch);
    curr_bit++;
  }
}

static void draw_signed_short_bits(int signed_s, struct selection* sel)
{

}

static void draw_bits(struct number* num, struct selection* sel)
{
  draw_signed_int_bits(num->int_value, sel);
  draw_signed_short_bits(num->short_value, sel);
}
  // for (int i = INT_WIDTH; i > 0; i--) 
  // {
  //   int result = binary_is_nth_bit_set(num->int_value, i);
  //   char bit = result ? '1' : '0';
  //   chtype ch = bit | A_BOLD;
  //   if ( (i % 8) == 0 ) {
  //     padding++; /* make spaces every byte */
  //   }
  //   mvwaddch(rotator_window, 1, (i + 5) - padding, ch);
  // }
  // padding = 0;
  // for (int i = SHORT_WIDTH; i > 0; i--)
  // {
  //   int result = binary_is_nth_bit_set(num->short_value, i);
  //   char bit = result ? '1' : '0';
  //   chtype ch = bit | A_BOLD;
  //   if ( i == sel->selected_bit ) 
  //   {
  //     ch |= A_BLINK;
  //   }
  //   if ( (i % 8) == 0 ) 
  //   {
  //     padding++; /* make spaces every byte */
  //   }
  //   mvwaddch(rotator_window, 3, (i + 5 + SHORT_WIDTH) - padding, ch);
  // }
  // padding = 0;
  // for (int i = CHAR_WIDTH; i > 0; i--)
  // {
  //   int result = binary_is_nth_bit_set(num->char_value, i);
  //   char bit = result ? '1' : '0';
  //   chtype ch = bit | A_BOLD;
  //   if ( (i % 8) == 0 ) {
  //     padding++; /* make spaces every byte */
  //   }
  //   mvwaddch(rotator_window, 5, (i + 5 + CHAR_WIDTH+SHORT_WIDTH) - padding, ch);
//   }
// }

static void draw_bits_heads_up(struct selection* sel)
{
  //wattron(rotator_window, A_STANDOUT | A_BLINK);
  mvwaddstr(rotator_window, 1, 39, "INT");
  mvwaddstr(rotator_window, 3, 39, "SHORT");
  mvwaddstr(rotator_window, 5, 39, "CHAR");
  //wattroff(rotator_window, A_STANDOUT | A_BLINK);
}

static void draw_info(struct number* num, struct selection* sel)
{
  box(info_window, ACS_VLINE, ACS_HLINE);
  mvwaddstr(info_window, 0, 3, "INFO");
  mvwprintw(info_window, 1, 1, "Type: %s", number_type_to_string(sel->selected_type));
  mvwprintw(info_window, 2, 1, "Decimal: %d", num->int_value);
  mvwprintw(info_window, 3, 1, "Selected bit: %d", sel->selected_bit);
}

void wait(void)
{
  getch();
}