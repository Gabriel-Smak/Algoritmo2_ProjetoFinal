/*
             ╔═══════════════════╗
 ╔═══════════║ Projeto Final (C) ║═══════════╗
             ╚═══════════════════╝
  
   * Disciplina: Algoritmos 2.
  
   * Aluno: Gabriel Henrique Smak de Andrade.
  
   * Professor: Paulo Henrique Bueno Lopes.
  
 ╚═══════════════════════════════════════════╝



   ╔════════════════╗
   ║  Bibliotecas:  ║
   ╚════════════════╝*/

    #include <stdio.h>
    #include <string.h>
    #include <windows.h> 
    #include <conio.h>
    #include <ctype.h>
    #include <stdbool.h>

    bool verdadeiro = true;



// ╔═══════════════════╗
// ║  Parametrização:  ║
// ╚═══════════════════╝

//   ╔═══════════════════════╗
//   ║  Tempos de Animação:  ║
//   ╚═══════════════════════╝

        #define Tempo_De_Piscar_Cursor       780
        #define Tempo_De_Piscar_Menu_Adicao  780
        #define Tempo_De_Espera_Animacao     390
        #define Tempo_De_Alerta_Erro         1100
        #define Tempo_Alerta_Rapido          400
        #define Tempo_Alerta_Longo           1200
        #define Tempo_Erro_Extenso           1300
        #define Tempo_Pausa_Sucesso          500
        #define Tempo_Pausa_Menu_Adicao      150



//   ╔═══════════════════════╗
//   ║  Limites de Memória:  ║
//   ╚═══════════════════════╝

        #define Tamanho_Maximo_Do_Telefone   12
        #define Tamanho_Maximo_Do_Nome       48
        #define Tamanho_Maximo_Do_Email      Tamanho_Maximo_Do_Nome



// ╔════════════╗
// ║  Structs:  ║
// ╚════════════╝

    typedef struct PESSOA {

        char     nome[Tamanho_Maximo_Do_Nome];
        char     email[Tamanho_Maximo_Do_Email];
        char     genero[2];
        char     telefone1[Tamanho_Maximo_Do_Telefone];
        char     telefone2[Tamanho_Maximo_Do_Telefone];

    } PESSOA;

    typedef struct CAIXA{

        PESSOA   pessoaRespectiva;
        int      numeroDaCaixa;
        char     tipoDaCaixa;

    }CAIXA;

    typedef struct SETOR {

        char     nomeDoSetor[6];
        int      quantidadeDeCaixasDoSetor;
        CAIXA    *caixasDasPessoasRegistradas;

    } SETOR;



// ╔════════════════╗
// ║  Assinaturas:  ║
// ╚════════════════╝

    void     prepararTerminalParaImpressao();

    void     gotoxy                  (int x, int y);

    CAIXA  * escolherPessoasDoSetor  (int * quantidadeTotalDeCaixas);

    PESSOA   escolherEntrada         (PESSOA pessoa, char caixa);

    int      posicionarEntrada       (char caractereDigitado, int indiceDaEntrada, char definirSituacao, int limiteMaximoDeCaixas);

    char   * lerGeneroNoTerminal     (char * genero, char posicaoDaCaixa, int localizacao);

    char   * lerTelefoneNoTerminal   (char * telefone, char caixa, char posicao, int localizacao);

    char   * lerNomeNoTerminal       (char * nome, char caixa, int localizacao);

    char   * lerEmailNoTerminal      (char * email, char caixa, int localizacao);



// ╔══════════╗
// ║  Cores:  ║
// ╚══════════╝

    #define vermelho        "\033[38;5;1m"
    #define fvermelho       "\033[48;5;1m\033[38;5;0m"
    #define azul            "\033[38;5;69m"
    #define verde           "\033[38;5;84m"
    #define fverde          "\033[38;5;0m\033[48;5;84m"
    #define BRANCO          "\033[97m"



// ╔═════════════════════════════╗
// ║  Trabalhos com o terminal:  ║
// ╚═════════════════════════════╝

    #define cleanT          "\033[1;1H\033[2J\033[3J\033[1;1H"
    #define esmaecer        "\033[2m"
    #define negrito         "\033[1m"
    #define reset           "\033[0m"
    #define inicio          "\033[%dG"
    #define sobe            "\033[%dA"
    #define desce           "\033[%dB"
    #define ande            "\033[%dC"
    #define volte           "\033[%dD"

    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif



//╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


// ╔═════ main ═════╗
     int main() {

        SetConsoleOutputCP(CP_UTF8);
        prepararTerminalParaImpressao();
        printf(cleanT reset);

        SETOR setor;
        strcpy(setor.nomeDoSetor, "GERAL");
        setor.quantidadeDeCaixasDoSetor = 0;

        setor.caixasDasPessoasRegistradas = escolherPessoasDoSetor(&setor.quantidadeDeCaixasDoSetor);

        printf(cleanT reset);


        FILE *arquivo = fopen("Registros.txt", "w");
        if (arquivo != NULL) {
            
            for (int i = 0; i < setor.quantidadeDeCaixasDoSetor; i++) {
                CAIXA  caixaRespectiva = setor.caixasDasPessoasRegistradas[i];
                PESSOA instanciaTemporariaDePessoa = caixaRespectiva.pessoaRespectiva;

                if (instanciaTemporariaDePessoa.nome[0] != EOF && instanciaTemporariaDePessoa.nome[0] != '\0') {
                    fprintf(arquivo, "Número da Caixa: │  %d (%s)\n", caixaRespectiva.numeroDaCaixa, (caixaRespectiva.tipoDaCaixa == 'i') ? "Impar" : "Par");
                    fprintf(arquivo, "Nome:            │  %s\n", instanciaTemporariaDePessoa.nome);
                    fprintf(arquivo, "E-mail:          │  %s\n", (instanciaTemporariaDePessoa.email[0] != EOF && instanciaTemporariaDePessoa.email[0] != '\0') ? instanciaTemporariaDePessoa.email : "N/A");
                    fprintf(arquivo, "Gênero:          │  %s\n", instanciaTemporariaDePessoa.genero[0] == 'M' ? "Masculino" : "Feminino");
                    fprintf(arquivo, "Telefone (1):    │  %s\n", instanciaTemporariaDePessoa.telefone1);
                    
                    if (instanciaTemporariaDePessoa.telefone2[0] != EOF && instanciaTemporariaDePessoa.telefone2[0] != '\0') {
                    fprintf(arquivo, "Telefone (2):    │  %s\n", instanciaTemporariaDePessoa.telefone2);
                    }
                    fprintf(arquivo, "─────────────────┴───────────────────────────────────────────────────\n");
                }
            }
            fclose(arquivo);
            printf(BRANCO "╔═══════════════════════════════════════════════════════╗\n");
            printf(BRANCO "║"reset fverde"               Dados salvos com sucesso!               "reset BRANCO"║\n");
            printf(BRANCO "╚═══════════════════════════════════════════════════════╝\n");
        }

        if (setor.caixasDasPessoasRegistradas != NULL) {
            free(setor.caixasDasPessoasRegistradas);
            setor.caixasDasPessoasRegistradas = NULL;
        }

        printf("\n");

        return 0;
}



// ╔══════ prepararTerminalParaImpressao ═════╗
     void prepararTerminalParaImpressao() {
          SetConsoleOutputCP(CP_UTF8);

          // =========================================================================
          // FIX 1: Desativar o "QuickEdit Mode" para evitar o congelamento da tela
          // =========================================================================
          HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
          DWORD prev_mode;
          if (GetConsoleMode(hInput, &prev_mode)) {
              // Desativa a flag ENABLE_QUICK_EDIT_MODE mantendo as outras intactas
              SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
          }

          // =========================================================================
          // FIX 2: Forçar Tela Cheia (F11 compatível com Windows Terminal moderno)
          // =========================================================================
          // Simula apertar a tecla F11
          keybd_event(VK_F11, 0, 0, 0);
          // Simula soltar a tecla F11
          keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

          // =========================================================================
          // FIX 3: Pausa vital de renderização
          // =========================================================================
          // Aguardamos 500ms para dar tempo do Windows fazer a animação de maximizar.
          // Sem isso, seu código vai chamar GetConsoleScreenBufferInfo() enquanto a
          // tela ainda está crescendo, quebrando todas as suas matrizes e 'gotoxy'.
          Sleep(500);

          HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
          DWORD dwMode = 0;
          if (GetConsoleMode(hOut, &dwMode)) {
              dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // Habilita o ASCII
              SetConsoleMode(hOut, dwMode);
        }
    }



//  ╔════════════ gotoxy ═══════════╗
      void gotoxy(int x, int y) {
         COORD coordenada;
         coordenada.X = x; 
         coordenada.Y = y; 
     
         SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordenada);
     }



// ╔═══════════════════════════════════════════════════ posicionarEntrada ══════════════════════════════════════════════════╗
     int posicionarEntrada(char caractereDigitado, int indiceDaEntrada, char definirSituacao, int limiteMaximoDeCaixas) {
         
         // ==========================================================
         // SITUAÇÃO '5' e '2': MODO FORMULÁRIO INTERNO
         // ==========================================================
         if (definirSituacao == '5') {
             if (caractereDigitado == 72 || caractereDigitado == 75 || caractereDigitado == 15) { 
                 switch (indiceDaEntrada) {
                     case 1: return 5;
                     case 2: return 1;
                     case 3: return 2;
                     case 4: return 3;
                     case 5: return 4;
                 }
             }
             else if (caractereDigitado == 80 || caractereDigitado == 77 || caractereDigitado == 9) { 
                 switch (indiceDaEntrada) {
                     case 1: return 2;
                     case 2: return 3;
                     case 3: return 4;
                     case 4: return 5;
                     case 5: return 1;
                 }
             }
         } 
         else if (definirSituacao == '2') {
             if (caractereDigitado == 72 || caractereDigitado == 75 || caractereDigitado == 15) return 1;
             else if (caractereDigitado == 80 || caractereDigitado == 77 || caractereDigitado == 9) return 2;
         }
         
         // ==========================================================
         // SITUAÇÃO 'C': MODO LINEAR DE CAIXAS (De 1 em 1)
         // ==========================================================
         else if (definirSituacao == 'C') {
             // Cima, Esquerda ou Shift+Tab -> Volta 1 unidade (ex: do 4 para o 3)
             if (caractereDigitado == 72 || caractereDigitado == 75 || caractereDigitado == 15) {
                 return (indiceDaEntrada > 1) ? indiceDaEntrada - 1 : limiteMaximoDeCaixas;
             } 
             // Baixo, Direita ou Tab -> Avança 1 unidade (ex: do 3 para o 4)
             else if (caractereDigitado == 80 || caractereDigitado == 77 || caractereDigitado == 9) {
                 return (indiceDaEntrada < limiteMaximoDeCaixas) ? indiceDaEntrada + 1 : 1;
             }
         }
         
         return indiceDaEntrada;
     }



