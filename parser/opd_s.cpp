#include "opd_s.h"
/******************************************************************************/
#ifdef NDEBUG
#define fprintf(...) 
#endif
/******************************************************************************/
#define NaN 0x7ff8000000000000 // double precision floating number NaN
/******************************************************************************/
struct opd_stack_t * opd_stack_create()
{
	struct opd_stack_t *s;
	s=(struct opd_stack_t*)malloc(sizeof(struct opd_stack_t));
	assert(s);
	memset(s,0,sizeof(struct opd_stack_t)); 
	s->curr=-1;
	return s;
} 
void opd_stack_destroy(struct opd_stack_t *s)
{
	free(s);
} 
void opd_stack_push(struct opd_stack_t *s, const double opd)
{
	assert(s->curr<OPD_S_CAPACITY-1);
	s->curr++;
	s->data[s->curr] = opd;
	fprintf(stderr,"\tpushed opd_s : %f\n",opd);
} 
double opd_stack_top(struct opd_stack_t *s)
{
	if (s->curr==-1)
		return NaN;
	else
		return s->data[s->curr];
}
double opd_stack_pop(struct opd_stack_t *s)
{
	double tmp;
	if (s->curr>-1) {
		tmp=s->data[s->curr];
		s->curr--;
		fprintf(stderr,"\tpoped  opd_s : %f\n",tmp);
	} else
		tmp=NaN;
	return tmp;
} 
void opd_stack_print(struct opd_stack_t *s)
{
	for (int i = 0; i <= s->curr; i++)
		printf("%f ",s->data[i]);
	printf("\n");
}
