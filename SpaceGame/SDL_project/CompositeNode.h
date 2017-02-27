#pragma once
#include "stdafx.h"
#include "TreeNode.h"

class CompositeNode : public TreeNode
{
public:
	const std::vector<TreeNode*>& getChildren() const { return children; }
	void addChild(TreeNode* child) { children.emplace_back(child); }

private:
	std::vector<TreeNode*> children;
};

