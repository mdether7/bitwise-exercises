/* main.c */
#include"binarotator.h"

static int binarotator_init(struct numbers* num, struct selection* sel);
static int number_init(struct numbers* n);
static int selection_init(struct selection* sel);
static void do_command(enum tool_command cmd, struct numbers* num, struct selection* sel);
static void toggle_selected_bit(struct numbers* num, struct selection* sel);
static void cycle_through_types(struct selection* sel);
static void move_through_bits(struct selection* sel, int direction);

static int number_init(struct numbers* n)
{
  n->int_value = 0;
  n->short_value = 0;
  n->char_value = 0;
  return 0;
}

static int selection_init(struct selection* sel)
{
  sel->selected_bit = 1; /* LSB set as the default */
  sel->selected_type = SIGNED_INT; /* currently selected type */
  return 0;                 /* to make operations on */
}

static int binarotator_init(struct numbers* num, struct selection* sel)
{
  number_init(num);
  selection_init(sel);
  return 0;
}

static void cycle_through_types(struct selection* sel)
{
  sel->selected_bit = 1; /* default to LSB at change */
  int current_type = sel->selected_type;
  current_type = (current_type + 1) % TOTAL_TYPES;
  sel->selected_type = current_type;
}

static void toggle_selected_bit(struct numbers* num, struct selection* sel)
{
  switch (sel->selected_type)
  {
    case SIGNED_INT:
      binary_toggle_nth_bit_int(&num->int_value, sel->selected_bit);
      break;
    case SIGNED_SHORT:
      binary_toggle_nth_bit_short(&num->short_value, sel->selected_bit);
      break;
    case SIGNED_CHAR:
      binary_toggle_nth_bit_char(&num->char_value, sel->selected_bit);
      break;
    default:
      break;
  }
}

static void move_through_bits(struct selection* sel, int direction)
{
  if (direction == LEFT)
  {
    sel->selected_bit = wrap(sel->selected_bit + 1, 1, selected_number_width(sel));
  }
  else /* RIGHT */
  {
    sel->selected_bit = wrap(sel->selected_bit - 1, 1, selected_number_width(sel));
  }
}

static void do_command(enum tool_command cmd, struct numbers* num, struct selection* sel)
{
  switch (cmd)
  {
    case TOGGLE_BIT:
      toggle_selected_bit(num, sel);
      break;
    case SWITCH_TYPE:
      cycle_through_types(sel);
      break;
    case MOVE_LEFT:
      move_through_bits(sel, LEFT);
      break;
    case MOVE_RIGHT:
      move_through_bits(sel, RIGHT);
      break;
    default:
      return;
  }
}

int main(void)
{
  struct numbers num;
  struct selection sel;
  binarotator_init(&num, &sel);
  display_init(&num, &sel);

  enum tool_command cmd;
  while (1) 
  {
    cmd = get_command();
    if (cmd == QUIT) {
      break;
    }
    do_command(cmd, &num, &sel);
    display_update(&num, &sel);
  }
  display_shutdown();
  return 0;
}