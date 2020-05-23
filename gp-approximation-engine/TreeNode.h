#pragma once

class TreeNode
{
public:
	TreeNode();

	virtual ~TreeNode();

	virtual TreeNode* clone();

	virtual TreeNode* cloneSubtree(int nodeIdx);

	virtual void replaceSubtreeAtAs(int nodeIdx, TreeNode*& newNode);

	virtual void buildSubtree(int dimenstions);

	virtual double evaluate(double* variableValues);

	virtual int getSize();

	virtual void print();
};