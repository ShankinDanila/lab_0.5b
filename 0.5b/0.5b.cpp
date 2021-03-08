/*
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Item {
	char c;
	struct Item *next;
} Item;

Item *deleteList(Item *ptr)
{
	Item *tmp = NULL;
	while (ptr != NULL) {
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	return ptr;
}

int getList(Item **pptr)
{
	char buf[100], *str;
	Item *head = (Item *)malloc(sizeof(Item));
	head->c = '\0';
	head->next = NULL;
	Item *last = head;
	int n, rc = 1;
	int test_size = 0;
	int status, is_newline;
	do {

		n = scanf_s("%99c", buf, 99);
		printf("Hasha n = %d\n", n);
		test_size = strlen(buf);
		printf("Buf lenght %d\n", test_size);
		status = scanf_s("%*1[\n]%n", &is_newline, 99);
		if (n < 0) {
			deleteList(head->next);
			head->next = NULL;
			rc = 0;
			break;
		}
		if (n > 0) {
			for (str = buf; *str != '\0'; ++str) {
				last->next = (Item *)malloc(sizeof(Item));
				last = last->next;
				last->c = *str;
			}
			last->next = NULL;
		}
		else {
			scanf_s("%*c", 99);
		}
		if (is_newline != 0) {
			rc = 1;
			break;
		}
	} while (n > 0);

	*pptr = head->next;
	printf("EOF\n");

	return rc;
}

void putList(Item *ptr)
{
	for (; ptr != NULL; ptr = ptr->next) {
		printf("%s", ptr->c);
	}
	printf("\"\n");
}

int main()
{
	Item *ptr = NULL;
	Item **item_array = (Item**)malloc(20 * sizeof(Item *));
	int i = 0;
	puts("Please, input string...");
	while (getList(&ptr)) {
		item_array[i] = ptr;
		i++;
	}
	for (int j = 0; j = i; ++j) {
		putList("Entered: \n", item_array[j]);
		printf("=====================\n");
		deleteList(item_array[j]);
	}

	return 0;
}
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>

char* get_str() {
	char buf[81] = { 0 };
	char *res = NULL;
	int len = 0;
	int n = 0;
	do 
	{
		n = scanf("%80[^\n]", buf);

		if (n < 0) 
		{
			if (!res) 
			{
				return NULL;
			}
		}
		else if (n > 0) {
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = (char*)realloc(res, str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;

		}
		else {
			scanf("%*c");
		}
	} while (n > 0);
		// hghkjhgkjgkjghg
	if (len > 0) 
	{
		res[len] = '\0';
	}
	
	else 
	{
		res = (char*)calloc(1, sizeof(char));
	}
	
	return res;
} 

char* transform(char* str)
{
	int counter_of_one = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '1')
		{
			 counter_of_one = counter_of_one + 1;
		}
		if ((str[i + 1] == ' ') || (str[i + 1] == '\0'))
		{
			if (counter_of_one % 2 == 0)
			{
				str = (char *)realloc(str, (strlen(str) + 2) * sizeof(char));
				for (int j = strlen(str) + 1; j > i; j--)
				{
					str[j] = str[j - 1];
				}
				str[i + 1] = '0';

				if (str[i + 2] == ' ')
				{
					i += 2;
				}

				else
				{
					i += 1;
				}
			}
			else
			{
				str = (char *)realloc(str, (strlen(str) + 2) * sizeof(char));
				for (int j = strlen(str) + 1; j > i; j--)
				{
					str[j] = str[j - 1];
				}
				str[i + 1] = '1';
				
				if (str[i + 2] == ' ')
				{
					i += 2;
				}

				else
				{
					i += 1;
				}
			}
			counter_of_one = 0;
		}
		i = i + 1;
	}
	
	return str;
}

int get1or0(char* str)
{
	if (str == NULL)
	{
		return 2;
	}

	for (int i = 0; i < strlen(str); i++)
	{
		if ((str[i] != '1') & (str[i] != '0') & (str[i] != ' ') & (str[i] != '\t'))
		{
			return 1;
		}
	}

	return 0;
}

char* skip(char* str)
{
	if (str == NULL)
	{
		return NULL;
	}
	int len = strlen(str);

	char space = ' ';


	for (int i = 0; i <= len - 1; i++)
	{//strchr для поиска пробелов, успешность выделения памяти, утечка при вводе
		if (((*(str + i) == ' ') || (*(str + i) == '\t')) && ((*(str + i + 1) == ' ') || (*(str + i + 1) == '\t')))
		{
			char tmp = str[i];
			for (int j = i; j < len - 1; j++)
			{
				str[j] = str[j + 1];
			}
			str[len] = tmp;

			str = (char *)realloc(str, (len) * sizeof(char));
			len -= 1;
			str[len] = '\0';
			i -= 1;
		}
	}	

	for (int i = 0; i < len; i++)
	{
		if (str[i] == '\t')
		{
			str[i] = ' ';
		}
	}
	return str;
}

int main() {
	char *s = { NULL };

	do {
		s = skip(get_str());

		if (get1or0(s) == 0) 
		{
			printf("%s\n", transform(s));
			free(s);
		}
		else  if (get1or0(s) == 1)
		{
			printf("ERROR");
			free(s);
			_CrtDumpMemoryLeaks();
			return -1;
		}
		else if (get1or0(s) == 2)
		{
			printf("EOF");
			free(s);
			_CrtDumpMemoryLeaks();
			return 2;
		}
	
	} while (s);
	
	_CrtDumpMemoryLeaks();
	return 0;
}