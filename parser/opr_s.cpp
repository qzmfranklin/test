#include "opr_s.h"
/******************************************************************************/
#ifdef NDEBUG
#define fprintf(...) 
#endif
/******************************************************************************/
struct opr_stack_t * opr_stack_create()
{
	struct opr_stack_t *s;
	s=(struct opr_stack_t*)malloc(sizeof(struct opr_stack_t));
	assert(s);
	memset(s,0,sizeof(struct opr_stack_t)); 
	s->curr=-1;
	return s;
} 
void opr_stack_destroy(struct opr_stack_t *s)
{
	free(s);
} 
void opr_stack_push(struct opr_stack_t *s, const enum OPR_CODE opr)
{
	assert(s->curr<OPR_S_CAPACITY-1);
	s->curr++;
	s->data[s->curr] = opr;
	fprintf(stderr,"\tpushed opr_s : %c (%d)\n",opr2char(opr),opr2char(opr));
} 
enum OPR_CODE opr_stack_top(struct opr_stack_t *s)
{
	if (s->curr>-1)
		return s->data[s->curr];
	else
		return OPR_CODE_EPT;
} 
enum OPR_CODE opr_stack_pop(struct opr_stack_t *s)
{
	enum OPR_CODE tmp;
	if (s->curr>-1) {
		tmp=s->data[s->curr];
		s->curr--;
		fprintf(stderr,"\tpoped  opr_s : %c (%d)\n",opr2char(tmp),opr2char(tmp));
	} else 
		tmp = OPR_CODE_EPT;
	return tmp;
}
void opr_stack_print(struct opr_stack_t *s)
{
	for (int i = 0; i <= s->curr; i++) {
		char c=opr2char(s->data[i]);
		printf("[%d]%c(%d) ",i,c,c);
	}
	printf("\n");
}
