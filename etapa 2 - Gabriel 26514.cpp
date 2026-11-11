/*===========================================================================
    Centro Universitario de Vicosa - UNIVICOSA
    Disciplina: INF101 - Programacao de Computadores I
    Trabalho - Sistema de Registro e Gestao de Contas Bancarias (ETAPA 2)
    ===========================================================================*/
#include <iostream>
#include <string>
#include <iomanip>   

using namespace std;

int main() {
    const int MAX_CONTAS = 100; 
    int numeroConta[MAX_CONTAS];
    string nomeCliente[MAX_CONTAS];
    string cpf[MAX_CONTAS];
    int tipoConta[MAX_CONTAS];     
    double saldo[MAX_CONTAS];
    bool contaAtiva[MAX_CONTAS];
    int quantidadeContas = 0;       
    const int MAX_MOVIMENTACOES = 500;
    int contaMovimentacao[MAX_MOVIMENTACOES];
    char tipoMovimentacao[MAX_MOVIMENTACOES];
    double valorMovimentacao[MAX_MOVIMENTACOES];
    int quantidadeMovimentacoes = 0;

    int opcao;
    cout << fixed << setprecision(2);

    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1 - Cadastrar contas" << endl;
        cout << "2 - Listar contas cadastradas" << endl;
        cout << "3 - Consultar conta pelo numero" << endl;
        cout << "4 - Realizar deposito" << endl;
        cout << "5 - Realizar saque" << endl;
        cout << "6 - Realizar transferencia" << endl;
        cout << "7 - Exibir extrato" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {

            // -------------------------------------------------------------
            // 1 - CADASTRAR CONTA
            // -------------------------------------------------------------
            case 1: {
                if (quantidadeContas < MAX_CONTAS) {
                    cout << "\n--- Cadastro de Conta ---" << endl;

                    int novoNumero;
                    cout << "Numero da conta: ";
                    cin >> novoNumero;

                    // Percorre as contas ja cadastradas para impedir
                    // duas contas com o mesmo numero
                    bool jaExiste = false;
                    for (int i = 0; i < quantidadeContas; i++) {
                        if (numeroConta[i] == novoNumero) {
                            jaExiste = true;
                        }
                    }

                    if (jaExiste) {
                        cout << "Ja existe uma conta com esse numero!" << endl;
                        break;
                    }

                    // A nova conta sera gravada na proxima posicao livre,
                    // que e exatamente o valor de quantidadeContas
                    numeroConta[quantidadeContas] = novoNumero;

                    cout << "Nome do cliente: ";
                    cin.ignore(); // Limpa o ENTER que sobrou no buffer, senao o getline le vazio
                    getline(cin, nomeCliente[quantidadeContas]);

                    cout << "CPF: ";
                    cin >> cpf[quantidadeContas];

                    cout << "Tipo da conta (1-Corrente, 2-Poupanca): ";
                    cin >> tipoConta[quantidadeContas];
                    if (tipoConta[quantidadeContas] != 1 && tipoConta[quantidadeContas] != 2) {
                        cout << "Tipo de conta invalido! Cadastro cancelado." << endl;
                        break;
                    }

                    cout << "Saldo inicial: ";
                    cin >> saldo[quantidadeContas];
                    if (saldo[quantidadeContas] < 0) {
                        cout << "Saldo inicial nao pode ser negativo! Cadastro cancelado." << endl;
                        break;
                    }

                    contaAtiva[quantidadeContas] = true;
                    quantidadeContas++; // So conta a nova conta depois que todos os dados estao validos

                    cout << "Conta cadastrada com sucesso!" << endl;
                } else {
                    cout << "Limite maximo de contas atingido!" << endl;
                }
                break;
            }

            // -------------------------------------------------------------
            // 2 - LISTAR CONTAS
            // -------------------------------------------------------------
            case 2: {
                cout << "\n--- Lista de Contas ---" << endl;
                if (quantidadeContas == 0) {
                    cout << "Nenhuma conta cadastrada ainda." << endl;
                } else {
                    // Percorre de 0 ate quantidadeContas-1 (so as posicoes preenchidas)
                    for (int i = 0; i < quantidadeContas; i++) {
                        cout << "Conta: " << numeroConta[i] << " | ";
                        cout << "Nome: " << nomeCliente[i] << " | ";
                        cout << "CPF: " << cpf[i] << " | ";
                        cout << "Tipo: " << (tipoConta[i] == 1 ? "Corrente" : "Poupanca") << " | ";
                        cout << "Saldo: R$ " << saldo[i] << " | ";
                        cout << "Situacao: " << (contaAtiva[i] ? "Ativa" : "Inativa") << endl;
                    }
                }
                break;
            }

            // -------------------------------------------------------------
            // 3 - CONSULTAR CONTA PELO NUMERO
            // -------------------------------------------------------------
            case 3: {
                cout << "\n--- Consulta de Conta ---" << endl;
                int numeroBusca;
                cout << "Numero da conta: ";
                cin >> numeroBusca;

                // BUSCA SEQUENCIAL: procura o numero digitado dentro do array.
                // indice guarda a posicao encontrada; -1 significa "nao encontrou".
                int indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                    }
                }

                if (indice == -1) {
                    cout << "Conta nao encontrada!" << endl;
                } else {
                    cout << "Conta: " << numeroConta[indice] << endl;
                    cout << "Nome: " << nomeCliente[indice] << endl;
                    cout << "CPF: " << cpf[indice] << endl;
                    cout << "Tipo: " << (tipoConta[indice] == 1 ? "Corrente" : "Poupanca") << endl;
                    cout << "Saldo: R$ " << saldo[indice] << endl;
                    cout << "Situacao: " << (contaAtiva[indice] ? "Ativa" : "Inativa") << endl;
                }
                break;
            }

            // -------------------------------------------------------------
            // 4 - DEPOSITO
            // -------------------------------------------------------------
            case 4: {
                cout << "\n--- Deposito ---" << endl;
                int numeroBusca;
                double valor;
                cout << "Numero da conta: ";
                cin >> numeroBusca;

                // Mesma busca sequencial da opcao 3
                int indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                    }
                }

                if (indice == -1) {
                    cout << "Conta nao encontrada!" << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "Conta inativa!" << endl;
                } else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    // Garante que ainda ha espaco no historico antes de operar
                    cout << "Historico de movimentacoes cheio!" << endl;
                } else {
                    cout << "Valor do deposito: ";
                    cin >> valor;

                    if (valor <= 0) {
                        cout << "O valor deve ser positivo!" << endl;
                    } else {
                        // 1) Altera o saldo da conta
                        saldo[indice] = saldo[indice] + valor;

                        // 2) Registra a movimentacao no historico
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        cout << "Deposito realizado! Novo saldo: R$ " << saldo[indice] << endl;
                    }
                }
                break;
            }

            // -------------------------------------------------------------
            // 5 - SAQUE (verifica se ha saldo suficiente)
            // -------------------------------------------------------------
            case 5: {
                cout << "\n--- Saque ---" << endl;
                int numeroBusca;
                double valor;
                cout << "Numero da conta: ";
                cin >> numeroBusca;

                int indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                    }
                }

                if (indice == -1) {
                    cout << "Conta nao encontrada!" << endl;
                } else if (!contaAtiva[indice]) {
                    cout << "Conta inativa!" << endl;
                } else if (quantidadeMovimentacoes >= MAX_MOVIMENTACOES) {
                    cout << "Historico de movimentacoes cheio!" << endl;
                } else {
                    cout << "Valor do saque: ";
                    cin >> valor;

                    if (valor <= 0) {
                        cout << "O valor deve ser positivo!" << endl;
                    } else if (valor > saldo[indice]) {
                        // Regra do saque: nao pode sacar mais do que tem na conta
                        cout << "Saldo insuficiente! Saldo atual: R$ " << saldo[indice] << endl;
                    } else {
                        saldo[indice] = saldo[indice] - valor;

                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indice];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        cout << "Saque realizado! Novo saldo: R$ " << saldo[indice] << endl;
                    }
                }
                break;
            }

            // -------------------------------------------------------------
            // 6 - TRANSFERENCIA ENTRE DUAS CONTAS
            // -------------------------------------------------------------
            case 6: {
                cout << "\n--- Transferencia ---" << endl;
                int numeroOrigem, numeroDestino;
                double valor;

                cout << "Numero da conta de origem: ";
                cin >> numeroOrigem;
                cout << "Numero da conta de destino: ";
                cin >> numeroDestino;

                // Localiza as duas contas (-1 = nao encontrada)
                int indiceOrigem = -1;
                int indiceDestino = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroOrigem) {
                        indiceOrigem = i;
                    }
                    if (numeroConta[i] == numeroDestino) {
                        indiceDestino = i;
                    }
                }

                if (indiceOrigem == -1 || indiceDestino == -1) {
                    cout << "Conta de origem ou destino nao encontrada!" << endl;
                } else if (indiceOrigem == indiceDestino) {
                    cout << "Origem e destino devem ser contas diferentes!" << endl;
                } else if (!contaAtiva[indiceOrigem] || !contaAtiva[indiceDestino]) {
                    cout << "As duas contas precisam estar ativas!" << endl;
                } else if (quantidadeMovimentacoes + 2 > MAX_MOVIMENTACOES) {
                    // Precisamos de espaco para DOIS registros (saida + entrada)
                    cout << "Historico sem espaco para a transferencia!" << endl;
                } else {
                    cout << "Valor da transferencia: ";
                    cin >> valor;

                    if (valor <= 0) {
                        cout << "O valor deve ser positivo!" << endl;
                    } else if (valor > saldo[indiceOrigem]) {
                        cout << "Saldo insuficiente na conta de origem! Saldo: R$ "
                             << saldo[indiceOrigem] << endl;
                    } else {
                        // 1) Atualiza os saldos: sai de uma conta e entra na outra
                        saldo[indiceOrigem] = saldo[indiceOrigem] - valor;
                        saldo[indiceDestino] = saldo[indiceDestino] + valor;

                        // 2) Registro de SAIDA na conta de origem
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceOrigem];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'S';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        // 3) Registro de ENTRADA na conta de destino
                        contaMovimentacao[quantidadeMovimentacoes] = numeroConta[indiceDestino];
                        tipoMovimentacao[quantidadeMovimentacoes] = 'D';
                        valorMovimentacao[quantidadeMovimentacoes] = valor;
                        quantidadeMovimentacoes++;

                        cout << "Transferencia realizada com sucesso!" << endl;
                        cout << "Saldo conta " << numeroConta[indiceOrigem] << ": R$ "
                             << saldo[indiceOrigem] << endl;
                        cout << "Saldo conta " << numeroConta[indiceDestino] << ": R$ "
                             << saldo[indiceDestino] << endl;
                    }
                }
                break;
            }

            // -------------------------------------------------------------
            // 7 - EXTRATO
            // -------------------------------------------------------------
            case 7: {
                cout << "\n--- Extrato ---" << endl;
                int numeroBusca;
                cout << "Numero da conta: ";
                cin >> numeroBusca;

                int indice = -1;
                for (int i = 0; i < quantidadeContas; i++) {
                    if (numeroConta[i] == numeroBusca) {
                        indice = i;
                    }
                }

                if (indice == -1) {
                    cout << "Conta nao encontrada!" << endl;
                } else {
                    cout << "Extrato da conta " << numeroConta[indice]
                         << " - " << nomeCliente[indice] << endl;

                    bool temMovimentacao = false; // Para avisar se a conta ainda nao tem nada

                    for (int i = 0; i < quantidadeMovimentacoes; i++) {
                        if (contaMovimentacao[i] == numeroConta[indice]) {
                            temMovimentacao = true;

                            if (tipoMovimentacao[i] == 'D') {
                                cout << "Deposito: R$ " << valorMovimentacao[i] << endl;
                            } else if (tipoMovimentacao[i] == 'S') {
                                cout << "Saque: R$ " << valorMovimentacao[i] << endl;
                            }
                        }
                    }

                    if (!temMovimentacao) {
                        cout << "Nenhuma movimentacao registrada." << endl;
                    }
                    cout << "Saldo atual: R$ " << saldo[indice] << endl;
                }
                break;
            }

            // -------------------------------------------------------------
            // 0 - SAIR
            // -------------------------------------------------------------
            case 0:
                cout << "Saindo..." << endl;
                break;

            default:
                cout << "Opcao invalida, digite novamente." << endl;
                break;
        }

    } while (opcao != 0); // Repete o menu ate o usuario escolher 0 (Sair)

    return 0;
}
