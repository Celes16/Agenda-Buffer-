#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 50  // Tamanho fixo para o nome
#define TAM_IDADE 4  // Tamanho fixo para a idade
#define TAM_EMAIL 50  // Tamanho fixo para o email
#define TAM_PESSOA (TAM_NOME + TAM_IDADE + TAM_EMAIL)  // Tamanho total

void *pbuffer = NULL;  // Ponteiro para a memória alocada
size_t tamanho_atual = 0;  // Tamanho atual do buffer
size_t num_registros = 0;  // Número de registros armazenados

// Inicializa o buffer com um malloc
void inicializar_buffer() {
    if (!pbuffer) { //Se pbuffer ainda não foi alocado
        pbuffer = malloc(TAM_PESSOA); //fazemos a alocação inicial. 
        if (!pbuffer) {
            printf("Erro ao alocar memória.\n"); //Se a alocação falhar, então reproduzimos uma mensagem de erro e encerramos o programa.
            exit(1);
        }
        tamanho_atual = TAM_PESSOA;
    }
}

// Adicionar pessoa
void adicionar_pessoa() {

    if (num_registros * TAM_PESSOA >= tamanho_atual) {   //Se o número de registros multiplicado pelo tamanho de uma pessoa for maior ou igual ao tamanho atual,
        void *novo_fim = realloc(pbuffer, tamanho_atual + TAM_PESSOA); // chamamos realloc para aumentar o buffer. 
        if (!novo_fim) {
            printf("Erro ao realocar memória.\n"); // Se a realocação falhar, exibimos uma mensagem de erro.
            return;
        }
        pbuffer = novo_fim;
        tamanho_atual += TAM_PESSOA;
    }

    char *ptr_nome = (char *)pbuffer + (num_registros * TAM_PESSOA); // A seguir, obtemos o ponteiro para o nome da nova pessoa. 

    printf("Nome: ");  
    fgets(ptr_nome, TAM_NOME, stdin); // função para ler a entrada do teclado, do nome inserido pelo usuario e armazenar na variável ptr_nome.
    ptr_nome[strcspn(ptr_nome, "\n")] = 0;  // Remove a nova linha que é adicionada ao final da string quando o usuário pressiona Enter.

    int *ptr_idade = (int *)(ptr_nome + TAM_NOME); //declara um ponteiro ptr_idade que aponta para a posição na memória onde a idade será armazenada.

    printf("Idade: ");
    scanf("%d", ptr_idade);
    while (getchar() != '\n');  

    char *ptr_email = (char *)(ptr_idade + 1);

    printf("Email: ");
    fgets(ptr_email, TAM_EMAIL, stdin);
    ptr_email[strcspn(ptr_email, "\n")] = 0;  

    num_registros++;  // Incrementa o número de registros
}

// Função para buscar um registro pelo nome
void *buscar_registro(char *nome_busca) {
    char *ptr_atual = (char *)pbuffer;  //ptr_atual é um ponteiro que começa apontando para o início do buffer pbuffer, que contém todos os registros de pessoas. 

    for (size_t i = 0; i < num_registros; i++) {
        //Este loop itera sobre todos os registros armazenados no buffer.
        char *ptr_nome = ptr_atual; //ptr_nome é definido como o ponteiro atual. Isso significa que ptr_nome agora aponta para o início do registro atual que estamos examinando.

        // Compara byte por byte até encontrar a correspondência ou até o final do nome
        if (strcmp(ptr_nome, nome_busca) == 0) {  
            return ptr_atual;  
        }

        // Se o nome não for encontrado, movemos o ponteiro ptr_atual para o próximo registro.
        ptr_atual += TAM_PESSOA;
    }

    return NULL;  // Não encontrou o nome
}

