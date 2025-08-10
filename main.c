#include"binarotator.h"

#define CHAR_WIDTH 8
#define SHORT_WIDTH 16
#define INT_WIDTH 32

int number_init(struct number* n)
{
  n->i = 0;
  n->s = 0;
  n->c = 0;
  return 0;
}

int main(void)
{
  struct number num;
  enum selected_number sel;
  sel = SSHORT;
  number_init(&num);
  display_init();

  display_update(&num, sel);
  wait();
  display_shutdown();
  return 0;
}