// ╔══════════════════════ escolherPessoasDoSetor ═════════════════════╗    
     CAIXA * escolherPessoasDoSetor(int * quantidadeTotalDeCaixas) {

        PESSOA *pessoasDoSetor = NULL;
        DWORD   tempoDeInicioDaFuncao = GetTickCount();
        CAIXA  *caixasRegistradas = NULL;

        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int Y_Origem = csbi.dwCursorPosition.Y;

        int     alterarFundo = 0;
        int     localizacao = 1;
        int     quantidadeDeCaixasImpressas = 0;
        int     caixaAtual = 1;

        bool    adicionarCaixa = true;
        char    caractereDigitado = 'i';

        while(1) {
            
            localizacao = (caixaAtual % 2 != 0) ? 1 : 71;

            while (!_kbhit()) {
                DWORD tempoAtualDaFuncao = GetTickCount();

                if (tempoAtualDaFuncao - tempoDeInicioDaFuncao >= Tempo_De_Piscar_Menu_Adicao) {
                    alterarFundo = !alterarFundo;
                    tempoDeInicioDaFuncao = tempoAtualDaFuncao;
                }

                printf(inicio, localizacao);
                int totalLimites = (quantidadeDeCaixasImpressas >= 10) ? 10 : quantidadeDeCaixasImpressas + 1;

                if (caixaAtual == totalLimites && quantidadeDeCaixasImpressas <= 9) {
                    if (alterarFundo) {
                      printf(reset esmaecer verde"╔════════════════════════════════════════════════════════════╗"reset inicio desce, localizacao, 1);
                            printf(esmaecer verde"║                                                            ║"reset inicio desce, localizacao, 1);
                            printf(esmaecer verde"║                              │                             ║"reset inicio desce, localizacao, 1);
                            printf(esmaecer verde"║                           ───┼───                          ║"reset inicio desce, localizacao, 1);
                            printf(esmaecer verde"║                              │                             ║"reset inicio desce, localizacao, 1);
                            printf(esmaecer verde"║                                                            ║"reset inicio desce, localizacao, 1);
                            printf(esmaecer verde"╚════════════════════════════════════════════════════════════╝"reset inicio sobe, localizacao, 6);
                    } else {
                              printf(reset verde"╔════════════════════════════════════════════════════════════╗"reset inicio desce, localizacao, 1);
                                    printf(verde"║                                                            ║"reset inicio desce, localizacao, 1);
                                    printf(verde"║                              │                             ║"reset inicio desce, localizacao, 1);
                                    printf(verde"║                           ───┼───                          ║"reset inicio desce, localizacao, 1);
                                    printf(verde"║                              │                             ║"reset inicio desce, localizacao, 1);
                                    printf(verde"║                                                            ║"reset inicio desce, localizacao, 1);
                                    printf(verde"╚════════════════════════════════════════════════════════════╝"reset inicio sobe, localizacao, 6);
                            }
                } else if(quantidadeDeCaixasImpressas <= 9){
                    if (alterarFundo) {
                       printf(reset BRANCO "╔══════════╦═════════════╦═════════════════╦═════════════════╗" inicio desce, localizacao, 1);
                            printf( BRANCO "║" inicio "║"   inicio  "║"     inicio    "║"    inicio     "║" inicio desce, localizacao + 11, localizacao + 25, localizacao + 43, localizacao + 61, localizacao, 1);
                            printf( BRANCO "╠══════════╬═════════════╩═════════════════╩═════════════════╣" inicio desce, localizacao, 1);
                            printf( BRANCO "║" inicio "║"                                     inicio    "║" inicio desce, localizacao + 11, localizacao + 61, localizacao, 1);
                            printf( BRANCO "╠══════════╬═════════════════════════════════════════════════╣" inicio desce, localizacao, 1);
                            printf( BRANCO "║" inicio "║"                                     inicio    "║" inicio desce, localizacao + 11, localizacao + 61, localizacao, 1);
                            printf( BRANCO "╚══════════╩═════════════════════════════════════════════════╝" inicio sobe reset,  localizacao, 6);
                    } else {
                      printf(reset esmaecer"╔══════════╦═════════════╦═════════════════╦═════════════════╗" inicio desce, localizacao, 1);
                            printf(esmaecer"║" inicio "║"   inicio  "║"     inicio    "║"    inicio     "║" inicio desce, localizacao + 11, localizacao + 25, localizacao + 43, localizacao + 61, localizacao, 1);
                            printf(esmaecer"╠══════════╬═════════════╩═════════════════╩═════════════════╣" inicio desce, localizacao, 1);
                            printf(esmaecer"║" inicio "║"                                     inicio    "║" inicio desce, localizacao + 11, localizacao + 61, localizacao, 1);
                            printf(esmaecer"╠══════════╬═════════════════════════════════════════════════╣" inicio desce, localizacao, 1);
                            printf(esmaecer"║" inicio "║"                                     inicio    "║" inicio desce, localizacao + 11, localizacao + 61, localizacao, 1);
                            printf(esmaecer"╚══════════╩═════════════════════════════════════════════════╝" inicio sobe reset,  localizacao, 6);
                    }
                }

                Sleep(Tempo_Pausa_Menu_Adicao);
            }

                       printf(reset BRANCO "╔══════════╦═════════════╦═════════════════╦═════════════════╗" inicio desce, localizacao, 1);
                            printf( BRANCO "║" inicio "║"   inicio  "║"     inicio    "║"    inicio     "║" inicio desce, localizacao + 11, localizacao + 25, localizacao + 43, localizacao + 61, localizacao, 1);
                            printf( BRANCO "╠══════════╬═════════════╩═════════════════╩═════════════════╣" inicio desce, localizacao, 1);
                            printf( BRANCO "║" inicio "║"                                     inicio    "║" inicio desce, localizacao + 11, localizacao + 61, localizacao, 1);
                            printf( BRANCO "╠══════════╬═════════════════════════════════════════════════╣" inicio desce, localizacao, 1);
                            printf( BRANCO "║" inicio "║"                                     inicio    "║" inicio desce, localizacao + 11, localizacao + 61, localizacao, 1);
                            printf( BRANCO "╚══════════╩═════════════════════════════════════════════════╝" inicio sobe reset,  localizacao, 6);

            caractereDigitado = _getch();

            if (caractereDigitado == 19 || caractereDigitado == 27) {

                if (quantidadeTotalDeCaixas != NULL) {
                    *quantidadeTotalDeCaixas = quantidadeDeCaixasImpressas; 
                }
                break;
            }

            if (caractereDigitado == 9 || caractereDigitado == 27 || caractereDigitado == -32 || caractereDigitado == 224 || caractereDigitado == 0) { 
        
                if(caractereDigitado == -32 || caractereDigitado == 224 || caractereDigitado == 0) {
                    caractereDigitado = _getch();
                } else if (caractereDigitado == 9 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)) {
                    caractereDigitado = 15;
                }
                
                int caixaAntiga = caixaAtual;
                int totalDeCaixas = (quantidadeDeCaixasImpressas >= 10) ? 10 : quantidadeDeCaixasImpressas + 1;
                
                caixaAtual = posicionarEntrada(caractereDigitado, caixaAtual, 'C', totalDeCaixas);
                

                if (caixaAntiga != caixaAtual) {
                    int localizacaoAntiga = (caixaAntiga % 2 != 0) ? 1 : 71;
                    printf(inicio sobe, localizacaoAntiga, 6);

                    int andarAntigo = (caixaAntiga - 1) / 2;
                    int linhaAbsolutaAntiga = Y_Origem + (andarAntigo * 9);
                    gotoxy(0, linhaAbsolutaAntiga);
                    
                    if (caixaAntiga == totalDeCaixas && quantidadeDeCaixasImpressas <= 9) {
                       printf(reset inicio esmaecer verde"╔════════════════════════════════════════════════════════════╗"reset inicio desce, localizacaoAntiga, localizacaoAntiga,1);
                                    printf(esmaecer verde"║                                                            ║"reset inicio desce, localizacaoAntiga, 1);
                                    printf(esmaecer verde"║                              │                             ║"reset inicio desce, localizacaoAntiga, 1);
                                    printf(esmaecer verde"║                           ───┼───                          ║"reset inicio desce, localizacaoAntiga, 1);
                                    printf(esmaecer verde"║                              │                             ║"reset inicio desce, localizacaoAntiga, 1);
                                    printf(esmaecer verde"║                                                            ║"reset inicio desce, localizacaoAntiga, 1);
                                    printf(esmaecer verde"╚════════════════════════════════════════════════════════════╝"reset inicio sobe, localizacaoAntiga, 6);
                    } else {
                            printf(reset inicio BRANCO "╔══════════╦═════════════╦═════════════════╦═════════════════╗" reset inicio desce, localizacaoAntiga, localizacaoAntiga, 1);
                                        printf( BRANCO "║" inicio "║"   inicio  "║"     inicio    "║"    inicio     "║" reset inicio desce, localizacaoAntiga + 11, localizacaoAntiga + 25, localizacaoAntiga + 43, localizacaoAntiga + 61, localizacaoAntiga, 1);
                                        printf( BRANCO "╠══════════╬═════════════╩═════════════════╩═════════════════╣" reset inicio desce, localizacaoAntiga, 1);
                                        printf( BRANCO "║" inicio "║"                                    inicio     "║" reset inicio desce, localizacaoAntiga + 11, localizacaoAntiga + 61, localizacaoAntiga, 1);
                                        printf( BRANCO "╠══════════╬═════════════════════════════════════════════════╣" reset inicio desce, localizacaoAntiga, 1);
                                        printf( BRANCO "║" inicio "║"                                    inicio     "║" reset inicio desce, localizacaoAntiga + 11, localizacaoAntiga + 61, localizacaoAntiga, 1);
                                        printf( BRANCO "╚══════════╩═════════════════════════════════════════════════╝" reset inicio sobe,  localizacaoAntiga, 6);
                    }
                }

                int andarNovo = (caixaAtual - 1) / 2;
                int colunaAbsoluta = (caixaAtual % 2 != 0) ? 0 : 70;
                int linhaAbsoluta = Y_Origem + (andarNovo * 9);
                
                gotoxy(colunaAbsoluta, linhaAbsoluta);
                continue;
            }

            else if (caractereDigitado == 13 || caractereDigitado == '+' || caractereDigitado == 61) {
                
                if (caixaAtual == quantidadeDeCaixasImpressas + 1 || caractereDigitado == '+' || caractereDigitado == 61) {
                    
                    if (quantidadeDeCaixasImpressas >= 10) continue;

                    if (caixaAtual != quantidadeDeCaixasImpressas + 1) {
                        int andarAtual = (caixaAtual - 1) / 2;
                        int linhaAbsolutaAtual = Y_Origem + (andarAtual * 9);
                        gotoxy(0, linhaAbsolutaAtual);
                        
                      printf(reset esmaecer "╔══════════╦═════════════╦═════════════════╦═════════════════╗" reset inicio desce, localizacao, 1);
                            printf(esmaecer "║" inicio "║"   inicio  "║"     inicio    "║"    inicio     "║" reset inicio desce, localizacao + 11, localizacao + 25, localizacao + 43, localizacao + 61, localizacao, 1);
                            printf(esmaecer "╠══════════╬═════════════╩═════════════════╩═════════════════╣" reset inicio desce, localizacao, 1);
                            printf(esmaecer "║" inicio "║"                                    inicio     "║" reset inicio desce, localizacao + 11, localizacao + 61, localizacao, 1);
                            printf(esmaecer "╠══════════╬═════════════════════════════════════════════════╣" reset inicio desce, localizacao, 1);
                            printf(esmaecer "║" inicio "║"                                    inicio     "║" reset inicio desce, localizacao + 11, localizacao + 61, localizacao, 1);
                            printf(esmaecer "╚══════════╩═════════════════════════════════════════════════╝" reset inicio sobe,  localizacao, 6);

                        int andarFinal = (quantidadeDeCaixasImpressas) / 2; 
                        int colunaAbsoluta = ((quantidadeDeCaixasImpressas + 1) % 2 != 0) ? 0 : 70;
                        int linhaAbsoluta = Y_Origem + (andarFinal * 9);
                        gotoxy(colunaAbsoluta, linhaAbsoluta);
                    }

                    quantidadeDeCaixasImpressas++;
                    caixaAtual = quantidadeDeCaixasImpressas;

                    caixasRegistradas = (CAIXA*) realloc(caixasRegistradas, quantidadeDeCaixasImpressas * sizeof(CAIXA));
                    if(caixasRegistradas == NULL) exit(1);
                    
                    localizacao = (caixaAtual % 2 != 0) ? 1 : 71;

                    caixasRegistradas[quantidadeDeCaixasImpressas - 1].numeroDaCaixa = quantidadeDeCaixasImpressas;
                    caixasRegistradas[quantidadeDeCaixasImpressas - 1].tipoDaCaixa = (localizacao == 1) ? 'i' : 'p';
                    
                    caixasRegistradas[quantidadeDeCaixasImpressas - 1].pessoaRespectiva.nome[0]       =  EOF;
                    caixasRegistradas[quantidadeDeCaixasImpressas - 1].pessoaRespectiva.email[0]      =  EOF;
                    caixasRegistradas[quantidadeDeCaixasImpressas - 1].pessoaRespectiva.genero[0]     =  EOF;
                    caixasRegistradas[quantidadeDeCaixasImpressas - 1].pessoaRespectiva.telefone1[0]  =  EOF;
                    caixasRegistradas[quantidadeDeCaixasImpressas - 1].pessoaRespectiva.telefone2[0]  =  EOF;

                    printf(reset inicio BRANCO "╔══════════╦═════════════╦═════════════════╦═════════════════╗" inicio desce, localizacao, localizacao, 1);
                                        printf("║   "azul"%02dº"reset"    ║   "esmaecer"Gênero"reset"    ║   "esmaecer"Telefone (1)"reset"  ║   "esmaecer"Telefone (2)"reset"  ║" inicio desce, quantidadeDeCaixasImpressas, localizacao, 1);
                                        printf("╠══════════╬═════════════╩═════════════════╩═════════════════╣" inicio desce, localizacao, 1);
                                        printf("║   "esmaecer"Nome:"reset"  ║ "esmaecer"-----------------------------------------------"reset" ║" inicio desce, localizacao, 1);
                                        printf("╠══════════╬═════════════════════════════════════════════════╣" inicio desce, localizacao, 1);
                                        printf("║  "esmaecer"E-mail:"reset" ║ "esmaecer"-----------------------------------------------"reset" ║" inicio desce, localizacao, 1);
                                        printf("╚══════════╩═════════════════════════════════════════════════╝" inicio sobe, localizacao, 6);

                    // Posiciona fisicamente o cursor para onde o próximo MENU + será renderizado
                    caixaAtual = (quantidadeDeCaixasImpressas >= 10) ? 10 : quantidadeDeCaixasImpressas + 1;
                    int andarMenu = (caixaAtual - 1) / 2;
                    int colunaMenu = (caixaAtual % 2 != 0) ? 0 : 70;
                    
                    gotoxy(colunaMenu, Y_Origem + (andarMenu * 9));

                    if(quantidadeDeCaixasImpressas <= 6)
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" sobe, 15);
                    
                } 
                else if (caractereDigitado == 13) {
                    printf(desce, 1); 
                    
                    caixasRegistradas[caixaAtual-1].pessoaRespectiva = escolherEntrada(
                        caixasRegistradas[caixaAtual-1].pessoaRespectiva, 
                        caixasRegistradas[caixaAtual-1].tipoDaCaixa);
                    
                    printf(reset); 
                }
            }
        } 

        return caixasRegistradas;
    }



