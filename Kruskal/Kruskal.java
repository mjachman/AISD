import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

class Node{
  int key;
  int rank;
  Node parent;
}
class DisjointSets{
  public static Node findSet(Node x){
    if (x != x.parent){
      x.parent = findSet(x.parent);
    }
    return x.parent;
  }
static void union(Node x, Node y){
  if(y.rank > x.rank)
  {
    x.parent = y;
  }
  else
  {
    y.parent = x;
    if(x.rank==y.rank)
    {
      x.rank++;
    }
  }
}
static Node makeSet(int k)
{
    Node x=new Node();
    x.key=k;
    x.parent=x;
    x.rank=0;
    return x;
}
}
class Graph{
  List<Integer> vertices = new ArrayList<>();
  List<Edge> edges = new ArrayList<>();

  void addVertex(int value){
    vertices.add(value);
  }
  void addEdge(int u, int v, int weight){
    edges.add(new Edge(u, v, weight));
  }
  void sortEdges(){
    Collections.sort(edges, new Comparator<Edge>(){
      public int compare(Edge e1, Edge e2){
        return e1.weight-e2.weight;
      }
    });
  }
}
class Edge{
  int u;
  int v;
  int weight;

  public Edge(int u, int v, int weight){
    this.u = u;
    this.v = v;
    this.weight = weight;
  }

  void printEdge(){
    System.out.println(this.u + "---"+ this.v+ " waga: " + this.weight);
  }
}
 class Kruskal{
  static void kruskal(Graph graph){
    Node[] vertices = new Node[graph.vertices.size()+1];
    for (int i = 0; i < graph.vertices.size(); i++){
      vertices[graph.vertices.get(i)] =
              DisjointSets.makeSet(graph.vertices.get(i));
    }    
    graph.sortEdges();
    for (Edge edge : graph.edges){
        Node ru=DisjointSets.findSet(vertices[edge.u]);
        Node rv=DisjointSets.findSet(vertices[edge.v]);
      if (ru != rv){
        edge.printEdge();  
        DisjointSets.union(ru,rv);
      }   
    }
  }
  public static void main(String[] args){
    Graph graph = new Graph();
    
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addVertex(6);
    graph.addVertex(7);
    
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 7, 6);
    graph.addEdge(1, 6, 6);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 7, 8);
    graph.addEdge(3, 7, 8);
    graph.addEdge(3, 4, 3);
    graph.addEdge(4, 7, 10);
    graph.addEdge(4, 5, 4);
    graph.addEdge(4, 7, 10);
    graph.addEdge(5, 6, 5);
    graph.addEdge(6, 7, 10);
    
    Kruskal.kruskal(graph);
  }
}