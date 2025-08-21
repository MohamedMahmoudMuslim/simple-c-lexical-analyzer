/* --- Function Prototypes (Declarations) --- */
int length_of_str(char *str);
int compare_str(char *str1, char *str2);
char *substring(char *str, int left, int right);
int is_operator(char ch);
int is_delimiter(char ch);
int is_valid_identifier(char *str);
int is_keyword(char *str);
int is_integer(char *str);
int is_real_number(char *str);
int tokenizer(char *str);
void read_code(char *code, const char *src_file_name);