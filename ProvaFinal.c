/*
             ╔═══════════════════╗
 ╔═══════════║  Prova Final (C)  ║═══════════╗
             ╚═══════════════════╝
  
   *       Disciplina: Algoritmos 2.
  
   * Professor: Paulo Henrique Bueno Lopes.
    
   * Aluno: Gabriel Henrique Smak de Andrade.
  
 ╚═══════════════════════════════════════════╝



   ╔════════════════╗
   ║  Bibliotecas:  ║
   ╚════════════════╝*/


    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <windows.h>
    #include <conio.h>



// ╔═══════════╗
// ║  Struct:  ║
// ╚═══════════╝

    typedef struct PESSOA{

        unsigned int  idDaPessoaReferida;
        char          nome[31];
        char          CPF[12];
        char          dataDeNascimento[9];
        char          email[31];
        char          telefone1[12];
        char          telefone2[12];

    } PESSOA;



// ╔═════════════════════════════╗
// ║  Trabalhos com o terminal:  ║
// ╚═════════════════════════════╝

    #define clean       "\033[1;1H\033[2J\033[3J\033[1;1H"
    #define negrito     "\033[1m"
    #define sublinhar   "\033[4m"
    #define reset       "\033[0m"
    #define sobe        "\033[%dA"
    #define desce       "\033[%dB"
    #define inicio      "\033[%dG"
    #define fvermelho   "\033[48;5;1m\033[38;5;0m"
    #define fverde      "\033[38;5;0m\033[48;5;84m"


    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif



// ╔════════════════╗
// ║  Assinaturas:  ║
// ╚════════════════╝

    void      prepararTerminalParaImpressao       ( );
    void      carregarDadosColetados              (PESSOA * pessoasRegistradas);
    void      imprimirMenu                        ( );
        
    bool      validarNome                         (char * nomeReferido, int localizacao);
    bool      validarCPF                          (char * CPFreferido, int localizacao);
    bool      validarDataDeNascimento             (char * dataReferida, int localizacao);
    bool      validarTelefone                     (char * telefoneReferido, int localizacao);
    bool      validarEmail                        (char * emailReferido, int localizacao);
        
    void      cadastrarPessoa                     (PESSOA * pessoasRegistradas);
    void      editarDadosDaPessoaRequerida        (PESSOA * pessoasRegistradas);
    void      excluirDadosDaPessoaReferida        (PESSOA * pessoasRegistradas);
    int       consultarPessoasCadastradas         (PESSOA * pessoasRegistradas, bool aprimorado);
    void      salvarDadosColetados                (PESSOA * pessoasRegistradas);





//╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


//    ╔══════ main ═════╗
        int main( ) {

            PESSOA  pessoasRegistradas[10];
            char    opcaoDigitada;
            bool    continuarLaco = true;
            int i = 0;
            
            prepararTerminalParaImpressao();
            
            for(; i <= 9; i++){
                pessoasRegistradas[i].idDaPessoaReferida   =    0;
                pessoasRegistradas[i].nome[0]              =  EOF;
                pessoasRegistradas[i].CPF[0]               =  EOF;
                pessoasRegistradas[i].dataDeNascimento[0]  =  EOF;
                pessoasRegistradas[i].email[0]             =  EOF;
                pessoasRegistradas[i].telefone1[0]         =  EOF;
                pessoasRegistradas[i].telefone2[0]         =  EOF;
            }

            carregarDadosColetados(pessoasRegistradas);

            while(continuarLaco){

            imprimirMenu();

            opcaoDigitada = _getch();

            if(opcaoDigitada >= 49 && opcaoDigitada <= 53){
                printf("%c", opcaoDigitada);
                Sleep(350);}

            while(_kbhit()) _getch();

            switch(opcaoDigitada) {

                case '1':  cadastrarPessoa(pessoasRegistradas);                      break;
                case '2':  editarDadosDaPessoaRequerida(pessoasRegistradas);         break;
                case '3':  excluirDadosDaPessoaReferida(pessoasRegistradas);         break;
                case '4':  consultarPessoasCadastradas(pessoasRegistradas, false);   break;
                case '5':
                    salvarDadosColetados(pessoasRegistradas);
                    continuarLaco = false;
                break;
            }

                if(opcaoDigitada == 27){
                    salvarDadosColetados(pessoasRegistradas);
                    return;
                }

            }

            return 0;
        }


//╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝





//╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


//    ╔══════ prepararTerminalParaImpressao ═════╗
        void prepararTerminalParaImpressao( ){

            HANDLE  hOut    =  GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD   dwMode  =  0;

            SetConsoleOutputCP(CP_UTF8);

            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);}
        }



//    ╔═══════════════════ carregarDadosColetados ═══════════════════╗
        void carregarDadosColetados(PESSOA * pessoasRegistradas) {

            FILE *arquivo  =  fopen("BancoDeDados.txt", "r");
            int  i         =  0;

            if (arquivo == NULL) {
                return;
            }

            while(i < 10 && fscanf(arquivo, "%d;%30[^;];%11[^;];%8[^;];%11[^;];%11[^;];%30[^\n]\n",
                                &pessoasRegistradas[i].idDaPessoaReferida,
                                pessoasRegistradas[i].nome,
                                pessoasRegistradas[i].CPF,
                                pessoasRegistradas[i].dataDeNascimento,
                                pessoasRegistradas[i].telefone1,
                                pessoasRegistradas[i].telefone2,
                                pessoasRegistradas[i].email) == 7) {
                i++;
            }

            fclose(arquivo);
        }



//    ╔══════ imprimirMenu ═════╗
        void imprimirMenu( ) {

            printf(clean);

            printf("\n\n\n\n\n\n\n" sobe, 7);

            printf("┌──────────────────────────────────────────────┐\n"
                   "│ "negrito"[ 1 ]" reset" ..... Cadastrar os dados de uma pessoa │\n"
                   "│ "negrito"[ 2 ]" reset" ......... Editar o dados de uma pessoa │\n"
                   "│ "negrito"[ 3 ]" reset" ....... Excluir os dados de uma pessoa │\n"
                   "│ "negrito"[ 4 ]" reset" ..... Consultar as pessoas cadastradas │\n"
                   "│ "negrito"[ 5 ]" reset" ..................... Sair do programa │\n"
                   "└──────────────────────────────────────────────┘");

                printf("\nDigite uma escolha: [ _ ]" inicio, 23);
        }


//╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝





//╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


//    ╔════════════════════════ validarNome ═══════════════════════╗
        bool validarNome(char * nomeReferido, int localizacao) {

            char  caracterDigitado =  EOF;
            int   indiceDoVetor    =  0;

            while(1){

                caracterDigitado = _getch();

                if(caracterDigitado == 27 || (caracterDigitado == 13 && indiceDoVetor >= 2)){

                    if(caracterDigitado == 27) {
                        indiceDoVetor = 0;
                        return false;
                    }
                    break;

                } else if(indiceDoVetor < 30 && caracterDigitado >= 'A' && caracterDigitado <= 'Z' &&
                        (nomeReferido[indiceDoVetor-1] == ' ' || nomeReferido[indiceDoVetor] == EOF || nomeReferido[indiceDoVetor] == 0)){

                    nomeReferido[indiceDoVetor] = caracterDigitado;
                    indiceDoVetor++;

                } else if((indiceDoVetor < 30 && caracterDigitado >= 'a' && caracterDigitado <= 'z') || (caracterDigitado == ' ')){

                    nomeReferido[indiceDoVetor] = caracterDigitado;
                    indiceDoVetor++;

                } else if(indiceDoVetor >= 1 && caracterDigitado == 8){

                    indiceDoVetor--;

                } else { continue; }

                nomeReferido[indiceDoVetor] = 0;
                printf(inicio "                              " inicio "%s", localizacao, localizacao, nomeReferido);

                while(_kbhit()) _getch();
            }

            return true;

        }



