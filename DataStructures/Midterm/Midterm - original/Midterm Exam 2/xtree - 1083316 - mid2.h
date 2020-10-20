// xtree internal header

#ifndef XTREE
#define XTREE

//--
#define red Color::Red
#define black Color::Black
using std::swap;
//--

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
        TreeNode< value_type >* p = node->parent;
        TreeNode< value_type >* g = p->parent;
        TreeNode< value_type >* u = p == g->left ? g->right : g->left;

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
            
            if (p == g->left) swap(g->color, p->color), LLRotation(p);
            else swap(g->color, p->color), RRRotation(p);
        }
   }

   // rotate right at g, where p = g->left and node = p->left
   //void set< Kty >::LLbRotation( TreeNode< value_type > *node )
   void LLRotation( TreeNode< value_type > *p )
   {
        TreeNode< value_type >* g = p->parent;

        g->left = p->right;
        if (!p->right->isNil) p->right->parent = g;

        p->parent = g->parent;
        if (g->parent->isNil) myHead->parent = p;
        else g == g->parent->left ? g->parent->left = p : g->parent->right = p;

        p->right = g;
        g->parent = p;
   }

   // rotate left at g, where p = g->right and node = p->right
   //void set< Kty >::RRbRotation( TreeNode< value_type > *node )
   void RRRotation( TreeNode< value_type > *p )
   {
        TreeNode< value_type >* g = p->parent;

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
        TreeNode< value_type >* p = node->parent;
        TreeNode< value_type >* c = node->left->isNil ? node->right : node->left;

        if (p->isNil && c->color == black)
        {
            myHead->parent = c;
            c->parent = myHead;
        }
        else
        {
            node == p->left ? p->left = c : p->right = c;
            if (!c->isNil) c->parent = p;

            if (node->color == black && c->color == black) fixUp(c, p);
            else if (c->color == red) c->color = black;
        }

        delete node;
        --mySize;
   }

   // rebalance for deletion
   void fixUp( TreeNode< value_type > *N, TreeNode< value_type > *P )
   {
        TreeNode< value_type >* s = N == P->left ? P->right : P->left;

        if (s->color == red)
        {
            swap(P->color, s->color);
            N == P->left ? RRRotation(s) : LLRotation(s);
        }

        s = N == P->left ? P->right : P->left;

        if (s->right->color == black && N == P->left && s->left->color == red)
        {
            swap(s->color, s->left->color);
            LLRotation(s->left);
        }
        if (s->left->color == black && N == P->right && s->right->color == red)
        {
            swap(s->color, s->right->color);
            RRRotation(s->right);
        }

        s = N == P->left ? P->right : P->left;

        if (s->right->color == red && N == P->left)
        {
            swap(P->color, s->color);
            s->right->color = black;
            RRRotation(s);
            return;
        }
        if (s->left->color == red && N == P->right)
        {
            swap(P->color, s->color);
            s->left->color = black;
            LLRotation(s);
            return;
        }
        
        if (s->right->color == black && s->left->color == black)
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
        TreeNode< value_type >* h = scaryVal.myHead;
        TreeNode< value_type >* n = h;
        TreeNode< value_type >* d = h->parent;

        while (!d->isNil && n->myval != val) n = d, d = keyCompare(val, d->myval) ? d->left : d->right;

        if (n->myval == val) return;

        auto N = new TreeNode< value_type >{ h, n, h, red, false, val };
        ++scaryVal.mySize;

        if (n->isNil) n->left = n->right = n->parent = N;
        else keyCompare(val, n->myval) ? n->left = N : n->right = N;

        if (keyCompare(val, h->left->myval)) h->left = N;
        if (keyCompare(h->right->myval, val)) h->right = N;

        scaryVal.reBalance(N);
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val )
   {
        TreeNode< value_type >* h = scaryVal.myHead;
        TreeNode< value_type >* n = h->parent;

        while (!n->isNil && n->myval != val) n = keyCompare(val, n->myval) ? n->left : n->right;

        if (n->isNil) return 0;

        if (!n->left->isNil && !n->right->isNil)
        {
            auto rl = n->right;
            while (!rl->left->isNil) rl = rl->left;
            n->myval = rl->myval;
            n = rl;
        }

        if (h->left == n) h->left = n->parent;
        if (h->right == n) h->right = n->parent;

        scaryVal.eraseDegreeOne(n);

        return 1;
   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE