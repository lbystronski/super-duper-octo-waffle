#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "user.h"

using namespace std;

int main()
{
    user a;
    int nvagas, opcao, verificador, mat, var;
    int valor, x, y;
    a.saldo=0;

    cout << "Informe o numero de vagas: ";
    cin >> nvagas; cout << endl;
    cout << "Informe o custo do estacionamento: ";
    cin >> valor; cout << endl;
    while (!0)
    {
        system("cls");
        cout << endl << "1 para entrada," << endl << "2 para saida," << endl << "3 para desbloquear," << endl << "4 para incluir saldo," << endl << "0 para finalizar: ";
        cin >> opcao; // grava opção de entrada ou saida
        if(opcao==0) break; if(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4){ cout << endl << "Opcao invalida" << endl;}
        if(opcao==1 || opcao==2 || opcao==3 || opcao==4)
        {
            mat=0; // zera matricula caso reinicie
            cout << endl << "Digite numero da matricula: ";
            cin >> mat; // carrega matricula para variavel de verificação de matricula

            ifstream parkverifica;
            parkverifica.open("park.txt");
            ofstream parkgrava;
            parkgrava.open("park2.txt");
            while ( ! parkverifica.eof() ) // cria copia com estado atualizado da matricula
            {
                parkverifica >> a.matricula;
                if(a.matricula==9999)
                {
                    parkgrava << "9999";
                    break;
                }
                parkgrava << a.matricula << " ";
                parkverifica >> a.saldo;
                parkverifica >> a.estado;
                    if (a.matricula==mat)
                    {
                        if (opcao==1 || opcao==3)
                        {
                            parkgrava << a.saldo << " ";
                        }else{
                        if (opcao==2)
                        {
                            x=a.saldo-valor;
                            if (x<0) { cout << "Saldo insuficiente para sair" << endl; opcao==4; parkgrava << a.saldo << " ";}
                            if (x>=0 && a.estado!=0) {a.saldo=x; parkgrava << a.saldo << " ";}
                            else{parkgrava << a.saldo << " ";}
                        }
                        if (opcao==4)
                        {
                            x=0;
                            cout << "Informe valor a ser incluido no saldo: "; cin >> x; a.saldo=a.saldo+x;
                            parkgrava << a.saldo << " ";
                        }}
                    }
                    else {parkgrava << a.saldo << " ";}

                if(a.matricula==mat)
                {
                        if (opcao==4){parkgrava << a.estado << endl;}
                        else{

                        if (opcao==3 && a.estado==0) // se opçao de desbloqueio
                        {
                            parkgrava << 3 << endl; // altera para estatus para desbloqueado
                            var=5;

                        }
                        else
                        {
                            if (opcao==1 && (a.estado==1 || a.estado==3)) // se opçao de entrada e estatus liberado entrada ou desbloqueado
                            {
                                parkgrava << 2 << endl; // altera para estatus de entrada
                                var=1;
                                nvagas = nvagas - 1;
                            }

                            if ((opcao==2 && (a.estado==2 || a.estado==3)) && x>=0) // se opçao de saida e estatus liberado saida ou desbloqueado
                            {
                                parkgrava << 1 << endl; // altera para estatus de saida
                                var=2;
                                nvagas = nvagas + 1;
                                y=x;
                            }
                            if ((opcao==2 && (a.estado==2 || a.estado==3)) && x<0){parkgrava << 2 << endl; var=3;y=x;}

                            if (((opcao==1 && a.estado==2) || (opcao==2 && a.estado==1) || (a.estado==0)) && opcao!=4) // se opçao de entrada e estatus não correspondem
                            {
                                parkgrava << 0 << endl; // altera para estatus para bloqueado
                                var=0;
                            }
                        }}


                }
                else {parkgrava << a.estado << endl;}

            }parkverifica.close(); parkgrava.close();

            ifstream parkgrava2;
            parkgrava2.open("park2.txt");
            ofstream parkverifica2;
            parkverifica2.open("park.txt");
            while ( ! parkgrava2.eof() ) // retorna dados atualizados para arquivo primario park.txt
            {
                parkgrava2 >> a.matricula;
                if(a.matricula==9999)
                {
                    parkverifica2 << "9999";
                    break;
                }
                parkverifica2 << a.matricula << " ";
                parkgrava2 >> a.saldo;
                parkverifica2 << a.saldo << " ";
                parkgrava2 >> a.estado;
                parkverifica2 << a.estado << endl;

            }parkverifica2.close(); parkgrava2.close();
            //remove("park2.txt");

        }



        if(var==0){cout << endl<< endl << "Matricula bloqueada, verifique situacao:" << endl<< endl;}
        if(var==1){cout << endl<< endl << "Entrada liberada com sucesso:" << endl; cout << "Saldo: "<< x << endl; cout << "Numero de vagas:" << nvagas << endl<< endl;}
        if(var==2){cout << endl<< endl << "Saida liberada com sucesso:" << endl; cout << "Saldo: "<< x << endl; cout << "Numero de vagas:" << nvagas << endl<< endl;}
        if(var==3){cout << endl<< endl << "Saida nao permitida:" << endl<< endl;}
        if(var==5){cout << endl<< endl << "Desbloqueado com sucesso:" << endl<< endl;}
        system("pause");
        //system("cls");
    }

    return(0);
}