//    ╔═══════════════════════ validarCPF ═══════════════════════╗
        bool validarCPF(char * CPFreferido, int localizacao) {

            char  caracterDigitado  =  EOF;
            int   indiceDoVetor     =  0;

            while(1){
            
                caracterDigitado = _getch();

                if(caracterDigitado == 27 || (indiceDoVetor == 11 && caracterDigitado == 13)){

                    if(caracterDigitado == 27){
                        indiceDoVetor = 0;
                        return false;
                    }
                    break;

                } else if(indiceDoVetor < 11 && caracterDigitado >= '0' && caracterDigitado <= '9'){

                    CPFreferido[indiceDoVetor] = caracterDigitado;
                    indiceDoVetor++;

                } else if (indiceDoVetor > 0 && caracterDigitado == 8){
                    
                    indiceDoVetor--;

                } else { continue; }

                CPFreferido[indiceDoVetor] = 0;
                printf(inicio"                              " inicio, localizacao, localizacao);

                int i = 0;
                for(; i < indiceDoVetor; i++){
                    printf("%c", CPFreferido[i]);
                    if(i == 2 || i == 5) printf(".");
                    if(i == 8) printf("-");
                }

            }

            return true;
        }



//    ╔════════════════════════ validarDataDeNascimento ═══════════════════════╗
        bool validarDataDeNascimento(char * dataReferida, int localizacao) {

            char  caracterDigitado  =  EOF;
            int   indiceDoVetor     =  0;

            while(1){
            
                caracterDigitado = _getch();

                if(caracterDigitado == 27 || (indiceDoVetor == 8 && caracterDigitado == 13)){

                    if(caracterDigitado == 27){
                        indiceDoVetor = 0;
                        return false;
                    }
                    break;

                } else if(indiceDoVetor < 8 && caracterDigitado >= '0' && caracterDigitado <= '9'){

                    dataReferida[indiceDoVetor] = caracterDigitado;
                    indiceDoVetor++;

                } else if (indiceDoVetor > 0 && caracterDigitado == 8){
                    
                    indiceDoVetor--;

                } else { continue; }

                dataReferida[indiceDoVetor] = 0;
                printf(inicio "                              " inicio, localizacao, localizacao);

                int i = 0;
                for(; i < indiceDoVetor; i++){
                    printf("%c", dataReferida[i]);

                    if(i == 1 || i == 3) printf("/");
                }


            }

            return true;
        }



//    ╔══════════════════════════ validarTelefone ═════════════════════════╗
        bool validarTelefone(char * telefoneReferido, int localizacao) {

            char  caracterDigitado  =  EOF;
            int   indiceDoVetor     =  0;

            while(1){
            
                caracterDigitado = _getch();

                if(caracterDigitado == 27 || (indiceDoVetor == 11 && caracterDigitado == 13)){

                    if(caracterDigitado == 27){
                        indiceDoVetor = 0;
                        return false;
                    }
                    break;

                } else if(indiceDoVetor < 11 && caracterDigitado >= '0' && caracterDigitado <= '9'){

                    telefoneReferido[indiceDoVetor] = caracterDigitado;
                    indiceDoVetor++;

                } else if (indiceDoVetor > 0 && caracterDigitado == 8){
                    
                    indiceDoVetor--;

                } else { continue; }

                telefoneReferido[indiceDoVetor] = 0;

                
                    printf(inicio"                              " inicio, localizacao, localizacao);

                    if(indiceDoVetor > 0){
                        printf("(");
                    }

                int i = 0;
                for(; i < indiceDoVetor; i++){
                    printf("%c", telefoneReferido[i]);
                    if( i == 1 ) printf(") ");
                    if( i == 2 ) printf(" ");
                    if( i == 6 ) printf("-");
                }

            }

            return true;

        }



