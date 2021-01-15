#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

struct Edge {
    int src, dest, weight;
};

class Graph {
    public:
        int N, M;       // Numero de vertices, Numero de arcos
        vector<vector<Edge>> adj_in;        // Adjacencias de entrada
        vector<vector<Edge>> adj_out;       // Adjacencias de saida

        Graph(int n) {
            adj_in.resize(n);
            adj_out.resize(n);
            N = n;
            M = 0;
        }

        // Adiciona aresta
        void add_edge(Edge e) {
            if (e.src > N || e.src < 0 || e.dest > N || e.dest < 0)
                return;

            adj_out[e.src].push_back(e);    // Adicionando adjacencia como saida
            adj_in[e.dest].push_back(e);    // Adicionando adjacencia como entrada

            M++;    
        }

        // Printa o grafo
        void const print() {
            for (int i = 0; i < N; i++) {
                cout << i  << " --> ";

                for (Edge e : adj_out[i])
                    cout << "(" << e.dest << ", weight: " << e.weight << ") ";
              cout << '\n';
            }
        }
};

vector<int> topological_sort(Graph G, vector<int> &sorted) {
    int S[G.N];             // Vetor marcando os vertices ja selecionados;
    int n_adj_in[G.N];      // Vetor com o numero de adjacencias de entrada de cada vertice.

    // Inicializando os dois vetores
    for (int i = 0; i < G.N; i++) {
        S[i] = 0;
        n_adj_in[i] = G.adj_in[i].size();
    }

    while (sorted.size() < G.N) {   //enquanto a ordenacao nao estiver completa

        // Encontra o proximo vertice fonte v ainda nao adicionado na ordenacao
        for (int v = 0; v < G.N; v++) {
            if (n_adj_in[v] == 0 && !S[v]) {
                // Marca v e o adiciona na ordenacao
                S[v] = 1;
                sorted.push_back(v);

                // Retira todas saidas de v
                for (Edge e : G.adj_out[v])
                    n_adj_in[e.dest]--;
                
                break;
            }
        }
    }
    return sorted;
}

int main(void) {
    int n, m;

    cin >> n >> m;

    Graph G (n);
    
    for (int i = 0; i < m; i++) {
        int x, y, w;

        cin >> x >> y >> w;

        G.add_edge(Edge {x, y, w});
    }
    vector<int> sorted;

    topological_sort(G, sorted);

    for (int i : sorted)
        cout << i << ' ';
    cout << '\n';

    return 0;
}