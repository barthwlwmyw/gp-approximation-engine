#pragma once
#include "TreeNode.h"

class DoubleChildNode :
	public TreeNode
{
public:

	DoubleChildNode();

	virtual ~DoubleChildNode();

	void buildSubtree(int dimensions);

	TreeNode* cloneSubtree(int nodeIdx);

	void replaceSubtreeAtAs(int nodeIdx, TreeNode*& newNode);

	int getSize();

protected:

	TreeNode* leftChild;

	TreeNode* rightChild;
};