// Remover pessoa
void remover_pessoa() {
    char nome_busca[TAM_NOME];  //Declara um vetor de caracteres nome_busca com tamanho TAM_NOME, que armazenará o nome da pessoa a ser removida.
    printf("Digite o nome da pessoa que deseja remover: "); 
    fgets(nome_busca, TAM_NOME, stdin); //Lê a entrada do usuário e armazena no vetor nome_busca
    nome_busca[strcspn(nome_busca, "\n")] = 0;  //encontra a posição do caractere '\n' (nova linha) dentro de nome_busca e o remove, para evitar problemas ao comparar nomes.


    void *registro_remover = buscar_registro(nome_busca); //Chama a função buscar_registro(nome_busca), que provavelmente retorna um ponteiro para o registro da pessoa se ela existir, ou NULL caso contrário.

    if (!registro_remover) {
        printf("Pessoa não encontrada.\n");
        return;
    }

    char *ptr_fim = (char *)pbuffer + (num_registros * TAM_PESSOA); // recalcula a posição do fim do buffer, 
    // Move os registros após o removido para o início
    size_t tamanho_remover = (char *)ptr_fim - (char *)registro_remover - TAM_PESSOA;


    memmove(registro_remover, (char *)registro_remover + TAM_PESSOA, tamanho_remover);
    //memmove(destino, origem, tamanho) copia os bytes da origem para o destino, lidando corretamente com sobreposição de memória.

    num_registros--;  // Decrementa o número de registros

    if (num_registros > 0 && num_registros * TAM_PESSOA < tamanho_atual - TAM_PESSOA) {


        void *novo_buffer = realloc(pbuffer, num_registros * TAM_PESSOA);
        if (novo_buffer) {
            pbuffer = novo_buffer;
            tamanho_atual = num_registros * TAM_PESSOA;
        } else {
            printf("Erro ao realocar memória.\n");
        }
    }
}

// Listar pessoas
void listar_pessoas() {
    if (num_registros == 0) {
        printf("Nenhuma pessoa cadastrada.\n");
        return;
    }

    printf("\nLista de Pessoas:\n");
    char *ptr_atual = (char *)pbuffer;  // Cast para char*

    for (size_t i = 0; i < num_registros; i++) {
        char *ptr_nome = ptr_atual;
        int *ptr_idade = (int *)(ptr_nome + TAM_NOME);
        char *ptr_email = (char *)(ptr_idade + 1);

        printf("Nome: %s\nIdade: %d\nEmail: %s\n", ptr_nome, *ptr_idade, ptr_email);

        // Move para o próximo registro
        ptr_atual += TAM_PESSOA;
    }
}

// Liberar memória
void liberar_memoria() {
    free(pbuffer);
    pbuffer = NULL;
    tamanho_atual = 0;
    num_registros = 0;
}

int main() {
    char opcao;

    do {
        printf("\nMenu:\n1. Adicionar Pessoa\n2. Listar Pessoas\n3. Remover Pessoa\n4. Buscar Pessoa\n5. Sair\nEscolha uma opção: ");
        opcao = getchar();
        while (getchar() != '\n');  

        if (opcao == '1') adicionar_pessoa();
        else if (opcao == '2') listar_pessoas();
        else if (opcao == '3') remover_pessoa();
        else if (opcao == '4') {
            char nome_busca[TAM_NOME];
            printf("Digite o nome da pessoa para buscar: ");
            fgets(nome_busca, TAM_NOME, stdin);
            nome_busca[strcspn(nome_busca, "\n")] = 0;  // Remove a nova linha
            void *registro = buscar_registro(nome_busca);
            if (registro) {
                char *ptr_nome = (char *)registro;
                int *ptr_idade = (int *)(ptr_nome + TAM_NOME);
                char *ptr_email = (char *)(ptr_idade + 1);
                printf("Pessoa encontrada:\nNome: %s\nIdade: %d\nEmail: %s\n", ptr_nome, *ptr_idade, ptr_email);
            } else {
                printf("Pessoa não encontrada.\n");
            }
        }
        else if (opcao == '5') liberar_memoria();
        else printf("Opção inválida.\n");

    } while (opcao != '5');

    return 0;
}