
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 255
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef unsigned char SString[MAXSTRLEN + 1];

Status StrAssign(SString &T, char *chars)
{
    int i;
    if (strlen(chars) > MAXSTRLEN)
        return ERROR;
    else
    {
        T[0] = strlen(chars);
        for (i = 1; i <= T[0]; i++)
            T[i] = *(chars + i - 1);
        return OK;
    }
}

Status Concat(SString &T, SString S1, SString S2)
{ // 算法4.2
    int i;
    Status uncut;
    if (S1[0] + S2[0] <= MAXSTRLEN)
    {
        for (i = 1; i <= S1[0]; i++)
            T[i] = S1[i];
        for (i = 1; i <= S2[0]; i++)
            T[i + S1[0]] = S2[i];
        T[0] = S1[0] + S2[0];
        uncut = TRUE;
    }
    else if (S1[0] < MAXSTRLEN)
    {
        for (i = 1; i <= S1[0]; i++)
            T[i] = S1[i];
        for (i = S1[0] + 1; i <= MAXSTRLEN; i++)
            T[i] = S2[i - S1[0]];
        T[0] = MAXSTRLEN;
        uncut = FALSE;
    }
    else
    {
        for (i = 0; i <= MAXSTRLEN; i++)
            T[i] = S1[i];
        uncut = FALSE;
    }
    return uncut;
}

Status SubString(SString &Sub, SString S, int pos, int len)
{ // 算法4.3
    int i;
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR;
    for (i = 1; i <= len; i++)
        Sub[i] = S[pos + i - 1];
    Sub[0] = len;
    return OK;
}

int Index(SString S, SString T, int pos)
{ // 算法4.5
    // T非空，1≤pos≤StrLength(S)
    int i = pos;
    int j = 1;
    while (i <= S[0] && j <= T[0])
    {
        if (S[i] == T[j])
        {
            ++i;
            ++j;
        }
        else
        {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T[0])
        return i - T[0];
    else
        return 0;
}
int main()
{
    SString s1;
    int i;
    char c1[] = "I am happy";
    StrAssign(s1, c1);
    printf("s1: ");
    for (i = 1; i <= s1[0]; i++)
        printf("%c", s1[i]);
    printf("\n");

    SString s2;
    char c2[] = "today";
    StrAssign(s2, c2);
    printf("s2: ");
    for (i = 1; i <= s2[0]; i++)
        printf("%c", s2[i]);
    printf("\n");

    SString s3;
    // 用s3返回由s1和s2连接而成的新串
    Concat(s3, s1, s2);
    printf("Concat(s3,s1,s2)结果s3: ");
    for (i = 1; i <= s3[0]; i++)
        printf("%c", s3[i]);
    printf("\n");
    // 用s3返回串s1的第3个字符起长度为2的子串
    SubString(s3, s1, 3, 2);
    printf("SubString(s3,s1,3,2)结果s3: ");
    for (i = 1; i <= s3[0]; i++)
        printf("%c", s3[i]);
    printf("\n");
    // 返回子串s3在主串s1中第1个字符之后的位置
    int index = Index(s1, s3, 1);
    printf("Index(s1,s3,1)结果: %d\n", index);
    return OK;
}