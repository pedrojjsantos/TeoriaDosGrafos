#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;

struct Edge {
    int src, dest, weight;
};

// Operador '<' para comparar pesos de arestas
struct Compare_Edges {
    bool operator() (const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    }
};

// Conjunto(arvore) para Union-Find
struct Subset {
    int parent, rank;
};

class Graph {
    public:
        int N, M;       // Numero de vertices, Numero de arcos
        vector<vector<Edge>> adj;   // Vetor de adjacencias

        Graph(int n) {
            adj.resize(n);
            N = n;
        }

        // Adiciona aresta
        void add_edge(Edge e) {
            if (e.src > N || e.src < 0 || e.dest > N || e.dest < 0)
                return;

            Edge reverse_e {e.dest, e.src, e.weight}; // invertendo a aresta (v u) para (u v)

            adj[e.src].push_back(e);            // Adicionando aresta (v, u) em v
            adj[e.dest].push_back(reverse_e);   // Adicionando aresta (u, v) em u
            M++;
        }

        // Printa o grafo
        void const print() {
            for (int i = 0; i < N; i++) {
                cout << i  << " --> ";

                for (Edge e : adj[i])
                    cout << "(" << e.dest   << ", weight: "
                                << e.weight << ") ";
              cout << '\n';
            }
        }
};

int Find(Subset S[], int x) {
    /*  Se x nao é o representante de seu conjunto,
        encontra esse representante,
        torna-o pai de x e o retorna.  */
    if (S[x].parent != x)
        S[x].parent = Find(S, S[x].parent);

    return S[x].parent;
}

void Union(Subset S[], int x, int y) {
    // Adiciona a arvore com menor rank como sub-arvore da outra
    if (S[x].rank > S[y].rank)
        S[y].parent = x;
    else if (S[x].rank < S[y].rank)
        S[x].parent = y;

    // Caso possuam mesmo rank
    else {
        S[y].parent = x;    // adiciona a arvore com raiz y como sub-arvore de x
        S[x].rank++;        // incrementa o rank de x
    }
}

Graph kruskal(Graph G) {
    Subset subsets[G.N];    // Cria a floresta do Union-Find

    // Inicializa a floresta
    for (int i = 0; i < G.N ;i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    vector<Edge> edges;     // Vetor com todas arestas
    vector<Edge> S;         // Vetor com arestas selecionadas

    // Adicionando todas arestas distintas de 'G' em 'edges'
    for (auto adj : G.adj) { 
        for (Edge e : adj) {
            // adicionando em 'edges' a primeira das copias de 'e'( (v u) e (u v) )
            if (e.src < e.dest)     
                edges.push_back(e);
        }
    }

    // Ordenando as arestas pelo peso, de forma crescente
    std::sort(edges.begin(), edges.end(), Compare_Edges{});

    for (Edge e : edges) {
        // Se os extremos da aresta 'e' estiverem na mesma componente, pula para proxima aresta
        if (Find(subsets, e.src) == Find(subsets, e.dest))
            continue;

        // Caso contrario seleciona 'e' e funde as componentes de seus extremos
        S.push_back(e); 
        Union(subsets, Find(subsets, e.src) ,Find(subsets, e.dest));
    }

    Graph tree (G.N);

    // Cria arvore geradora com as arestas selecionadas e a retorna
    for (Edge e : S)
        tree.add_edge(e);
    
    return tree;
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

    Graph tree = kruskal(G);

    tree.print();

    return 0;
}