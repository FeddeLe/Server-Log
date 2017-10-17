#include "Server_Header.h"

int Log_In (char *u,char *p)
{
	char User[20];
	char Pass[20];

	FILE *database;
	database = fopen("Registered_Users","r");


	while(fscanf(database,"%s %s",User,Pass) != EOF)
	{
		if (String_Compare(u,User) == 1 && String_Compare(p,Pass) == 1)
		{
			fclose(database);
			return 1;
		}
	}

	fclose(database);
	return 0;
}


int Create_User (char *u,char *p)
{
	int counter,flag_upper,flag_lower,flag_num;
	counter = flag_upper = flag_lower = flag_num = 0;

	char User[20];
	char Pass[20];

	FILE *database;
	database = fopen("Registered_Users","r");


	while(fscanf(database,"%s %s",User,Pass) != EOF)
	{
		if (String_Compare(u,User) == 1)
		{
			fclose(database);
			return 0;
		}
	}

	if (String_Lenght(p) < 6)
	{
		return (-1);
	}

	while(p[counter] != '\0')
	{
		if (p[counter] >= 'A' && p[counter] <= 'Z')
		{
			flag_upper++;
		}
		if (p[counter] >= 'a' && p[counter] <= 'z')
		{
			flag_lower++;
		}
		if (p[counter] >= '0' && p[counter] <= '9')
		{
			flag_num++;
		}
		counter++;
	}

	if (flag_upper != 0 && flag_lower != 0 && flag_num != 0)
	{
		fclose(database);
		database = fopen("Registered_Users","a");
		fprintf(database,"%s\n%s\n\n",u,p);
		fclose(database);
		return 1;
	}

	else
	{
		return (-1);
	}
}


int String_Compare (char *s1,char *s2)
{
    int count = 0;
    int cont = 0;

    while(s1[count] != '\0')
    {
        count++;
    }

    while(s2[cont] != '\0')
    {
        cont++;
    }

    if (count != cont)
    {
        return 0;
    }

    count = 0;

    while(count < cont)
    {
        if (s1[count] != s2[count])
        {
            return 0;
        }
        count++;
    }

    return 1;
}


int String_Lenght(char *str)
{
	int counter = 0;

	while(str[counter] != '\0')
	{
		counter++;
	}

	return counter;
}
