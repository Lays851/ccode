#include <stdio.h>
#include <ctype.h>

int main(void)
{
	int c;
	int spaces = 0;
	int lines = 0;
	int characters = 0;

	printf("请输入文本（井号#结束）:\n");

	while((c=getchar()) != '#')
	{
		switch(c)
		{
			case ' ':
				spaces++;
				break;
			case '\n':
				lines++;
				break;
			default:
				characters++;
		}
	}

	printf("空格数=%d, 行数=%d, 其他字符=%d\n", 
		   spaces, lines, characters);
	return 0;
}