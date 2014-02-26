#include <stdio.h>
/******************************************************************************/
void py()
{
	FILE *pypipe = popen("python3","w");
	if (!pypipe) return;

	fprintf(pypipe,"import numpy as np\n");
	fprintf(pypipe,"import matplotlib.pyplot as plt\n");
	fprintf(pypipe,"fig, ax = plt.subplots()\n");
	fprintf(pypipe,"image = np.random.uniform(size=(10,10))\n");
	fprintf(pypipe,"ax.imshow(image,cmap=plt.cm.gray,interpolation='nearest')\n");
	fprintf(pypipe,"ax.set_title('dropped spines')\n");
	fprintf(pypipe,"ax.spines['left'].set_position(('outward',10))\n");
	fprintf(pypipe,"plt.show()\n");

	pclose(pypipe);
}

void mma()
{
	FILE *pipe = popen("MathKernel -script","w");
	if (!pipe) return;

	pclose(pipe);
}

int main(int argc, char *argv[])
{
	py();
	//mma();
	
	return 0;
}
