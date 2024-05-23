#include <stdio.h>
#include <ctype.h>

void encrypt(char text[100] , int key){
    char ch;
    for (int i = 0; text[i] != '\0'; i++) {
        ch = text[i];
        if (isalnum(ch)) {
            if (islower(ch))
                ch = (ch - 'a' + key) % 26 + 'a';
            if (isupper(ch))
                ch = (ch - 'A' + key) % 26 + 'A';
        }
        text[i] = ch;
    }
}

void decrypt(char text[100], int key){
    encrypt(text,26-key);
}

int main() {
    char text[100], ch;
    int key;
    printf("Enter the text to encode: \n");
    fgets(text, 100, stdin);
    printf("Enter the key: \n");
    scanf("%d", & key);

    encrypt(text,key);
    printf("Encrypted message: %s\n", text);
    
    decrypt(text,key);
    printf("Decrypted message: %s\n" ,text);
}

