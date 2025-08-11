/* utility.c */
#include"binarotator.h"

const char* number_type_to_string(enum number_type type)
{
  switch(type)
  {
    case SIGNED_CHAR:
      return "Signed char";
    case SIGNED_SHORT:
      return "Signed short";
    case SIGNED_INT:
      return "Signed int";
    default:
      return "???";
  }
}

int selected_number_width(struct selection* sel)
{
  switch (sel->selected_type)
  {
    case SIGNED_INT: return INT_WIDTH;
    case SIGNED_SHORT: return SHORT_WIDTH;
    case SIGNED_CHAR: return CHAR_WIDTH;
    default: return 0;
  }
}

int wrap(int val, int min, int max) 
{
    if (val > max) return min;
    if (val < min) return max;
    return val;
}

/* not in use currently */

// int selected_number_value(struct numbers* nums, struct selection* sel)
// {
//   switch (sel->selected_type)
//   {
//     case SIGNED_INT: return nums->int_value;
//     case SIGNED_SHORT: return nums->short_value;
//     case SIGNED_CHAR: return nums->char_value;
//     default:
//       return 0;
//   }
// }

