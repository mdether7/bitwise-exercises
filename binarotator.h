/* binarotator.h */
#ifndef BINAROTATOR_H
#define BINAROTATOR_H

/* XXX my defines */
#define UNUSED __attribute__((unused))

#define TOTAL_TYPES 3
#define CHAR_WIDTH 8
#define SHORT_WIDTH 16
#define INT_WIDTH 32

#define LEFT 0
#define RIGHT 1

#include <stdint.h>

/* XXX enums */
enum number_type { SIGNED_INT = 0, SIGNED_SHORT, SIGNED_CHAR };
enum tool_command { TOGGLE_BIT = 0, SWITCH_TYPE, MOVE_LEFT, MOVE_RIGHT, QUIT };

/* XXX structs */
struct numbers {
  int32_t int_value; /* Stores all three distinct available */
  int16_t short_value; /* types for bit manupulation */
  int8_t char_value;
};

struct selection {
  int selected_bit;
  enum number_type selected_type;
};

/* XXX display.c */
int display_init(struct numbers* num, struct selection* sel);
int display_shutdown(void);
void display_update(struct numbers* num, struct selection* sel);
enum tool_command get_command(void);
/* debug only */
void printmsg(const char* msg);
void wait(void);

/* XXX binary.c */
int binary_is_lsb_set(int num);
int binary_is_msb_set(int num);
int binary_count_leading_zeros(int num);
int binary_is_nth_bit_set(int num, int n);
void binary_set_nth_bit(int* num, int n);
void binary_clear_nth_bit(int* num, int n);
/* \/ Used ones | Not used ones /\ */
void binary_toggle_nth_bit_int(int32_t* num, int n);
void binary_toggle_nth_bit_short(int16_t* num, int n);
void binary_toggle_nth_bit_char(int8_t* num, int n);

/* XXX utility.c */
const char* number_type_to_string(enum number_type type);
int selected_number_width(struct selection* sel);
int wrap(int val, int min, int max);

#endif