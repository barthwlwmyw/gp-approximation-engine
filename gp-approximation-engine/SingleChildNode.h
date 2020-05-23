#pragma once
#include "TreeNode.h"

class SingleChildNode :
	public TreeNode
{
public:

	SingleChildNode();

	virtual ~SingleChildNode();

	void buildSubtree(int dimensions);

	TreeNode* cloneSubtree(int nodeIdx);

	void replaceSubtreeAtAs(int nodeIdx, TreeNode*& newNode);

	int getSize();

protected:

	TreeNode* child;
};
