

#include <bits/stdc++.h>
using namespace std;

#define N 20
int c[N][N];
char b[N][N];
void LCSLength(string X, string Y){
  int m = X.length();
  int n = Y.length();
  int i, j;

  for(i = 0; i <= m; i++) c[i][0] = 0;
  for(j = 0; j <= n; j++) c[0][j] = 0;

  for(i = 1; i <= m; i++)
    for(j = 1; j <= n; j++)
      if(X[i-1] == Y[j-1])
      {
        c[i][j] = c[i-1][j-1] + 1;
        b[i][j] = '\\';
      }
      else
        if(c[i-1][j] >= c[i][j-1])
        {
          c[i][j] = c[i-1][j];
          b[i][j] = '|';
        }
        else
        {
          c[i][j] = c[i][j-1];
          b[i][j] = '-';
        }
}
void PrintLCS(string x, string y, int i, int j){
  if(i == 0 || j == 0)
    return;
  if(b[i][j] == '\\')
  {
    PrintLCS(x, y, i-1, j-1);
    cout << x[i-1];
  }
  else
    if(b[i][j] == '|')
      PrintLCS(x, y, i-1, j);
    else
      PrintLCS(x, y, i, j-1);
}
set<string> LCSall(string X, string Y, int m, int n)
{
    set<string> s;

    if (m == 0 || n == 0)
    {
        s.insert("");
        return s;
    }
    if (X[m - 1] == Y[n - 1])
    {
        set<string> tmp = LCSall(X, Y, m - 1, n - 1);
        for (string str : tmp)
            s.insert(str + X[m - 1]);
    }
    else
    {
        if (c[m - 1][n] >= c[m][n - 1])
            s = LCSall(X, Y, m - 1, n);
        if (c[m][n - 1] >= c[m - 1][n])
        {
            set<string> tmp = LCSall(X, Y, m, n - 1);
            s.insert(tmp.begin(), tmp.end());
        }
    }
    return s;
}
void printAll(set<string> s)
{   cout<< endl << "---Wszystkie NWP---" << endl;
    for (string str : s)
        cout << str << endl;
}
int main()
{
    //string X = "ABCBDAB";
    //string Y = "BDCABA";

    string X = "BAB";
    string Y = "ABA";
    int m = X.length();
    int n = Y.length();
    LCSLength(X,Y);
    cout << "---NWP---" << endl;
    PrintLCS(X,Y,m,n);
    set<string> s = LCSall(X, Y, m, n);
    printAll(s);

    return 0;
}
