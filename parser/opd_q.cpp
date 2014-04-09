#include "opd_q.h"
/******************************************************************************/
#ifdef NDEBUG
#define fprintf(...) 
#endif
/******************************************************************************/
#define NaN 0x7ff8000000000000 // double precision floating number NaN
/******************************************************************************/
struct opd_queue_t * opd_queue_create()
{
	struct opd_queue_t *s;
	s=(struct opd_queue_t*)malloc(sizeof(struct opd_queue_t));
	assert(s);
	memset(s,0,sizeof(struct opd_queue_t)); 
	return s;
} 
void opd_queue_destroy(struct opd_queue_t *s)
{
	free(s);
} 
void opd_queue_push(struct opd_queue_t *s, const double opd)
{
	assert(s->size<OPD_Q_CAPACITY);
	s->data[s->end] = opd;
	s->end=(s->end+1)%OPD_Q_CAPACITY;
	s->size++;
	fprintf(stderr,"\tpushed opd_q : %f\n",opd);
} 
double opd_queue_top(struct opd_queue_t *s)
{
	if (s->size)
		return s->data[s->start];
	else
		return NaN;
}
double opd_queue_pop(struct opd_queue_t *s)
{
	double tmp;
	if (s->size) {
		tmp=s->data[s->start];
		s->start=(s->start+1)%OPD_Q_CAPACITY;
		s->size--;
		fprintf(stderr,"\tpoped  opd_q : %f\n",tmp);
	} else
		tmp=NaN;
	return tmp;
} 
void opd_queue_print(struct opd_queue_t *s)
{
	for (int i = 0; i <s->size; i++)
		printf("%f ",s->data[(i+s->start)%OPD_Q_CAPACITY]);
	printf("\n");
}
