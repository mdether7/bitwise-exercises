#include <stdio.h>

/* Thank god i just used << in count leading zeros XD */
/* Im leavin it here just for the record */
#define BIT_POS_1   1
#define BIT_POS_2   2
#define BIT_POS_3   4
#define BIT_POS_4   8
#define BIT_POS_5   16
#define BIT_POS_6   32
#define BIT_POS_7   64
#define BIT_POS_8   128
#define BIT_POS_9   256
#define BIT_POS_10  512
#define BIT_POS_11  1024
#define BIT_POS_12  2048
#define BIT_POS_13  4096
#define BIT_POS_14  8192
#define BIT_POS_15  16384
#define BIT_POS_16  32768
#define BIT_POS_17  65536
#define BIT_POS_18  131072
#define BIT_POS_19  262144
#define BIT_POS_20  524288
#define BIT_POS_21  1048576
#define BIT_POS_22  2097152
#define BIT_POS_23  4194304
#define BIT_POS_24  8388608
#define BIT_POS_25  16777216
#define BIT_POS_26  33554432
#define BIT_POS_27  67108864
#define BIT_POS_28  134217728
#define BIT_POS_29  268435456
#define BIT_POS_30  536870912
#define BIT_POS_31  1073741824
#define BIT_POS_32  2147483648U

int binary_is_lsb_set(int num)
{
  return num & 1;
}

int binary_is_msb_set(int num)
{
  int shift = (sizeof(int) * 8) - 1; /* Start at most significant bit */
  return num & (1U << shift);
}

int binary_count_leading_zeros(int num)
{
  int shift = (sizeof(int) * 8) - 1;
  int zeros = 0;
  while (!(num & (1U << shift--))) {
     zeros++;
  }
  return zeros;
}

// int binary_is_nth_bit_set(int num, int n)
// {

// }

enum operation { LSB_CHECK = 0, LEADING_ZEROS };

int main(void)
{
  int number = 43543;
  char* message;
  enum operation type = LEADING_ZEROS;

  switch (type)
  {
    case LSB_CHECK:
      message = binary_is_lsb_set(number) ? "LSB present!" : "LSB not present!";
      printf("%s\n", message);
      break;
    case LEADING_ZEROS:
      printf("Number %d has %d leading zeros\n", number, binary_count_leading_zeros(number));
      break;
  }
  return 0;
}