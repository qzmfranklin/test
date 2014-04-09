#ifndef _OPD_Q_H_
#define _OPD_Q_H_
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "opr.h" 
/**************************************/
const int OPD_Q_CAPACITY=500;
struct opd_queue_t {
	int start;
	int end;
	int size;
	double data[OPD_Q_CAPACITY];
}; 
/**************************************/
struct opd_queue_t * opd_queue_create();
void opd_queue_destroy(struct opd_queue_t *s);
void opd_queue_push(struct opd_queue_t *s, const double opd);
double opd_queue_top(struct opd_queue_t *s);
double opd_queue_pop(struct opd_queue_t *s);
void opd_queue_print(struct opd_queue_t *s);
/******************************************************************************/ 
#endif /* end of include guard */
