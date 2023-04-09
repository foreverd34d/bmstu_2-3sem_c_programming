#ifndef STUD_H
#define STUD_H

#include <stdio.h>
#include <stdbool.h>

#define SURNAME_LEN 25
#define NAME_LEN 10
#define GRADES_AMOUNT 4

#define NO_ARG_ERR 53
#define FILE_ERR 53
#define UNKNOWN_KEY_ERR 53

typedef struct student_t
{
    char surname[SURNAME_LEN + 1];
    char name[NAME_LEN + 1];
    unsigned long grades[GRADES_AMOUNT];
} student_t;

student_t get_student_by_pos(FILE *f, long pos);
void set_student_by_pos(FILE *f, long pos, student_t st);
void swap_positions(FILE *f, long pos1, long pos2);

int compare_by_name(student_t a, student_t b);
int compare_by_surname(student_t a, student_t b);
void sort_comp(FILE *f, int comparator(student_t, student_t));
void sort_students(FILE *f);
void print_students(FILE *f);

bool strbegins(char *str, char *substr);
void find_students(FILE *from, FILE *to, char *substr);

double avgrade(student_t *st);
double avgrade_average(FILE *f);
void delete_students(FILE *f);

#endif // !STUD_H