//    ╔════════════════════════ validarEmail ════════════════════════╗
        bool validarEmail(char * emailReferido, int localizacao) {

            char  caracterDigitado  =  EOF;
            int   indiceDoVetor     =  0;

            while(1){

                caracterDigitado = _getch();

                if(caracterDigitado == 27 || (caracterDigitado == 13 && indiceDoVetor >= 2)){

                    if(caracterDigitado == 27){
                        indiceDoVetor = 0;
                        return false;
                    }

                    if(caracterDigitado == 13) {
                        if(strchr(emailReferido, '@') == NULL && indiceDoVetor < 21){ strcat(emailReferido, "@gmail.com");}
                        else if(indiceDoVetor > 19 && strchr(emailReferido, '@') == NULL) { continue; }
                    }
                    break;

                } else if((indiceDoVetor < 27 || (strchr(emailReferido, '@') != NULL && indiceDoVetor < 30)) &&
                        ((caracterDigitado >= 'a' && caracterDigitado <= 'z') ||
                        (caracterDigitado >= '0' && caracterDigitado <= '9'))){

                    emailReferido[indiceDoVetor] = caracterDigitado;
                    indiceDoVetor++;        

                } else if(indiceDoVetor >= 1 && caracterDigitado == 8){

                    indiceDoVetor--;

                } else if ((caracterDigitado == '@' && indiceDoVetor > 1 && strchr (emailReferido, '@') == NULL) ||
                        (caracterDigitado == '.' && indiceDoVetor > 1)){
                    emailReferido[indiceDoVetor] = caracterDigitado;
                    indiceDoVetor++;
                } else { continue; }

                emailReferido[indiceDoVetor] = 0;

                printf(inicio "                              " inicio "%s", localizacao, localizacao, emailReferido);
            }

            return true;

        }


//╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝





//╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
//╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝


//    ╔═══════════════════ cadastrarPessoa ═══════════════════╗
        void cadastrarPessoa(PESSOA * pessoasRegistradas) {

            int indiceDoVetor      =  0;
            int maiorIDEncontrado  =  0;
            int i                  =  0;
            char caracterDigitado  =  EOF;
            

            for(; indiceDoVetor <= 9; indiceDoVetor++){
                if(pessoasRegistradas[indiceDoVetor].idDaPessoaReferida == 0){break;}
            }

            printf(clean);


            printf("┌──────────────────────────────────────────────────────┐\n"
                   "│ Nome.................                                │\n"
                   "│ CPF..................                                │\n"
                   "│ Data de Nascimento...                                │\n"
                   "│ Telefone (1).........                                │\n"
                   "│ Telefone (2).........                                │\n"
                   "│ E-mail...............                                │\n"
                   "└──────────────────────────────────────────────────────┘");


                printf(sobe inicio, 6, 25);
                if(!validarNome(pessoasRegistradas[indiceDoVetor].nome, 25)) return;

                printf(desce inicio, 1, 25);
                if(!validarCPF(pessoasRegistradas[indiceDoVetor].CPF, 25)) return;

                printf(desce inicio, 1, 25);
                if(!validarDataDeNascimento(pessoasRegistradas[indiceDoVetor].dataDeNascimento, 25)) return;

                printf(desce inicio, 1, 25);
                if(!validarTelefone(pessoasRegistradas[indiceDoVetor].telefone1, 25)) return;

                printf(desce inicio "Inserir um segundo telefone?", 1, 25);

                while(1){
                caracterDigitado = _getch();

                if(caracterDigitado == 13){
                    printf(inicio "                              " inicio, 25, 25);
                    if(!validarTelefone(pessoasRegistradas[indiceDoVetor].telefone2, 25)) return;
                    break;
                } else if(caracterDigitado == 27 || caracterDigitado == 8){

                    printf(inicio "------------------------------", 25);
                    pessoasRegistradas[indiceDoVetor].telefone2[0] = '-';
                    pessoasRegistradas[indiceDoVetor].telefone2[1] = 0;
                    break;
                }

                }

                printf(desce inicio, 1, 25);
                if(!validarEmail(pessoasRegistradas[indiceDoVetor].email, 25)) return;

                for(; i < 10; i++) {
                    if(pessoasRegistradas[i].idDaPessoaReferida > maiorIDEncontrado) {
                        maiorIDEncontrado = pessoasRegistradas[i].idDaPessoaReferida;
                    }
                }

                pessoasRegistradas[indiceDoVetor].idDaPessoaReferida = maiorIDEncontrado + 1;

                Sleep(350);


        }



