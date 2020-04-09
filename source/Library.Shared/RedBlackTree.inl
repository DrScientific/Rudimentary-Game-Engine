#include "RedBlackTree.h"
#include <assert.h>

namespace FIEAGameEngine
{
	template<typename T, typename LessThanFunctor>
	inline RedBlackTree<T, LessThanFunctor>::Node::Node(T const& data, Node* parent, Node* left, Node* right) :mData(data), mParent(parent), mLeft(left), mRight(right)
	{
	}
	
	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Node* RedBlackTree<T, LessThanFunctor>::Node::GetSibling() const
	{
		if (!mParent)
		{
			return nullptr;
		}
		else if (this == mParent->mLeft)
		{
			return mParent->mRight;
		}
		else
		{
			return mParent->mLeft;
		}
	}


	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::Node::IsLeftChild()const
	{
		return mParent && mParent->mLeft == this;
	}

	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::Node::IsRightChild() const
	{
		return !IsLeftChild();
	}

	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::Node::HasRedChild() const
	{
		return (mLeft && mLeft->mColor == Color::Red) || (mRight && mRight->mColor == Color::Red);
	}

	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::Node::HasRedSibling() const
	{
		return (mParent && ((mParent->mLeft == this && mParent->mRight && mParent->mRight->mColor == Color::Red) || (mParent->mRight == this && mParent->mLeft && mParent->mLeft->mColor == Color::Red)));
	}

	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::Node::HasInnerRedChild() const
	{
		return GetInnerRedChild();
	}

	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::Node::HasOuterRedChild() const
	{
		return GetOuterRedChild();
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Node* RedBlackTree<T, LessThanFunctor>::Node::GetInnerRedChild() const
	{
		Node* innerRedChild = nullptr;
		if (mParent)
		{
			if (mParent->mLeft == this && mRight && mRight->mColor == Color::Red)
			{
				innerRedChild = mRight;
			}
			else if (mParent->mRight == this && mLeft && mLeft->mColor == Color::Red)
			{
				innerRedChild = mLeft;
			}
		}
		return innerRedChild;
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Node* RedBlackTree<T, LessThanFunctor>::Node::GetOuterRedChild() const
	{
		Node* outerRedChild = nullptr;
		if (mParent)
		{
			if (mParent->mLeft == this && mLeft && mLeft->mColor == Color::Red)
			{
				outerRedChild = mLeft;
			}
			else if (mParent->mRight == this && mRight && mRight->mColor == Color::Red)
			{
				outerRedChild = mRight;
			}
		}
		return outerRedChild;
	}

	template<typename T, typename LessThanFunctor>
	inline RedBlackTree<T, LessThanFunctor>::Iterator::Iterator(const RedBlackTree& owner, Node* node) : mOwner(&owner), mNode(node)
	{
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Iterator& RedBlackTree<T, LessThanFunctor>::Iterator::operator++()
	{
		if (!mNode)
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		else if (mNode->mRight)
		{
			mNode = mOwner->FindMin(mNode->mRight);
		}
		else
		{
			Node* parent = mNode->mParent;
			while (parent && mNode == parent->mRight)
			{
				mNode = parent;
				parent = parent->mParent;
			}
			mNode = parent;
		}
		return *this;
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Iterator RedBlackTree<T, LessThanFunctor>::Iterator::operator++(int)
	{
		Iterator iteratorBeforeIncrement(*this);
		operator++();
		return iteratorBeforeIncrement;
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Iterator& RedBlackTree<T, LessThanFunctor>::Iterator::operator--()
	{
		if (mNode == mOwner->FindMin(mOwner->mRoot))
		{
			throw std::exception(attemptToIteratareBeforeFirstElementException.c_str());
		}
		else if (!mNode)
		{
			mNode = mOwner->FindMax(mOwner->mRoot);
		}
		else if (mNode->mLeft)
		{
			mNode = mOwner->FindMax(mNode->mLeft);
		}
		else
		{
			Node* parent = mNode->mParent;
			while (parent && mNode == parent->mLeft)
			{
				mNode = parent;
				parent = parent->mParent;
			}
			mNode = parent;
		}
		return *this;
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Iterator RedBlackTree<T, LessThanFunctor>::Iterator::operator--(int)
	{
		Iterator iteratorBeforeDecrement(*this);
		operator--();
		return iteratorBeforeDecrement;
	}

	template<typename T, typename LessThanFunctor>
	inline typename bool RedBlackTree<T, LessThanFunctor>::Iterator::operator==(Iterator const& rhs) const
	{
		return (!mNode && !rhs.mNode) || ((mNode && rhs.mNode) && (mNode->mData == rhs.mNode->mData && mOwner == rhs.mOwner));
	}

	template<typename T, typename LessThanFunctor>
	inline typename bool RedBlackTree<T, LessThanFunctor>::Iterator::operator!=(Iterator const& rhs) const
	{
		return !operator==(rhs);
	}

	template<typename T, typename LessThanFunctor>
	inline typename T const& RedBlackTree<T, LessThanFunctor>::Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == const_cast<RedBlackTree*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return mNode->mData;
	}

	template<typename T, typename LessThanFunctor>
	inline RedBlackTree<T, LessThanFunctor>::RedBlackTree(std::initializer_list<T> iList)
	{
		for (auto element : iList)
		{
			Insert(element);
		}
	}

	template<typename T, typename LessThanFunctor>
	inline RedBlackTree<T, LessThanFunctor>::RedBlackTree(RedBlackTree const& other)
	{
		
	}

	template<typename T, typename LessThanFunctor>
	inline RedBlackTree<T, LessThanFunctor>::RedBlackTree(RedBlackTree && other)
	{

	}

	template<typename T, typename LessThanFunctor>
	inline RedBlackTree<T, LessThanFunctor>& RedBlackTree<T, LessThanFunctor>::operator=(RedBlackTree const& other)
	{

	}

	template<typename T, typename LessThanFunctor>
	inline RedBlackTree<T, LessThanFunctor>& RedBlackTree<T, LessThanFunctor>::operator=(RedBlackTree && other)
	{

	}

	template<typename T, typename LessThanFunctor>
	inline RedBlackTree<T, LessThanFunctor>::~RedBlackTree()
	{
		Clear();
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Iterator RedBlackTree<T, LessThanFunctor>::begin()
	{
		return Iterator(*this, FindMin(mRoot));
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::const_Iterator RedBlackTree<T, LessThanFunctor>::begin() const
	{
		return cbegin();
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Iterator RedBlackTree<T, LessThanFunctor>::end()
	{
		return Iterator(*this, nullptr);
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::const_Iterator RedBlackTree<T, LessThanFunctor>::end() const
	{
		return cend();
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::const_Iterator RedBlackTree<T, LessThanFunctor>::cbegin() const
	{
		return const_Iterator(this, FindMin(mRoot));
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::const_Iterator RedBlackTree<T, LessThanFunctor>::cend() const
	{
		return const_Iterator(this, nullptr);
	}

	template<typename T, typename LessThanFunctor>
	inline std::pair<typename RedBlackTree<T, LessThanFunctor>::Iterator, bool> RedBlackTree<T, LessThanFunctor>::Insert(T const& data)
	{
		std::pair<Node*, bool> insertResult = Insert(mRoot, data);
		if (insertResult.second)
		{
			InsertFixUp(insertResult.first);
		}
		return std::pair<Iterator, bool>(Iterator(*this, insertResult.first), insertResult.second);
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Iterator RedBlackTree<T, LessThanFunctor>::Find(T const& data) const
	{
		return Iterator(this, Search(mRoot,data));
	}

	template<typename T, typename LessThanFunctor>
	inline void RedBlackTree<T, LessThanFunctor>::Remove(T const& data)
	{
		Remove(mRoot, data);
	}

	template<typename T, typename LessThanFunctor>
	inline size_t RedBlackTree<T, LessThanFunctor>::Size() const
	{
		return Size(mRoot);
	}

	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::IsEmpty() const
	{
		return mRoot;
	}

	template<typename T, typename LessThanFunctor>
	inline void RedBlackTree<T, LessThanFunctor>::Clear()
	{
		DeleteSubtree(mRoot);
	}

	template<typename T, typename LessThanFunctor>
	inline std::pair<typename RedBlackTree<T, LessThanFunctor>::Node*, bool> RedBlackTree<T, LessThanFunctor>::Insert(Node* subtreeRoot, T const& data)
	{
		std::pair<Node*, bool> insertionResult(nullptr, false);
		if (subtreeRoot)
		{
			if (lessThan(data, subtreeRoot->mData))
			{
				insertionResult = Insert(subtreeRoot->mLeft, data);
				if (!subtreeRoot->mLeft)
				{
					subtreeRoot->mLeft = insertionResult.first;
				}
				if (!insertionResult.first->mParent)
				{
					insertionResult.first->mParent = subtreeRoot;
				}
			}
			else if (!lessThan(subtreeRoot->mData, data))
			{
				insertionResult = { subtreeRoot, false };
			}
			else
			{
				insertionResult = Insert(subtreeRoot->mRight, data);
				if (!subtreeRoot->mRight)
				{
					subtreeRoot->mRight = insertionResult.first;
				}
				if (!insertionResult.first->mParent)
				{
					insertionResult.first->mParent = subtreeRoot;
				}
			}
		}
		else if(mRoot)
		{
			insertionResult = { new Node(data), true };
		}
		else
		{
			mRoot = new Node(data);
			insertionResult = { mRoot, true };
		}
		return insertionResult;
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Node* RedBlackTree<T, LessThanFunctor>::Search(Node* subtreeRoot, T const& data) const
	{
		if (subtreeRoot)
		{
			if (lessThan(data, subtreeRoot->mData))
			{
				subtreeRoot = Search(subtreeRoot->mLeft, data);
			}
			else if (lessThan(subtreeRoot->mData, data))
			{
				subtreeRoot = Search(subtreeRoot->mRight, data);
			}
		}
		return subtreeRoot;
	}

	template<typename T, typename LessThanFunctor>
	inline void RedBlackTree<T, LessThanFunctor>::Remove(Node* subtreeRoot, T const& data)
	{
		Node* nodeToDataSwap = Search(subtreeRoot, data);
		if (nodeToDataSwap)
		{
			Node* nodeToDelete = nodeToDataSwap;
			if (nodeToDataSwap->mLeft)
			{
				nodeToDelete = FindMax(nodeToDataSwap->mLeft);
			}
			else if (nodeToDataSwap->mRight)
			{
				nodeToDelete = FindMin(nodeToDataSwap->mRight);
			}
			if (nodeToDelete != mRoot)
			{
				*const_cast<T*>(&nodeToDataSwap->mData) = std::move(nodeToDelete->mData);

				Node* parentOfDeletedNode = nodeToDelete->mParent;

		
				Node* childOfDeletedNode = nullptr;
				if (nodeToDelete->mLeft)
				{
					childOfDeletedNode = nodeToDelete->mLeft;
					childOfDeletedNode->mParent = parentOfDeletedNode;
				}
				else if (nodeToDelete->mRight)
				{
					childOfDeletedNode = nodeToDelete->mRight;
					childOfDeletedNode->mParent = parentOfDeletedNode;
				}

				if (parentOfDeletedNode)
				{
					nodeToDelete->IsLeftChild() ? parentOfDeletedNode->mLeft = childOfDeletedNode : parentOfDeletedNode->mRight = childOfDeletedNode;
				}

				if (!parentOfDeletedNode->mLeft && !parentOfDeletedNode->mRight && !parentOfDeletedNode->mParent)
				{
					mRoot = parentOfDeletedNode;
				}

				//Case 1: The node to delete is red. Only thing left to do is to delete the node.
				
				//Case 2: The node to delete is black. The properties of the tree need to fixed up.
				if(nodeToDelete->mColor == Color::Black)
				{
					if (childOfDeletedNode)
					{
						if (childOfDeletedNode->mColor == Color::Black)
						{
							childOfDeletedNode->mColor = Color::DoubleBlack;
						}
						else
						{
							childOfDeletedNode->mColor = Color::Black;
						}
					}
					Node* currentNode = childOfDeletedNode;
					Node* parent = parentOfDeletedNode;
					Node* sibling;
					while ((!currentNode || currentNode->mColor == Color::DoubleBlack) && currentNode != mRoot)
					{
						sibling = (currentNode == parent->mLeft ? parent->mRight : parent->mLeft);

						if (sibling->mColor == Color::Black && sibling->HasRedChild())
						{
							//Left Case (Sibling is the left child of it's parent.)
							if (sibling->IsLeftChild())
							{
								//Left-Left Case (Sibling's red child is either it's left child or both of its children are red)
								if (sibling->mLeft && sibling->mLeft->mColor == Color::Red)
								{
									sibling->mLeft->mColor = sibling->mColor;
									sibling->mColor = parent->mColor;
									RotateRight(parent);
								}
								//Left-Right Case (Only the sibling's right child is red)
								else
								{
									sibling->mRight->mColor = parent->mColor;
									RotateLeft(sibling);
									RotateRight(parent);
								}
								parent->mColor = Color::Black;
								if (currentNode)
								{
									currentNode->mColor = Color::Black;
								}
								break;
							}
							//Right Case (Sibling is the right child of it's parent.)
							else
							{
								//Right-Right Case (Sibling's red child is either it's right child or both of its children are red)
								if (sibling->mRight && sibling->mRight->mColor == Color::Red)
								{
									sibling->mRight->mColor = sibling->mColor;
									sibling->mColor = parent->mColor;
									RotateLeft(parent);
								}
								//Right-Left Case (Only the sibling's left child is red)
								else
								{
									sibling->mLeft->mColor = parent->mColor;
									RotateRight(sibling);
									RotateLeft(parent);
								}
								parent->mColor = Color::Black;
								if (currentNode)
								{
									currentNode->mColor = Color::Black;
								}
								break;
							}

						}
						else if (sibling->mColor == Color::Black)
						{
							sibling->mColor = Color::Red;
							if (currentNode)
							{
								currentNode->mColor = Color::Black;
							}
							if (parent->mColor == Color::Black)
							{
								parent->mColor = Color::DoubleBlack;
							}
							else
							{
								parent->mColor = Color::Black;
							}
							currentNode = parent;
							parent = parent->mParent;
						}
						else
						{
							assert(sibling->mColor == Color::Red);
							if (sibling->IsLeftChild())
							{
								RotateRight(parent);
							}
							else
							{
								RotateLeft(parent);
							}
							sibling->mColor = Color::Black;
							parent->mColor = Color::Red;
						}
					}
					mRoot->mColor = Color::Black;
				}
			}
			else
			{
			mRoot = nullptr;
			}
			/*
			//Case 1: The node to be deleted is red. (We've already done what we need to for this, we simply don't do anything more.)
			
			//Case 2 or 3
			if (nodeToDelete->mColor == Color::Black)
			{
				//Case 2: The node to be deleted is black and has a red child.
				if (nodeToDelete->HasRedChild())
				{
					if (childOfDeletedNode)
					{
						childOfDeletedNode->mColor = Color::Black;
					}
				}
				//Case 3: The node to delete is black only has black children.
				else if (childOfDeletedNode || parentOfDeletedNode)
				{
					if (childOfDeletedNode)
					{
						childOfDeletedNode->mColor = Color::DoubleBlack;
					}
					Node* currentNode = childOfDeletedNode;
					Node* parent = parentOfDeletedNode;
					while (true)
					{
						Node* sibling = nullptr;
						if (currentNode)
						{
							sibling = currentNode->GetSibling();
						}
						else if (parent)
						{
							sibling = parent->mLeft ? parent->mLeft : parent->mRight;
						}
						//Case 3.1 (Terminal): The node to be deleted is black and is the root node.
						if (currentNode == mRoot)
						{
							if (currentNode)
							{
								currentNode->mColor = Color::Black;
							}
							break;
						}
						//Case 3.2: The node being deleted is black, has a black parent, and a red sibling.
						else if (parent && parent->mColor == Color::Black && parent->HasRedChild())
						{
							if (parent->mLeft == currentNode)
							{
								RotateLeft(parent);
							}
							else
							{
								RotateRight(parent);
							}
							parent->mColor = Color::Red;
							parent->mParent->mColor = Color::Black;
						}
						//Case 3.3: The node being deleted is black, has a black parent, and a black sibling with two black children.
						else if (parent && parent->mColor == Color::Black && sibling->mColor == Color::Black && !sibling->HasRedChild())
						{
							parent->mColor = Color::DoubleBlack;
							if (currentNode)
							{
								currentNode->mColor = Color::Black;
							}
							sibling->mColor = Color::Red;
							currentNode = parent;
							parent = parent->mParent;
						}
						//Case 3.4(Terminal): The node to be deleted is black, has a red parent, and it's sibling does not have red children.
						else if (parent && parent->mColor == Color::Red && !sibling->HasRedChild())
						{
							parent->mColor = Color::Black;
							if (currentNode)
							{
								currentNode->mColor = Color::Black;
							}
							sibling->mColor = Color::Red;
							break;
						}
						//Case 3.5: The node being deleted is black, has a black parent, and a black sibling with one inner red child.
						else if (parent && parent->mColor == Color::Black && sibling->mColor == Color::Black && sibling->HasInnerRedChild())
						{
							if (sibling->IsLeftChild())
							{
								RotateLeft(sibling);
							}
							else
							{
								RotateRight(sibling);
							}
							sibling->mColor = Color::Red;
							sibling->mParent->mColor = Color::Black;
						}
						//Case 3.6:(Terminal): The node being deleted is black and has a black sibling with an outer red child.
						else if (parent && sibling && sibling->mColor == Color::Black && sibling->HasOuterRedChild())
						{
							Node* outerRedChild = sibling->GetOuterRedChild();
							if (sibling->IsLeftChild())
							{
								RotateRight(parent);
							}
							else
							{
								RotateLeft(parent);
							}
							outerRedChild->mColor = Color::Black;
							parent->mColor = Color::Black;
							if (currentNode)
							{
								currentNode->mColor = Color::Black;
							}
							break;
						}
						else
						{
							assert(false);
						}
					}
				}
				//Case 4: We are deleteing the root of an otherwise empty tree
				else
				{
					mRoot = nullptr;
				}
			}*/
			delete nodeToDelete;
		}
	}

	template<typename T, typename LessThanFunctor>
	inline size_t RedBlackTree<T, LessThanFunctor>::Size(Node* subtreeRoot) const
	{
		if (subtreeRoot == nullptr)
		{
			return 0;
		}

		return 1 + Size(subtreeRoot->mLeft) + Size(subtreeRoot->mRight);
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Node* RedBlackTree<T, LessThanFunctor>::FindMin(Node* subtreeRoot) const
	{
		if (subtreeRoot)
		{
			while (subtreeRoot && subtreeRoot->mLeft)
			{
				subtreeRoot = subtreeRoot->mLeft;
			}
		}
		return subtreeRoot;
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Node* RedBlackTree<T, LessThanFunctor>::FindMax(Node* subtreeRoot) const
	{
		if (subtreeRoot)
		{
			while (subtreeRoot && subtreeRoot->mRight)
			{
				subtreeRoot = subtreeRoot->mRight;
			}
		}
		return subtreeRoot;
	}

	template<typename T, typename LessThanFunctor>
	inline void RedBlackTree<T, LessThanFunctor>::InsertFixUp(Node* node)
	{
		Node* currentNode = node;
		while (currentNode != mRoot && currentNode->mColor == Color::Red && currentNode->mParent->mColor == Color::Red)
		{
			Node* parent = currentNode->mParent;
			Node* grandParent = currentNode->mParent->mParent;
			//Case A
			if (parent == grandParent->mLeft)
			{
				Node* pibling = grandParent->mRight;
				//Case 1A
				if (pibling && pibling->mColor == Color::Red)
				{
					grandParent->mColor = Color::Red;
					parent->mColor = Color::Black;
					pibling->mColor = Color::Black;
					currentNode = grandParent;
				}
				else
				{
					//Case 2A
					if (currentNode == parent->mRight)
					{
						RotateLeft(parent);
						currentNode = parent;
						parent = parent->mParent;
					}
					//Case 3A
					RotateRight(grandParent);
					Color swapBuffer = parent->mColor;
					parent->mColor = grandParent->mColor;
					grandParent->mColor = swapBuffer;
					currentNode = parent;
				}
			}
			//Case B
			else
			{
				Node* pibling = grandParent->mLeft;
				//Case 1B
				if (pibling && pibling->mColor == Color::Red)
				{
					grandParent->mColor = Color::Red;
					parent->mColor = Color::Black;
					pibling->mColor = Color::Black;
					currentNode = grandParent;
				}
				else
				{
					//Case 2B
					if (currentNode == parent->mLeft)
					{
						RotateRight(parent);
						currentNode = parent;
						parent = parent->mParent;
					}
					//Case 3B
					RotateLeft(grandParent);
					Color swapBuffer = parent->mColor;
					parent->mColor = grandParent->mColor;
					grandParent->mColor = swapBuffer;
					currentNode = parent;
				}
			}
		}
		mRoot->mColor = Color::Black;
	}

	template<typename T, typename LessThanFunctor>
	inline void RedBlackTree<T, LessThanFunctor>::RemoveFixUp(std::pair<Node*, Node*> childAndParent)
	{
		
	}

	template<typename T, typename LessThanFunctor>
	inline void RedBlackTree<T, LessThanFunctor>::PushUpBlackLevel(Node* node, Node* parent)
	{
		assert(node == parent->mLeft || node == parent->mRight);
		Node* sibling = node == parent->mLeft ? parent->mRight : parent->mLeft;
		if (node)
		{
			if (node->mColor == Color::DoubleBlack)
			{
				node->mColor = Color::Black;
			}
			else if(node->mColor == Color::Black)
			{
				node->mColor = Color::Red;
			}
		}
		if (sibling)
		{
			if (sibling->mColor == Color::DoubleBlack)
			{
				sibling->mColor = Color::Black;
			}
			else if (sibling->mColor == Color::Black)
			{
				sibling->mColor = Color::Red;
			}
		}
		if (parent->mColor == Color::Black)
		{
			parent->mColor = Color::DoubleBlack;
		}
		else
		{
			parent->mColor = Color::Black;
		}
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Node* RedBlackTree<T, LessThanFunctor>::RotateRight(Node* node)
	{
		Node* newParent = node->mLeft;
		node->mLeft = newParent->mRight;

		if (newParent->mRight)
		{
			newParent->mRight->mParent = node;
		}
		newParent->mParent = node->mParent;

		if (!node->mParent)
		{
			mRoot = newParent;
		}
		else if (node->mParent->mRight == node)
		{
			node->mParent->mRight = newParent;
		}
		else
		{
			node->mParent->mLeft = newParent;
		}

		newParent->mRight = node;
		node->mParent = newParent;

		return newParent;
	}

	template<typename T, typename LessThanFunctor>
	inline typename RedBlackTree<T, LessThanFunctor>::Node* RedBlackTree<T, LessThanFunctor>::RotateLeft(Node* node)
	{
		Node* newParent = node->mRight;
		node->mRight = newParent->mLeft;

		if (newParent->mLeft)
		{
			newParent->mLeft->mParent = node;
		}
		newParent->mParent = node->mParent;

		if (!node->mParent)
		{
			mRoot = newParent;
		}
		else if (node->mParent->mLeft == node)
		{
			node->mParent->mLeft = newParent;
		}
		else
		{
			node->mParent->mRight = newParent;
		}

		newParent->mLeft = node;
		node->mParent = newParent;

		return newParent;
	}
	template<typename T, typename LessThanFunctor>
	inline void RedBlackTree<T, LessThanFunctor>::DeleteSubtree(Node* node)
	{
		if (node)
		{
			DeleteSubtree(node->mLeft);
			DeleteSubtree(node->mRight);
			delete node;
		}
	}
#if defined(UNIT_TEST)
	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::VerifyRedBlackTree()
	{
		int treeBlackHeight = FindBlackHeight();

		int currentBlackHeight = 0;

		return VerifyNode(mRoot, treeBlackHeight, currentBlackHeight);
	}

	template<typename T, typename LessThanFunctor>
	inline int RedBlackTree<T, LessThanFunctor>::FindBlackHeight()
	{
		int blackHeight = 0;
		Node* currentNode = mRoot;

		while (currentNode)
		{
			if (currentNode->mColor == Color::Black)
			{
				blackHeight++;
			}
			currentNode = currentNode->mLeft;
		}
		return blackHeight + 1;
	}

	template<typename T, typename LessThanFunctor>
	inline bool RedBlackTree<T, LessThanFunctor>::VerifyNode(RedBlackTree<T, LessThanFunctor>::Node* node, int const& treeBlackHeight, int& currentBlackHeight)
	{
		if (node)
		{
			//Increase current black height if necessary
			if (node->mColor == Color::Black)
			{
				currentBlackHeight++;
			}

			//Verify the left child is less than this node.
			if (node->mLeft && (node->mData <= node->mLeft->mData))
			{
				return false;
			}
			//Verify the right child is greater than this node.
			if (node->mRight && (node->mData >= node->mRight->mData))
			{
				return false;
			}

			//If root verify root is black
			if (node == mRoot && node->mColor != Color::Black)
			{
				return false;
			}
			//Verify color is valid (this node and parent are not red, and node is not somehow double black)
			else if ((node->mColor == Color::Red && node->mParent->mColor == Color::Red) || node->mColor == Color::DoubleBlack)
			{
				return false;
			}
			//Call recursively on other nodes
			else if (!VerifyNode(node->mLeft, treeBlackHeight, currentBlackHeight) || !VerifyNode(node->mRight, treeBlackHeight, currentBlackHeight))
			{
				return false;
			}
			//Decrease current black height if necessary
			if (node->mColor == Color::Black)
			{
				currentBlackHeight--;
			}
		}
		//If the node is null verify the black height is correct
		else if (currentBlackHeight + 1 != treeBlackHeight)
		{
			return false;
		}
		return true;
	}
#endif
}