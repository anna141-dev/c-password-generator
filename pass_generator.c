/**
 * Gerador e avaliador de senhas escrito em c.
 *
 * Dev: Anna
 * Github: https://github.com/anna141-dev
 * Repo: c-password-generator
 *
 * Este software está sob licença MIT.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

const char POSSIBLE_CHARS[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    "1234567890!@#$%&*()-_=+,.;:/?@";

char* generatePassword(int length);
double shannonEntropy(const char* password);
void passwordSafety(double entropy);

int main() {
  int length;

  printf("Tamanho da Senha (INT): ");
  scanf("%d", &length);

  char *password = generatePassword(length);
  double entropy = shannonEntropy(password);

  if (!password) {
    fprintf(stderr, "Erro ao alocar memória.\n");
    return 1;
  }

  printf("Senha Gerada: %s\n", password);
  printf("Comprimento: %d Caracteres\n", length);
  printf("Entropia: %.2f bits\n", entropy);
  passwordSafety(entropy);

  free(password);

  return 0;
}

/**
 * Gera a senha, escolhe um caractere "aleatorio" no conjunto de
 * caracteres possiveis e adiciona a senha num range de length
 */
char* generatePassword(int length) {
  srand(time(NULL));

  int num_chars = sizeof(POSSIBLE_CHARS) - 1;

  char *password = malloc((length + 1) * sizeof(char));
  if (!password) return NULL;

  for (int i = 0; i < length; i++) {
    password[i] = POSSIBLE_CHARS[rand() % num_chars];
  }
  password[length] = 0;

  return password;
}

/**
 * Calcula a entropia da senha com a entropia de shannon:
 * h = -Σ p(c) . log₂(p(c))
 *
 * Onde p(c) é a proporção de cada caractere único na senha
 */

double shannonEntropy(const char* password) {
  int length = strlen(password);
  if (length == 0) return 0.0;

  // conta a frequencia de cada byte possivel
  char freq[256] = {0};
  for (int i = 0; i < length; i++) {
    freq[(unsigned char)password[i]]++;
  }

  double entropy = 0.0;
  for (int i = 0; i < 256; i++) {
    if (freq[i] == 0) continue;
    double p = (double)freq[i] / length;
    entropy -= p * log2(p);
  }

  return entropy * length;
}
      
/**
 * Exibe a segurança da senha baseada em entropia
 */
void passwordSafety(double entropy) {
  const char* safety;

  if (entropy < 28.0) safety = "Muito Fraca";
  else if (entropy <= 35.0) safety = "Fraca";
  else if (entropy <= 59.0) safety = "Razoável";
  else if (entropy <= 127.0) safety = "Forte";
  else safety = "Muito Forte";

  printf("Segurança da senha: %s\n", safety);
}