//    ╔═══════════════════ editarDadosDaPessoaRequerida ═══════════════════╗
        void editarDadosDaPessoaRequerida(PESSOA * pessoasRegistradas) {

            int   indiceDaEdicao       =  consultarPessoasCadastradas(pessoasRegistradas, true);
            int   posicaoDaEdicao      =  1;
            int   i                    =  0;
            char  caracterDigitado     =  EOF;
            bool  atualizarCaixaMenor  =  true;


            if(indiceDaEdicao == -1){
                return;
            }

            printf(sobe inicio, 6, 1);

            printf("┌──────────────────── Editar dados ────────────────────┐\n\n"
                " " inicio " \n"
                "1" inicio "2\n"
                "↑" inicio "↓\n"
                " " inicio " " sobe inicio, 56, 56, 56, 56, 3, 66);

            printf("┌──────────────────────────────────────────────────────┐\n" inicio
                   "│                                                      │\n" inicio
                   "└──────────────────────────────────────────────────────┘" sobe inicio, 66, 66, 1, 67);
            

            while(1){

                if (atualizarCaixaMenor) {
                    switch(posicaoDaEdicao) {
                        case 1: printf(inicio " Nome.................                                " inicio, 67, 67); break;
                        case 2: printf(inicio " CPF..................                                " inicio, 67, 67); break;
                        case 3: printf(inicio " Data de Nascimento...                                " inicio, 67, 67); break;
                        case 4: printf(inicio " Telefone (1).........                                " inicio, 67, 67); break;
                        case 5: printf(inicio " Telefone (2).........                                " inicio, 67, 67); break;
                        case 6: printf(inicio " E-mail...............                                " inicio, 67, 67); break;
                    }
                    atualizarCaixaMenor = false;
                }


                caracterDigitado = _getch();
                if(caracterDigitado == 27 || caracterDigitado == 9){ return; }

                if(caracterDigitado == '1' || caracterDigitado == '2') {

                    if(caracterDigitado == '1') { 
                        posicaoDaEdicao--;
                        if (posicaoDaEdicao < 1) posicaoDaEdicao = 6;
                    } else { 
                        posicaoDaEdicao++;
                        if (posicaoDaEdicao > 6) posicaoDaEdicao = 1;
                    }

                    atualizarCaixaMenor = true;

                } else if(caracterDigitado == 13 || caracterDigitado == 8) {

                    printf(inicio, 90);

                    switch(posicaoDaEdicao) {
                        case 1:
                        
                            validarNome(pessoasRegistradas[indiceDaEdicao].nome, 90);

                            printf(sobe inicio "                                " inicio "%s" desce inicio,
                                    2, 24, 25, pessoasRegistradas[indiceDaEdicao].nome, 2 ,90);
                            printf(inicio, 90);
                        
                        break;
                        

                        case 2:  
                        
                            validarCPF(pessoasRegistradas[indiceDaEdicao].CPF, 90);
                            printf(sobe inicio "                                " inicio, 1, 24, 25);


                            for(i = 0; i < strlen(pessoasRegistradas[indiceDaEdicao].CPF); i++){
                                printf("%c", pessoasRegistradas[indiceDaEdicao].CPF[i]);
                                if(i == 2 || i == 5) printf(".");
                                if(i == 8) printf("-");
                            }
                            printf(desce inicio, 1, 90);
                            
                        break;


                        case 3:
                        
                            validarDataDeNascimento(pessoasRegistradas[indiceDaEdicao].dataDeNascimento, 90);
                            printf(inicio "                                " inicio, 24, 25);

                            for(i = 0; i < strlen(pessoasRegistradas[indiceDaEdicao].dataDeNascimento); i++){
                                printf("%c", pessoasRegistradas[indiceDaEdicao].dataDeNascimento[i]);
                                if(i == 1 || i == 3) printf("/");
                            }
                            printf(inicio, 90);
                            
                        break;


                        case 4:
                        
                            validarTelefone(pessoasRegistradas[indiceDaEdicao].telefone1, 90);
                            printf(desce inicio "                                " inicio "(", 1, 24, 25);
                            for(i = 0; i < strlen(pessoasRegistradas[indiceDaEdicao].telefone1); i++){
                                printf("%c", pessoasRegistradas[indiceDaEdicao].telefone1[i]);
                                if( i == 1 ) printf(") ");
                                if( i == 2 ) printf(" ");
                                if( i == 6 ) printf("-");
                            }
                            printf(sobe inicio, 1, 90);
                            
                        break;


                        case 5:
                        
                            validarTelefone(pessoasRegistradas[indiceDaEdicao].telefone2, 90);
                            printf(desce inicio "                                " inicio "(", 2, 24, 25);
                            for(i = 0; i < strlen(pessoasRegistradas[indiceDaEdicao].telefone2); i++){
                                printf("%c", pessoasRegistradas[indiceDaEdicao].telefone2[i]);
                                if( i == 1 ) printf(") ");
                                if( i == 2 ) printf(" ");
                                if( i == 6 ) printf("-");
                            }
                            printf(sobe inicio, 2, 90);
                        
                        break;


                        case 6:
                        
                            validarEmail(pessoasRegistradas[indiceDaEdicao].email, 90);
                            printf(desce inicio "                                " inicio "%s" desce inicio,
                                    3, 24, 25, pessoasRegistradas[indiceDaEdicao].email, 2 ,90);
                            printf(sobe inicio, 5, 90);
                        
                        break;
                    }

                    atualizarCaixaMenor = true;
                
                } else if(caracterDigitado == 27 || caracterDigitado == 9){
                    return;
                }


            }



        }



