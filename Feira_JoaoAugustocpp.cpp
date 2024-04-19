#include <iostream>
#include <fstream>

using namespace std;
 // forçar que não seja alterado os valores
const int PedidoMAX = 100;
const int MAX_BEBIDAS = 100;

struct Estoque {
    double queijo;
    double presunto;
    double frango;
};

struct Pedido {
    int numeroPedido;
    string nomeCliente;
    string saborPastel;
    int quantidade;
    string* bebidas;
    int quantidadeBebida;
};

void inicializarEstoque(Estoque& estoque) {
    estoque.queijo = 50000.0;
    estoque.presunto = 20000.0;
    estoque.frango = 10000.0;
}

void atualizarEstoque(Estoque& estoque, const string& saborPastel, int quantidade) {
    if (saborPastel == "Pizza") {
        estoque.queijo -= 30.0 * quantidade;
        estoque.presunto -= 30.0 * quantidade;
    } else if (saborPastel == "Frango") {
        estoque.frango -= 30.0 * quantidade;
    } else if (saborPastel == "Queijo") {
        estoque.queijo -= 50.0 * quantidade;
    }
}

void liberarMemoriaPedidos(Pedido* pedidos, int numPedidos) {
    for (int i = 0; i < numPedidos; ++i) {
        if (pedidos[i].saborPastel == "Pizza" || pedidos[i].saborPastel == "Frango" ||
            pedidos[i].saborPastel == "Queijo" || pedidos[i].saborPastel == "Vento") {
            delete[] pedidos[i].bebidas;
        }
    }
    delete[] pedidos;
}

void ListaPedidos(Pedido* pedidos, int& numPedidos, Estoque& estoque) {
    if (numPedidos < PedidoMAX) {
        char resp = 'S';

        do {
            Pedido* novoPedido = new Pedido;

            novoPedido->numeroPedido = numPedidos + 1;

            cout << "\nDigite o nome do cliente: ";
            getline(cin, novoPedido->nomeCliente); // facilitar a entrada de arquivos

            do {
                cout << "Digite o sabor do pastel: ";
                getline(cin, novoPedido->saborPastel);

                cout << "Digite a quantidade: ";
                cin >> novoPedido->quantidade;

                cin.ignore();

                if (novoPedido->saborPastel == "Pizza" || novoPedido->saborPastel == "Frango" ||
                    novoPedido->saborPastel == "Queijo" || novoPedido->saborPastel == "Vento") {
                    novoPedido->bebidas = new string[MAX_BEBIDAS];

                    cout << "Escolha a bebida (Coca-Cola ou Pepsi): ";
                    getline(cin, novoPedido->bebidas[0]);

                    cout << "Digite a quantidade da bebida: ";
                    cin >> novoPedido->quantidadeBebida;
                }

                pedidos[numPedidos++] = *novoPedido;

                atualizarEstoque(estoque, novoPedido->saborPastel, novoPedido->quantidade);

                cout << "Gostaria de incluir outro sabor no pedido? (S/N): ";
                cin >> resp;

                cin.ignore();

            } while (resp == 'S' || resp == 's');

            cout << "Pedido cadastrado com sucesso!" << endl;

            cout << "Gostaria de cadastrar outro pedido? (S/N): " << endl;
            cin >> resp;

            cin.ignore();

        } while (resp == 'S' || resp == 's');
    } else {
        cout << "Limite máximo de pedidos atingido." << endl;
    }
}

void mostrarPedidos(const Pedido* pedidos, int numPedidos) {
    if (numPedidos > 0) {
        cout << "Lista de Pedidos:" << endl;
        for (int i = 0; i < numPedidos; ++i) {
            cout << "Cliente: " << pedidos[i].nomeCliente << "\tSabor: " << pedidos[i].saborPastel
                 << "\tQuantidade: " << pedidos[i].quantidade;
            if (pedidos[i].saborPastel == "Pizza" || pedidos[i].saborPastel == "Frango") {
                cout << "\tBebida: " << pedidos[i].bebidas[0];
            }
            cout << endl;
        }
    } else {
        cout << "Nao ha pedidos cadastrados." << endl;
    }
}