// ╔═══════════════════ escolherEntrada ══════════════════╗
     PESSOA escolherEntrada(PESSOA pessoa, char caixa){
     
         char caractereDigitado, memoriaDeTeclas[3];
         char posicao;
         int indiceDaEntrada = 1;
         int forcarAvancoDinamico = 0;
         int localizacao;
     
     
             if (caixa == 'i') {
                 localizacao = 13;
             } else {
                 localizacao = 83;
             }
     
     
         printf(inicio, localizacao);
         while(1) {
             
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║ LOCAL PARA RENDERIZAÇÃO DE FOCO:                                                   ║
             //║ Exemplo de sinalização visual: você pode sobrepor a palavra do campo selecionado   ║
             //║ com o comando fverde (Fundo Verde) alertando o usuário da posição atual na memória.║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
     
             // 
             if (forcarAvancoDinamico) {
                 caractereDigitado = 13;
                 forcarAvancoDinamico = 0; // Desarma para aguardar a próxima leitura
             } else {
                 caractereDigitado = _getch();
             }
     
             memoriaDeTeclas[1] = caractereDigitado;
     
     
             // Verifica se a leitura é uma Tecla Estendida (As setas direcionais acionam essa trava)
             if (caractereDigitado == 9 || caractereDigitado == 27 || caractereDigitado == -32 || caractereDigitado == 224 || caractereDigitado == 13 || caractereDigitado == 0) { 
                 
                 if(caractereDigitado == -32 || caractereDigitado == 224 || caractereDigitado == 0) {
                     //localiza qual das 4 setas foi precionada.
                     caractereDigitado = _getch();
                     indiceDaEntrada = posicionarEntrada(caractereDigitado, indiceDaEntrada, '5', 0);
                 } else if(caractereDigitado == 9){
                     if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
                         caractereDigitado = 72; // Shift pressionado: Força a agir como Seta Cima (Voltar)
                     } else {
                         caractereDigitado = 80; // Apenas Tab: Força a agir como Seta Baixo (Avançar)
                     }
                     indiceDaEntrada = posicionarEntrada(caractereDigitado, indiceDaEntrada, '5', 0);
                 } else if(caractereDigitado == 27) {
                     
                     localizacao = (caixa == 'i') ? 1 : 71;
     
                     if(indiceDaEntrada == 1 ||
                        indiceDaEntrada == 2 ||
                        indiceDaEntrada == 3)      { printf(inicio sobe, localizacao, 1); }
                     else if(indiceDaEntrada == 4) { printf(inicio sobe, localizacao, 3); }
                     else if(indiceDaEntrada == 5) { printf(inicio sobe, localizacao, 5); }
     
                     if(caixa == 'i') { printf(inicio, 1); } 
                     else { printf(inicio, 71); }
     
     
                     break;
                 } else {
                     // animação de confirme
                 }
                 
                 if (caractereDigitado == 75) caractereDigitado = 72;
                 if (caractereDigitado == 77) caractereDigitado = 80;
                
              
     
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║ ENTER (CONFIRMAÇÃO DO FOCO E ACESSO À MEMÓRIA):                                    ║
             //║   Se o operador apertar enter (13), avaliamos o índice do vetor de foco e          ║
             //║ redirecionará a execução de forma definitiva para as funções construídas.          ║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
     
                 if(caractereDigitado !=13){
                 switch (indiceDaEntrada){
                     
                     case 1: //Gênero:
     
                         if(caixa == 'i'){
     
                             // Vindo do Telefone (1) de uma caixa impar:
                                 if(localizacao == 27){
                                     if (pessoa.telefone1[0] == EOF){ printf(inicio esmaecer"   Telefone (1)  " reset, 27); }
                                     printf(inicio, 1); }
     
                             // Vindo do E-mail de uma caixa impar:      
                                 else if(localizacao == 13) {
                                     if(pessoa.email[0] == EOF){ printf(inicio esmaecer"  E-mail: " inicio " ----------------------------------------------- " reset, 2, 13); }
                                     printf(sobe inicio, 4, 1);
                                 } localizacao = 13;
     
                         } else {
                             
                             // Vindo do Telefone (1) de uma caixa par:
                                 if(localizacao == 97){
                                     if (pessoa.telefone1[0] == EOF){ printf(inicio esmaecer"   Telefone (1)  " reset, 97); }
                                     printf(inicio, 83); }
     
                             // Vindo do E-mail de uma caixa par:         
                                 else if(localizacao == 83) {
                                     if(pessoa.email[0] == EOF){ printf(inicio esmaecer"  E-mail: " inicio " ----------------------------------------------- " reset, 72, 83); }
                                     printf(sobe inicio, 4, 71);
                                 } localizacao = 83;
                         }
     
                         break;
     
     
                     case 2: // Telefone (1):
                         
                         
                     
                         if(caixa == 'i') { 
                             // Vindo do Gênero de uma caixa impar:
                             if(pessoa.genero[0] == EOF){ printf(inicio esmaecer"   Gênero    ", 13); }
     
                             // Vindo do Telefone (2) de uma caixa impar: 
                             else if (pessoa.telefone2[0] == EOF){ printf(inicio esmaecer"   Telefone (2)  " reset, 45); }
                             localizacao = 1; }
                         else { 
                             // Vindo do Gênero de uma caixa par:
                             if(pessoa.genero[0] == EOF){ printf(inicio esmaecer"   Gênero    ", 83); }
     
                             // Vindo do Telefone (2) de uma caixa par: 
                             else if (pessoa.telefone2[0] == EOF){ printf(inicio esmaecer"   Telefone (2)  " reset, 115); }
                             localizacao = 71; }
                         localizacao += 26;
                         printf(inicio, localizacao);
                         
                         break;
     
     
                     case 3: // Telefone (2):
     
                      
     
                         if(caixa == 'i') {
                             // Vindo do Telefone (1) de uma caixa impar:
                             if(localizacao == 27){
                                 if (pessoa.telefone1[0] == EOF){ printf(inicio esmaecer"   Telefone (1)  " reset, 27); }
                                 printf(inicio, 48); }
     
                             // Vindo do Nome de uma caixa impar:   
                             else if(localizacao == 13) {
                                 if(pessoa.nome[0] == EOF){ printf(inicio esmaecer "   Nome:  " inicio " ----------------------------------------------- " reset, 2, 13); } 
                                 printf (sobe inicio, 2, 48); }
                                 else if (pessoa.telefone1[0] == EOF){ printf(inicio esmaecer "   Telefone (1)  " reset, 27); }
                                 localizacao = 1;
     
                         } else {
                             // Vindo do Telefone (1) de uma caixa par:
                             if(localizacao == 97){ 
                                 if (pessoa.telefone1[0] == EOF){ printf(inicio esmaecer"   Telefone (1)  " reset, 97); }
                                 printf(inicio, 115); }
     
                             //Vindo do Nome de uma caixa par:
                             else if(localizacao == 83) {
                                 if(pessoa.nome[0] == EOF){ printf(inicio esmaecer "   Nome:  " inicio " ----------------------------------------------- " reset, 72, 83); } 
                                 printf (sobe inicio, 2, 115); }
                                 else if (pessoa.telefone1[0] == EOF){ printf(inicio esmaecer "   Telefone (1)  " reset, 97); }
     
                             localizacao = 71;
     
                         }localizacao += 44;
     
                         printf(inicio, localizacao);
     
                         break;
     
                     case 4: //Nome
     
                         
                         
                         if(caixa == 'i'){
     
                             //Vindo do Telefone (2) de uma caixa impar:
                             if(localizacao == 45){
                                 if(pessoa.telefone2[0] == EOF){ printf(inicio esmaecer"   Telefone (2)  " reset, 45); }
                                 printf(desce inicio, 2, 13);
                             }
     
                             //Vindo do E-mail de uma caixa impar:
                             else if(localizacao == 13){
                                 if(pessoa.email[0] == EOF){ printf(inicio esmaecer"  E-mail: " inicio " ----------------------------------------------- " reset, 2, 13); }
                                 printf(sobe inicio, 2, 13);
                             }
                             
                             localizacao = 13;
     
                         } else {
     
                             //Vindo do Telefone (2) de uma caixa par:
                             if(localizacao == 115){
                                 if(pessoa.telefone2[0] == EOF){ printf(inicio esmaecer"   Telefone (2)  " reset, 115); }
                                 printf(desce inicio, 2, 83);
                             }
     
                             //Vindo do E-mail de uma caixa par:
                             else if(localizacao == 83){
                                 if(pessoa.email[0] == EOF){ printf(inicio esmaecer"  E-mail: " inicio " ----------------------------------------------- " reset, 72, 83); }
                                 printf(sobe inicio, 2, 83);
                             }
                             
                             localizacao = 83;
                         }
     
                         break;
     
                     case 5: //E-mail
     
                       
                         if(caixa == 'i'){
     
                             if(caractereDigitado == 72 || caractereDigitado == 75){ 
     
                             // Vindo do Gênero de uma caixa impar:
                                 if (pessoa.genero[0]== EOF ){ printf(inicio esmaecer "   Gênero    " inicio reset, 13, 13); }
                                 printf(desce, 4); 
                         
                             // Vindo do Nome de uma caixa impar:
                             } else if(caractereDigitado == 80) {
                                 if(pessoa.nome[0] == EOF) { printf(inicio esmaecer "   Nome:  " inicio " ----------------------------------------------- " reset, 2, 13);}
                                 printf(desce, 2); 
                             }
                             
                             localizacao = 13;
                         } else if(caractereDigitado == 77 || caractereDigitado == 80 || caractereDigitado == 72){
     
                             if(caractereDigitado == 72){ 
     
                             // Vindo do Gênero de uma caixa par:
                                 if (pessoa.genero[0]== EOF ){ printf(inicio esmaecer "   Gênero    " inicio reset, 83, 83); }
                                 printf(desce, 4);
                         
                             // Vindo do Nome de uma caixa par:
                             } else if(caractereDigitado == 80) {
                                 if(pessoa.nome[0] == EOF) { printf(inicio esmaecer "   Nome:  " inicio " ----------------------------------------------- " reset desce, 72, 83, 2);}
                                 //printf(desce, 2); 
                             }
                             
                             localizacao = 83;
                         }
     
                         break;
     
                 }
                 }
                 
                 
                 printf(inicio, localizacao);
     
     
                 if(caractereDigitado == 13){
                 switch(indiceDaEntrada) {
                     case 1: 
     
                         if(pessoa.genero[0] == EOF || pessoa.genero[0] == '\0') { lerGeneroNoTerminal(pessoa.genero, caixa, localizacao); }
                         else{
                                 char confirmarAcao;
     
                                 while (1)
                                 {
                                     printf(inicio fvermelho "   Excluir?  " reset volte, localizacao, 1);
                                     confirmarAcao = _getch();
     
                                     if(confirmarAcao == 13 || confirmarAcao == 8) { 
                                     printf(inicio, localizacao);
                                     lerGeneroNoTerminal(pessoa.genero, caixa, localizacao);
                                 } else if(confirmarAcao == 9 || confirmarAcao == 27){
     
                                     printf(inicio "             " inicio BRANCO" (", localizacao, localizacao);
     
                                         if(pessoa.genero[0] == 'M'){
                                             printf(inicio"  Masculino  ", localizacao);
                                         }else {
                                             printf(inicio"  Feminino   ", localizacao);
                                         }
     
                                     printf(inicio reset, localizacao);
                                     break;
                                 } else { 
                                     printf(inicio  fverde "  Confirma?  " reset volte, localizacao, 1);
                                     Sleep(Tempo_Alerta_Longo);
                                     continue; }
     
                                 }
                                 
     
                         }
     
                         if(pessoa.genero[0] != EOF && pessoa.genero[0] != '\0') {
                             indiceDaEntrada ++;
                             int posicaoDoCursor = (caixa == 'i') ? 27 : 97;
                             printf(inicio, posicaoDoCursor);
                             localizacao = posicaoDoCursor;
                             
                                 if(pessoa.telefone1[0] == EOF || pessoa.telefone1[0] == 0){forcarAvancoDinamico = 1;}
                                 else continue;
                         } else {
                             forcarAvancoDinamico = 0;
                         }
                         
     
                         break;
     
                     case 2: 
     
                         if(pessoa.telefone1[0] == EOF || pessoa.telefone1[0] == '\0') { lerTelefoneNoTerminal(pessoa.telefone1, caixa, 'i', localizacao); }
                         else{
                                 char confirmarAcao;
     
                                 while (1)
                                 {
                                     printf(inicio fvermelho "    Excluir?     " reset volte, localizacao, 1);
                                     confirmarAcao = _getch();
     
                                     if(confirmarAcao == 13 || confirmarAcao == 8) { 
                                     printf(inicio, localizacao);
                                     lerTelefoneNoTerminal(pessoa.telefone1, caixa, 'p', localizacao);
                                 } else if(confirmarAcao == 9 || confirmarAcao == 27){
     
                                     printf(inicio "                 " inicio BRANCO" (", localizacao, localizacao);
                                     int i;
                                     for(i = 0; i < 11; i++) {
                                         printf("%c", pessoa.telefone1[i]);
                                         if(i == 1) printf(") ");
                                         if(i == 6) printf("-");
                                     }
                                     printf(inicio reset, localizacao);
                                     break;
                                 } else { 
                                     printf(inicio  fverde "    Confirma?    " reset volte, localizacao, 1);
                                     Sleep(Tempo_Alerta_Longo);
                                     continue; }
     
                                 }
                                 
     
                         }
                     
     
                         if(pessoa.telefone1[0] != EOF && pessoa.telefone1[0] != '\0') {
                             int posicaoDoCursor = (caixa == 'i') ? 45 : 115;
                             printf(inicio, posicaoDoCursor);
                             indiceDaEntrada ++;
                             localizacao = posicaoDoCursor;
                             if(pessoa.telefone2[0] == EOF || pessoa.telefone2[0] == 0){forcarAvancoDinamico = 1;}
                             else continue;
                         } else {
                             forcarAvancoDinamico = 0;
                         }
     
     
                         break;
     
     
                     case 3: 
     
                         if(pessoa.telefone2[0] == EOF || pessoa.telefone2[0] == '\0') { lerTelefoneNoTerminal(pessoa.telefone2, caixa, 'p', localizacao); }
                         else{
                                 char confirmarAcao;
     
                                 while (1)
                                 {
                                     printf(inicio fvermelho "    Excluir?     " reset volte, localizacao, 1);
                                     confirmarAcao = _getch();
     
                                     if(confirmarAcao == 13 || confirmarAcao == 8) { 
                                     printf(inicio, localizacao);
                                     lerTelefoneNoTerminal(pessoa.telefone2, caixa, 'p', localizacao);
                                 } else if(confirmarAcao == 9 || confirmarAcao == 27){
     
                                     printf(inicio "                 " inicio BRANCO" (", localizacao, localizacao);
                                     int i;
                                     for(i = 0; i < 11; i++) {
                                         printf("%c", pessoa.telefone2[i]);
                                         if(i == 1) printf(") ");
                                         if(i == 6) printf("-");
                                     }
                                     printf(inicio reset, localizacao);
                                     break;
                                 } else { 
                                     printf(inicio  fverde "    Confirma?    " reset volte, localizacao, 1);
                                     Sleep(Tempo_Alerta_Longo);
                                     continue; }
     
                                 }
                                 
     
                         }
     
                         if(pessoa.telefone2[0] != EOF && pessoa.telefone2[0] != '\0'){ 
                             int posicaoDoCursor = (caixa == 'i') ? 13 : 83;
                             printf(desce inicio, 2, posicaoDoCursor);
                             indiceDaEntrada ++;
                             localizacao = posicaoDoCursor;
                             if(pessoa.nome[0] == EOF || pessoa.nome[0] == 0){forcarAvancoDinamico = 1;}
                                 else continue;
                         } else {
                             forcarAvancoDinamico = 0;
                         }
     
     
                         break;
     
     
                     case 4: 
     
                         //if se a não memoria estiver preenchida
                         
                         if(pessoa.nome[0] == EOF || pessoa.nome[0] == '\0') { lerNomeNoTerminal(pessoa.nome, caixa, localizacao); }
                         else {
     
                                 char confirmarAcao;
     
                                 while (1){
                                 printf(inicio  fvermelho "                    Excluir?                     " reset volte, localizacao, 1);
                                 confirmarAcao = _getch();
     
                                 if(confirmarAcao == 13 || confirmarAcao == 8) { 
                                     printf(inicio, localizacao);
                                     lerEmailNoTerminal(pessoa.nome, caixa, localizacao);
                                 } else if(confirmarAcao == 9 || confirmarAcao == 27){
     
                                     int tamanhoDoEmail = strlen(pessoa.nome);
                                     int ancoramentoFinal = (localizacao + 23) - (tamanhoDoEmail / 2);
                                     printf(inicio "                                                 " inicio BRANCO "%s" inicio, localizacao, ancoramentoFinal +1, pessoa.nome, localizacao);
                                     break;
                                 } else { 
                                     printf(inicio  fverde "                    Confirma?                    " reset volte, localizacao, 1);
                                     Sleep(Tempo_Alerta_Longo);
                                     continue; }
     
                                 }
     
                         }
     
                         if(pessoa.nome[0] != EOF && pessoa.nome[0] != '\0') {
                             int posicaoDoCursor = (caixa == 'i') ? 13 : 83;
                             printf(desce inicio, 2, posicaoDoCursor);
                             indiceDaEntrada ++;
                             localizacao = posicaoDoCursor;
                             if(pessoa.email[0] == EOF || pessoa.email[0] == 0){forcarAvancoDinamico = 1;}
                             else continue;
     
                         } else {
                             forcarAvancoDinamico = 0;
                         }
     
                         break;
     
                     case 5: 
                         
                         if(pessoa.email[0] == EOF || pessoa.email[0] == '\0') { lerEmailNoTerminal(pessoa.email, caixa, localizacao); }
                         else {
     
                             char confirmarAcao;
     
                             while (1){
                             printf(inicio  fvermelho "                    Excluir?                     " reset volte, localizacao, 1);
                             confirmarAcao = _getch();
     
                             if(confirmarAcao == 13 || confirmarAcao == 8) { 
                                 printf(inicio, localizacao);
                                 lerEmailNoTerminal(pessoa.email, 'i', localizacao);
                             } else if(confirmarAcao == 9 || confirmarAcao == 27){
     
                                 int tamanhoDoEmail = strlen(pessoa.email);
                                 int ancoramentoFinal = (localizacao + 23) - (tamanhoDoEmail / 2);
                                 printf(inicio "                                                 " inicio BRANCO "%s" inicio, localizacao, ancoramentoFinal +1, pessoa.email, localizacao);
                                 break;
                             } else { 
                                 printf(inicio  fverde "                    Confirma?                    " reset volte, localizacao, 1);
                                 Sleep(Tempo_Alerta_Longo);
                                 continue; }
     
                             }
     
                         }
     
                         if(pessoa.email[0] != EOF && pessoa.email[0] != '\0') {
                             int posicaoDoCursor = (caixa == 'i') ? 13 : 83;
                             printf(sobe inicio, 4, posicaoDoCursor);
                             indiceDaEntrada = 1;
                             localizacao = posicaoDoCursor;
                             if(pessoa.genero[0] == EOF || pessoa.genero[0] == 0){forcarAvancoDinamico = 1;}
                             else continue;
                         } else
                         
                         {
                             //printf(sobe inicio, 4, (caixa == 'i') ? 13 : 83);
                             forcarAvancoDinamico = 0;
                         }
     
     
                         break;
                 
                     }
     
                      int verificarDadosCompletos = (pessoa.genero[0] != EOF && pessoa.genero[0] != '\0' &&
                                                     pessoa.telefone1[0] != EOF && pessoa.telefone1[0] != '\0' &&
                                                     pessoa.telefone2[0] != EOF && pessoa.telefone2[0] != '\0' &&
                                                     pessoa.nome[0] != EOF && pessoa.nome[0] != '\0' &&
                                                     pessoa.email[0] != EOF && pessoa.email[0] != '\0');
     
                     if (verificarDadosCompletos) {
                         
                         
                     }
     
                     
     
     
                 }/*Fim-if Enter*/
     
     
             }
     
             memoriaDeTeclas[0] = memoriaDeTeclas[1];
         }
         return pessoa;
     }



