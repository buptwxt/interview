#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "qh_string.h"

using namespace qh;

void test_case(char* str)
{
    string str1(str);
    string str2(str1);

    int len=strlen(str);
    string str3(str, len);
    string str4=str1;

    string *pStrArray[4];
         
    pStrArray[0] = &str1; 
    pStrArray[1] = &str2; 
    pStrArray[2] = &str3; 
    pStrArray[3] = &str4;

    for(int i=0; i<4; i++)
    {
        assert(len == pStrArray[i]->size());
        if(NULL !=  pStrArray[i]->data())
            assert(strcmp(str, pStrArray[i]->data()) == 0);
	if(len != 0)
            assert((*(*pStrArray[i])[len-1]) == str[len-1]);
	if(NULL != pStrArray[i]->c_str())
            assert(strcmp(str, pStrArray[i]->c_str()) == 0);
	    
    }
    printf("case passed\n");
}

int main(int argc, char* argv[])
{
    //TODO ��������ӵ�Ԫ���ԣ�Խ��Խ�ã�����·��������ԽȫԽ��
    //TODO ��Ԫ����д����ο�INIParser�Ǹ���Ŀ����Ҫдһ��printf��Ҫ��assert���ж����жϡ�
    char str1[] = "";
    char str2[] = "a";
    char str3[] = "safasfsa";

    test_case(str1);
    test_case(str2);
    test_case(str3);

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

