#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include "stud.h"

/*
 * Universal functions
 */

student_t get_student(FILE *f, long pos)
{
    student_t st;
    fseek(f, pos * sizeof(st), SEEK_SET);
    fread(&st, sizeof(st), 1, f);
    return st;
}

void put_student(FILE *f, long pos, student_t st)
{
    fseek(f, pos * sizeof(st), SEEK_SET);
    fwrite(&st, sizeof(st), 1, f);
}

void swap_positions(FILE *f, long pos1, long pos2)
{
    student_t buf = get_student(f, pos2);
    put_student(f, pos2, get_student(f, pos1));
    put_student(f, pos1, buf);
}


/*
 * Sorting functions
 */

void sort_students(FILE *f)
{
    sort_comp(f, compare_by_name);
    sort_comp(f, compare_by_surname);
}

void sort_comp(FILE *f, int comparator(student_t, student_t))
{
    fseek(f, 0, SEEK_END);
    long end = ftell(f);
    fseek(f, 0, SEEK_SET);
    long beg = ftell(f);

    for (long i = 1; i * (long)sizeof(student_t) < end; i++)
    {
        for (long j = i; j > beg && comparator(get_student(f, j - 1), get_student(f, j)) > 0; j--)
        {
            swap_positions(f, j - 1, j);
        }
    }
}

int compare_by_name(student_t a, student_t b)
{
    return strcmp(a.name, b.name);
}

int compare_by_surname(student_t a, student_t b)
{
    return strcmp(a.surname, b.surname);
}

void print_students(FILE *f)
{
    student_t st;
    while (fread(&st, sizeof(st), 1, f) == 1)
    {
        printf("%s\n", st.surname);
        printf("%s\n", st.name);
        for (int i = 0; i < GRADES_AMOUNT; i++)
        {
            printf("%lu ", st.grades[i]);
        }
        printf("\n");
    }
}


/*
 * Find functions
 */

void find_students(FILE *from, FILE *to, char *substr)
{
    student_t st;
    rewind(from);
    while (fread(&st, sizeof(st), 1, from) == 1)
    {
        if (strbegins(st.surname, substr))
        {
            fwrite(&st, sizeof(st), 1, to);
        }
    }
}


bool strbegins(char *str, char *substr)
{
    int i = 0;
    bool result = true;
    for (; str[i] && substr[i] && result == 1; i++)
    {
        if (str[i] != substr[i])
        {
            result = false;
        }
    }

    if (substr[i] && !str[i])
    {
        result = false;
    }

    return result;
}

/*
 * Delete functions
 */

void delete_students(FILE *f)
{
    student_t st;
    int st_count = 0;
    double grade = avgrade_average(f);

    rewind(f);
    for (int i = 0; fread(&st, sizeof(st), 1, f) == 1; i++)
    {
        if (avgrade(&st) >= grade)
        {
            long current_loc = ftell(f);
            put_student(f, st_count++, st);
            fseek(f, current_loc, SEEK_SET);
        }
    }

    fseek(f, 0, SEEK_SET);
    ftruncate(fileno(f), st_count * sizeof(st));
}

double avgrade(student_t *st)
{
    int i = 0;
    double sum = 0;
    for (; i < GRADES_AMOUNT; i++)
    {
        sum += st->grades[i];
    }
    return sum / i;
}

double avgrade_average(FILE *f)
{
    student_t st;
    int c = 0;
    double sum = 0;

    rewind(f);
    for (; fread(&st, sizeof(st), 1, f) == 1; c++)
    {
        sum += avgrade(&st);
    }

    return sum / c;
}