//    ╔═══════════════════ excluirDadosDaPessoaReferida ═══════════════════╗
        void excluirDadosDaPessoaReferida(PESSOA * pessoasRegistradas) {

            int   indiceDaExclusao  =  consultarPessoasCadastradas(pessoasRegistradas, true);
            char  caracterDigitado  =  EOF;

            if(indiceDaExclusao == -1){
                return;
            }

        printf(sobe inicio, 4, 68);

             printf("┌──────────────────────────────────┐\n"
            inicio"┌─┘  Comfirma a exclusão dos dados?  └─┐\n"
            inicio"│" fvermelho"                                      "reset"│\n"
            inicio"└──────────────────────────────────────┘" sobe inicio, 66, 66, 66, 2, 101);

            while(1){
                caracterDigitado = _getch();

                if(caracterDigitado == 13 || caracterDigitado == 8){

                    pessoasRegistradas[indiceDaExclusao].idDaPessoaReferida   =  0;
                    pessoasRegistradas[indiceDaExclusao].nome[0]              =  EOF;
                    pessoasRegistradas[indiceDaExclusao].CPF[0]               =  EOF;
                    pessoasRegistradas[indiceDaExclusao].dataDeNascimento[0]  =  EOF;
                    pessoasRegistradas[indiceDaExclusao].email[0]             =  EOF;
                    pessoasRegistradas[indiceDaExclusao].telefone1[0]         =  EOF;
                    pessoasRegistradas[indiceDaExclusao].telefone2[0]         =  EOF;

                    printf(inicio, 69);

                    printf("   Dados excluidos com sucesso!   \n" inicio
                    fverde"                                      "reset sobe inicio, 67, 1, 100);
                    Sleep(1200);
                    break;

                } else if(caracterDigitado == 27){
                    return;
                }
            }
        }



