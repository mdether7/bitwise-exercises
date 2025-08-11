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

