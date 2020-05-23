#include "pch.h"
#include "DoubleChildNode.h"
#include "TreeNodeFactory.h"

#include <iostream>

DoubleChildNode::DoubleChildNode() :TreeNode() {
	leftChild = nullptr;
	rightChild = nullptr;
}

DoubleChildNode::~DoubleChildNode() {
	delete leftChild;
	delete rightChild;
}

void DoubleChildNode::buildSubtree(int dimensions) {
	TreeNodeFactory* nodeFactory = new TreeNodeFactory();

	leftChild = nodeFactory->generateRandomNode(dimensions);
	rightChild = nodeFactory->generateRandomNode(dimensions);

	leftChild->buildSubtree(dimensions);
	rightChild->buildSubtree(dimensions);

	delete nodeFactory;
}

void DoubleChildNode::replaceSubtreeAtAs(int nodeIdx, TreeNode*& newNode) {
	if (nodeIdx == 1) {
		delete leftChild;
		leftChild = newNode;
		return;
	}

	if (nodeIdx > 1) {
		leftChild->replaceSubtreeAtAs(nodeIdx - 1, newNode);
	}

	int leftChildSize = leftChild->getSize();

	if (nodeIdx - leftChildSize == 1) {
		delete rightChild;
		rightChild = newNode;
		return;
	}

	if (nodeIdx - leftChildSize > 1) {
		rightChild->replaceSubtreeAtAs((nodeIdx - 1) - leftChildSize, newNode);
	}
}

TreeNode* DoubleChildNode::cloneSubtree(int nodeIdx) {
	if (nodeIdx == 0) {
		return this->clone();
	}
	else if (nodeIdx > 0) {
		TreeNode* node = leftChild->cloneSubtree(nodeIdx - 1);
		if (node == nullptr) {
			return rightChild->cloneSubtree(nodeIdx - 1 - leftChild->getSize());
		}
		else {
			return node;
		}
	}
}

int DoubleChildNode::getSize() {
	return 1 + leftChild->getSize() + rightChild->getSize();
}
