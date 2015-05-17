#include <stdio.h>
#include <assert.h>
#include<string.h>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

int atoi(char *str)
{
    int res = 0;
    while(*str != '\0')
    {
    	if('0' < *str && *str < '9')
	{
	    res = res*10+(*str-'0');
	}
	str++;
    }
    return res;
}

int resolve(const char* input)
{
    int total = 0;
    char buf[100] = {'\0'};
    char *pBuf = buf;
    char *pInput = const_cast<char *>(input);
    while(*pInput != '\0')
    {
    	*pBuf = *pInput;
	pBuf++;
	pInput++;
    }
    
    pBuf = buf;
    char *result = strtok(pBuf, "\n");
    int flag = 0;
    int count = 0;
    int array[100];
    int i = 0;
    
    while(result != NULL)
    {
    	flag++;
    	if(flag == 1)
	{
	    count = atoi(result);
	}
	else
	{
	    char *pTemp = result;
	    sscanf(pTemp, "%d,%d,%d", &array[i], &array[i+1], &array[i+2]);
	    i += 3;
	}
	result = strtok(NULL, "\n");
    }

    for(int j=0; j<count; j++)
    {
    	total += 2*array[j*3+2];

	if(j != count-1)
	{
	    if(array[j*3+1] >= array[(j+1)*3])
	    {
	        if(array[j*3+2] > array[(j+1)*3+2])
	        {
	    	    total -= 2*array[(j+1)*3+2];
	        }
	        else
	        {
	    	    total -= 2*array[(j)*3+2];
	        }
	    }
	}
    }

    total += array[(count-1)*3+1];
    return total;
}

int main(int argc, char* argv[]) 
{
	const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }

    return 0;
}
