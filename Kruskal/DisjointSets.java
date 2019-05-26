package rzr;

class Node{
  int key;
  Node parent;
  int rank;
}

class DisjointSets{
static Node makeSet(int k)
{
    Node x=new Node();
    x.key=k;
    x.parent=x;
    x.rank=0;
    return x;
}
static Node findSet(Node x)
{
    if(x!=x.parent)
    {
        x.parent= findSet(x.parent);
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

static void printPath(Node x,String s)
{
if(x.parent==x)
{
System.out.println(s+ x.key+"("+x.rank+ ")");
return;
}
printPath(x.parent,s+x.key+"->");
}

    public static void main(String[] args) {
        Node z1=makeSet(1);
        Node z2=makeSet(2);
        Node z3=makeSet(3);
        Node z4=makeSet(4);
        Node z5=makeSet(5);
        Node z6=makeSet(6);
        Node z7=makeSet(7);
        Node z8=makeSet(8);
        Node z9=makeSet(9);

       union(findSet(z1),findSet(z2));
       union(findSet(z3),findSet(z4));
       union(findSet(z5),findSet(z4));
       union(findSet(z1),findSet(z5));
       union(findSet(z6),findSet(z7));
       union(findSet(z8),findSet(z9));
       union(findSet(z6),findSet(z8));
       union(findSet(z7),findSet(z4));
       
       printPath(z1,"");
       printPath(z2,"");
       printPath(z3,"");
       printPath(z4,"");
       printPath(z5,"");     
       printPath(z6,"");
       printPath(z7,"");
       printPath(z8,"");
       printPath(z9,"");

    }
    
}
