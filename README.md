# C-Password-Generator

![Language](https://img.shields.io/badge/language-C-blue?style=flat-square&logo=c)
![License](https://img.shields.io/badge/license-MIT-green?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey?style=flat-square)

- Gerador de senhas simples escrito em C. Gera senhas aleatórias, calcula a entropia usando a entropia de shannon e classifica a força da senha.

## Compilação

- Primeiro, escolha uma versão.

- password_generator: A padrão, usa a função rand() da linguagem C para escolher os caracteres. Menos seguro criptograficamente.
- password_generator_urandom: Usa o /dev/urandom para escolher os caracteres. Mais seguro criptograficamente.
- Futuramente, irei implementar Rejection Sampling.

```bash
gcc password_generator.c -o password_generator -lm

# Ou...

gcc password_generator_urandom.c -o password_generator_urandom -lm
```

-  A flag -lm é usada pra vincular a libm, usada pela função log2() no cálculo de entropia

## Uso

```bash
./password_generator
```

- Exemplo de uso e saida:

```
Tamanho da Senha (INT): 20
Senha Gerada: Mve(LyF4+x=:ReiP3x@l
Comprimento: 20 Caracteres
Entropia: 82.44 bits
Segurança da senha: Forte
```

## Entropia de Shannon

- (Aconselho ler mais sobre isso depois caso queira ir a fundo)
- A força da senha é medida em bits de entropia, calculada com a fórmula de Shannon aplicada a distribuição real dos caracteres da senha gerada:

$$H = -\sum p(c) \cdot \log_2(p(c))$$

- `H` = entropia total (em bits)
- `p(c)` = proporção de ocorrências do caractere `c` na senha

- Ao considerar a frequência real de cada caractere, reflete a distribuição efetiva da senha, nao apenas o tamanho do conjunto de caracteres possíveis, dando um resultado mais preciso

- Nota: Quanto maior a entropia, mais imprevisível é a senha e mais difícil de ser quebrada por força bruta.
- Os critérios de força da senha com base em entropia estão na função `passwordSafety`

## Privacidade

- Este programa não armazena, registra ou transmite nenhuma senha gerada, tudo ocorre em memória durante a execução, ao encerrar o programa, a senha deixa de existir

## Licença

- Distribuído sob a licença MIT. Consulte o arquivo [`LICENSE.md`](./LICENSE.md) para mais detalhes.
