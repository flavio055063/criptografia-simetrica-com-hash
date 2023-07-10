////////////////////////////////////////////////////////
//                                                    //
//    Flávio Augusto Aló Torres - 2020030477          //
//    Ciência da computação - UNIFEI                  //
//    Trabalho 03                                     //
//    Implementando Message Authentication Code       //
//                                                    //
////////////////////////////////////////////////////////

// O passo a passo desse algoritmo pode ser observado no item b)
// disponível no slide 11 disponibilizado. Também é possível
// ver no diagrama.png aqui.
// é possível ver que apenas o Hash é criptografado com a chave K.
// A mensagem em si fica em texto aberto, de acordo ao diagrama.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY "minhachaveK"

void encrypt(char *message) {
  int i;
  int keyLen = strlen(KEY);
  int msgLen = strlen(message);

  for (i = 0; i < msgLen; i++) {
    message[i] = message[i] ^ KEY[i % keyLen];
  }
}

void decrypt(char *message) { encrypt(message); }

unsigned int calculateHash(const char *message) {
  unsigned int hash = 0;
  int len = strlen(message);

  for (int i = 0; i < len; i++) {
    hash += message[i];
  }

  return hash;
}

int main() {
  FILE *file;
  char message[100];
  char encryptedHash[100];
  char filename[] = "mensagem.txt";
  char filenameWithHash[] = "msgCryptoHash.txt";
  unsigned int hash;

  // Passo 1: Ler a frase do arquivo
  file = fopen(filename, "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  fgets(message, sizeof(message), file);
  fclose(file);

  printf("----[ CLIENTE 1 ]----\n");
  printf("Mensagem original: %s\n", message);

  // Passo 2: Calcular o hash da frase
  hash = calculateHash(message);

  printf("Hash da mensagem: %u\n", hash);

  // Passo 3: Criptografar o hash
  sprintf(encryptedHash, "%u", hash);
  encrypt(encryptedHash);

  printf("Hash criptografado com chave K: %s\n", encryptedHash);

  // Passo 4: Concatenar o hash criptografado à frase e guardar em arquivo
  file = fopen(filenameWithHash, "w");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  fprintf(file, "%s\n%s", message, encryptedHash);
  fclose(file);

  printf("Mensagem + Hash criptografado salvo no arquivo: %s\n\n",
         filenameWithHash);

  return 0;
}
