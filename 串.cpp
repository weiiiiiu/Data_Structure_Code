
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
{ // �㷨4.2
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
{ // �㷨4.3
    int i;
    if (pos < 1 || pos > S[0] || len < 0 || len > S[0] - pos + 1)
        return ERROR;
    for (i = 1; i <= len; i++)
        Sub[i] = S[pos + i - 1];
    Sub[0] = len;
    return OK;
}

int Index(SString S, SString T, int pos)
{ // �㷨4.5
    // T�ǿգ�1��pos��StrLength(S)
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
    // ��s3������s1��s2���Ӷ��ɵ��´�
    Concat(s3, s1, s2);
    printf("Concat(s3,s1,s2)���s3: ");
    for (i = 1; i <= s3[0]; i++)
        printf("%c", s3[i]);
    printf("\n");
    // ��s3���ش�s1�ĵ�3���ַ��𳤶�Ϊ2���Ӵ�
    SubString(s3, s1, 3, 2);
    printf("SubString(s3,s1,3,2)���s3: ");
    for (i = 1; i <= s3[0]; i++)
        printf("%c", s3[i]);
    printf("\n");
    // �����Ӵ�s3������s1�е�1���ַ�֮���λ��
    int index = Index(s1, s3, 1);
    printf("Index(s1,s3,1)���: %d\n", index);
    return OK;
}