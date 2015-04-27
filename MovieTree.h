#ifndef MOVIETREE_H
#define MOVIETREE_H

#include<string>

struct MovieNode
{
  MovieNode();
  MovieNode(int& rank, std::string& ttl, int& yr, int& qtty);
  virtual ~MovieNode();
  friend std::ostream& operator<<(std::ostream& os, MovieNode* n);

  MovieNode* parent;
  MovieNode* left;
  MovieNode* right;
    int ranking;
    std::string title;
    int year;
    int quantity;
};


class MovieTree
{
public:
  MovieTree();
  virtual ~MovieTree();

  inline void test()
  {
    delete_tree(root);
  }

  void addRawNode(int&, std::string&, int&, int&);
  void insert(MovieNode*);        
  void insert(MovieNode*, MovieNode*);  
  void inorder_walk();          
  MovieNode* search(std::string&);    
  MovieNode* iterative_search(std::string&); 
  MovieNode* minimum();         
  MovieNode* maximum();         

private:
  MovieNode *root;

  void inorder_walk(MovieNode*);      
  MovieNode* search(MovieNode*, std::string&);
  MovieNode* minimum(MovieNode*);     
  MovieNode* maximum(MovieNode*);     
  MovieNode* successor(MovieNode*);   
  MovieNode* predecessor(MovieNode*);   
  void transplant(MovieNode*, MovieNode*);
  void delete_node(MovieNode*);     
  void delete_tree(MovieNode*);     
};

#endif // MOVIETREE_H