// ╔════════════════════════════════ lerGeneroNoTerminal ═══════════════════════════════╗
     char * lerGeneroNoTerminal(char * genero, char posicaoDaCaixa, int localizacao){
         int indiceAtualDaString = 0;
         genero[1] = 'c';
         int alternarFundo = 0;
         DWORD tempoAnteriorDaAnimacao = GetTickCount();
     
         printf(inicio"             "inicio, localizacao, localizacao);
     
         while(1){
             if(indiceAtualDaString == 0){
                 while(!_kbhit()){
                     //╔════════════════════════════════════════════════════════════════════════════════════╗
                     //║   A função _kbhit() retorna 1 quando alguma tecla for apertada e 0 enquanto espera ║
                     //║ a atividade do usuário. Logo, a expressão !_kbhit retorna exatamente o inverso.    ║
                     //╚════════════════════════════════════════════════════════════════════════════════════╝
                     DWORD tempoAtualDaAnimacao = GetTickCount();
     
                     if(tempoAtualDaAnimacao - tempoAnteriorDaAnimacao >= Tempo_De_Piscar_Cursor) {
                         alternarFundo = !alternarFundo;
                         tempoAnteriorDaAnimacao = tempoAtualDaAnimacao; 
                     }
     
                     if(alternarFundo){
                         printf(fverde inicio"   Gênero    " volte, localizacao, 1);
                     } else {
                         printf(reset BRANCO inicio"   Gênero    "inicio, localizacao, localizacao);
                     }
     
                     Sleep(Tempo_De_Espera_Animacao);
                     //╔════════════════════════════════════════════════════════════════════════════════════╗
                     //║   O objetivo desta instrução é fazer o laço de repetição iterar 4 vezes,  servindo ║
                     //║ como uma trava de tempo até inverter a cor do texto, gerando o efeito visual.      ║
                     //╚════════════════════════════════════════════════════════════════════════════════════╝
                 }
             }
     
             char caractereDigitado = _getch();
             if(caractereDigitado == 27 || caractereDigitado == 9){
                 printf(reset inicio esmaecer "   Gênero    " reset inicio, localizacao, localizacao);
              break;}
             caractereDigitado = toupper(caractereDigitado);
             
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║   Transforma caracteres alfabéticos  em maiúsculos de  forma definitiva na memória ║
             //║ ou simplesmente retorna o original, padronizando a entrada recebida no vetor.      ║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
             if(caractereDigitado != 13 && indiceAtualDaString > 0 && caractereDigitado != 8){
                 printf(fverde inicio"  Confirme!  "inicio, localizacao, localizacao);
                 Sleep(Tempo_De_Alerta_Erro);
                 printf(reset verde);
                 if(genero[0] == 'M'){
                     printf(inicio"  Masculino  "inicio, localizacao, localizacao + 11);
                 }else {
                     printf(inicio"  Feminino   "inicio, localizacao, localizacao + 10);
                 }
                 while(_kbhit()) _getch();
                 continue;
     
             //╔═════════════════════════════════╗
             //║ Enter (Confirmação da entrada): ║
             //╚═════════════════════════════════╝
             } else if(caractereDigitado == 13 && indiceAtualDaString > 0){ 
                 printf(reset);
                 if(genero[0] == 'M'){
                     printf(inicio"  Masculino  ", localizacao);
                 }else {
                     printf(inicio"  Feminino   ", localizacao);
                 }
                 break;
     
             //╔══════════════════════════╗
             //║ Estrutura de Backspace:  ║
             //╚══════════════════════════╝
             } else if(caractereDigitado == 8 && indiceAtualDaString > 0) { 
                 genero[1] = 'c';
                 genero[0] = 0;
                 indiceAtualDaString--;
                 printf(inicio"             "inicio, localizacao, localizacao);
                 
             } else if(indiceAtualDaString == 0 ) {
                 printf(reset);
     
                 if(caractereDigitado == 'M'){
                     genero[0] = caractereDigitado;
                     printf(verde inicio"  Masculino  \33[2D" reset, localizacao);
                     indiceAtualDaString++;
     
                 } else if(caractereDigitado == 'F') {
                     genero[0] = caractereDigitado;
                     printf(verde inicio"  Feminino   \33[3D" reset, localizacao);
                     indiceAtualDaString++;
     
                 } else {
                     printf(fvermelho inicio"   Gênero    "inicio, localizacao, localizacao);
                     Sleep(Tempo_De_Alerta_Erro);
                     printf(reset inicio"   Gênero    "inicio, localizacao, localizacao);
                     while(_kbhit()) _getch();
                 }
             }
             genero[1] = 0;  
         }
         return genero;
     }



