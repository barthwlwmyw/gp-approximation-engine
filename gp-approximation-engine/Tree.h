#include"TreeNode.h"

class Tree
{
public:

	Tree(int dims);

	~Tree();

	void generateRandom();

	void mutateSelf();

	void crossoverWith(Tree*& secondParent);

	void replaceSubtreeAtAs(int nodeIdx, TreeNode*& newNode);

	Tree* clone();

	TreeNode* cloneSubtree(int nodeIdx);

	double evaluate(double* varValues);

	int getTreeSize();

	void print();

	void testBuild();

private:

	TreeNode* root;

	int dimensions;

	friend class Tree;
};

