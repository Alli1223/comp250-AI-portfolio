#pragma once
#include "stdafx.h"

// This is the root class for each node
// These classes and code are derrived from this fourm code http://www.cplusplus.com/forum/general/141582/

class BehaviourTree
{
public:
	class Node
	{
	public:

		virtual bool run() = 0;
	};

	class CompositeNode : public Node
	{  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
	private:
		std::list<Node*> children;
	public:
		const std::list<Node*>& getChildren() const { return children; }
		void addChild(Node* child) { children.emplace_back(child); }
	};

	// If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
	class Selector : public CompositeNode
	{
	public:
		virtual bool run() override
		{
			for (Node* child : getChildren())
			{  // The generic Selector implementation
				if (child->run())  
					return true;
			}
			return false;  // All children failed so the entire run() operation fails.
		}
	};

	// If one child fails, then enter operation run() fails.  Success only results if all children succeed.
	class Sequence : public CompositeNode
	{
	public:
		virtual bool run() override
		{
			for (Node* child : getChildren())
			{  // The generic Sequence implementation.
				if (!child->run())  
					return false;
			}
			return true;  // All children suceeded, so the entire run() operation succeeds.
		}
	};

	
};

class Action : public BehaviourTree::Node {
private:
	std::string name;
	int probabilityOfSuccess;
public:
	Action(const std::string newName, int prob) : name(newName), probabilityOfSuccess(prob) {}
private:
	virtual bool run() override {
		if (std::rand() % 100 < probabilityOfSuccess) {
			std::cout << name << " succeeded." << std::endl;
			return true;
		}
		std::cout << name << " failed." << std::endl;
		return false;
	}
};