#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

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

Graph dijkstra(Graph G, int n, int v) {
    int cost[n];    // Custo 'cost[u]' para chegar a um vertice 'u' a partir de 'v'
    int prev[n];    // Vertice 'prev[u]' antecessor ou pai de 'u'
    int S[n];       // Vertices ja selecionados com custo minimo 

    // Inicializando os vetores
    for (int i = 0; i < n; i++) {
        cost[i] = INT32_MAX;
        prev[i] = -1;
        S[i] = 0;
    }

    cost[v] = 0; // setando o  custo de 'v' como 0, pois 'v' será a raiz da arvore de Dijkstra

    // Criando a fila de prioridade que retorna o menor valor (comparando o peso)
    priority_queue <Adjacency, vector<Adjacency>, Compare_Adj> queue;

    // Inserindo os vertices e seus custos na fila
    for (int i = 0; i < n; i++) {
        Adjacency e {cost[i], i};
        queue.push(e);
    }

    int count = 0;      // Criando contador que conta a quantidade de vertices selecionados
    while (count < n) {     // Enquanto houver vertices nao selecionados
        Adjacency e;

        // Retira o topo 'e' da fila e checa se:
        // 'e' possui os valores desatualizados ou se 'e.v' ja foi selecionado
        // caso verdade descarta 'e' e retira o novo topo 'e' e repete, caso contrario continua
        do {
            e = queue.top();
            queue.pop();
        } while (e.weight != cost[e.v] || S[e.v]);

        // Seleciona 'e.v' e incrementa o contador
        S[e.v] = 1;
        count++;

        // Para toda adjacencia do vertice de 'e'
        for (Adjacency a : G.adj[e.v]) {
            // atualiza o custo de 'e.v' se for menor que o custo atual
            if (a.weight + cost[e.v] < cost[a.v]) {
                cost[a.v] = a.weight + cost[e.v];
                prev[a.v] = e.v;    // atualiza o pai de 'e.v'

                queue.push(Adjacency {cost[a.v], a.v}); // coloca o vertice atualizado na fila
            }
        }
    }

    Graph Dtree (n);

    // Cria a arvore de dijkstra usando o prev[] e o cost[]
    for (int u = 1; u < n; u++) {
        int parent = prev[u];
        int weight = cost[u] - cost[parent];

        Dtree.adj[u].push_back(Adjacency {weight, parent});
        Dtree.adj[parent].push_back(Adjacency {weight, u});
    }

    return Dtree;
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

    Graph Dtree = dijkstra(G, n, 0);

    Dtree.print(n);

    return 0;
}