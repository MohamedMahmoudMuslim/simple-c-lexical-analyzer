#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexical.h"

int main (void)
{
    // A large enough buffer to hold the source code.
    char code_buffer[2048];
    
    printf("--- Test Case 1 ---\n");
    read_code(code_buffer, "test_code1.c");
    printf("Tokenizing code: %s\n", code_buffer);
    tokenizer(code_buffer);
    
    printf("\n--- Test Case 2 ---\n");
    read_code(code_buffer, "test_code2.c");
    printf("Tokenizing code: %s\n", code_buffer);
    tokenizer(code_buffer);
    
    return 0;
}

/* --- Function Implementations (Definitions) --- */

int length_of_str(char *str)
{
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

int compare_str(char *str1, char *str2)
{
    return strcmp(str1, str2) == 0;
}

char *substring(char *src_str, int left, int right)
{
    int len = right - left + 1;
    char *dest_str = (char *)malloc(sizeof(char) * (len + 1));
    if (dest_str == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        dest_str[i] = src_str[left + i];
    }
    dest_str[len] = '\0';
    return dest_str;
}

int is_operator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '%' || ch == '=' ||
        ch == '>' || ch == '<' || ch == '!') {
        return 1;
    }
    return 0;
}

int is_delimiter(char ch)
{
    if (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r' ||
        ch == ';' || ch == ',' || ch == '(' || ch == ')' || 
        ch == '{' || ch == '}' || ch == '[' || ch == ']' ||
        ch == '#') { // We also need to handle '#' for preprocessor directives
        return 1;
    }
    if (is_operator(ch)) {
        return 1;
    }
    return 0;
}

int is_keyword(char *str)
{
    if (compare_str(str, "auto") || compare_str(str, "break") ||
        compare_str(str, "case") || compare_str(str, "char") ||
        compare_str(str, "const") || compare_str(str, "continue") ||
        compare_str(str, "default") || compare_str(str, "do") ||
        compare_str(str, "double") || compare_str(str, "else") ||
        compare_str(str, "enum") || compare_str(str, "extern") ||
        compare_str(str, "float") || compare_str(str, "for") ||
        compare_str(str, "goto") || compare_str(str, "if") ||
        compare_str(str, "int") || compare_str(str, "long") ||
        compare_str(str, "register") || compare_str(str, "return") ||
        compare_str(str, "short") || compare_str(str, "signed") ||
        compare_str(str, "sizeof") || compare_str(str, "static") ||
        compare_str(str, "struct") || compare_str(str, "switch") ||
        compare_str(str, "typedef") || compare_str(str, "union") ||
        compare_str(str, "unsigned") || compare_str(str, "void") ||
        compare_str(str, "volatile") || compare_str(str, "while"))
    {
       return 1;
    }
    return 0;
}

int is_valid_identifier(char *str)
{
    if (str == NULL || str[0] == '\0') {
        return 0;
    }
    if (!isalpha(str[0]) && str[0] != '_') {
        return 0;
    }
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return 0;
        }
    }
    if (is_keyword(str)) {
        return 0;
    }
    return 1;
}

int is_integer(char *str)
{
    int len = length_of_str(str);
    if (len == 0) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

int is_real_number(char *str)
{
    int decimal_flag = 0;
    int len = length_of_str(str);
    if (len == 0) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            if (decimal_flag) {
                return 0;
            }
            decimal_flag = 1;
        } else if (!isdigit(str[i])) {
            return 0;
        }
    }
    if (len == 1 && decimal_flag == 1) {
        return 0;
    }
    return decimal_flag;
}

int tokenizer (char *str)
{
    int left = 0, right = 0;
    int len = length_of_str(str);

    while (right <= len) {
        // Skip over leading whitespace
        while (str[left] == ' ' || str[left] == '\n' || str[left] == '\t' || str[left] == '\r') {
            left++;
        }
        right = left;

        // Find the end of the next token
        while (right <= len && !is_delimiter(str[right]) && str[right] != '\0') {
            right++;
        }

        // Process the token we just found
        if (left < right) {
            char *token = substring(str, left, right - 1);
            if (is_keyword(token)) {
                printf("Keyword: %s\n", token);
            } else if (is_valid_identifier(token)) {
                printf("Identifier: %s\n", token);
            } else if (is_integer(token)) {
                printf("Integer: %s\n", token);
            } else if (is_real_number(token)) {
                printf("Real Number: %s\n", token);
            } else {
                printf("Unknown Token: %s\n", token);
            }
            free(token);
        }

        // Process the delimiter itself (if it exists)
        if (right <= len && is_delimiter(str[right])) {
            if (str[right] != ' ' && str[right] != '\n' && str[right] != '\t' && str[right] != '\r' && str[right] != '\0') {
                 // Check for multi-character operators here
                if ((str[right] == '=' && str[right+1] == '=') ||
                    (str[right] == '>' && str[right+1] == '=') ||
                    (str[right] == '<' && str[right+1] == '=') ||
                    (str[right] == '!' && str[right+1] == '=')) {
                    char *op_token = substring(str, right, right + 1);
                    printf("Operator: %s\n", op_token);
                    free(op_token);
                    right++; // Skip the second character
                } else {
                    // It's a single-character delimiter
                    char *delim_token = substring(str, right, right);
                    if (is_operator(delim_token[0])) {
                        printf("Operator: %s\n", delim_token);
                    } else {
                        printf("Delimiter: %s\n", delim_token);
                    }
                    free(delim_token);
                }
            }
            left = right + 1;
        }
        right++;
    }
    return 0;
}


void read_code(char *code, const char *src_file_name)
{
    FILE* src_file = NULL;
    if((src_file = fopen(src_file_name, "r")) != NULL)
    {
        // Set the first character to null terminator to start with an empty string
        code[0] = '\0'; 
        int len = 0;
        while(fgets(code + len, 2048 - len, src_file) != NULL)
        {
            len = length_of_str(code);
        }
        fclose(src_file);

        // Replace all newlines with spaces for single-line tokenization
        int i = 0;
        while(code[i] != '\0')
        {
            if(code[i] == '\n')
            {
                code[i] = ' ';
            }
            i++;
        }
    } else {
        perror("Error opening file");
    }
}
