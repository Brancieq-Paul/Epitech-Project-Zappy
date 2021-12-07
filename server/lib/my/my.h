/*
** EPITECH PROJECT, 2019
** Pushswap
** File description:
** Header file for libmy.a
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdbool.h>

    char *my_remove_whitespace(char *str);
    char *my_replace_char(char *str, char find, char replace);
    int rand_between_two_value(int lower, int upper);
    bool my_str_isnum_pos(char const *str);
    char *my_str_toupper(char *str);
    char *my_strdupcat(char const *s1, char const *s2);
    char *my_int_to_strnum(int nb);
    unsigned int my_intlen(int nb);
    char *my_revstr(char *str);
    char **get_filenames(char const *dir_path);
    char *get_file_buffer(char const *filepath);
    char **get_file_lines(char const *pathname);
    unsigned int get_file_size(char const *filepath);
    int get_nb_files_in_dir(char const *pathname);
    char **my_str_to_word_array(char const *str, char const sep);
    unsigned int my_count_until_sep(char const *str, char const sep);
    unsigned int my_count_char(char const *str, char const to_count);
    char *remove_before_sep(char *str, char sep);
    char *my_sdup(int nb_str, ...);
    char *my_strarr_to_str(char **args, const char *sep);
    char **add_str_to_array(char **array, char *str);

#endif
