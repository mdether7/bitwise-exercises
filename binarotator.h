/* binarotator.h */
#ifndef BINAROTATOR_H
#define BINAROTATOR_H

/* XXX my defines */
#define UNUSED __attribute__((unused))
#define CHAR_WIDTH 8
#define SHORT_WIDTH 16
#define INT_WIDTH 32

#include <stdint.h>

/* XXX enums */
enum number_type { SCHAR = 0, SSHORT, SINT };

/* XXX structs */
struct number {
  int32_t int_value; /* Stores all three distinct available */
  int16_t short_value; /* types for bit manupulation */
  int8_t char_value;
};

struct selection {
  int selected_bit;
  enum number_type selected_type;
};

/* XXX display.c */
int display_init(void);
int display_shutdown(void);
void display_update(struct number* num, struct selection* sel);
void wait(void);

/* XXX binary.h */
int binary_is_lsb_set(int num);
int binary_is_msb_set(int num);
int binary_count_leading_zeros(int num);
int binary_is_nth_bit_set(int num, int n);
void binary_set_nth_bit(int* num, int n);
void binary_clear_nth_bit(int* num, int n);

#endif