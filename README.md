# Agenda-Buffer-

# 📋 Gerenciador de Pessoas em C

Este é um simples sistema de gerenciamento de registros de pessoas, implementado em C, com armazenamento em memória dinâmica (`malloc`/`realloc`). O sistema permite **adicionar**, **listar**, **buscar** e **remover** pessoas utilizando ponteiros e manipulação direta de memória.

## Funcionalidades

- Adicionar novo registro de pessoa (nome, idade, e-mail)
- Listar todas as pessoas cadastradas
- Remover uma pessoa pelo nome
- Buscar uma pessoa pelo nome
- Gerenciamento dinâmico de memória com realocação
- Interface via terminal

## Estrutura dos Dados

Cada pessoa é armazenada em uma área contínua de memória alocada dinamicamente.

### Exemplo

Interaja com o menu inicialmente:
```shell
Menu:
1. Adicionar Pessoa
2. Listar Pessoas
3. Remover Pessoa
4. Buscar Pessoa
5. Sair
Escolha uma opção: 
```

teste 1 - adiciona e lista as pessoas na agenda:
```shell
Escolha uma opção: 1
Nome: Alice
Idade: 25
Email: alice@email.com

Menu:
Escolha uma opção: 2

Lista de Pessoas:
Nome: Alice
Idade: 25
Email: alice@email.com
```
