#ifndef _OPR_Q_H
#define _OPR_Q_H
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "opr.h" 
/**************************************/
const int OPR_Q_CAPACITY=500;
/**************************************/
struct opr_queue_t {
	int start;
	int end;
	int size;
	enum OPR_CODE data[OPR_Q_CAPACITY];
}; 
/**************************************/
struct opr_queue_t * opr_queue_create();
void opr_queue_destroy(struct opr_queue_t *s);
void opr_queue_push(struct opr_queue_t *s, const enum OPR_CODE opr);
enum OPR_CODE opr_queue_top(struct opr_queue_t *s);
enum OPR_CODE opr_queue_pop(struct opr_queue_t *s);
void opr_queue_print(struct opr_queue_t *s);
/******************************************************************************/ 
#endif /* end of include guard */
