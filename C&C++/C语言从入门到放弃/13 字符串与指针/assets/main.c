#include <stdio.h>

//版本一：
int romanToInt(char *s)
{
    int sum = 0;
    while (*s != '\0')
    {
        switch (*s)
        {
        case 'M':
            sum += 1000;
            s++;
            break;
        case 'D':
            sum += 500;
            s++;
            break;
        case 'C':
            if (*(s+1) == 'D')
            {
                sum += 400;
                s+=2;
                break;
            }
            else if (*(s+1) == 'M')
            {
                sum += 900;
                s+=2;
                break;
            }
            else
            {
                sum += 100;
                s++;
                break;
            }
        case 'L':
            sum += 50;
            s++;
            break;
        case 'X':
            if (*(s+1) == 'L')
            {
                sum += 40;
                s+=2;
                break;
            }
            else if (*(s+1) == 'C')
            {
                sum += 90;
                s+=2;
                break;
            }
            else
            {
                sum += 10;
                s++;
                break;
            }
        case 'V':
            sum += 5;
            s++;
            break;
        case 'I':
            if (*(s+1) == 'V')
            {
                sum += 4;
                s+=2;
                break;
            }
            else if (*(s+1) == 'X')
            {
                sum += 9;
                s+=2;
                break;
            }
            else
            {
                sum += 1;
                s++;
                break;
            }
        }
    }
    return sum;
}

//版本二：
int foo(char ch)
{
    switch (ch)
    {
    case 'I': return 1; 
    case 'V': return 5; 
    case 'X': return 10; 
    case 'L': return 50; 
    case 'C': return 100; 
    case 'D': return 500; 
    case 'M': return 1000; 
    default: return 0 ;
    }
}

int romanToInt_1(char *s)
{
    int sum = 0;
   while(*s) 
   {
        if(foo(*s) >= foo(*(s+1)))
        {
            sum += foo(*s);
            s++;
        }
        else
        {
            sum +=  foo(*(s+1)) - foo(*s);
            s+=2;   
        }
   }
   return sum;
}

int main()
{
    const char* str[]=
    {
        "III",
        "IV",
        "IX",
        "LVIII",
        "MCMXCIV"
    };
    for(int i=0;i<5;i++)
    {
        printf("%s:%d\n",str[i],romanToInt_1(str[i]));
    }
    return 0;
};