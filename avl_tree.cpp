#include <algorithm>

class CAVLTree {
public:
	CAVLTree() : root( 0 ) {}
	~CAVLTree();

	void Add( int key );

private:
	struct CAVLNode {
		int Key;
		CAVLNode* Left;
		CAVLNode* Right;
		int Height;

		explicit CAVLNode( int key ) : Key( key ), Left( 0 ), Right( 0 ), Height( 1 ) {}
	};
	CAVLNode* root;

	static void deleteNode( CAVLNode* node );
	static void addNode( int key, CAVLNode*& node );
	static void balance( CAVLNode*& node );
	static void rotateLeft( CAVLNode*& node );
	static void rotateRight( CAVLNode*& node );
	static int height( CAVLNode* node );
	static void fixHeight( CAVLNode* node );
};

CAVLTree::~CAVLTree()
{
	deleteNode( root );
}

void CAVLTree::deleteNode( CAVLNode* node ) {
	if( node == 0 )
		return;
	deleteNode( node->Left );
	deleteNode( node->Right );
	delete node;
}

void CAVLTree::Add( int key ) {
	addNode( key, root );
}

void CAVLTree::addNode( int key, CAVLNode*& node ) {
	if( node == 0 ) {
		node = new CAVLNode( key );
		return;
	}
	if( key < node->Key ) {
		addNode( key, node->Left );
	} else {
		addNode( key, node->Right );
	}
	balance( node );
}

void CAVLTree::balance( CAVLNode*& node ) {
	if( height( node->Right ) == height( node->Left ) + 2 ) {
		if( height( node->Right->Left ) == height( node->Right->Right ) + 1 )
			rotateRight( node->Right );
		rotateLeft( node );
	}
	// + Симметричный случай...
}

void CAVLTree::rotateLeft( CAVLNode*& node ) {
	// Крутим...
	fixHeight( node->Left );
	fixHeight( node );
}

int CAVLTree::height( CAVLNode* node ) {
	return node == 0 ? 0 : node->Height;
}

void CAVLTree::fixHeight( CAVLNode* node ) {
	node->Height = std::max( height( node->Left ), height( node->Right ) ) + 1;
}

int main() {
	return 0;
}