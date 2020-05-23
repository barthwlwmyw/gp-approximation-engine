#include "pch.h"
#include "Tree.h"
#include "TreeNodeFactory.h"

#include<iostream>
#include<cstdlib>

Tree::Tree(int dims) {
	dimensions = dims;
	root = nullptr;
}

Tree::~Tree() {
	delete root;
}

void Tree::generateRandom() {
	TreeNodeFactory* nodeFactory = new TreeNodeFactory();

	root = nodeFactory->generateRandomNode(dimensions);
	root->buildSubtree(dimensions);

	delete nodeFactory;
}

void Tree::mutateSelf() {
	TreeNodeFactory* nodeFactory = new TreeNodeFactory();

	int nodeToMutateIdx = std::rand() % getTreeSize();
	TreeNode* newSubtree = nodeFactory->generateRandomNode(dimensions);
	newSubtree->buildSubtree(dimensions);

	if (nodeToMutateIdx == 0) {
		delete root;
		root = newSubtree;
	}
	else {
		root->replaceSubtreeAtAs(nodeToMutateIdx, newSubtree);
	}
	delete nodeFactory;
}

void Tree::crossoverWith(Tree*& secondParent) {

	int parentACutNodeIdx = std::rand() % this->getTreeSize();
	int parentBCutNodeIdx = std::rand() % secondParent->getTreeSize();

	TreeNode* parentASubtree = this->cloneSubtree(parentACutNodeIdx);
	TreeNode* parentBSubtree = secondParent->cloneSubtree(parentBCutNodeIdx);

	this->replaceSubtreeAtAs(parentACutNodeIdx, parentBSubtree);
	secondParent->replaceSubtreeAtAs(parentBCutNodeIdx, parentASubtree);
}

void Tree::replaceSubtreeAtAs(int nodeIdx, TreeNode*& newNode) {

	if (nodeIdx == 0) {
		delete root;
		root = newNode;
	}
	else {
		root->replaceSubtreeAtAs(nodeIdx, newNode);
	}
}

Tree* Tree::clone() {
	Tree* newTree = new Tree(dimensions);
	newTree->root = root->clone();
	return newTree;
}

TreeNode* Tree::cloneSubtree(int nodeIdx) {
	return root->cloneSubtree(nodeIdx);
}

double Tree::evaluate(double* varValues) {
	return root->evaluate(varValues);
}

int Tree::getTreeSize() {
	return root->getSize();
}

void Tree::print() {
	root->print();
}