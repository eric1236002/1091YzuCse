// xtree internal header

#define red Color::Red
#define black Color::Black
using std::swap;

#ifndef XTREE
#define XTREE

enum class Color{ Red, Black }; // colors for link to parent

template< typename Ty >
struct TreeNode
{
   using NodePtr = TreeNode *;
   using value_type = Ty;

   NodePtr    left;   // left subtree, or smallest element if head
   NodePtr    parent; // parent, or root of tree if head
   NodePtr    right;  // right subtree, or largest element if head
   Color      color;  // Red or Black, Black if head
   bool       isNil;  // true only if head (also nil) node
   value_type myval;  // the stored value, unused if head
};

// CLASS TEMPLATE TreeVal
template< typename Ty >
class TreeVal
{
public:
   using NodePtr = TreeNode< Ty > *;

   using value_type = Ty;
   using size_type  = size_t;

   TreeVal()
      : myHead( new TreeNode< value_type > ),
        mySize( 0 )
   {
      myHead->left = myHead;
      myHead->parent = myHead;
      myHead->right = myHead;
      myHead->color = Color::Black;
      myHead->isNil = true;
   }

   ~TreeVal()
   {
      clear( myHead->parent );
      delete myHead;
   }

   // Removes all elements from the set object (which are destroyed)
   void clear( TreeNode< value_type > *node )
   {
      if( !node->isNil ) // node is not an external node
      {
         clear( node->left );
         clear( node->right );
         delete node;
      }
   }

   // rebalance for insertion
   void reBalance( TreeNode< value_type > *node )
   {  // node->parent cannot be the root
       auto p = node->parent, g = p->parent, u = p == g->left ? g->right : g->left;

       if (p->isNil) { node->color = black; return; }

       if (p->color == black) return;

       if (u->color == red)
       {
           p->color = u->color = black;
           g->color = red;
           reBalance(g);
       }
       else
       {
           if (p == g->left)
           {
               if (node == p->left) LLRotation(p), swap(p->color, g->color);       // LLb
               else LRRotation(node), swap(node->color, g->color);                 // LRb
           }
           else
           {
               if (node == p->left) RLRotation(node), swap(node->color, g->color); // RLb
               else RRRotation(p), swap(p->color, g->color);                       // RRb
           }
       }
   }

   // rotate right at g, where p = g->left and node = p->left
   //void set< Kty >::LLbRotation( TreeNode< value_type > *node )
   void LLRotation( TreeNode< value_type > *p )
   {
       auto g = p->parent;

       g->left = p->right;
       if (!p->right->isNil) p->right->parent = g;
       
       p->parent = g->parent;
       if (g->parent->isNil) myHead->parent = p;
       else g == g->parent->left ? g->parent->left = p : g->parent->right = p;

       p->right = g;
       g->parent = p;
   }

   // LR rotation; p = g->left and node = p->right
   void LRRotation( TreeNode< value_type > *node )
   {
       RRRotation(node);
       LLRotation(node);
   }

   // RL rotation; p = g->right and node = p->left
   void RLRotation( TreeNode< value_type > *node )
   {
       LLRotation(node);
       RRRotation(node);
   }

   // rotate left at g, where p = g->right and node = p->right
   //void set< Kty >::RRbRotation( TreeNode< value_type > *node )
   void RRRotation( TreeNode< value_type > *p )
   {
       auto g = p->parent;

       g->right = p->left;
       if (!p->left->isNil) p->left->parent = g;

       p->parent = g->parent;
       if (g->parent->isNil) myHead->parent = p;
       else g == g->parent->left ? g->parent->left = p : g->parent->right = p;

       p->left = g;
       g->parent = p;
   }

   // erase node provided that the degree of node is at most one
   void eraseDegreeOne( TreeNode< value_type > *node )
   {
       auto p = node->parent, c = node->left->isNil ? node->right : node->left;

       if (node->color == black && c->color == black && p->isNil)
       {
           myHead->parent = c;
           c->parent = myHead;
       }
       else
       {
           node == p->left ? p->left = c : p->right = c;
           if (!c->isNil) c->parent = p;

           if (node->color == black && c->color == black) fixUp(c, p);
           else if (node->color == black) c->color = black;
       }

       delete node;
       --mySize;
   }

