#include"binarotator.h"

#define INT_WIDTH 32
#define SHORT_WIDTH 16
#define CHAR_WIDTH 8

static int number_init(struct number* n)
{
  n->int_value = 0;
  n->short_value = 0;
  n->char_value = 0;
  return 0;
}

static int selection_init(struct selection* sel)
{
  sel->selected_bit = 1; /* LSB set as the default */
  sel->selected_type = SCHAR; /* */
  return 0;
}

static int binarotator_init(struct number* num, struct selection* sel)
{
  number_init(num);
  selection_init(sel);
  return 0;
}

int main(void)
{
  struct number num;
  struct selection sel;
  binarotator_init(&num, &sel);
  display_init();
  int quit = 0;
  while (!quit) 
  {
    display_update(&num, &sel);
    wait();
  }
  display_shutdown();
  return 0;
}