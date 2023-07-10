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
// De acordo o diagrama, é possível ver que apenas o Hash é criptografado com a chave K.
// ATENÇÃO: escreva apenas em uma linha a mensagem que irá ser
//          passada para o cliente 2, no arquivo mensagem.txt

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
  char filenameWithHash[] = "msgCryptoHash.txt";
  unsigned int hash;

  printf("----[ CLIENTE 2 ]----\n");
  printf("   -obs: o arquivo foi usado para simular comunicacao\n");

  // Abrir o arquivo, pegar o hash criptografado e descriptografar
  file = fopen(filenameWithHash, "r");
  if (file == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return 1;
  }

  fgets(message, 100, file);
  message[strcspn(message, "\n")] = '\0';
  
  fgets(encryptedHash, 100, file);
  encryptedHash[strcspn(encryptedHash, "\n")] = '\0';
  
  fclose(file);

  printf("Mensagem que chegou: %s\n", message);

  // Calculando o hash da frase que chegou
  hash = calculateHash(message);
  printf("Hash da mensagem: %d\n", hash);

  int messageLen = strlen(message);
  int hashLen = strlen(encryptedHash);

  printf("Hash criptografado extraído: %s\n", encryptedHash);

  // Descriptografar o hash criptografado
  decrypt(encryptedHash);
  printf("Hash descriptografado: %s\n\n", encryptedHash);
  
  if(atoi(encryptedHash) == hash){
    printf("[ OK ] Hash criptografado que chegou é igual ao hash da frase, o que garante a autenticação\n");
  }else{
    printf("[ ERR ] Algo deu errado, hashes diferem. (tente colocar a frase em apenas uma linha no mensagem.txt)\n");
  }

  return 0;
}
