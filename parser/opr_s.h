#ifndef _OPR_S_H_
#define _OPR_S_H_
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "opr.h" 
/**************************************/
static const int OPR_S_CAPACITY=500;
struct opr_stack_t {
	int curr;
	enum OPR_CODE data[OPR_S_CAPACITY];
}; 
/**************************************/
struct opr_stack_t * opr_stack_create();
void opr_stack_destroy(struct opr_stack_t *s);
void opr_stack_push(struct opr_stack_t *s, const enum OPR_CODE opr);
enum OPR_CODE opr_stack_top(struct opr_stack_t *s);
enum OPR_CODE opr_stack_pop(struct opr_stack_t *s);
void opr_stack_print(struct opr_stack_t *s);
/******************************************************************************/ 
#endif /* end of include guard */
