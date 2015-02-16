#include <stdio.h>
#include <string.h>

struct Record
{
	char name[30],address[30],number[7];
};

struct PhoneBook
{
	struct Record records[2];
}phonebook;

printRecords(struct PhoneBook *pBook)
{
	int numOfRecords = sizeof(pBook->records)/sizeof(pBook->records[0]);
	printf("%d",numOfRecords);
	int i;
	for(i=0;i<numOfRecords;i++)
	{
		struct Record record = pBook->records[i];
		printf("Name:%s\nAddress:%s\nNumber:%s\n\n",record.name,record.address,record.number);
	}
}

struct Record findRecord(char name[30])
{
	int numOfRecords = sizeof(phonebook.records)/sizeof(phonebook.records[0]);

	int i;
	for(i=0;i<numOfRecords;i++)
	{
		struct Record record = phonebook.records[i];
		if(strcmp(name,record.name)==0)
			return record;
	}
	return ;
}

main()
{
	struct Record tiffany;
	struct Record john;

	strcpy(tiffany.name,"Tiffany");
	strcpy(tiffany.number,"4442442");
	strcpy(tiffany.address,"gaza road");

	phonebook.records[0] = tiffany;

	strcpy(john.name,"John");
	strcpy(john.number,"1655132");
	strcpy(john.address,"lane avenue");

	phonebook.records[1] = john;

	struct PhoneBook *pBook = &phonebook;
	printRecords(pBook);
	struct Record record = findRecord("John");
	printf("John's number is %s\n",record.number);
}