//    ╔═══════════════════════════ consultarPessoasCadastradas ═══════════════════════════╗
        int consultarPessoasCadastradas(PESSOA * pessoasRegistradas, bool aprimorado) {

            int   i = 0;
            int   quantidadeDePessoasEncontradas;
            int   idsPreenchidos[10];
            char  caracterDigitado;

            printf(clean);

            int indiceDoVetor = 0;

            for(; i < 10; i++){
                idsPreenchidos[i] = -1;
                if(pessoasRegistradas[i].idDaPessoaReferida != 0){
                    idsPreenchidos[indiceDoVetor] = i;
                    indiceDoVetor++;
                }
            }
            quantidadeDePessoasEncontradas = indiceDoVetor;

            if(quantidadeDePessoasEncontradas == 0){
                printf("Ainda não há pessoas registradas. Por favor insira o dados de uma!");
                while(!_kbhit());
                return -1;
            }

            printf("\n\n\n\n\n\n\n\n" sobe, 8);

            printf("┌────────────── ← 1 ──────────────── 2 → ──────────────┐\n"
                   "│ Nome.................                                │\n"
                   "│ CPF..................                                │\n"
                   "│ Data de Nascimento...                                │\n"
                   "│ Telefone (1).........                                │\n"
                   "│ Telefone (2).........                                │\n"
                   "│ E-mail...............                                │\n"
                   "└──────────────────────────────────────────────────────┘\n");
                printf(sobe, 2);
            

            int posicaoAtual = 0;

            while(1){

                    int pessoaAtual = idsPreenchidos[posicaoAtual];
                    int y;

                    printf(sobe inicio, 5, 25);
                    //Imprime o nome registrado:
                    printf("                              " inicio "%s" inicio, 25, pessoasRegistradas[pessoaAtual].nome, 25);



                    //Imprime o CPF registrado:

                    printf(desce "                              " inicio , 1, 25);
                    for(y = 0; y < strlen(pessoasRegistradas[pessoaAtual].CPF); y++){
                        printf("%c", pessoasRegistradas[pessoaAtual].CPF[y]);
                        if(y == 2 || y == 5) printf(".");
                        if(y == 8) printf("-");
                    }
                    printf(inicio, 25);



                    //Imprime a data de nascimento registrada:

                    printf(desce "                              " inicio , 1, 25);
                    for(y = 0; y < strlen(pessoasRegistradas[pessoaAtual].dataDeNascimento); y++){
                        printf("%c", pessoasRegistradas[pessoaAtual].dataDeNascimento[y]);
                        if(y == 1 || y == 3) printf("/");
                    }
                    printf(inicio, 25);



                    //Imprime o telefone (1) registrado:

                    printf(desce "                              " inicio "(", 1, 25);
                    for(y = 0; y < strlen(pessoasRegistradas[pessoaAtual].telefone1); y++){
                        printf("%c", pessoasRegistradas[pessoaAtual].telefone1[y]);
                        if( y == 1 ) printf(") ");
                        if( y == 2 ) printf(" ");
                        if( y == 6 ) printf("-");
                    }
                    printf(inicio, 25);

                
                    //Imprime o telefone (2) registrado:

                    printf(desce "                              " inicio "(" , 1, 25);
                    if(pessoasRegistradas[pessoaAtual].telefone2[0] == '-'){ printf(inicio "------------------------------", 25); }
                    else{
                    for(y = 0; y <strlen(pessoasRegistradas[pessoaAtual].telefone2); y++){
                            printf("%c", pessoasRegistradas[pessoaAtual].telefone2[y]);
                            if( y == 1 ) printf(") ");
                            if( y == 2 ) printf(" ");
                            if( y == 6 ) printf("-");
                        }
                    }
                    printf(inicio, 25);



                    //Imprime o E-mail cadastrado:

                    printf(desce "                              " inicio "%s" inicio, 1, 25, pessoasRegistradas[pessoaAtual].email, 57);
            

                    caracterDigitado = _getch();


                    if(caracterDigitado == '2' || caracterDigitado == 9) {
                        posicaoAtual++;
                        if(posicaoAtual >= quantidadeDePessoasEncontradas){
                            posicaoAtual = 0; 
                            }
                    } else if(caracterDigitado == '1') {
                        posicaoAtual--;
                        
                        if(posicaoAtual < 0){
                            posicaoAtual = quantidadeDePessoasEncontradas - 1; 
                        }
                    }
                    else if(caracterDigitado == 27 || caracterDigitado == 8) {
                        break; 
                    } else if(caracterDigitado == 13 && aprimorado){
                        return pessoaAtual;
                    }

                    while(_kbhit()) _getch();
                }

                return -1;
            }



