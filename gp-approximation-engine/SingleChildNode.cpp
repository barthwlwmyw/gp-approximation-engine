#include "pch.h"
#include "SingleChildNode.h"
#include "TreeNodeFactory.h"

SingleChildNode::SingleChildNode() :TreeNode() {
	child = nullptr;
}

SingleChildNode::~SingleChildNode() {
	delete child;
}

void SingleChildNode::buildSubtree(int dimensions) {
	TreeNodeFactory* nodeFactory = new TreeNodeFactory();

	child = nodeFactory->generateRandomNode(dimensions);
	child->buildSubtree(dimensions);

	delete nodeFactory;
}

void SingleChildNode::replaceSubtreeAtAs(int nodeIdx, TreeNode*& newNode) {
	if (nodeIdx == 1) {
		delete child;
		child = newNode;
		return;
	}

	if (nodeIdx > 1) {
		child->replaceSubtreeAtAs(nodeIdx - 1, newNode);
	}
}

TreeNode* SingleChildNode::cloneSubtree(int nodeIdx) {
	if (nodeIdx == 0) {
		return this->clone();
	}
	else if (nodeIdx > 0) {
		return child->cloneSubtree(nodeIdx - 1);
	}
}

int SingleChildNode::getSize() {
	return 1 + child->getSize();
}
