#include "list.h"
#include "numbers_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ./app.exe FILE_1 FILE_2 FILE_OUT
//      FILE_1      –   первый список
//      FILE_2      –   второй список
//      FILE_OUT    –   выход
//
//      1. склеить списки
//      2. отсортировать
//      3. переставить первый элемент в конец
//      4. записать в выходной файл
//
// ./app.exe f VALUE FILE_IN FILE_OUT
//
//      1. найти элемент списка
//      2. записать в выходной файл элементы после него

#define OK              0
#define ERR_ARGS        1
#define ERR_FILE_OPEN   2
#define ERR_FILE_READ   3
#define ERR_NO_RESULT   4
#define ERR_MEM         5

int numbers_find_after_value(node_t **list_result, FILE *in_file, int value);
int numbers_transform(node_t **list_result, FILE *fst_in_file, FILE *snd_in_file);
void file_close(FILE *f);

int main(int argc, char **argv)
{
    int err = OK;

    int value;
    node_t *result = NULL;
    FILE *out_file = NULL;

    if (argc == 5 && !strcmp(argv[1], "f") && read_int_str(&value, argv[2]))
    {
        FILE *in_file = fopen(argv[3], "r");
        out_file = fopen(argv[4], "w");

        if (!in_file || !out_file)
        {
            err = ERR_FILE_OPEN;
        }
        else
        {
            err = numbers_find_after_value(&result, in_file, value);
        }

        file_close(in_file);
    }
    else if (argc == 4)
    {
        FILE *fst_in_file = fopen(argv[1], "r");
        FILE *snd_in_file = fopen(argv[2], "r");
        out_file = fopen(argv[3], "w");

        if (!fst_in_file || !snd_in_file || !out_file)
        {
            err = ERR_FILE_OPEN;
        }
        else
        {
            err = numbers_transform(&result, fst_in_file, snd_in_file);
        }

        file_close(fst_in_file);
        file_close(snd_in_file);
    }
    else
    {
        err = ERR_ARGS;
    }

    if (!err)
    {
        print_num_list_file(out_file, result);
    }

    file_close(out_file);
    list_free(result, free);

    return err;
}

int numbers_find_after_value(node_t **list_result, FILE *in_file, int value)
{
    int err = OK;

    node_t *num_list = read_num_list_file(in_file);

    if (!num_list)
    {
        err = ERR_FILE_READ;
    }
    else
    {
        node_t *nums_after_value = node_get_next(find(num_list, &value, numbers_comparator));
        if (!nums_after_value)
        {
            list_free(num_list, free);
            err = ERR_NO_RESULT;
        }
        else
        {
            // Trim list to avoid memleak
            while (num_list != nums_after_value)
            {
                free(pop_front(&num_list));
            }

            list_free(*list_result, free);
            *list_result = nums_after_value;
        }
    }

    return err;
}

int numbers_transform(node_t **list_result, FILE *fst_in_file, FILE *snd_in_file)
{
    int err = OK;

    node_t *first_nums = read_num_list_file(fst_in_file);
    node_t *second_nums = read_num_list_file(snd_in_file);

    if (!first_nums || !second_nums)
    {
        list_free(first_nums, free);
        list_free(second_nums, free);
        err = ERR_FILE_READ;
    }
    else
    {
        append(&first_nums, &second_nums);
        first_nums = sort(first_nums, numbers_comparator);
        node_t *first_node = node_create(pop_front(&first_nums));

        if (!first_node)
        {
            err = ERR_MEM;
            list_free(first_nums, free);
        }
        else
        {
            append(&first_nums, &first_node);

            list_free(*list_result, free);
            *list_result = first_nums;
        }
    }

    return err;
}

void file_close(FILE *f)
{
    if (f)
    {
        fclose(f);
    }
}