//    ╔═══════════════════ salvarDadosColetados ═══════════════════╗
       void salvarDadosColetados(PESSOA * pessoasRegistradas) {

            FILE *arquivo = fopen("BancoDeDados.txt", "w");
            
            if (arquivo == NULL) {
                printf("Erro ao tentar salvar o arquivo de banco de dados!\n");
                return;
            }

            int i = 0;
            for (; i < 10; i++) {

                if (pessoasRegistradas[i].idDaPessoaReferida != 0) {
                    fprintf(arquivo, "%d;%s;%s;%s;%s;%s;%s\n",
                            pessoasRegistradas[i].idDaPessoaReferida,
                            pessoasRegistradas[i].nome,
                            pessoasRegistradas[i].CPF,
                            pessoasRegistradas[i].dataDeNascimento,
                            pessoasRegistradas[i].telefone1,
                            pessoasRegistradas[i].telefone2,
                            pessoasRegistradas[i].email);
                }
            }

            fclose(arquivo);
        }

/*
╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝






            ╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
╔═══════════║  ───────────────────────────────────────────────────────────────────────────────────── ARTES ─────────────────────────────────────────────────────────────────────────────────────  ║═════════════╗
╚═══════════╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝═════════════╝

                       ╔════════════════╗
    ╔══════════════════║ Menu do Início ║═════════════════╗
                       ╚════════════════╝
        ┌──────────────────────────────────────────────┐
        │ [ 1 ] ..... Cadastrar os dados de uma pessoa │
        │ [ 2 ] ......... Editar o dados de uma pessoa │
        │ [ 3 ] ....... Excluir os dados de uma pessoa │
        │ [ 4 ] ..... Consultar as pessoas cadastradas │
        │ [ 5 ] ..................... Sair do programa │
        └──────────────────────────────────────────────┘

    ╚═════════════════════════════════════════════════════╝




                          ╔══════════════════╗
    ╔═════════════════════║ Menu da Consulta ║════════════════════╗
                          ╚══════════════════╝
        ┌────────────── ← 1 ──────────────── 2 → ──────────────┐
        │ Nome................. ------------------------------ │
        │ CPF.................. ------------------------------ │
        │ Data de Nascimento... ------------------------------ │
        │ Telefone (1)......... ------------------------------ │
        │ Telefone (2)......... ------------------------------ │
        │ E-mail............... ------------------------------ │
        └──────────────────────────────────────────────────────┘

    ╚══════════════════════════════════════════════════════════════╝




                                                          ╔══════════════════╗
    ╔═════════════════════════════════════════════════════║ Menu para Edição ║═════════════════════════════════════════════════════╗
                                                          ╚══════════════════╝

        ┌──────────────────── Editar dados ────────────────────┐         
        │ Nome................. ------------------------------ │         
          CPF.................. ------------------------------           ┌──────────────────────────────────────────────────────┐
        1 Data de Nascimento... ------------------------------ 2         │ Nome................. ------------------------------ │
        ↑ Telefone (1)......... ------------------------------ ↓         └──────────────────────────────────────────────────────┘    
          Telefone (2)......... ------------------------------                
        │ E-mail............... ------------------------------ │
        └──────────────────────────────────────────────────────┘
    
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝




╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝*/