// ╔════════════════════════════════════ lerTelefoneNoTerminal ═══════════════════════════════════╗
     char * lerTelefoneNoTerminal(char * telefone, char caixa, char posicao, int localizacao) {
         char  caractereDigitado;
         int   indiceAtualDaString = 0;
         int   quantidadeCaracteresImpressos = 0;
         int   alternarFundo = 0;
         int   i;
         DWORD tempoAnteriorDaAnimacao = GetTickCount();
     
         //╔════════════════════════════════════════════════════════════════════════════════════╗
         //║   O tipo DWORD  é somente uma unsigned long int.  O objetivo disto é o de garantir ║
         //║ um melhor manejo da memória. A função GetTickCount() captura  o tempo de atividade ║
         //║ em que o boot do Windows está funcionando desde a sua última inatividade.          ║
         //╚════════════════════════════════════════════════════════════════════════════════════╝
     
         printf(inicio"                 "inicio, localizacao, localizacao);
        
     
         while(indiceAtualDaString < Tamanho_Maximo_Do_Telefone) {
             
             if(indiceAtualDaString == 0) {
                 printf(reset" Telefone (%d)"inicio, posicao == 'i' ? 1:2, localizacao);
     
                 while(!_kbhit()){
                     //╔════════════════════════════════════════════════════════════════════════════════════╗
                     //║   A função _kbhit() retorna 1 quando alguma tecla for apertada e 0 enquanto espera ║
                     //║ a atividade do usuário. A expressão !_kbhit() retorna exatamente o inverso.        ║
                     //╚════════════════════════════════════════════════════════════════════════════════════╝
                     DWORD tempoAtualDaAnimacao = GetTickCount();
     
                     if(tempoAtualDaAnimacao - tempoAnteriorDaAnimacao >= Tempo_De_Piscar_Cursor) {
                         alternarFundo = !alternarFundo;
                         tempoAnteriorDaAnimacao = tempoAtualDaAnimacao; 
                     }
     
                     if(alternarFundo){
                         printf(fverde negrito inicio"   Telefone (%d)  " reset volte,  localizacao, posicao == 'i' ? 1:2, 1);
                     } else {
                         printf(BRANCO inicio"   Telefone (%d)  "inicio reset,  localizacao, posicao == 'i' ? 1:2, localizacao);
                     }
     
                     Sleep(Tempo_De_Espera_Animacao);
                     //╔════════════════════════════════════════════════════════════════════════════════════╗
                     //║   O objetivo desta instrução  é fazer o laço de repetição iterar 4 vezes, servindo ║
                     //║ como uma trava de tempo até inverter a cor do texto, gerando o efeito de piscar.   ║
                     //╚════════════════════════════════════════════════════════════════════════════════════╝
                 }
             } // Fim-if (animação)
     
             caractereDigitado = _getch();
             if((caractereDigitado == 27 || caractereDigitado == 9) && indiceAtualDaString == 0){
                 printf(reset inicio esmaecer "   Telefone (%d)  " reset inicio, localizacao, posicao == 'i' ? 1:2, localizacao);
                 break;
             } 
     
             if(indiceAtualDaString == Tamanho_Maximo_Do_Telefone - 1) {
                 //╔════════════════════════════════════════════════════════════════════════════════════╗
                 //║   O objetivo deste if é o de fornecer uma trava para que o usuário confirme o quer ║
                 //║ que seja inserido na memória de uma maneira mais definitiva. Caso o próprio queira ║
                 //║ reformular a resposta existe uma  estrutura de backspace  para a última posição do ║
                 //║ vetor.                                                                             ║
                 //╚════════════════════════════════════════════════════════════════════════════════════╝
                 
                 //╔═════════════════════════════════╗
                 //║ Enter (Confirmação da entrada): ║
                 //╚═════════════════════════════════╝
                 if(caractereDigitado == 13) { 
                     printf(BRANCO inicio"                 "inicio" (", localizacao, localizacao);
                     for(i = 0; i < indiceAtualDaString; i++) {
                         printf("%c", telefone[i]);
                         if(i == 1) printf(") ");
                         if(i == 6) printf("-");
                     }
                     break;
                     
                 //╔══════════════════════════╗
                 //║ Estrutura de Backspace:  ║
                 //╚══════════════════════════╝
                 } else if(caractereDigitado == 8 && indiceAtualDaString > 0) { 
                     indiceAtualDaString--;
                     telefone[indiceAtualDaString] = '\0';
                 } else {
                     
                     printf(inicio fverde "    Confirme!    " reset volte, localizacao, 1);
                     Sleep(Tempo_De_Alerta_Erro);
                     printf(inicio verde" (", localizacao);
                     for(i = 0; i <= indiceAtualDaString; i++) {
                         
                         printf("%c", telefone[i]);
                         if(i == 1) printf(") ");
                         if(i == 6) printf("-");
                         
                     }
     
                     
                     while(_kbhit()) _getch();
                     
                     continue;
                 }
     
             } else if(indiceAtualDaString == 2 && caractereDigitado != '9' && caractereDigitado != 8) {
                 //╔════════════════════════════════════════════════════════════════════════════════════╗
                 //║   O objetivo desta verificação é o de impossibilitar que o número após o DDD seja  ║
                 //║ diferente de "9". Elabora uma animação no processo para alertar o usuário.         ║
                 //╚════════════════════════════════════════════════════════════════════════════════════╝
                 printf(inicio vermelho " (%c%c) " reset, localizacao, telefone[0], telefone[1]);
                 Sleep(Tempo_De_Alerta_Erro);
                 printf(inicio verde " (%c%c) " reset, localizacao, telefone[0], telefone[1]);
                 while(_kbhit()) _getch();
                 continue;
     
             } else if(caractereDigitado >= '0' && caractereDigitado <= '9') {
                 //╔════════════════════════════════════════════════════════════════════════════════════╗
                 //║   O objetivo deste if é o de salvar apenas os caracteres numéricos recebidos  pela ║
                 //║ função "_getch()" de maneira definitiva na alocação do vetor.                      ║
                 //╚════════════════════════════════════════════════════════════════════════════════════╝
                 telefone[indiceAtualDaString] = caractereDigitado;
                 indiceAtualDaString++;
                 telefone[indiceAtualDaString] = '\0';
                 
                 if(indiceAtualDaString == 1){
                     printf(reset verde"(");
                 }            
     
             //╔══════════════════════════╗
             //║ Estrutura de Backspace:  ║
             //╚══════════════════════════╝
             } else if(caractereDigitado == 8 && indiceAtualDaString > 0) { 
                 //╔════════════════════════════════════════════════════════════════════════════════════╗
                 //║   O objetivo deste  if é o de possibilitar  a formatação do  número recebido e  já ║
                 //║ gravado na memória do vetor. Porém, não altera o caractere já impresso no terminal.║
                 //╚════════════════════════════════════════════════════════════════════════════════════╝
                 indiceAtualDaString--;
                 telefone[indiceAtualDaString] = '\0';
     
                 if (indiceAtualDaString == 0) {
                     printf("\033[2D "); 
                 }
     
             } else {
                 //╔════════════════════════════════════════════════════════════════════════════════════╗
                 //║  Faz o laço de repetição iterar imediatamente para os demais caracteres digitados. ║
                 //║ Realiza uma animação no processo para garantir o feedback visual da inserção.      ║
                 //╚════════════════════════════════════════════════════════════════════════════════════╝
                 if(indiceAtualDaString == 0){
                     printf(inicio fvermelho "   Telefone (%d)  " reset volte, localizacao, posicao == 'i' ? 1:2, 1);
                     Sleep(Tempo_De_Piscar_Cursor);
                     printf(inicio, localizacao);
                     
                 } else {
                     
                     printf(inicio vermelho " (", localizacao);
                     for(i = 0; i < indiceAtualDaString; i++) {
                         
                         printf("%c", telefone[i]);
                         if(i == 1) printf(") ");
                         if(i == 6) printf("-");
                         
                     }
     
                     Sleep(Tempo_Pausa_Sucesso);
                     printf(inicio verde " (", localizacao);
                     if(caractereDigitado == 13){
                         printf(inicio verde " (", localizacao);
                     }
     
     
                     for(i = 0; i < indiceAtualDaString; i++) {
                         printf("%c", telefone[i]);
                         if(i == 1) printf(") ");
                         if(i == 6) printf("-");
                     }
                 }
                 while(_kbhit()) _getch();
                 continue;
             }
             
             if(quantidadeCaracteresImpressos > 0) {
                 //╔════════════════════════════════════════════════════════════════════════════════════╗
                 //║   Posiciona o cursor para a reformulação da imagem de caracteres válidos que foram ║
                 //║ devidamente computados no terminal.                                                ║
                 //╚════════════════════════════════════════════════════════════════════════════════════╝
                 printf(inicio"                 "inicio, localizacao, localizacao);
             }
     
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║   "Apaga" a imagem dos caracteres validados no terminal de maneira definitiva para ║
             //║ receber a renderização atualizada.                                                 ║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
             printf(inicio"                 ", localizacao);
             
             quantidadeCaracteresImpressos = 0;
             
             
                 printf(inicio verde " (", localizacao);
             
     
             for(i = 0; i < indiceAtualDaString; i++) {
                 //╔════════════════════════════════════════════════════════════════════════════════════╗
                 //║   O objetivo deste for é o de realizar  a  impressão estilizada do número que está ║
                 //║ devidamente alocado na memória do vetor.                                           ║
                 //╚════════════════════════════════════════════════════════════════════════════════════╝
                 printf("%c", telefone[i]);
                 quantidadeCaracteresImpressos++;
     
                 if(i == 1) {
                     printf(") ");
                     quantidadeCaracteresImpressos += 2;
                 }
                 if(i == 6) {
                     printf("-");
                     quantidadeCaracteresImpressos++;
                 }
             }
     
             if(indiceAtualDaString == 0) {
                 continue;
             } else if(caractereDigitado == 13) {
                 printf(BRANCO);
                 break;
             }
         } // Fim do while principal
         
         //╔════════════════════════════════════════════════════════════════════════════════════╗
         //║  Esta trava serve como um sistema de segurança definitivo para que o dado coletado ║
         //║ seja devidamente impresso no arquivo GERAL.txt sem falhas de alocação.             ║
         //╚════════════════════════════════════════════════════════════════════════════════════╝
         telefone[Tamanho_Maximo_Do_Telefone - 1] = '\0';
         return telefone;
     }



