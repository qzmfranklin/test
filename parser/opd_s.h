#ifndef _OPD_H_
#define _OPD_H_ 
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "opr.h" 
/**************************************/
static const int OPD_S_CAPACITY=500;
struct opd_stack_t {
	int curr;
	double data[OPD_S_CAPACITY];
}; 
/**************************************/
struct opd_stack_t * opd_stack_create();
void opd_stack_destroy(struct opd_stack_t *s);
void opd_stack_push(struct opd_stack_t *s, const double opd);
double opd_stack_top(struct opd_stack_t *s);
double opd_stack_pop(struct opd_stack_t *s);
void opd_stack_print(struct opd_stack_t *s);
/******************************************************************************/
#endif /* end of include guard */
