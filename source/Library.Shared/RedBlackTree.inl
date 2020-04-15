#include "RedBlackTree.h"

namespace FIEAGameEngine
{
	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::RedBlackNode(TKey const& key, RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right) :mKey(key), mParent(parent), mLeft(left), mRight(right)
	{
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::RedBlackNode(RedBlackNode const& other) : mKey(other.mKey), mColor(other.mColor)
	{
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::RedBlackNode(RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right, RedBlackNode const& other) : RedBlackNode(other)
	{
		mParent = parent;
		mLeft = left;
		mRight = right;
	}

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::operator==(RedBlackNode const& other) const
	{
		return mKey == other.mKey;
	}

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::operator!=(RedBlackNode const& other) const
	{
		return !operator==(other);
	}
	
	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::GetSibling() const
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


	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::IsLeftChild()const
	{
		return mParent && mParent->mLeft == this;
	}

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::IsRightChild() const
	{
		return !IsLeftChild();
	}

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::HasRedChild() const
	{
		return (mLeft && mLeft->mColor == Color::Red) || (mRight && mRight->mColor == Color::Red);
	}

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::RedBlackNode::HasRedSibling() const
	{
		return (mParent && ((mParent->mLeft == this && mParent->mRight && mParent->mRight->mColor == Color::Red) || (mParent->mRight == this && mParent->mLeft && mParent->mLeft->mColor == Color::Red)));
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>::Iterator::Iterator(RedBlackTree const& owner, RedBlackNode* node) : mOwner(&owner), mNode(node)
	{
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator& RedBlackTree<TKey, LessThanFunctor>::Iterator::operator++()
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
			RedBlackNode* parent = mNode->mParent;
			while (parent && mNode == parent->mRight)
			{
				mNode = parent;
				parent = parent->mParent;
			}
			mNode = parent;
		}
		return *this;
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator RedBlackTree<TKey, LessThanFunctor>::Iterator::operator++(int)
	{
		Iterator iteratorBeforeIncrement(*this);
		operator++();
		return iteratorBeforeIncrement;
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator& RedBlackTree<TKey, LessThanFunctor>::Iterator::operator--()
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
			RedBlackNode* parent = mNode->mParent;
			while (parent && mNode == parent->mLeft)
			{
				mNode = parent;
				parent = parent->mParent;
			}
			mNode = parent;
		}
		return *this;
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator RedBlackTree<TKey, LessThanFunctor>::Iterator::operator--(int)
	{
		Iterator iteratorBeforeDecrement(*this);
		operator--();
		return iteratorBeforeDecrement;
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename bool RedBlackTree<TKey, LessThanFunctor>::Iterator::operator==(Iterator const& other) const
	{
		return (!mNode && !other.mNode) || ((mNode && other.mNode) && (*mNode == *(other.mNode)) && (mOwner == other.mOwner));
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename bool RedBlackTree<TKey, LessThanFunctor>::Iterator::operator!=(Iterator const& other) const
	{
		return !operator==(other);
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename TKey const& RedBlackTree<TKey, LessThanFunctor>::Iterator::operator*() const
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == const_cast<RedBlackTree*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return mNode->mKey;
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>::RedBlackTree(std::initializer_list<TKey> iList)
	{
		for (auto element : iList)
		{
			Insert(element);
		}
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>::RedBlackTree(RedBlackTree const& other)
	{
		*this = other;
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>::RedBlackTree(RedBlackTree && other)
	{
		*this = other;
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>& RedBlackTree<TKey, LessThanFunctor>::operator=(RedBlackTree const& other)
	{
		Clear();
		mRoot = CopySubtree<RedBlackNode>(nullptr, other.mRoot);
		return *this;
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>& RedBlackTree<TKey, LessThanFunctor>::operator=(RedBlackTree && other)
	{
		Clear();
		mRoot = other.mRoot;
		other.mRoot = nullptr;
		return *this;
	}

	template<typename TKey, typename LessThanFunctor>
	inline RedBlackTree<TKey, LessThanFunctor>::~RedBlackTree()
	{
		Clear();
	}

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::operator==(RedBlackTree const& other) const
	{
		bool bAreEqual = false;
		if (Size() == other.Size())
		{
			bAreEqual = true;
			Iterator thisIt = begin();
			Iterator rhsIt = other.begin();

			while (bAreEqual && thisIt != end())
			{
				bAreEqual = (*(thisIt++.mNode) == *(rhsIt++.mNode));
			}
		}
		return bAreEqual;
	}

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::operator!=(RedBlackTree const& other) const
	{
		return !operator==(other);
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator RedBlackTree<TKey, LessThanFunctor>::begin()
	{
		return Iterator(*this, FindMin(mRoot));
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator RedBlackTree<TKey, LessThanFunctor>::begin() const
	{
		return cbegin();
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator RedBlackTree<TKey, LessThanFunctor>::end()
	{
		return Iterator(*this, nullptr);
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator RedBlackTree<TKey, LessThanFunctor>::end() const
	{
		return cend();
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator RedBlackTree<TKey, LessThanFunctor>::cbegin() const
	{
		return const_Iterator(*this, FindMin(mRoot));
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator RedBlackTree<TKey, LessThanFunctor>::cend() const
	{
		return const_Iterator(*this, nullptr);
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator RedBlackTree<TKey, LessThanFunctor>::Find(TKey const& key)
	{
		return Iterator(*this, Search(mRoot, key));
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator RedBlackTree<TKey, LessThanFunctor>::Find(TKey const& key) const
	{
		return const_Iterator(*this, Search(mRoot,key));
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator RedBlackTree<TKey, LessThanFunctor>::LowerBound(TKey const& key)
	{
		return Iterator(*this, LowerBound(mRoot, key));
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator RedBlackTree<TKey, LessThanFunctor>::LowerBound(TKey const& key) const
	{
		return const_Iterator(*this, LowerBound(mRoot, key));
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::Iterator RedBlackTree<TKey, LessThanFunctor>::UpperBound(TKey const& key)
	{
		return Iterator(*this, UpperBound(mRoot, key));
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator RedBlackTree<TKey, LessThanFunctor>::UpperBound(TKey const& key) const
	{
		return const_Iterator(*this, UpperBound(mRoot, key));
	}

	template<typename TKey, typename LessThanFunctor>
	inline std::pair<typename RedBlackTree<TKey, LessThanFunctor>::Iterator, typename RedBlackTree<TKey, LessThanFunctor>::Iterator> RedBlackTree<TKey, LessThanFunctor>::EqualRange(TKey const& key)
	{
		return std::pair<Iterator, Iterator>(Iterator(*this, LowerBound(mRoot, key), Iterator(*this, UpperBound(mRoot, key))));
	}

	template<typename TKey, typename LessThanFunctor>
	inline std::pair<typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator, typename RedBlackTree<TKey, LessThanFunctor>::const_Iterator> RedBlackTree<TKey, LessThanFunctor>::EqualRange(TKey const& key) const
	{
		return std::pair<const_Iterator, const_Iterator>(const_Iterator(*this, LowerBound(mRoot, key), const_Iterator(*this, UpperBound(mRoot, key))));
	}

	template<typename TKey, typename LessThanFunctor>
	inline void RedBlackTree<TKey, LessThanFunctor>::Remove(TKey const& key)
	{
		Remove(mRoot, key);
	}

	template<typename TKey, typename LessThanFunctor>
	inline void RedBlackTree<TKey, LessThanFunctor>::Swap(RedBlackTree& other)
	{
		RedBlackNode* oldRoot = mRoot;
		mRoot = other.mRoot;
		other.mRoot = oldRoot;
	}

	template<typename TKey, typename LessThanFunctor>
	inline size_t RedBlackTree<TKey, LessThanFunctor>::Size() const
	{
		return Size(mRoot);
	}

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::IsEmpty() const
	{
		return mRoot;
	}

	template<typename TKey, typename LessThanFunctor>
	inline void RedBlackTree<TKey, LessThanFunctor>::Clear()
	{
		DeleteSubtree(mRoot);
		mRoot = nullptr;
	}

	template<typename TKey, typename LessThanFunctor>
	inline LessThanFunctor RedBlackTree<TKey, LessThanFunctor>::GetKeyComparison() const
	{
		return lessThan;
	}

	template<typename TKey, typename LessThanFunctor>
	inline std::pair<typename RedBlackTree<TKey, LessThanFunctor>::Iterator, bool> RedBlackTree<TKey, LessThanFunctor>::Insert(TKey const& key)
	{
		std::pair<RedBlackNode*, bool> insertResult = Insert<RedBlackNode>(mRoot, key);
		if (insertResult.second)
		{
			InsertFixUp(insertResult.first);
		}
		return std::pair<Iterator, bool>(Iterator(*this, insertResult.first), insertResult.second);
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* RedBlackTree<TKey, LessThanFunctor>::Search(RedBlackNode* subtreeRoot, TKey const& key) const
	{
		if (subtreeRoot)
		{
			if (lessThan(key, subtreeRoot->mKey))
			{
				subtreeRoot = Search(subtreeRoot->mLeft, key);
			}
			else if (lessThan(subtreeRoot->mKey, key))
			{
				subtreeRoot = Search(subtreeRoot->mRight, key);
			}
		}
		return subtreeRoot;
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* RedBlackTree<TKey, LessThanFunctor>::LowerBound(RedBlackNode* subtreeRoot, TKey const& key) const
	{
		if (subtreeRoot)
		{
			if (!lessThan(key, subtreeRoot->mKey))
			{
				subtreeRoot = Search(subtreeRoot->mLeft, key);
			}
		}
		return subtreeRoot;
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* RedBlackTree<TKey, LessThanFunctor>::UpperBound(RedBlackNode* subtreeRoot, TKey const& key) const
	{
		if (subtreeRoot)
		{
			if (lessThan(subtreeRoot->mKey, key))
			{
				subtreeRoot = Search(subtreeRoot->mRight, key);
			}
		}
		return subtreeRoot;
	}

	template<typename TKey, typename LessThanFunctor>
	template<typename NodeType>
	inline std::pair<NodeType*, bool> RedBlackTree<TKey, LessThanFunctor>::Insert(RedBlackNode* subtreeRoot, TKey const& key)
	{
		std::pair<RedBlackNode*, bool> insertionResult(nullptr, false);
		if (subtreeRoot)
		{
			if (lessThan(key, subtreeRoot->mKey))
			{
				insertionResult = Insert<NodeType>(subtreeRoot->mLeft, key);
				if (!subtreeRoot->mLeft)
				{
					subtreeRoot->mLeft = insertionResult.first;
				}
				if (!insertionResult.first->mParent)
				{
					insertionResult.first->mParent = subtreeRoot;
				}
			}
			else if (!lessThan(subtreeRoot->mKey, key))
			{
				insertionResult = { static_cast<NodeType*>(subtreeRoot), false };
			}
			else
			{
				insertionResult = Insert<NodeType>(subtreeRoot->mRight, key);
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
			//TODO: Perhaps create a virtual function that creates nodes of the appropriate type (not templated). This would allow for construction of val data when the node is constructed for node that stor more than just a key.
			insertionResult = { new NodeType(key), true };
		}
		else
		{
			mRoot = new NodeType(key);
			insertionResult = { static_cast<NodeType*>(mRoot), true };
		}
		return insertionResult;
	}

	template<typename TKey, typename LessThanFunctor>
	inline void RedBlackTree<TKey, LessThanFunctor>::InsertFixUp(RedBlackNode* node)
	{
		RedBlackNode* currentNode = node;
		while (currentNode != mRoot && currentNode->mColor == Color::Red && currentNode->mParent->mColor == Color::Red)
		{
			RedBlackNode* parent = currentNode->mParent;
			RedBlackNode* grandParent = currentNode->mParent->mParent;
			//Case A
			if (parent == grandParent->mLeft)
			{
				RedBlackNode* pibling = grandParent->mRight;
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
				RedBlackNode* pibling = grandParent->mLeft;
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

	template<typename TKey, typename LessThanFunctor>
	inline void RedBlackTree<TKey, LessThanFunctor>::Remove(RedBlackNode* subtreeRoot, TKey const& key)
	{
		RedBlackNode* nodeToDataSwap = Search(subtreeRoot, key);
		if (nodeToDataSwap)
		{
			RedBlackNode* nodeToDelete = nodeToDataSwap;
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
				*const_cast<TKey*>(&nodeToDataSwap->mKey) = std::move(nodeToDelete->mKey);

				RedBlackNode* parentOfDeletedNode = nodeToDelete->mParent;

		
				RedBlackNode* childOfDeletedNode = nullptr;
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
					RedBlackNode* currentNode = childOfDeletedNode;
					RedBlackNode* parent = parentOfDeletedNode;
					RedBlackNode* sibling;
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
			delete nodeToDelete;
		}
	}

	template<typename TKey, typename LessThanFunctor>
	inline size_t RedBlackTree<TKey, LessThanFunctor>::Size(RedBlackNode* subtreeRoot) const
	{
		if (subtreeRoot == nullptr)
		{
			return 0;
		}

		return 1 + Size(subtreeRoot->mLeft) + Size(subtreeRoot->mRight);
	}

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* RedBlackTree<TKey, LessThanFunctor>::FindMin(RedBlackNode* subtreeRoot) const
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

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* RedBlackTree<TKey, LessThanFunctor>::FindMax(RedBlackNode* subtreeRoot) const
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

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* RedBlackTree<TKey, LessThanFunctor>::RotateRight(RedBlackNode* node)
	{
		RedBlackNode* newParent = node->mLeft;
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

	template<typename TKey, typename LessThanFunctor>
	inline typename RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* RedBlackTree<TKey, LessThanFunctor>::RotateLeft(RedBlackNode* node)
	{
		RedBlackNode* newParent = node->mRight;
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

	template<typename TKey, typename LessThanFunctor>
	template<typename NodeType>
	inline NodeType* RedBlackTree<TKey, LessThanFunctor>::CopySubtree(NodeType* subtreeRoot, NodeType* otherSubtreeRoot)
	{
		if (otherSubtreeRoot)
		{
			NodeType* nodeAddress = static_cast<NodeType*>(malloc(sizeof(NodeType)));
			return new (nodeAddress) NodeType(subtreeRoot, CopySubtree(nodeAddress, otherSubtreeRoot->mLeft), CopySubtree(nodeAddress, otherSubtreeRoot->mRight), *otherSubtreeRoot);
		}
		return nullptr;
	}

	template<typename TKey, typename LessThanFunctor>
	inline void RedBlackTree<TKey, LessThanFunctor>::DeleteSubtree(RedBlackNode* node)
	{
		if (node)
		{
			DeleteSubtree(node->mLeft);
			DeleteSubtree(node->mRight);
			delete node;
		}
	}
#if defined(UNIT_TEST)
	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::VerifyRedBlackTree()
	{
		int treeBlackHeight = FindBlackHeight();

		int currentBlackHeight = 0;

		return VerifyNode(mRoot, treeBlackHeight, currentBlackHeight);
	}

	template<typename TKey, typename LessThanFunctor>
	inline int RedBlackTree<TKey, LessThanFunctor>::FindBlackHeight()
	{
		int blackHeight = 0;
		RedBlackNode* currentNode = mRoot;

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

	template<typename TKey, typename LessThanFunctor>
	inline bool RedBlackTree<TKey, LessThanFunctor>::VerifyNode(RedBlackTree<TKey, LessThanFunctor>::RedBlackNode* node, int const& treeBlackHeight, int& currentBlackHeight)
	{
		if (node)
		{
			//Increase current black height if necessary
			if (node->mColor == Color::Black)
			{
				currentBlackHeight++;
			}

			//Verify the left child is less than this node.
			if (node->mLeft && (node->mKey <= node->mLeft->mKey))
			{
				return false;
			}
			//Verify the right child is greater than this node.
			if (node->mRight && (node->mKey >= node->mRight->mKey))
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