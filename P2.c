#include<stdio.h>
#include<string.h>
#include<ctype.h>
char encrypt(char ch, char key[]) {
  if (isalpha(ch)) {
    if (islower(ch))
      return tolower(key[ch - 'a']);
    else
      return key[ch - 'A'];
  } else {
    return ch;
  }
}

char decrypt(char ch, char key[]) {
  if (isalpha(ch)) {
    for (int i = 0; i < 26; i++) {
      if (tolower(key[i]) == tolower(ch)) {
        if (islower(ch))
          return 'a' + i;
        else
          return 'A' + i;
      }
    }
    return ch; // If character not found in key, return unchanged
  } else {
    return ch;
  }
}

void mono_cipher(char * input, char * output, char key[], int encrypt_flag) {
  int length = strlen(input);
  for (int i = 0; i < length; i++) {
    if (encrypt_flag)
      output[i] = encrypt(input[i], key);
    else
      output[i] = decrypt(input[i], key);
  }
  output[length] = '\0'; // Null-terminate the string
}

int main() {
  char plaintext[100];
  printf("Enter the plaintext: ");
  fgets(plaintext, 100, stdin);

  char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
  char ciphertext[strlen(plaintext) + 1];
  char decryptedtext[strlen(plaintext) + 1];

  mono_cipher(plaintext, ciphertext, key, 1); // Encrypt
  printf("Encrypted text: %s", ciphertext);

  mono_cipher(ciphertext, decryptedtext, key, 0); // Decrypt
  printf("Decrypted text: %s", decryptedtext);

  return 0;
}