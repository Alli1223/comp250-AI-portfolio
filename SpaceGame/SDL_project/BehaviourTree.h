#pragma once
#include "stdafx.h"

// This is the root class for each node
// These classes and code are derrived from this fourm code http://www.cplusplus.com/forum/general/141582/
class BehaviourTreeNode
{
public:
	virtual bool run() = 0;
};

class CompositeNode : public BehaviourTreeNode 
{  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
private:
	std::list<BehaviourTreeNode*> children;
public:
	const std::list<BehaviourTreeNode*>& getChildren() const { return children; }
	void addChild(BehaviourTreeNode* child) { children.emplace_back(child); }
};

class Selector : public CompositeNode 
{
public:
	virtual bool run() override 
	{
		for (BehaviourTreeNode* child : getChildren()) 
		{  // The generic Selector implementation
			if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
				return true;
		}
		return false;  // All children failed so the entire run() operation fails.
	}
};

class Sequence : public CompositeNode 
{
public:
	virtual bool run() override 
	{
		for (BehaviourTreeNode* child : getChildren()) 
		{  // The generic Sequence implementation.
			if (!child->run())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
				return false;
		}
		return true;  // All children suceeded, so the entire run() operation succeeds.
	}
};

