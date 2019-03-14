
#include <iostream>
#include <tuple>
#include <queue>
#include <list> 
using namespace std; 
# define INF 1000000000 
  
typedef pair<int, int> iPair; 
  
 
class Graph 
{ 
    int V;    // количество вершин  
    list< pair<int, int> > *adj; //лист пар: вершина - ее вес
  
public: 
    Graph(int V);  
    
    void addEdge(int u, int v, int w); 

    void shortestPath(int s); 
}; 
   
Graph::Graph(int V) 
{ 
    this->V = V; 
    adj = new list<iPair> [V]; 
} 
  
void Graph::addEdge(int u, int v, int w) 
{ 
    cout << u << " " << v << " " << w << endl; 
    adj[u].push_back(make_pair(v, w)); 
    adj[v].push_back(make_pair(u, w)); 
} 
   
void Graph::shortestPath(int src) 
{ 
    
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq; // приоритетная очередь для вершин, которые еще обрабатываются
   
    vector<int> dist(V, INF); // вектор расстояний до каждой вершины 
  
    pq.push(make_pair(0, src)); 
    dist[src] = 0; 
  

    while (!pq.empty()) 
    {   
        // обращаемся к вершине с наименьшим расстоянием и
        // здесь же удаляем ее
        int u = pq.top().second; 
        pq.pop(); 
  
        // итерируемся по всем вершинам, с которыми соединена u-ая вершина 
        list< pair<int, int> >::iterator i; 
        for (i = adj[u].begin(); i != adj[u].end(); ++i) 
        { 
            //  v - вершина, weight - вес ребра между u и v
            int v = (*i).first; 
            int weight = (*i).second; 
  
            if (dist[v] > dist[u] + weight) 
            { 
                dist[v] = dist[u] + weight; 
                // Помещаем в кучу пару(расстояние, вершина),
                // чтобы дальше идти от вершины с наименьшим расстоянием
                pq.push(make_pair(dist[v], v)); 
            } 
        } 
    } 
  
    cout << "Vertex   Distance from Source" << endl; 
    for (int i = 0; i < V; ++i) 
        cout << i << "\t\t" << dist[i] << endl; 
} 
  
int main() 
{  
    int V = 6; 
    Graph g(V); 
    // пример взят с https://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%94%D0%B5%D0%B9%D0%BA%D1%81%D1%82%D1%80%D1%8B
    g.addEdge(0, 1, 7); 
    g.addEdge(0, 2, 9); 
    g.addEdge(0, 5, 14);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 5, 2);
    g.addEdge(2, 3, 11);
    g.addEdge(4, 5, 9);
    g.addEdge(3, 4, 6); 
  
    g.shortestPath(0); 
  
    return 0; 
} 
