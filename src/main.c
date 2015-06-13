#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int randint(int min_num, int max_num)
{
    int result = 0;

    result = (rand()%((max_num+1)-min_num))+min_num;
    return result;
}

char *crypt(char *str)
{
    size_t length = strlen(str);
    size_t final_length = length * 2;

    unsigned char f_char = str[0];
    unsigned char l_char = str[length-1]+1;
    unsigned int middle_chars = 1;
    
    int i;
    for (i = 1; i < length-1; i++) {
        middle_chars *= str[i]+i;
    }

    char *final = malloc(final_length+1);// * sizeof(char));    
    for (i = 0; i < final_length+1; i++) {
        final[i] = ' ';
    }    

    srand(length * (l_char + f_char + middle_chars));
    
    int choice;
    final_length = strlen(final);
    for (i = 0; i < final_length; i++) {
        choice = randint(1,3);        
        do {
            switch (choice) {
            case 1:
                final[i] = randint(48,57);
                break;
            case 2:
                final[i] = randint(65,90);
                break;
            case 3:
                final[i] = randint(97,122);
                break;
            }
        } while (final[i] < 48 || (final[i] > 57 && final[i] < 65) ||
              (final[i] > 90 && final[i] < 97));
    }

    return final;
}

int main(int argc, char* argv[])
{
    char *arg = (argc >= 2) ? argv[1] : "Hello World!";

    char *crypted = crypt(arg);

    printf("%s\n", crypted);   

    free(crypted);

    return 0;
}

