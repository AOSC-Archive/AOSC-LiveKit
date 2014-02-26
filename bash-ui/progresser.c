#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	int all;
	char buf[10002];
	sscanf(getenv("ITEM_ALL"),"%d",&all);
	int count = 0;
	while(!feof(stdin))
	{
		fgets(buf,10000,stdin);
		count++;
		printf("%d\n",count*100/all);
	}
	printf("100\n");
	return 0;
}
