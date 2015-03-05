#include <stdio.h>
#include <string.h>

struct inventory {
	char name[30];
	int count;
	float price;
}logs[75];


int main()
{
	FILE *fpt;
	fpt = fopen("inventory.txt","w");

	struct log[75] log1;
	strcpy(logs[0].name,"Javon");
	logs[0].count =4;
	logs[0].price=8.4;

	strcpy(logs[1].name,"Jadasd");
	logs[1].count =3;
	logs[1].price=8.34;

	fwrite(logs,sizeof(logs[0]),75,fpt);

	fclose(fpt);
}