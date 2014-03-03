/* This is a header file for the integer stack */

#ifndef boolean_defined
#define boolean_defined
typedef enum {NOT_OK, OK } Tboolean;
#endif

#define MAX_INT_STACK_SIZE 100
typedef struct {
	int array[MAX_INT_STACK_SIZE]; // change to use characters
	int top;
} Tintstack;

void     initialize_int_stack (Tintstack *Pstack);
Tboolean push_int( Tintstack *Pstack, int item);
Tboolean pop_int( Tintstack *Pstack, int *Pitem);
void     print_int_stack (const Tintstack *Pstack);
int      is_empty_int_stack(const Tintstack *Pstack);
