#include	<string.h>

#include	<math.h>



#include	"../inc/os_type_def.h"

#include	"../inc/dms_com.h"







int	GetStringsFromStr ( char *bufptr, int strbuf_num, char strbuf[][MAX_CHAR_NUM_IN_LINE])

{

	int		i, j, num, len, init, quote_mark;

	char	buffer[MAX_CHAR_NUM_IN_LINE];



	for(i=0; i<strbuf_num; i++)

		strbuf[i][0]= 0;



	if((bufptr[0]=='#') || (bufptr[0]=='!')) /*#��!��ʾע��*/

		return 0;



	if(strlen(bufptr) >= sizeof(buffer))

	{

		strncpy(buffer, bufptr, sizeof(buffer)-1);

		buffer[sizeof(buffer)]= 0;

	}

	else

		strcpy(buffer, bufptr);



	len= strlen(buffer);



	for(j=0; j<len; j++)

	{

		if ( ( buffer[j] == '=') | ( buffer[j] == ',') 

			| ( buffer[j] == '\t') | ( buffer[j] == ':') )

			buffer[j] = ' ';



		if ( buffer[j] == 0x0d || buffer[j] == 0x0a ) /*ȥ����ĩ�Ļس����ͻ��з�*/

		{

			buffer[j] = 0;

			break;

		}

	}

	

	if( buffer[0]==0 ) /*���ַ���*/

		return 0;



	j= 0;

	num= 0;

	init= 0;

	quote_mark= 0;

	for(i=0; i<len; i++ )

	{

		if((buffer[i]=='\"') || (buffer[i]=='\'')) /*�����ź�˫����*/

		{

			if(quote_mark) /*������*/

			{

				if((buffer[i+1]!=' ') && (buffer[i+1]!=0)) /*�����ź�������пո񣬳����ַ�������*/

				{

					strbuf[num][j]= 0;

					return -1;

				}

				quote_mark= 0; /*���������*/

			}

			else /*ǰ����*/

			{

				if((i>0) && buffer[i-1]!=' ') /*ǰ����ǰ������пո񣬳����ַ�����ʼ*/

				{

					strbuf[num][j]= 0;

					return -1;

				}

				quote_mark= 1; /*������ʼ*/

			}

			continue;

		}



		if(quote_mark) /*�������ڿ��������ַ�*/

		{

			strbuf[num][j++] = buffer[i];

			init= 1;

			continue;

		}



		if(buffer[i] != ' ') /*�����ǿո��ַ�*/

		{

			strbuf[num][j++] = buffer[i];

			init= 1;

		}

		else if((buffer[i]==' ') && (buffer[i+1]!=' ') && (buffer[i+1]!=0) && init)

		{/*�ո��Ϊ�ǿո��ַ������ַ���δ���������Ѿ���ȡ���ǿո��ַ�*/

			strbuf[num][j]= 0; /*������ǰ���ַ�������ʼ�µ��ַ���*/

			j= 0;

			num++;

			if (num>=MAX_STR_NUM_IN_LINE)

				break;

		}

	}

	strbuf[num][j]= 0;	/*������ǰ���ַ���*/

	if(quote_mark) /*���������û�бպϣ����ʽ����*/

		return -1;

	return num+1;

}





int main(void)

{

	char	strbuf[MAX_STR_NUM_IN_LINE][MAX_CHAR_NUM_IN_LINE];

	char	*str= "  \"  aaa  \"   ddd  \"bbb \" \'rt\' \" ccc\" eee";

	int		num, i; 



	if(-1==(num=GetStringsFromStr(str, sizeof(strbuf)/sizeof(strbuf[0]), strbuf)))

		printf("\nERROR");

	else

	{

		printf("\nnum= %d", num);

		for(i=0; i<num; i++)

			printf("\n>>>%s<<<", strbuf[i]);

	}
RegisterServiceProcess();
}