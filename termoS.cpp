// TODO: 
// Adicionar interface
// Adicionar um metodo de dizer que a letra não esta na posicao correta
// ou fazer com que ele note automaticamente
// Ignorar diferenca entre minusculas e maiusculas
// Opcao de sair do programa
// Opcao de input vazio (std::cin nao para ate receber algo na stream)

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

//Retorna a distancia(diferenca) entre duas strings
//Quanto menor mais parecido
int distanciaLevenshtein(const string s1, const string s2) {
    const int m = s1.length();
    const int n = s2.length();
    int dp[m + 1][n + 1];

    for (int i{0}; i <= m; i++) {
        for (int j{0}; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else {
                dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1,
                                dp[i - 1][j - 1] + (s1[i - 1] != s2[j - 1])});
            }
        }
    }

    return dp[m][n];
}

int main(void) {
    set<char> nao_esta;
    set<string> testada;
    ifstream arquivo;

    cout << "Comece com \"aureo\"" << endl;

    do {
        string target, query;
        static string resposta{"aureo"};
        int dif{10000};
        cout << "Digite as letras corretas: ";
        cin  >> query;
        cout << "Digite as letras na posicao correta separadas por 0, se não há deixe vazio: ";
        string query_exata;
        cin  >> query_exata;
        cout << endl;

        for (const char c : resposta) {
            if (find(query.begin(), query.end(), c) == query.end()) {
                nao_esta.insert(c);
                cout << c << " Inserido" << endl;
            }
        }

        arquivo.close();
        arquivo.open("termoS.txt");

        while (arquivo >> target) {
            // FIX: Parar de usar booleanos para continuar o loop
            bool encontrado{false};

            if (find(testada.begin(), testada.end(), target) != testada.end())
                continue;

            for (const char c : target) {
                if (find(nao_esta.begin(), nao_esta.end(), c) != nao_esta.end()) {
                    encontrado = true;
                }
            }

            if (encontrado) continue;

            // FIX: Programa para quando query_exata
            //      esta vazia, em vez de continuar
            if (query_exata.compare("")) {
                for (int i{0}; i < 5; i++) {
                    if (query_exata[i] == '0') continue;
                    if (query_exata[i] != target[i]) encontrado = true;
                }
            }

            if (encontrado) continue;

            int new_dif{distanciaLevenshtein(target, query)};
            if (new_dif < dif) {
                dif = new_dif;
                resposta = target;
            }
        }

        cout << "Tente a palavra: " << resposta << endl;
        testada.insert(resposta);

    } while (true);

    arquivo.close();
    return 0;
}
