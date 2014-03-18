#include <stdio.h>
/******************************************************************************/
void py()
{
	FILE *pypipe = popen("python","w");
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

void mtlb()
{
	FILE *pipe = popen("env matlab -nodesktop -nosplash","w");
	if (!pipe) return;
	fprintf(pipe,"n=50;\n");
	fprintf(pipe,"r=rand(n,1);\n");
	fprintf(pipe,"set(gcf,'Visible','off')\n");
	fprintf(pipe,"plot(r);\n");
	fprintf(pipe,"m=mean(r);\n");
	fprintf(pipe,"hold on\n");
	fprintf(pipe,"plot([0,n],[m,m])\n");
	fprintf(pipe,"hold off\n");
	fprintf(pipe,"title('Mean of Random Uniform Data')\n"); 
	fprintf(pipe,"hgexport(gcf,'figure1',hgexport('factorystyle'),'Format','eps')\n");
	fprintf(pipe,"exit\n");

	pclose(pipe);
}

int main(int argc, char *argv[])
{
	//py();
	mtlb();
	

	return 0;
}
