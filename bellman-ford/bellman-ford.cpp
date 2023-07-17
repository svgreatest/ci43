#include <vector>
#include <iostream>
#include <map>

const int INF= 1000000000;

class Edge {
    public:
        int u;
        int v;
        int w;
        Edge(int u, int v, int w) : u(u), v(v), w(w) {}
        friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
            os << "(" << e.u << ", " << e.v << ", " << e.w << ")";
            return os;
        }
};

class DirectedGraph {
    public:
        std::map<int, std::vector<Edge>> adj_list;
        std::vector<std::vector<int>> shortest_paths;
    
        DirectedGraph() {
            adj_list = {};
        }

        int bellman_ford_dp(int s, int t);
        void add_edge(const Edge& e);
        int get_no_of_edges();
        void print_graph();
        int get_no_of_vertices();
        void set_weights(std::vector<int>);
        
};

void DirectedGraph::add_edge(const Edge& e) {
    adj_list[e.u].push_back(e);
    if (adj_list.find(e.v) == adj_list.end()) {
        adj_list[e.v] = {};
    }
}

int DirectedGraph::get_no_of_edges() {
    int edges = 0;
    for (auto it = adj_list.begin(); it != adj_list.end(); it++) {
        edges += it->second.size();
    }
    return edges;
}

int DirectedGraph::get_no_of_vertices() {
    return adj_list.size();
}

void DirectedGraph::print_graph() {
    for (auto it = adj_list.begin(); it != adj_list.end(); it++) {
        std::cout << it->first << ": ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            std::cout << *it2 << " ";
        }
        std::cout << std::endl;
    }
}

int DirectedGraph::bellman_ford_dp(int s, int t) {
    int n = get_no_of_vertices();
    std::cout<<"n: "<<n<<std::endl;
    shortest_paths.resize(n);
    for (int i = 0; i < n; i++) {
        shortest_paths[i].resize(n);
    }
    for(int i = 0; i < n; i++) {
        shortest_paths[0][i] = INF;
    }
    std::cout<<"Shortest paths matrix before: "<<std::endl;
        shortest_paths[0][t] = 0;
    for(int i = 1; i <= n-1; i++) {
        for (int v = 0; v < n; v++) {
            shortest_paths[i][v] = shortest_paths[i - 1][v];
            for (auto it = adj_list[v].begin(); it != adj_list[v].end(); it++) {
                std::cout <<"i :"<<i<<" v: " << v << " it->v: " << it->v << " it->w: " << it->w << std::endl;
                    if(shortest_paths[i - 1][it->v] != INF) {
                        shortest_paths[i][v] = std::min(shortest_paths[i][v], shortest_paths[i - 1][it->v] + it->w);
                    }
            }
        }
    }
    std::cout << "Shortest paths matrix after: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << shortest_paths[i][j] << "\t\t";
        }
        std::cout << std::endl;
    }
    return shortest_paths[n-1][s];
}

int main() {
    DirectedGraph g;
    g.add_edge(Edge(0, 5, -3));
    g.add_edge(Edge(0, 1, -4));
    g.add_edge(Edge(1, 4, -2));
    g.add_edge(Edge(1, 3, -1));
    g.add_edge(Edge(2, 1, 8));
    g.add_edge(Edge(2, 5, 3));
    g.add_edge(Edge(3, 0, 6));
    g.add_edge(Edge(3, 5, 4));
    g.add_edge(Edge(4, 2, -3));
    g.add_edge(Edge(4, 5, 2));
    g.print_graph();
    int source = 0;
    int destination = 5;
    int ans = g.bellman_ford_dp(source, destination);
    std::cout<< "Shortest path from 0 to 6: " << ans << std::endl;

}