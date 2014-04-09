#include "opr_q.h"
/******************************************************************************/
#ifdef NDEBUG
#define fprintf(...) 
#endif
/******************************************************************************/
struct opr_queue_t * opr_queue_create()
{
	struct opr_queue_t *s;
	s=(struct opr_queue_t*)malloc(sizeof(struct opr_queue_t));
	assert(s);
	memset(s,0,sizeof(struct opr_queue_t)); 
	return s;
} 
void opr_queue_destroy(struct opr_queue_t *s)
{
	free(s);
} 
void opr_queue_push(struct opr_queue_t *s, const enum OPR_CODE opr)
{
	assert(s->size<OPR_Q_CAPACITY);
	s->data[s->end] = opr;
	s->end=(s->end+1)%OPR_Q_CAPACITY;
	s->size++;
	fprintf(stderr,"\tpushed opr_q : %c (%d)\n",opr2char(opr),opr2char(opr));
} 
enum OPR_CODE opr_queue_top(struct opr_queue_t *s)
{
	if (s->size)
		return s->data[s->start];
	else
		return OPR_CODE_EPT;
} 
enum OPR_CODE opr_queue_pop(struct opr_queue_t *s)
{
	enum OPR_CODE tmp;
	if (s->size) {
		tmp=s->data[s->start];
		s->start=(s->start+1)%OPR_Q_CAPACITY;
		s->size--;
		fprintf(stderr,"\tpoped  opr_q : %c (%d)\n",opr2char(tmp),opr2char(tmp)); 
	} else
		tmp=OPR_CODE_EPT;
	return tmp;
}
void opr_queue_print(struct opr_queue_t *s)
{
	for (int i = 0; i <s->size; i++)
		printf("%c ",opr2char(s->data[(i+s->start)%OPR_Q_CAPACITY]));
	printf("\n");
}