   // rebalance for deletion
   void fixUp( TreeNode< value_type > *N, TreeNode< value_type > *P )
   {
       auto s = N == P->left ? P->right : P->left;

       if (s->color == red)
       {
           swap(s->color, P->color);
           N == P->left ? RRRotation(s) : LLRotation(s);
       }

       s = N == P->left ? P->right : P->left;

       if (s->color == black && s->right->color == black && N == P->left && s->left->color == red)
       {
           swap(s->color, s->left->color);
           LLRotation(s->left);
       }
       if (s->color == black && s->left->color == black && N == P->right && s->right->color == red)
       {
           swap(s->color, s->right->color);
           RRRotation(s->right);
       }

       s = N == P->left ? P->right : P->left;

       if (s->color == black && s->right->color == red && N == P->left)
       {
           swap(P->color, s->color);
           s->right->color = black;
           RRRotation(s);
           return;
       }
       if (s->color == black && s->left->color == red && N == P->right)
       {
           swap(P->color, s->color);
           s->left->color = black;
           LLRotation(s);
           return;
       }

       if (s->color == black && s->right->color == black && s->left->color == black)
       {
           if (P->color == red) swap(s->color, P->color);
           else s->color = red, fixUp(P, P->parent);
       }
   }
/*
   // preorder traversal and inorder traversal
   void twoTraversals()
   {
      cout << "Preorder sequence:\n";
      preorder( myHead->parent );

      cout << "\nInorder sequence:\n";
      inorder( myHead->parent );
      cout << endl;
   }

   // preorder traversal
   void preorder( TreeNode< value_type > *node )
   {
      if( node != myHead )
      {
         cout << setw( 5 ) << node->myval << ( node->color == Color::Red ? "R" : "B" );
         preorder( node->left );
         preorder( node->right );
      }
   }

   // inorder traversal
   void inorder( TreeNode< value_type > *node )
   {
      if( node != myHead )
      {
         inorder( node->left );
         cout << setw( 5 ) << node->myval << ( node->color == Color::Red ? "R" : "B" );
         inorder( node->right );
      }
   }
*/
   NodePtr myHead;   // pointer to head node
   size_type mySize; // number of elements
};

// CLASS TEMPLATE Tree
template< typename Traits >
class Tree // ordered red-black tree for map/multimap/set/multiset
{
public:
   using value_type = typename Traits::value_type;

protected:
   using ScaryVal = TreeVal< value_type >;

public:
   using key_type      = typename Traits::key_type;
   using key_compare   = typename Traits::key_compare;

   using size_type       = size_t;

   Tree( const key_compare &parg )
      : keyCompare( parg ),
        scaryVal()
   {
   }

   ~Tree()
   {
   }

   // Extends the container by inserting a new element,
   // effectively increasing the container size by one.
   void insert( const value_type &val )
   {
       auto head = scaryVal.myHead, node = head, dummy = head->parent;

       while (!dummy->isNil && node->myval != val)
           node = dummy, dummy = keyCompare(val, dummy->myval) ? dummy->left : dummy->right;
       
       if (node->myval == val) return;

       auto newNode = new TreeNode< value_type >{ head, node, head, red, false, val };
       ++scaryVal.mySize;

       if (node->isNil) head->left = head->right = head->parent = newNode;
       else keyCompare(val, node->myval) ? node->left = newNode : node->right = newNode;
       
       if (keyCompare(val, head->left->myval)) head->left = newNode;
       if (keyCompare(head->right->myval, val)) head->right = newNode;

       scaryVal.reBalance(newNode);
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val )
   {
       auto head = scaryVal.myHead, node = head->parent;
       
       while (!node->isNil && node->myval != val)
           node = keyCompare(val, node->myval) ? node->left : node->right;

       if (node->isNil) return 0;

       if (!node->left->isNil && !node->right->isNil)
       {
           auto RL = node->right;
           while (!RL->left->isNil) RL = RL->left;
           node->myval = RL->myval;
           node = RL;
       }

       if (node == head->left) head->left = node->parent;
       if (node == head->right) head->right = node->parent;

       scaryVal.eraseDegreeOne(node);

       return 1;
   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE