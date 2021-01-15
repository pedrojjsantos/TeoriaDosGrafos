#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

// Adjacencia com peso e destino
struct Adjacency {
    int weight, v;
};

// Operador '>' para comparar pesos de adjacencias
struct Compare_Adj {
    bool operator() (const Adjacency &a, const Adjacency &b) {
        return a.weight > b.weight;
    }
};

class Graph {
    public:
        vector<vector<Adjacency>> adj;  // Vetor de adjacencias

        Graph(int n) {
            adj.resize(n);
        }

        // Printa o grafo
        void const print(int n) {
            for (int i = 0; i < n; i++) {
                cout << i << " --> ";

                for (Adjacency e : adj[i])
                    cout << "(" << e.v << ", weight: " << e.weight << ") ";
                cout << '\n';
            }
        }
};

Graph prim(Graph G, int n) {
    // Menor peso das arestas de 'u' (com o extremo 'prev[u]' ja selecionado (S[prev[u]] == 1))
    int weights[n]; 
    int prev[n];    // Vertice 'prev[u]' antecessor de 'u' que forma aresta com peso minimo
    int S[n];       // Vertices ja selecionados com peso minimo

    // Inicializando os vetores
    for (int i = 0; i < n; i++) {
        weights[i] = INT32_MAX;
        prev[i] = -1;
        S[i] = 0;
    }

    // setando o peso e 'prev' de 'v' como 0, pois 'v' será a raiz da arvore geradora
    prev[0] = 0;
    weights[0] = 0;
    
    // Criando a fila de prioridade que retorna o menor valor (comparando o peso)
    priority_queue < Adjacency, vector<Adjacency>, Compare_Adj > queue;

    // Inserindo os vertices e seus custos na fila
    for (int i = 0; i < n; i++) {
        Adjacency e {weights[i], i};
        queue.push(e);
    }

    int count = 0;  // Criando contador que conta a quantidade de vertices selecionados
    while (count < n) { // Enquanto houver vertices nao selecionados
        Adjacency e;

        // Retira o topo 'e' da fila e checa se:
        // 'e' possui os valores desatualizados ou se 'e.v' ja foi selecionado
        // caso verdade descarta 'e' e retira o novo topo 'e' e repete, caso contrario continua
        do {
            e = queue.top();
            queue.pop();
        } while (e.weight != weights[e.v] || S[e.v] == 1);

        int v = e.v;
        // Seleciona 'e.v' e incrementa o contador
        S[v] = 1;
        count++;

        // Para cada aresta de v
        for (Adjacency edge : G.adj[v]) {
            int u = edge.v;
            int weight = edge.weight;

            // Se nao tiver sido seleciona e possuir um peso menor que o peso minimo atual
            if (!S[u] && weight < weights[u]) {
                // Atualiza o peso minimo e o antecessor do vertice
                weights[u] = weight;
                prev[u] = v;

                // coloca os valores atualizados na fila
                queue.push(Adjacency{weight, u});
            }
        }
    }

    Graph tree (n);

    // Cria arvore geradora com as arestas selecionadas e a retorna
    for (int v = 1; v < n; v++) {
        int parent = prev[v];

        tree.adj[v].push_back(Adjacency{weights[v], parent});
        tree.adj[parent].push_back(Adjacency{weights[v], v});
    }

    return tree;
}

int main(void) {
    int n, m;

    cin >> n >> m;

    Graph G (n);
    
    for (int i = 0; i < m; i++) {
        int x, y, w;
        
        cin >> x >> y >> w;

        G.adj[x].push_back(Adjacency {w, y});
        G.adj[y].push_back(Adjacency {w, x});
    }

    Graph tree = prim(G, n);

    tree.print(n);

    return 0;
}