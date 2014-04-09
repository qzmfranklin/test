#ifndef _OPR_H_
#define _OPR_H_
/******************************************************************************/	
enum OPR_CODE {
	OPR_CODE_EPT = 0,	// empty operator
	OPR_CODE_NAO = 1,	// not an operator
	OPR_CODE_ADD = 100,	// a + b
	OPR_CODE_SUB = 101,	// a - b
	OPR_CODE_MUL = 400,	// a * b
	OPR_CODE_DIV = 401,	// a / b
	OPR_CODE_POW = 600,	// a ^ b
	OPR_CODE_FAC = 900,	// a!
};

// +: opr1>opr2
static int opr_priority(enum OPR_CODE opr1, enum OPR_CODE opr2)
{
	return opr1/100 - opr2/100;
}

// convert char to OPR_CODE
static enum OPR_CODE char2opr(const char c)
{
	enum OPR_CODE opr;
	switch (c) {
		case '+':
			opr=OPR_CODE_ADD;
			break;
		case '-':
			opr=OPR_CODE_SUB;
			break;
		case '*':
			opr=OPR_CODE_MUL;
			break;
		case '/':
			opr=OPR_CODE_DIV;
			break;
		case '^':
			opr=OPR_CODE_POW;
			break;
		case '!':
			opr=OPR_CODE_FAC;
			break;
		default:
			opr=OPR_CODE_NAO;
			break;
	}
	return opr;
}
// convert OPR_CODE to char
static char opr2char(const enum OPR_CODE opr)
{
	char c=0;
	switch (opr) {
		case OPR_CODE_ADD:
			c='+';
			break;
		case OPR_CODE_SUB:
			c='-';
			break;
		case OPR_CODE_MUL:
			c='*';
			break;
		case OPR_CODE_DIV:
			c='/';
			break;
		case OPR_CODE_POW:
			c='^';
			break;
		case OPR_CODE_FAC:
			c='!';
			break;
		default:
			break;
	}
	return c;
}

// number of operand of operator
static int opr_opdnum(enum OPR_CODE opr)
{
	int res;
	switch (opr) {
		case OPR_CODE_ADD:
			res=2;
			break;
		case OPR_CODE_SUB:
			res=2;
			break;
		case OPR_CODE_MUL:
			res=2;
			break;
		case OPR_CODE_DIV:
			res=2;
			break;
		case OPR_CODE_POW:
			res=2;
			break;
		case OPR_CODE_FAC:
			res=1;
			break;
		default:
			break;
	}
	return res;
}

static double fact(const double x)
{
	return tgamma(x+1.0);
}
// operator with a single operand
static double opr_action1(enum OPR_CODE opr, double opd)
{ 
	double res;
	switch (opr) {
		case OPR_CODE_FAC:
			res = fact(opd);
			break;
		default:
			break;
	}
	return res;
}
// operator with two operands
static double opr_action2(enum OPR_CODE opr, double opd1, double opd2)
{ 
	double res;
	switch (opr) {
		case OPR_CODE_ADD:
			res = opd1 + opd2;
			break;
		case OPR_CODE_SUB:
			res = opd1 - opd2;
			break;
		case OPR_CODE_MUL:
			res = opd1 * opd2;
			break;
		case OPR_CODE_DIV:
			res = opd1 / opd2;
			break;
		case OPR_CODE_POW:
			res = pow(opd1,opd2);
			break;
		default:
			break;
	}
	return res;
}
/******************************************************************************/	
#endif /* end of include guard */
