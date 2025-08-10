/* binarotator.h */

#ifndef BINAROTATOR_H
#define BINAROTATOR_H

#define UNUSED __attribute__((unused))

/* XXX structs */
struct number {
  int i;
  short s;
  char c;
};

/* XXX enums */
enum selected_number { SCHAR = 0, SSHORT, SINT };

/* XXX display.c */
int display_init(void);
int display_shutdown(void);
void display_update(struct number* num, enum selected_number sel);
void wait(void);

/* XXX binary.h */
int binary_is_lsb_set(int num);
int binary_is_msb_set(int num);
int binary_count_leading_zeros(int num);
int binary_is_nth_bit_set(int num, int n);
void binary_set_nth_bit(int* num, int n);
void binary_clear_nth_bit(int* num, int n);

#endif