// ╔═══════════════════════════ lerNomeNoTerminal ══════════════════════════╗
     char * lerNomeNoTerminal(char * nome, char caixa, int localizacao) {
     
         char caractereDigitado;
         int indiceAtualDaString = 0;
         int alternarFundo = 0;
         DWORD tempoAnteriorDaAnimacao = GetTickCount();
         int ancoramentoAtual;
     
     
         nome[0] = '\0';
         int centroDaCaixaDeNome = localizacao + 23;
     
         // Move o cursor coordenadamente para a coluna 14 (Exatamente após o limite: "║   Nome:  ║ ")
         printf(reset inicio BRANCO "Nome:" inicio"                                                 "inicio, localizacao - 8, localizacao, localizacao);
     
         while(indiceAtualDaString < Tamanho_Maximo_Do_Nome - 1) {
     
             if(indiceAtualDaString == 0) {
                 while(!_kbhit()) {
                     DWORD tempoAtualDaAnimacao = GetTickCount();
                     if(tempoAtualDaAnimacao - tempoAnteriorDaAnimacao >= Tempo_De_Piscar_Cursor) {
                         alternarFundo = !alternarFundo;
                         tempoAnteriorDaAnimacao = tempoAtualDaAnimacao; 
                     }
     
                     if(alternarFundo) {
                         printf(fverde inicio" ----------------------------------------------- " reset volte, localizacao, 1);
                     } else {
                         printf(BRANCO inicio" ----------------------------------------------- "inicio reset, localizacao, localizacao);
                     }
                     Sleep(Tempo_De_Espera_Animacao);
                 }
             }
     
             caractereDigitado = _getch();
             if((caractereDigitado == 27 || caractereDigitado == 9) && indiceAtualDaString == 0) {
                 printf(inicio esmaecer "Nome:" inicio " ----------------------------------------------- " inicio, localizacao - 8, localizacao, localizacao);
            
                 break;}
     
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║ Filtragem das entradas e vetor:  Estrutura lógica para tratar e validar a inserção ║
             //║ do usuário de forma segura antes da alocação no vetor.                             ║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
             if(indiceAtualDaString == 0 && 
               (caractereDigitado == 8 || caractereDigitado == 32 ||
               (caractereDigitado >= '0' && caractereDigitado <= '9'))){
                 continue;
             } else if((caractereDigitado >= 'A' && caractereDigitado <= 'Z') ||
                (caractereDigitado >= 'a' && caractereDigitado <= 'z') ||
                caractereDigitado == 32 || caractereDigitado == '.') {
                 
                 // Trava de segurança para não ultrapassar a caixa
                 if(indiceAtualDaString >= Tamanho_Maximo_Do_Nome - 2) continue;
     
                 // Tratamento: Espaço
                 if(caractereDigitado == 32) {
                     // Impede múltiplos espaços seguidos ou espaços no início
                     if((indiceAtualDaString < 2 || nome[indiceAtualDaString - 1] == 32 || nome[indiceAtualDaString - 1] == '.') && indiceAtualDaString > 0){
                         printf(inicio"                                                 ", localizacao);
                         printf(inicio vermelho "%s" reset, ancoramentoAtual+1, nome);
                         Sleep(Tempo_Pausa_Sucesso);
                         while(_kbhit()) _getch();
                         printf(inicio"                                                 ", localizacao);
                         printf(inicio verde "%s" reset, ancoramentoAtual+1, nome);
                         printf(inicio, ancoramentoAtual + indiceAtualDaString + 1);
                         
                         continue;
                     } 
                     nome[indiceAtualDaString++] = 32;
                      
                 } 
                 // Tratamento: Pontuação
                 else if(caractereDigitado == '.') {
     
                     int temEspaco = (strchr(nome, ' ') != NULL);
     
                     if( !temEspaco || indiceAtualDaString < 4 || nome[indiceAtualDaString - 1] == 32 || nome[indiceAtualDaString - 1] == '.') {
                         printf(inicio"                                                 ", localizacao);
                         printf(inicio vermelho "%s" reset, ancoramentoAtual+1, nome);
                         Sleep(Tempo_Pausa_Sucesso);
                         printf(inicio"                                                 ", localizacao);
                         printf(inicio verde "%s" reset, ancoramentoAtual+1, nome);
                         continue;
                     }
     
                     nome[indiceAtualDaString++] = '.';
                     nome[indiceAtualDaString++] = 32; // Injeta automaticamente um espaço depois do ponto
                 } 
                 // Tratamento: Letras Minúsculas no input
                else if(caractereDigitado >= 'a' && caractereDigitado <= 'z' && nome[indiceAtualDaString - 1] == '.'){
                     nome[indiceAtualDaString] --;
                     continue;
     
                 } else if(caractereDigitado >= 'a' && caractereDigitado <= 'z') {
                     if(indiceAtualDaString == 0 || nome[indiceAtualDaString - 1] == 32) {
                         nome[indiceAtualDaString++] = caractereDigitado - 32; // Força para Masiúscula
                     } else {
                         nome[indiceAtualDaString++] = caractereDigitado;
                     }
                 } 
                 // Tratamento: Letras Maiúsculas no input
                 else { 
                     if(indiceAtualDaString == 0 || nome[indiceAtualDaString - 1] == 32) {
                         nome[indiceAtualDaString++] = caractereDigitado;
                     } else {
                         nome[indiceAtualDaString++] = caractereDigitado + 32; // Força para Minúscula
                     }
                 } 
             } 
             //╔══════════════════════════╗
             //║ Estrutura de Backspace:  ║
             //╚══════════════════════════╝
             else if (caractereDigitado == 8) { 
                 if(indiceAtualDaString > 0) indiceAtualDaString--;
                 if(indiceAtualDaString == 0) continue;
             } 
             //╔═════════════════════════════════╗
             //║ Enter (Confirmação da entrada): ║
             //╚═════════════════════════════════╝
             else if (caractereDigitado == 13) { 
     
                  if(indiceAtualDaString > 5 && (nome[indiceAtualDaString - 2] == '.' || nome[indiceAtualDaString - 1] == '.')){
     
                         printf(inicio fvermelho "       Primeiro e ultimo nome completos!         " reset volte, localizacao, 1);
                         Sleep(Tempo_Alerta_Longo);
                         
                         while(_kbhit()) {
                             _getch();
                     }
                     printf(inicio"                                                 ", localizacao);
                         printf(inicio verde "%s" reset, ancoramentoAtual + 1, nome);
                         continue;
                 }
     
     
                 // Exige o mínimo de 2 caracteres para ser um nome coerente no Brasil
                 if (indiceAtualDaString >= 2 && nome[indiceAtualDaString-1] != '.') { 
                     // Auto-Trim: Corrige sujeiras deixadas na ponta da string
                     if (nome[indiceAtualDaString - 1] == 32 || nome[indiceAtualDaString - 1] == '.') {
                         indiceAtualDaString--; 
                     } 
     
                     nome[indiceAtualDaString] = '\0';
     
                     
     
                     int ancoramentoFinal = centroDaCaixaDeNome - (indiceAtualDaString / 2);
                     printf(inicio"                                                 ", localizacao); // Limpa fundo
                     printf(inicio BRANCO "%s" reset, ancoramentoFinal, nome); // Imprime verde no centro
                     break;
                     
                 }            
                 else {
                     // Alerta de erro caso ele tente pular esse menu
                     printf(inicio fvermelho "          Nome Invalido! (Mín. 2 letras)         " reset, localizacao);
                     Sleep(Tempo_Erro_Extenso);
                     printf(inicio"                                                 ", localizacao);
                     printf(inicio verde "%s" reset, ancoramentoAtual + 1, nome);
                     continue;
                     
                 }
                 while(!_kbhit()) _getch();
             }  else if(indiceAtualDaString == 0){
                     printf(inicio fvermelho " ----------------------------------------------- " reset volte, 13, 1);
                     Sleep(Tempo_De_Piscar_Cursor);
                     printf(inicio " ----------------------------------------------- " inicio, 13, 13);
                     while(_kbhit()) _getch();
     
                 }
             
             else {
                 printf(inicio"                                                 ", localizacao);
                 printf(inicio vermelho "%s" reset, ancoramentoAtual+1, nome);
                 Sleep(Tempo_Pausa_Sucesso);
                 printf(inicio"                                                 ", localizacao);
                 printf(inicio verde "%s" reset, ancoramentoAtual+1, nome);
                 continue;
             }
     
     
             nome[indiceAtualDaString] = '\0';
     
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║ RENDERIZAÇÃO NA INTERFACE: Calcula a âncora atual e limpa resquícios no terminal   ║
             //║ para desenhar os caracteres gravados na memória.                                   ║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
             ancoramentoAtual = centroDaCaixaDeNome - (indiceAtualDaString / 2);
     
             // 2. Limpeza absoluta do campo inteiro (evita fantasmas de Backspace na esquerda/direita)
             printf(inicio"                                                 ", localizacao);
             
             // 3. Pulo para a "ancoramentoAtual" calculada e escrevo a string.
             printf(inicio verde "%s" reset, ancoramentoAtual+1, nome);
             
             // 4. Movo o cursor para piscar exatamente após a última letra.
             // O cursor deve ficar na (ancoramentoAtual + tamanho do indice).
             printf(inicio, ancoramentoAtual + indiceAtualDaString + 1);
         }
     
         if(nome[strlen(nome) - 1] == 32){
             nome[strlen(nome - 1)] = 0;
         } else {
             nome[strcspn(nome, "\n")] = 0;
         }
     
         return nome;
     }
 


