#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "opr_q.h"
#include "opd_q.h"
#include "opr_s.h"
#include "opd_s.h"
/******************************************************************************/
#ifdef NDEBUG
#define fprintf(...) 
#endif
/******************************************************************************/
static int isdigit(const char c)
{
	return (c>='0' && c<='9') || c=='.';
}
static int iseol(const char c)
{
	return c==0 || c=='\n';
}
double parse(const char *s)
{
	// first pass, create queues
	char   curr_char=0,prev_char=0;
	double curr_opd=0.0;
	struct opr_queue_t *opr_q=opr_queue_create();
	struct opd_queue_t *opd_q=opd_queue_create();
	int i=0;
	int dot_flag=0;
	do { 
		prev_char=curr_char;
		curr_char=s[i++];
		fprintf(stderr,"[%5d]\n",i);
		fprintf(stderr,"\tcurr_char = %c (%d)\n",curr_char,curr_char);
		fprintf(stderr,"\tprev_char = %c (%d)\n",prev_char,prev_char);
		if (isdigit(curr_char)) {
			if (curr_char=='.') {
				dot_flag=1;
				continue;
			} else if (dot_flag) 
				dot_flag++;
			curr_opd = 10*curr_opd + (double)(curr_char-'0');
			fprintf(stderr,"\tcurr_opd  = %f\n",curr_opd);
			continue;
		}
		if (isdigit(prev_char)) {
			for (int j = 0; j < dot_flag-1; j++)
				curr_opd *= 0.1;
			opd_queue_push(opd_q,curr_opd);
			curr_opd=0.0;
			dot_flag=0;
		}
		if (curr_char==' ') continue;
		enum OPR_CODE curr_opr=char2opr(curr_char);
		if (curr_opr==OPR_CODE_NAO && !iseol(curr_char)) exit(1);
		opr_queue_push(opr_q,curr_opr);
	} while (!iseol(curr_char));

	//opr_queue_print(opr_q);
	//opd_queue_print(opd_q);

	// second pass, clean the queues
	struct opr_stack_t *opr_s=opr_stack_create();
	struct opd_stack_t *opd_s=opd_stack_create(); 
	opd_stack_push(opd_s,opd_queue_pop(opd_q));
	//i=0;
	//while (opr_q->size && i++<10) {
	while (opd_q->size || opd_s->curr>0) {
		//printf("\n");
		//printf("[queue]\n");
		//opd_queue_print(opd_q);
		//opr_queue_print(opr_q);
		//printf("[stack]\n");
		//opd_stack_print(opd_s);
		//opr_stack_print(opr_s);
		//printf("\n");

		enum OPR_CODE opr1,opr2;
		double opd1,opd2;

		// stack top operator highest priority
		opr1=opr_stack_top(opr_s);
		opr2=opr_queue_top(opr_q);
		if (opr_priority(opr1,opr2)>0) {
			fprintf(stderr,"\t<stack top>\n");
			opr_stack_pop(opr_s);
			switch (opr_opdnum(opr1)){
			case 1:
				opd1=opd_stack_pop(opd_s);
				opd_stack_push(opd_s,opr_action1(opr1,opd1));
				break;
			case 2:
				opd2=opd_stack_pop(opd_s);
				opd1=opd_stack_pop(opd_s);
				opd_stack_push(opd_s,opr_action2(opr1,opd1,opd2));
				break;
			default:
				break;
			}
			continue;
		} 

		opr1=opr_queue_pop(opr_q);
		opr2=opr_queue_top(opr_q);
		//printf("opr1=%c (%d)\n",opr2char(opr1),opr2char(opr1));
		//printf("opr2=%c (%d)\n",opr2char(opr2),opr2char(opr2));

		// queue right
		if (opr_priority(opr1,opr2)<0) { 
			fprintf(stderr,"\t<queue right>\n");
			opr_stack_push(opr_s,opr1);
			opd_stack_push(opd_s,opd_queue_pop(opd_q));
			continue;
		}

		// queue top
		fprintf(stderr,"\t<queue top>\n");
		switch (opr_opdnum(opr1)){
		case 1:
			opd1=opd_stack_pop(opd_s);
			opd_stack_push(opd_s,opr_action1(opr1,opd1));
			break;
		case 2:
			opd1=opd_stack_pop(opd_s);
			opd2=opd_queue_pop(opd_q);
			opd_stack_push(opd_s,opr_action2(opr1,opd1,opd2));
			break;
		default:
			break;
		}
	}

	//double result=opd_queue_top(opd_q);
	double result=opd_stack_top(opd_s);

	// release memory
	opr_queue_destroy(opr_q);
	opd_queue_destroy(opd_q);
	opr_stack_destroy(opr_s);
	opd_stack_destroy(opd_s);

	return result;
}

/**************************************/
int main(int argc, char const* argv[])
{
	char buf[200];
	while(1) {
		fgets(buf,200,stdin);
		if (!strcmp(buf,"quit\n")) break;

		double res;
		printf("%s",buf);
		res = parse(buf);

		printf("=%f\n",res);
		printf("\n");
	}

	return 0;
}
