#pragma once
#include "TreeNode.h"

class Leaf :
	public TreeNode
{
public:

	Leaf();

	virtual ~Leaf();

	TreeNode* cloneSubtree(int nodeIdx);

	int getSize();
};
