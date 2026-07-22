#include <stdio.h>
#include <stdlib.h>
#include   <windows.h>
#include   <locale.h>


#define    finalDoArquivo    arquivo, 0, SEEK_END
#define    Ainicio           arquivo, ftell(arquivo), SEEK_CUR

#define    CSuperior       "╔══════════════════════════════════════════════════╗\n"
#define    Ccomum          "║                                                  ║\n"
#define    CSepararTitulo  "╠═══════════════════╦══════════════════════════════╣\n"
#define    CSepararItens   "╠═══════════════════╬══════════════════════════════╣\n"
#define    CInferior       "╚═══════════════════╩══════════════════════════════╝\n"


#define    imprimirTabelaDoEmprestimo  CSuperior "║     CALCULADORA PARA PARCELAS DE EMPRÉTIMOS      ║\n" CSepararTitulo "║  Valor Recebido:  ║                              ║\n" CSepararItens "║   Taxa de juros:  ║                              ║\n" CSepararItens "║  Data de inicio:  ║                              ║\n" CSepararItens "║Número de parcelas:║                              ║\n" CInferior


void main() {

    
    SetConsoleOutputCP(CP_UTF8);
    //setlocale(LC_ALL, "");

    FILE *arquivo = fopen("teste.txt", "wb+");

    fprintf(arquivo)

    fclose(arquivo)

    printf("\n\n\n\n"imprimirTabelaDoEmprestimo"\n\n\n\n");

}
