#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////////////

int randint(int min_num, int max_num)
{
    // Returns a random number between min_num and max_num (inclusive)
    int result = 0;

    result = (rand()%((max_num+1)-min_num))+min_num;
    return result;
}

char *crypt(char *str)
{
    // Returns the crypted result of str

    int i;
    
    // Defines the final length (which will be the length of len(str) * 2 + 1)
    size_t length = strlen(str);
    size_t final_length = length * 2;

    // Defines the first and the last chars to define 
    unsigned char f_char = str[0]*final_length +1;
    unsigned char l_char = str[length-1]*length+1;
    
    // Defines all the middle chars of str (multiplication of all the chars
    // times their position plus their position)
    // middle_chars *= ALL{str[i] * i + i}
    // i being the position of the char
    unsigned int middle_chars = 1;
    for (i = 1; i < length-1; i++) {
        middle_chars *= str[i]*i+i;
    }

    // Allocates the final crypted string
    char *final = malloc(final_length+1);    

    // Defines the seed so that the hash stays the same on the same computer
    srand(length * (l_char + f_char + middle_chars));
    
    // Defines the final string between 0-9, a-z, and A-Z
    int choice;
    for (i = 0; i < final_length+1; i++) {
        choice = randint(1,3);        
        
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

