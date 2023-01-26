#include <bits/stdc++.h>
using namespace std;
class DisjointUnionSets{
   vector<int> rank, parent;
   int n;
   public:
   DisjointUnionSets(int n){
      rank.resize(n);
      parent.resize(n);
      this->n = n;
      makeSet();
   }
   void makeSet(){
      for (int i = 0; i < n; i++)
      parent[i] = i;
   }
   int find(int x){
      if (parent[x] != x){
         return find(parent[x]);
      }
      return x;
   }
   void Union(int x, int y){
      int xRoot = find(x);
      int yRoot = find(y);
      if (xRoot == yRoot)
         return;
      if (rank[xRoot] < rank[yRoot])
         parent[xRoot] = yRoot;
      else if (rank[yRoot] < rank[xRoot])
         parent[yRoot] = xRoot;
      else {
         parent[yRoot] = xRoot;
         rank[xRoot] = rank[xRoot] + 1;
      }
   }
};
int findIslandCount(vector<vector<int>> mat){
   int n = mat.size();
   int m = mat[0].size();
   DisjointUnionSets *dus = new DisjointUnionSets(n * m);
   for (int j = 0; j < n; j++){
      for (int k = 0; k < m; k++){
         if (mat[j][k] == 0)
            continue;
         if (j + 1 < n && mat[j + 1][k] == 1)
            dus->Union(j * (m) + k, (j + 1) * (m) + k);
         if (j - 1 >= 0 && mat[j - 1][k] == 1)
            dus->Union(j * (m) + k, (j - 1) * (m) + k);
         if (k + 1 < m && mat[j][k + 1] == 1)
            dus->Union(j * (m) + k, (j) * (m) + k + 1);
         if (k - 1 >= 0 && mat[j][k - 1] == 1)
            dus->Union(j * (m) + k, (j) * (m) + k - 1);
         if (j + 1 < n && k + 1 < m && mat[j + 1][k + 1] == 1)
            dus->Union(j * (m) + k, (j + 1) * (m) + k + 1);
         if (j + 1 < n && k - 1 >= 0 && mat[j + 1][k - 1] == 1)
            dus->Union(j * m + k, (j + 1) * (m) + k - 1);
         if (j - 1 >= 0 && k + 1 < m && mat[j - 1][k + 1] == 1)
            dus->Union(j * m + k, (j - 1) * m + k + 1);
         if (j - 1 >= 0 && k - 1 >= 0 && mat[j - 1][k - 1] == 1)
            dus->Union(j * m + k, (j - 1) * m + k - 1);
      }
   }
   int *c = new int[n * m];
   int islands = 0;
   for (int j = 0; j < n; j++){
      for (int k = 0; k < m; k++){
         if (mat[j][k] == 1){
            int x = dus->find(j * m + k);
            if (c[x] == 0){
               islands++;
               c[x]++;
            }
            else
            c[x]++;
         }
      }
   }
   return islands;
}
int main(void){
   int n,a;
   vector<vector<int>> mat;
   cout<<"Enter the  matrix size:\n";
   cin>>n;
   for(int i=0;i<n;i++){
       vector<int> temp;
       for(int j=0;j<n;j++){
           cin>>a;
           temp.push_back(a);
       }
       mat.push_back(temp);
   }
   
   cout<<"The number of islands in binary matrix is : "<<findIslandCount(mat);
}