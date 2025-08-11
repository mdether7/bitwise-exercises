/* main.c */
#include"binarotator.h"

static int binarotator_init(struct numbers* num, struct selection* sel);
static int number_init(struct numbers* n);
static int selection_init(struct selection* sel);

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

static void do_command(enum tool_command cmd)
{
  switch (cmd)
  {
    case TOGGLE_BIT:
      printmsg("UFO BIT");
      break;
    case MOVE_LEFT:
      printmsg("LEFT UFO");
      break;
    case MOVE_RIGHT:
      printmsg("RIGHT UFO");
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
  display_init();

  enum tool_command cmd;
  int quit = 0;
  while (!quit) 
  {
    display_update(&num, &sel);
    cmd = get_command();
    do_command(cmd);
  }
  display_shutdown();
  return 0;
}