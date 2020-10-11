// xtree internal header

using std::swap;
#define red Color::Red
#define black Color::Black

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
   {   // node->parent cannot be the root
       // refer to the video of class and the internet
       // p -> parent, g -> grand, u -> uncle
       TreeNode< value_type >* p = node->parent;
       TreeNode< value_type >* g = node->parent->parent;
       TreeNode< value_type >* u = p == g->left ? g->right : g->left;
       
       // Case 1 -> node is the root, make node black
       if (p->isNil) { node->color = black; return; }

       // boundary condition of Case 2
       if (p->color == black) return;

       // XYr
       if (u->color == red)
       {   // Case 2 -> LLr, LRr, RLr, or RRr
           p->color = u->color = black;
           g->color = red;
           // do the same thing to g
           reBalance(g);
           return;
       }

       // XYb
       if (p == g->left && node == p->left)
       {   // Case 3 -> LLb
           LLRotation(p); // rotate right at g
           swap(p->color, g->color);
           return;
       }

       if (p == g->right && node == p->right)
       {   // Case 4 -> RRb
           RRRotation(p); // rotate left at g
           swap(p->color, g->color);
           return;
       }

       if (p == g->left && node == p->right)
       {   // Case 5 -> LRb
           // rotate left at p first, then rotate right at g
           LRRotation(node);
           swap(node->color, g->color);
           return;
       }

       if (p == g->right && node == p->left)
       {   // Case 6 -> RLb
           // rotate right at p first, then rotate left at g
           RLRotation(node);
           swap(node->color, g->color);
       }
   }

   // rotate right at g, where p = g->left and node = p->left
   //void set< Kty >::LLbRotation( TreeNode< value_type > *node )
   void LLRotation( TreeNode< value_type > *p )
   {
       TreeNode< value_type >* g = p->parent;

       // connect g and p's right child
       g->left = p->right;
       if (!p->right->isNil) p->right->parent = g;

       // connect g's parent and p
       p->parent = g->parent;
       if (g->parent->isNil) myHead->parent = p;
       else g == g->parent->left ? g->parent->left = p : g->parent->right = p;

       // connect p and g
       p->right = g;
       g->parent = p;
   }

   // LR rotation; p = g->left and node = p->right
   void LRRotation( TreeNode< value_type > *node )
   {   // LRb rotation
       RRRotation(node); // rotate left at p first
       LLRotation(node); // then rotate right at g
   }

   // RL rotation; p = g->right and node = p->left
   void RLRotation( TreeNode< value_type > *node )
   {   // RLb rotation
       LLRotation(node); // rotate right at p first
       RRRotation(node); // then rotate left at g
   }

   // rotate left at g, where p = g->right and node = p->right
   //void set< Kty >::RRbRotation( TreeNode< value_type > *node )
   void RRRotation( TreeNode< value_type > *p )
   {
       TreeNode< value_type >* g = p->parent;

       // connect g and p's left child
       g->right = p->left;
       if (!p->left->isNil) p->left->parent = g;

       // connect g's parent and p
       p->parent = g->parent;
       if (g->parent->isNil) myHead->parent = p;
       else g == g->parent->left ? g->parent->left = p : g->parent->right = p;

       // connect p and g
       p->left = g;
       g->parent = p;
   }

   // erase node provided that the degree of node is at most one
   void eraseDegreeOne( TreeNode< value_type > *node )
   {   // refer to the video of class
       // M -> the node need to delete
       // P -> M's parent, if M is the root, P is myHead
       // C -> M's only child, if M doesn't have any child, C is the nil node
       TreeNode< value_type >* M = node;
       TreeNode< value_type >* P = node->parent;
       TreeNode< value_type >* C = node->left->isNil ? node->right : node->left;

       // Simple Case 3 -> M and C are black, and M is the root
       if (M->color == black && C->color == black && P->isNil)
       {   // delete M and make C be the root
           myHead->parent = C;
           C->parent = myHead;
           delete M;
           --mySize;
           return;
       }

       // Simple Case 1 -> M is red or M is a leaf node : delete M and connect P and C

       // connect P and C
       M == P->left ? P->left = C : P->right = C;
       if (!C->isNil) C->parent = P;

       // Complex Case -> M and C are black, and M is not the root : connect P and C, then rebalance
       if (M->color == black && C->color == black && !P->isNil) fixUp(C, P);
       
       // Simple Case 2 -> M is black, C is red : delete M, connect P and C, and make C black
       if (M->color == black && C->color == red) C->color = black;

       delete M;
       --mySize;
   }

   // rebalance for deletion
   void fixUp( TreeNode< value_type > *N, TreeNode< value_type > *P )
   {   // refer to Assignment 3.pptx
       TreeNode< value_type >* S = N == P->left ? P->right : P->left; // N's sibling
       
       // Case 1
       if (S->color == red && N == P->left)
       {   // Case 1.1 -> S is red and N is P's left child
           swap(P->color, S->color);
           RRRotation(S); // rotate left at P
           // update S, then go to Case 2.1, 3.1, or 4
       }
       if (S->color == red && N == P->right)
       {   // Case 1.2 -> S is red and N is P's right child
           swap(P->color, S->color);
           LLRotation(S); // rotate right at P
           // update S, then go to Case 2.2, 3.2, or 4
       }

       // update S
       S = N == P->left ? P->right : P->left;

       // Case 3
       if (S->color == black && S->right->color == black && N == P->left && S->left->color == red)
       {   // Case 3.1 -> S and SR are black, N is P's left child, but SL is red
           swap(S->color, S->left->color);
           LLRotation(S->left); // rotate right at S
           // update S, then go to Case 2.1
       }
       if (S->color == black && S->left->color == black && N == P->right && S->right->color == red)
       {   // Case 3.2 -> S and SL are black, N is P's right child, but SR is red
           swap(S->color, S->right->color);
           RRRotation(S->right); // rotate left at S
           // update S, then go to Case 2.2
       }

       // update S
       S = N == P->left ? P->right : P->left;

       // Case 2
       if (S->color == black && S->right->color == red && N == P->left)
       {   // Case 2.1 -> S is black, SR is red and N is P's left child
           swap(P->color, S->color);
           S->right->color = black;
           RRRotation(S); // rotate left at P
           return;
       }
       if (S->color == black && S->left->color == red && N == P->right)
       {   // Case 2.2 -> S is black, SL is red and N is the right child of P
           swap(P->color, S->color);
           S->left->color = black;
           LLRotation(S); // rotate right at P
           return;
       }

       // Case 4 -> S, SR and SL are black, but P is red
       if (S->color == black && S->right->color == black && S->left->color == black && P->color == red)
       {   // Just exchange the colors of S and of P
           swap(S->color, P->color);
           return;
       }

       // Case 5 -> S, SR, SL and P are black
       if (S->color == black && S->right->color == black && S->left->color == black && P->color == black)
       {
           S->color = red;
           fixUp(P, P->parent);
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
       // head -> the reference of scaryVal.myHead
       // node -> new node's parent
       // dummy -> dummy node
       TreeNode< value_type >* head = scaryVal.myHead;
       TreeNode< value_type >* node = head;
       TreeNode< value_type >* dummy = head->parent;

       // find new node's parent and also find if the key already exists or not
       while (!dummy->isNil && node->myval != val)
           node = dummy, dummy = keyCompare(val, dummy->myval) ? dummy->left : dummy->right;
           
       // if the key already exists
       if (val == node->myval) return;

       // new node's color should be red first
       auto newNode = new TreeNode< value_type >{ head, node, head, red, false, val };
       ++scaryVal.mySize;

       // connect node and new node, if new node is the root, update head's pointers
       if (node->isNil) head->left = head->right = head->parent = newNode;
       else keyCompare(val, node->myval) ? node->left = newNode : node->right = newNode;

       // update head's pointers
       if (keyCompare(val, head->left->myval)) head->left = newNode;
       if (keyCompare(head->right->myval, val)) head->right = newNode;

       scaryVal.reBalance(newNode);
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val )
   {
       TreeNode< value_type >* head = scaryVal.myHead; // reference
       TreeNode< value_type >* node = scaryVal.myHead->parent; // root

       // find the key
       while (!node->isNil && val != node->myval)
           node = keyCompare(val, node->myval) ? node->left : node->right;

       // not found
       if (node->isNil) return 0;

       // if node has two children
       if (!node->left->isNil && !node->right->isNil)
       {   // let the node's right subtree's leftmost node's val replace node's val
           TreeNode< value_type >* RL = node->right;
           while (!RL->left->isNil) RL = RL->left;
           node->myval = RL->myval;
           node = RL; // delete RL
       }

       // update head's pointers
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