#include <stdio.h>
#include <string.h>

char *my_strchr(const char *str, int c);
char *my_strrchr(const char *str, int c);
char *my_strpbrk(const char *str1, const char *str2);

int test_strchr(void);
int comp_strchr(const char *str, int c);

int test_strrchr(void);
int comp_strrchr(const char *str, int c);

int test_strpbrk(void);
int comp_strpbrk(const char *str1, const char *str2);

int main(void)
{
    int failed = 0;

    failed += test_strchr();
    failed += test_strrchr();
    failed += test_strpbrk();

    printf("%d\n", failed);
    return 0;
}

int test_strchr(void)
{
    int failed = 0;
    char ch, *str;

    // 1. Символ находится в начале строки
    str = "abcxyz", ch = 'a';
    failed += comp_strchr(str, ch);

    // 2. Символ находится в середине строки
    str = "abcxyz", ch = 'c';
    failed += comp_strchr(str, ch);

    // 3. Символ находится в конце строки
    str = "abcxyz", ch = 'z';
    failed += comp_strchr(str, ch);

    // 4. Символ отсутствует в строке
    str = "abcxyz", ch = 'g';
    failed += comp_strchr(str, ch);

    // 5. Символ целиком состоит из искомого символа
    str = "aaaaaa", ch = 'a';
    failed += comp_strchr(str, ch);

    // 6. Пустая строка
    str = "", ch = 'a';
    failed += comp_strchr(str, ch);

    // 7. Символы повторяются
    str = "aboba", ch = 'b';
    failed += comp_strchr(str, ch);

    // 8. Строка длиной в единицу
    str = "a", ch = 'a';
    failed += comp_strrchr(str, ch);

    // 9. Нулевой символ
    str = "abcxyz", ch = '\0';
    failed += comp_strchr(str, ch);

    // 10. Нулевой символ и нулевая строка
    str = "", ch = '\0';
    failed += comp_strchr(str, ch);

    return failed;
}

// Возвращает 1 в случае провала
int comp_strchr(const char *str, int c)
{
    return my_strchr(str, c) != strchr(str, c);
}

int test_strrchr(void)
{
    int failed = 0;
    char ch, *str;

    // 1. Символ находится в начале строки
    str = "abcxyz", ch = 'a';
    failed += comp_strrchr(str, ch);

    // 2. Символ находится в середине строки
    str = "abcxyz", ch = 'c';
    failed += comp_strrchr(str, ch);

    // 3. Символ находится в конце строки
    str = "abcxyz", ch = 'z';
    failed += comp_strrchr(str, ch);

    // 4. Символ отсутствует в строке
    str = "abcxyz", ch = 'g';
    failed += comp_strrchr(str, ch);

    // 5. Строка целиком состоит из искомого символа
    str = "aaaaaa", ch = 'a';
    failed += comp_strrchr(str, ch);

    // 6. Пустая строка
    str = "", ch = 'a';
    failed += comp_strrchr(str, ch);

    // 7. Строка длиной в единицу
    str = "a", ch = 'a';
    failed += comp_strrchr(str, ch);

    // 8. Символы повторяются
    str = "aboba", ch = 'b';
    failed += comp_strchr(str, ch);

    // 9. Нулевой символ
    str = "abcxyz", ch = '\0';
    failed += comp_strchr(str, ch);

    // 10. Нулевой символ и нулевая строка
    str = "", ch = '\0';
    failed += comp_strchr(str, ch);

    return failed;
}

// Возвращает 1 в случае провала
int comp_strrchr(const char *str, int c)
{
    return my_strrchr(str, c) != strrchr(str, c);
}

int test_strpbrk(void)
{
    int failed = 0;
    char *s1, *s2;
    
    // 1. Символы находятся в начале строки
    s1 = "abcxyz", s2 = "acbz";
    failed += comp_strpbrk(s1, s2);

    // 2. Символы находятся в середине строки
    s1 = "abcxyz", s2 = "xcb";
    failed += comp_strpbrk(s1, s2);

    // 3. Символы находятся в конце строки
    s1 = "abcxyz", s2 = "zax";
    failed += comp_strpbrk(s1, s2);

    // 4. Первый символ в str2 находится в конце str1, а последний символ – в начале
    s1 = "abcxyz", s2 = "zca";
    failed += comp_strpbrk(s1, s2);

    // 5. Символы отсутствуют в строке
    s1 = "abcxyz", s2 = "def";
    failed += comp_strpbrk(s1, s2);

    // 6. Строка целиком состоит из искомых символов
    s1 = "eddffd", s2 = "def";
    failed += comp_strpbrk(s1, s2);

    // 7. Пустая строка str1
    s1 = "", s2 = "def";
    failed += comp_strpbrk(s1, s2);

    // 8. Пустая строка str2
    s1 = "abcxyz", s2 = "";
    failed += comp_strpbrk(s1, s2);

    // 9. Обе строки пусты
    s1 = "", s2 = "";
    failed += comp_strpbrk(s1, s2);
    
    return failed;
}

// Возвращает 1 в случае провала
int comp_strpbrk(const char *str1, const char *str2)
{
    return my_strpbrk(str1, str2) != strpbrk(str1, str2);
}

char *my_strpbrk(const char *str1, const char *str2)
{
    const char *res = NULL;
    for (; *str1 && res == NULL; str1++)
    {
        if (strchr(str2, *str1) != NULL)
        {
            res = str1;
        }
    }

    return (char *) res;
}

char *my_strchr(const char *str, int c)
{
    const char *res = NULL;
    for (; *str && res == NULL; str++)
    {
        if (*str == c)
        {
            res = str;
        }
    }

    // Check the last symbol
    if (res == NULL && *str == c)
    {
        res = str;
    }

    return (char *) res;
}

char *my_strrchr(const char *str, int c)
{
    const char *beg = str;
    for (; *str; str++);

    const char *res = NULL;
    for (; (str + 1) != beg && res == NULL; str--)
    {
        if (*str == c)
        {
            res = str;
        }
    }

    return (char *) res;
}