void editarPedido(Pedido* pedidos, int numPedidos, Estoque& estoque) {
    if (numPedidos > 0) {
        int senhaPedido;
        cout << "Digite a senha do pedido que deseja editar: ";
        cin >> senhaPedido;

        cin.ignore();

        for (int i = 0; i < numPedidos; ++i) {
            if (pedidos[i].quantidade > 0 && senhaPedido == i + 1) {
                cout << "Informacoes atuais do pedido:" << endl;
                cout << "Cliente: " << pedidos[i].nomeCliente << "\tSabor: " << pedidos[i].saborPastel
                     << "\tQuantidade: " << pedidos[i].quantidade;
                if (pedidos[i].saborPastel == "Pizza" || pedidos[i].saborPastel == "Frango") {
                    cout << "\tBebida: " << pedidos[i].bebidas[0];
                }
                cout << endl;

                cout << "Digite o novo sabor do pastel: ";
                getline(cin, pedidos[i].saborPastel);

                cout << "Digite a nova quantidade: ";
                cin >> pedidos[i].quantidade;

                cin.ignore();

                if (pedidos[i].saborPastel == "Pizza" || pedidos[i].saborPastel == "Frango" ||
                    pedidos[i].saborPastel == "Queijo" || pedidos[i].saborPastel == "Vento") {
                    cout << "Escolha a nova bebida (Coca-Cola ou Pepsi): ";
                    getline(cin, pedidos[i].bebidas[0]);

                    cout << "Digite a nova quantidade da bebida: ";
                    cin >> pedidos[i].quantidadeBebida;
                }

                atualizarEstoque(estoque, pedidos[i].saborPastel, pedidos[i].quantidade);

                cout << "Pedido editado com sucesso!" << endl;
                return;
            }
        }
        cout << "Pedido nao encontrado." << endl;
    } else {
        cout << "Nao ha pedidos cadastrados." << endl;
    }
}

void entregarPedido(Pedido* pedidos, int& numPedidos, Estoque& estoque) {
    if (numPedidos > 0) {
        int senhaPedido;
        cout << "Digite a senha do pedido entregue: ";
        cin >> senhaPedido;

        cin.ignore();

        for (int i = 0; i < numPedidos; ++i) {
            if (pedidos[i].quantidade > 0 && senhaPedido == i + 1) {
                atualizarEstoque(estoque, pedidos[i].saborPastel, pedidos[i].quantidade);
                pedidos[i].quantidade = 0;

                cout << "Pedido entregue com sucesso!" << endl;
                return;
            }
        }
        cout << "Pedido nao encontrado." << endl;
    } else {
        cout << "Nao ha pedidos cadastrados." << endl;
    }
}

void gerarRelatorio(const Pedido* pedidos, int numPedidos, const Estoque& estoque) {
    ofstream arquivoRelatorio("relatorio.txt");

    if (arquivoRelatorio.is_open()) {
        arquivoRelatorio << "Relatorio de Vendas do Dia:" << endl << endl;

        int totalVendidos = 0;

        arquivoRelatorio << "Pedidos Cadastrados:" << endl;
        for (int i = 0; i < numPedidos; ++i) {
            if (pedidos[i].quantidade > 0) {
                arquivoRelatorio << "Cliente: " << pedidos[i].nomeCliente << "\tSabor: " << pedidos[i].saborPastel
                                 << "\tQuantidade: " << pedidos[i].quantidade;
                if (pedidos[i].saborPastel == "Pizza" || pedidos[i].saborPastel == "Frango") {
                    arquivoRelatorio << "\tBebida: " << pedidos[i].bebidas[0];
                }
                arquivoRelatorio << endl;
                totalVendidos += pedidos[i].quantidade;
            }
        }

        arquivoRelatorio << "\nTotal de Pasteis Vendidos: " << totalVendidos << endl;

        arquivoRelatorio << "\nRelatorio de Estoque:" << endl;
        arquivoRelatorio << "Queijo: " << estoque.queijo << " gramas" << endl;
        arquivoRelatorio << "Presunto: " << estoque.presunto << " gramas" << endl;
        arquivoRelatorio << "Frango: " << estoque.frango << " gramas" << endl;

        cout << "Relatorio gerado com sucesso (arquivo: relatorio.txt)." << endl;
        arquivoRelatorio.close();
    } else {
        cout << "Erro ao abrir o arquivo de relatorio." << endl;
    }
}

int main() {
    Pedido* pedidos = new Pedido[PedidoMAX];
    int numPedidos = 0;

    Estoque estoque;
    inicializarEstoque(estoque);

    int escolha;

    do {
        cout << "\n=== Menu da Feira de Pastel ===" << endl;
        cout << "1. Cadastrar Pedido" << endl;
        cout << "2. Editar Pedido" << endl;
        cout << "3. Entregar Pedido" << endl;
        cout << "4. Mostrar Pedidos" << endl;
        cout << "5. Imprimir Relatorio de Vendas" << endl;
        cout << "6. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        cin.ignore();

        switch (escolha) {
            case 1:
                cout << "Sabores disponiveis: \n";
                cout << "Pizza" << endl << "Frango" << endl << "Queijo" << endl << "Vento" << endl;
                ListaPedidos(pedidos, numPedidos, estoque);
                break;
            case 2:
                editarPedido(pedidos, numPedidos, estoque);
                break;
            case 3:
                entregarPedido(pedidos, numPedidos, estoque);
                break;
            case 4:
                mostrarPedidos(pedidos, numPedidos);
                break;
            case 5:
                gerarRelatorio(pedidos, numPedidos, estoque);
                break;
            case 6:
                cout << "Saindo do programa. Obrigado!" << endl;
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }

    } while (escolha != 6);

    liberarMemoriaPedidos(pedidos, numPedidos);

    return 0;
}