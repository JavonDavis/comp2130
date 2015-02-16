#include <stdio.h>

float dotProduct(float row[3],float col[3])
{
	int i,sum=0;
	for(i=0;i<3;i++)
	{
		sum+=row[i]*col[i];
	}
	return sum;
}

main()
{

	float a[2][3],b[3][2],c[2][2];
	
	a[0][0] = 1;
	a[0][1] = 2;
	a[0][2] = 3;
	a[1][0] = 1;
	a[1][1] = 2;
	a[1][2] = 3;

	b[0][0] = 1;
	b[0][1] = 2;
	b[1][0] = 1;
	b[1][1] = 2;
	b[2][0] = 1;
	b[2][1] = 2;

	float bCol1[] = {b[0][0],b[1][0],b[2][0]}; 
	float bCol2[] = {b[0][1],b[1][1],b[2][1]}; 

	c[0][0] = dotProduct(a[0],bCol1);
	c[0][1] = dotProduct(a[0],bCol2);
	c[1][0] = dotProduct(a[1],bCol1);
	c[1][1] = dotProduct(a[1],bCol2);

	printf("%.2f",c[0][0]);
	
}