// ╔════════════════════════════ lerEmailNoTerminal ═══════════════════════════╗
     char * lerEmailNoTerminal(char * email, char caixa, int localizacao) {
         char caractereDigitado;
         int indiceAtualDaString = 0;
         int alternarFundo = 0;
         DWORD tempoAnteriorDaAnimacao = GetTickCount();
         int ancoramentoAtual;
     
         email[0] = '\0';
         int centroDaCaixaDeEmail = localizacao + 23;
     
         // Limpa o campo coordenadamente (comprimento de 47 espaços da caixinha)
         printf(reset inicio BRANCO "E-mail:" inicio"                                                 "inicio, localizacao - 9, localizacao, localizacao);
     
         while(1) {
             // Animação de piscar a barra enquanto o campo estiver vazio
             if(indiceAtualDaString == 0) {
                 while(!_kbhit()) {
                     DWORD tempoAtualDaAnimacao = GetTickCount();
                     if(tempoAtualDaAnimacao - tempoAnteriorDaAnimacao >= Tempo_De_Piscar_Cursor) {
                         alternarFundo = !alternarFundo;
                         tempoAnteriorDaAnimacao = tempoAtualDaAnimacao; 
                     }
     
                     if(alternarFundo) {
                         printf(fverde inicio" ----------------------------------------------- " reset volte, localizacao, 1);
                     } else {
                         printf(BRANCO inicio" ----------------------------------------------- "inicio reset, localizacao, localizacao);
                     }
                     Sleep(Tempo_De_Espera_Animacao);
                 }
             }
     
             caractereDigitado = _getch();
             if((caractereDigitado == 27 || caractereDigitado == 9) && indiceAtualDaString == 0) {
                 printf(inicio esmaecer "E-mail:" inicio " ----------------------------------------------- " inicio, localizacao -9, localizacao, localizacao
                 ); 
                 break;}
     
             // Converte automaticamente letras maiúsculas para minúsculas
             if (caractereDigitado >= 'A' && caractereDigitado <= 'Z') {
                 caractereDigitado = tolower(caractereDigitado);
             }
     
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║ FILTRAGEM DE CARACTERES VÁLIDOS: Estrutura que funciona como uma trava de          ║
             //║ segurança para salvar no vetor apenas os caracteres permitidos em domínios reais.  ║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
             if(indiceAtualDaString ==0 && (caractereDigitado == 8 || caractereDigitado == 32)){
                 continue;
             }else if ((caractereDigitado >= 'a' && caractereDigitado <= 'z') ||
                 (caractereDigitado >= '0' && caractereDigitado <= '9') ||
                 caractereDigitado == '@' || caractereDigitado == '.' || 
                 caractereDigitado == '_' || caractereDigitado == '-') {
                 
                 int temArroba = (strchr(email, '@') != NULL);
     
                 // Evita a inserção de múltiplos "@"
                 if (caractereDigitado == '@' && temArroba) {
                     continue; 
                 }
     
                 // Trava de segurança para evitar estouro de buffer (Tamanho_Maximo_Do_Email = 48)
                 // Se não tem '@', reserva 11 espaços para o autocomplete "@gmail.com"
                 int limiteSeguro = temArroba ? (Tamanho_Maximo_Do_Email - 1) : (Tamanho_Maximo_Do_Email - 12);
     
                 if(indiceAtualDaString >= limiteSeguro + 1) {
                     
                 if (!temArroba && caractereDigitado == '@') {
                         // Libera a passagem do @ mesmo estando no limite
                 } else {
                         printf(inicio fvermelho "        Limite máximo! Somente dominios.         " reset volte, localizacao, 1);
                         Sleep(Tempo_Alerta_Longo);
                         
                         while(_kbhit()) {
                             _getch();
                     }
                     printf(inicio"                                                 ", localizacao);
                         printf(inicio verde "%s" reset, ancoramentoAtual + 1, email);
                         continue;
                     }
                 }
     
                 email[indiceAtualDaString++] = caractereDigitado;
                 email[indiceAtualDaString] = '\0';
             } 
             //╔══════════════════════════╗
             //║ Estrutura de Backspace:  ║
             //╚══════════════════════════╝
             else if (caractereDigitado == 8 && indiceAtualDaString > 0) { 
                 indiceAtualDaString--;
                 email[indiceAtualDaString] = '\0';
             } 
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║ ENTER (CONFIRMAÇÃO E AUTOCOMPLETE): Confirma a inserção na memória de maneira      ║
             //║ definitiva e completa a string automaticamente caso o usuário omita o domínio.     ║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
             else if (caractereDigitado == 13) { 
                 // Validação de tamanho mínimo (2 caracteres)
                 if (indiceAtualDaString >= 2) { 
                     char *posArroba = strchr(email, '@');
     
                     if (posArroba == NULL) {
                         // Caso 1: Digitou sem o arroba -> completa com @gmail.com
                         strcat(email, "@gmail.com");
                         indiceAtualDaString = strlen(email);
                     } else if (email[indiceAtualDaString - 1] == '@') {
                         // Caso 2: Último caractere digitado foi o arroba -> completa com gmail.com
                         strcat(email, "gmail.com");
                         indiceAtualDaString = strlen(email);
                     }
     
                     email[indiceAtualDaString] = '\0';
     
                     // Renderização Final Centralizada em BRANCO para indicar campo fixado
                     int ancoramentoFinal = centroDaCaixaDeEmail - (indiceAtualDaString / 2);
                     printf(inicio"                                                 ", localizacao);
                     printf(inicio BRANCO "%s" reset, ancoramentoFinal+1, email);
                     break; 
                     
                 } else {
                     // Alerta de erro caso possua menos de 2 caracteres
                     printf(inicio fvermelho "      E-mail Inválido! (Mín. 2 caracteres)       " reset volte, localizacao, 1);
                     printf(inicio, localizacao);
                 }
                 while(_kbhit()) _getch();
             }  else if(indiceAtualDaString == 0){
                     printf(inicio fvermelho " ----------------------------------------------- " reset volte, 13, 1);
                     Sleep(Tempo_De_Piscar_Cursor);
                     printf(inicio " ----------------------------------------------- " inicio, 13, 13);
                     while(_kbhit()) _getch();
     
                 } 
             // Tratamento para qualquer outro caractere inválido digitado
             else {
                 printf(inicio"                                                 ", localizacao);
                 printf(inicio vermelho "%s" reset, ancoramentoAtual + 1, email);
                 Sleep(Tempo_Alerta_Rapido);
                 printf(inicio verde "%s" reset, ancoramentoAtual + 1, email);
                 continue;
             }
     
             //╔════════════════════════════════════════════════════════════════════════════════════╗
             //║ RENDERIZAÇÃO EM TEMPO REAL: Apaga os resquícios no buffer visual e redesenha       ║
             //║ os caracteres alocados para garantir a responsividade durante a digitação.         ║
             //╚════════════════════════════════════════════════════════════════════════════════════╝
             ancoramentoAtual = centroDaCaixaDeEmail - (indiceAtualDaString / 2);
     
             // Limpa o rastro anterior
             printf(inicio"                                                 ", localizacao);
             
             // Imprime o texto centralizado dinamicamente em verde
             printf(inicio verde "%s" reset, ancoramentoAtual + 1, email);
             
             // Reposiciona o cursor piscante logo após a última letra inserida
             printf(inicio, ancoramentoAtual + indiceAtualDaString + 1);
         }
         return email;
     }

/*


            ╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
╔═══════════║  ───────────────────────────────────────────────────────────────────────────────────── ARTES ─────────────────────────────────────────────────────────────────────────────────────  ║═════════════╗
╚═══════════╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝═════════════╝

                                ╔═════════════╗
     ╔══════════════════════════║ Caixa Vazia ║═════════════════════════╗
                                ╚═════════════╝
        ╔══════════╦═════════════╦═════════════════╦═════════════════╗
        ║    nº    ║   Gênero    ║   Telefone (1)  ║   Telefone (2)  ║
        ╠══════════╬═════════════╩═════════════════╩═════════════════╣
        ║   Nome:  ║ ----------------------------------------------- ║
        ╠══════════╬═════════════════════════════════════════════════╣
        ║  E-mail: ║ ----------------------------------------------- ║
        ╚══════════╩═════════════════════════════════════════════════╝
        
     ╚══════════════════════════════════════════════════════════════════╝
        


    
                                ╔═════════════╗
     ╔══════════════════════════║ Caixa Limpa ║═════════════════════════╗
                                ╚═════════════╝
        ╔══════════╦═════════════╦═════════════════╦═════════════════╗
        ║    nº    ║   Gênero    ║   Telefone (1)  ║   Telefone (2)  ║
        ╠══════════╬═════════════╩═════════════════╩═════════════════╣
        ║   Nome:  ║                                                 ║
        ╠══════════╬═════════════════════════════════════════════════╣
        ║  E-mail: ║                                                 ║
        ╚══════════╩═════════════════════════════════════════════════╝
    
     ╚══════════════════════════════════════════════════════════════════╝


     
                        ╔═════════════════════════════╗
     ╔══════════════════║ Caixa para Adição de caixas ║═════════════════╗
                        ╚═════════════════════════════╝
        ╔════════════════════════════════════════════════════════════╗
        ║                                                            ║
        ║                             │                              ║
        ║                          ───┼───                           ║
        ║                             │                              ║
        ║                                                            ║
        ╚════════════════════════════════════════════════════════════╝
    
     ╚══════════════════════════════════════════════════════════════════╝


                                                                     ╔═══════╗
     ╔═══════════════════════════════════════════════════════════════║ Setor ║═══════════════════════════════════════════════════════════════╗
                                                                     ╚═══════╝

        ╔══════════╦═════════════╦═════════════════╦═════════════════╗        ╔══════════╦═════════════╦═════════════════╦═════════════════╗
        ║    nº    ║   Gênero    ║   Telefone (1)  ║   Telefone (2)  ║        ║    nº    ║   Gênero    ║   Telefone (1)  ║   Telefone (2)  ║
        ╠══════════╬═════════════╩═════════════════╩═════════════════╣        ╠══════════╬═════════════╩═════════════════╩═════════════════╣
        ║   Nome:  ║                                                 ║        ║   Nome:  ║                                                 ║
        ╠══════════╬═════════════════════════════════════════════════╣        ╠══════════╬═════════════════════════════════════════════════╣
        ║  E-mail: ║                                                 ║        ║  E-mail: ║                                                 ║
        ╚══════════╩═════════════════════════════════════════════════╝        ╚══════════╩═════════════════════════════════════════════════╝
        
        
        ╔══════════╦═════════════╦═════════════════╦═════════════════╗        ╔══════════╦═════════════╦═════════════════╦═════════════════╗
        ║    nº    ║   Gênero    ║   Telefone (1)  ║   Telefone (2)  ║        ║    nº    ║   Gênero    ║   Telefone (1)  ║   Telefone (2)  ║
        ╠══════════╬═════════════╩═════════════════╩═════════════════╣        ╠══════════╬═════════════╩═════════════════╩═════════════════╣
        ║   Nome:  ║                                                 ║        ║   Nome:  ║                                                 ║
        ╠══════════╬═════════════════════════════════════════════════╣        ╠══════════╬═════════════════════════════════════════════════╣
        ║  E-mail: ║                                                 ║        ║  E-mail: ║                                                 ║
        ╚══════════╩═════════════════════════════════════════════════╝        ╚══════════╩═════════════════════════════════════════════════╝
        
        
        ╔══════════╦═════════════╦═════════════════╦═════════════════╗        ╔══════════╦═════════════╦═════════════════╦═════════════════╗
        ║    nº    ║   Gênero    ║   Telefone (1)  ║   Telefone (2)  ║        ║    nº    ║   Gênero    ║   Telefone (1)  ║   Telefone (2)  ║
        ╠══════════╬═════════════╩═════════════════╩═════════════════╣        ╠══════════╬═════════════╩═════════════════╩═════════════════╣
        ║   Nome:  ║                                                 ║        ║   Nome:  ║                                                 ║
        ╠══════════╬═════════════════════════════════════════════════╣        ╠══════════╬═════════════════════════════════════════════════╣
        ║  E-mail: ║                                                 ║        ║  E-mail: ║                                                 ║
        ╚══════════╩═════════════════════════════════════════════════╝        ╚══════════╩═════════════════════════════════════════════════╝
        
     ╚════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝




╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


                                             ╔═══════════════════════════════════════════════════════════════════════════════════════╗
                                             ║  Dos problemas que continuam persistindo no código e algumas limitações do terminal:  ║
                                             ╚═══════════════════════════════════════════════════════════════════════════════════════╝


                                                                                   ╔═════════════╗
          ╔════════════════════════════════════════════════════════════════════════║ Do terminal ║════════════════════════════════════════════════════════════════════════╗
                                                                                   ╚═════════════╝

               O terminal, ainda que seja uma interface gráfica, é estruturado para a apresentação de textos, apresentando alguns comportamentos peculiares— semelhantes
           aos de um bloco de notas,  por exemplo —,  onde, dependendo do tamanho da janela,  geram-se "linhas fantasmas".  Isso pode simplesmente impossibilitar que as
           animações aconteçam,  tornando a tela ilegível ao  utilizador.  Há também o receio fútil quanto aos comandos de escape ASCII,  a extrema dificuldade  para se
           imprimir para baixo (mesmo com comandos mais consistentes, como o "\n")  e, com ainda mais ardor,  imprimir textos para cima. A sua estrutura, ao mesmo tempo
           que facilita as expressões textuais, é exatamente aquilo que gera instabilidade devido à posição atual do cursor.

          ╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


          
                                                                                  ╔═══════════════╗
          ╔═══════════════════════════════════════════════════════════════════════║ Dos ponteiros ║═══════════════════════════════════════════════════════════════════════╗
                                                                                  ╚═══════════════╝

               No que diz respeito ao código, existe uma falta de estrutura em relação à utilização dos ponteiros. Algumas das structs, no código mais completo, utilizam
            ponteiros de ponteiros para outras structs, que, por sua vez, possuem outros ponteiros para structs.  Isso confere competência ao código,  mas também o torna
            mais complexo de ser entendido, requerendo um estudo mais aprofundado.
           
          ╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝



                                                                                    ╔════════════╗
          ╔═════════════════════════════════════════════════════════════════════════║ Da memória ║════════════════════════════════════════════════════════════════════════╗
                                                                                    ╚════════════╝
                A falta de um arquivo .txt aberto em "a+" para o salvamento de dados — que,  neste caso, seria o correto para conseguirmos ler o arquivo sem possibilitar
            alguma entrada que o invalide— ocorre mais pela ausência de um script do tipo .bat que insira os dados nos desenhos antes de o usuário interagir, já deixando
            o cursor devidamente posicionado.

          ╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝



                                  ╔═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
            ╔═════════════════════║                                                  Comentários                                                  ║═════════════════════╗
                                  ╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

                  Por mais que  o código se apresente incompleto em suas funcionalidades —  como a falta de registros em arquivos .txt abertos em "r+" e em "a+" para a
              preservação dos dados coletados —,  o próprio desenvolvimento dos setores  e  a escrita destes em  ASCII Art  já são capazes  de  demonstrar como podemos
              poupar processos que o computador faria.  Evitamos os descartes de impressões apenas locomovendo o cursor de posição ou trazendo animações mais "baratas"
              em pleno terminal, o que gera uma coleta de dados mais interativa e um código de simulação mais fechado,  onde os itens se apresentam de uma maneira mais
              agradável e ágil ao usuário.
                  Acredito que as funções  responsáveis pelas entradas fazem uma utilização deveras intrigante da função  _getch().  É interessante  observar como essa
              função nos possibilita o acesso às entradas do tipo stdin e o poder de "ramificá-las" ao nosso interesse. Ela realiza uma captura "antecipada" e,  graças
              a esta instância, somos capazes de executar uma verificação mais madura do que realmente estamos coletando. Essa organização entre o que queremos mostrar
              à pessoa  e aquilo de que o computador realmente precisa enriquece nosso código,  já que podemos organizar tanto uma leitura mais útil  e  correta para a
              máquina quanto uma estrutura mais adequada a quem utilizará o software produzido.

            ╚═══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝



╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝*/
