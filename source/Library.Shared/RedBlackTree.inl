#include "RedBlackTree.h"

namespace FIEAGameEngine
{
	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackNode::RedBlackNode(ValueType const& value, RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right) :mValue(value), mParent(parent), mLeft(left), mRight(right)
	{
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackNode::RedBlackNode(RedBlackNode const& other) : mValue(other.mValue), mColor(other.mColor)
	{
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackNode::RedBlackNode(RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right, RedBlackNode const& other) : RedBlackNode(other)
	{
		mParent = parent;
		mLeft = left;
		mRight = right;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::operator==(RedBlackNode const& other) const
	{
		return mValue == other.mValue;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::operator!=(RedBlackNode const& other) const
	{
		return !operator==(other);
	}
	
	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::GetSibling() const
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


	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::IsLeftChild()const
	{
		return mParent && mParent->mLeft == this;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::IsRightChild() const
	{
		return !IsLeftChild();
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::HasRedChild() const
	{
		return (mLeft && mLeft->mColor == Color::Red) || (mRight && mRight->mColor == Color::Red);
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::HasRedSibling() const
	{
		return (mParent && ((mParent->mLeft == this && mParent->mRight && mParent->mRight->mColor == Color::Red) || (mParent->mRight == this && mParent->mLeft && mParent->mLeft->mColor == Color::Red)));
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::TreeIterator::TreeIterator(RedBlackTree const& owner, RedBlackNode* node) : mOwner(&owner), mNode(node)
	{
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeIterator& RedBlackTree<TreeTraits>::TreeIterator::operator++()
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

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeIterator RedBlackTree<TreeTraits>::TreeIterator::operator++(int)
	{
		Iterator iteratorBeforeIncrement(*this);
		operator++();
		return iteratorBeforeIncrement;
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeIterator& RedBlackTree<TreeTraits>::TreeIterator::operator--()
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

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeIterator RedBlackTree<TreeTraits>::TreeIterator::operator--(int)
	{
		Iterator iteratorBeforeDecrement(*this);
		operator--();
		return iteratorBeforeDecrement;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::TreeIterator::operator==(TreeIterator const& other) const
	{
		return (!mNode && !other.mNode) || ((mNode && other.mNode) && (*mNode == *(other.mNode)) && (mOwner == other.mOwner));
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::TreeIterator::operator!=(TreeIterator const& other) const
	{
		return !operator==(other);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ValueType& RedBlackTree<TreeTraits>::TreeIterator::operator*()
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == const_cast<RedBlackTree*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return mNode->mValue;
	}

	template<typename TreeTraits>
	inline RedBlackTree<TreeTraits>::TreeConstIterator::TreeConstIterator(RedBlackTree const& owner, RedBlackNode* node) : mOwner(&owner), mNode(node)
	{
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeConstIterator& RedBlackTree<TreeTraits>::TreeConstIterator::operator++()
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

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeConstIterator RedBlackTree<TreeTraits>::TreeConstIterator::operator++(int)
	{
		ConstIterator iteratorBeforeIncrement(*this);
		operator++();
		return iteratorBeforeIncrement;
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeConstIterator& RedBlackTree<TreeTraits>::TreeConstIterator::operator--()
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

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeConstIterator RedBlackTree<TreeTraits>::TreeConstIterator::operator--(int)
	{
		TreeConstIterator iteratorBeforeDecrement(*this);
		operator--();
		return iteratorBeforeDecrement;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::TreeConstIterator::operator==(TreeConstIterator const& other) const
	{
		return (!mNode && !other.mNode) || ((mNode && other.mNode) && (*mNode == *(other.mNode)) && (mOwner == other.mOwner));
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::TreeConstIterator::operator!=(TreeConstIterator const& other) const
	{
		return !operator==(other);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ValueType& RedBlackTree<TreeTraits>::TreeConstIterator::operator*()
	{
		if (mOwner == nullptr)
		{
			throw std::exception(ownerIsNullException.c_str());
		}
		if (*this == const_cast<RedBlackTree*>(mOwner)->end())
		{
			throw std::exception(attemptToIteratarePastLastElementException.c_str());
		}
		return mNode->mValue;
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackTree(std::initializer_list<ValueType> iList)
	{
		for (auto element : iList)
		{
			Insert(element);
		}
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackTree(RedBlackTree const& other)
	{
		*this = other;
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackTree(RedBlackTree && other)
	{
		*this = other;
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>& RedBlackTree<TreeTraits>::operator=(RedBlackTree const& other)
	{
		Clear();
		mRoot = CopySubtree(nullptr, other.mRoot);
		return *this;
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>& RedBlackTree<TreeTraits>::operator=(RedBlackTree && other)
	{
		Clear();
		mRoot = other.mRoot;
		other.mRoot = nullptr;
		return *this;
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::~RedBlackTree()
	{
		Clear();
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::operator==(RedBlackTree const& other) const
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

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::operator!=(RedBlackTree const& other) const
	{
		return !operator==(other);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::begin()
	{
		return Iterator(*this, FindMin(mRoot));
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::begin() const
	{
		return cbegin();
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::end()
	{
		return Iterator(*this, nullptr);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::end() const
	{
		return cend();
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::cbegin() const
	{
		return ConstIterator(*this, FindMin(mRoot));
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::cend() const
	{
		return ConstIterator(*this, nullptr);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::Find(ValueType const& value)
	{
		return Iterator(*this, Search(mRoot, value));
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::Find(ValueType const& value) const
	{
		return ConstIterator(*this, Search(mRoot,value));
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::LowerBound(ValueType const& value)
	{
		return Iterator(*this, LowerBound(mRoot, value));
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::LowerBound(ValueType const& value) const
	{
		return ConstIterator(*this, LowerBound(mRoot, value));
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::UpperBound(ValueType const& value)
	{
		return Iterator(*this, UpperBound(mRoot, value));
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::UpperBound(ValueType const& value) const
	{
		return ConstIterator(*this, UpperBound(mRoot, value));
	}

	template <typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::Iterator, typename RedBlackTree<TreeTraits>::Iterator> RedBlackTree<TreeTraits>::EqualRange(ValueType const& value)
	{
		return std::pair<Iterator, Iterator>(Iterator(*this, LowerBound(mRoot, value), Iterator(*this, UpperBound(mRoot, value))));
	}

	template <typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::ConstIterator, typename RedBlackTree<TreeTraits>::ConstIterator> RedBlackTree<TreeTraits>::EqualRange(ValueType const& value) const
	{
		return std::pair<ConstIterator, ConstIterator>(ConstIterator(*this, LowerBound(mRoot, value), ConstIterator(*this, UpperBound(mRoot, value))));
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::Remove(ValueType const& value)
	{
		Remove(mRoot, value);
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::Swap(RedBlackTree& other)
	{
		RedBlackNode* oldRoot = mRoot;
		mRoot = other.mRoot;
		other.mRoot = oldRoot;
	}

	template <typename TreeTraits>
	inline size_t RedBlackTree<TreeTraits>::Size() const
	{
		return Size(mRoot);
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::IsEmpty() const
	{
		return mRoot;
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::Clear()
	{
		DeleteSubtree(mRoot);
		mRoot = nullptr;
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::KeyCompare RedBlackTree<TreeTraits>::GetKeyComparison() const
	{
		return keyCompare;
	}

	template <typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::Iterator, bool> RedBlackTree<TreeTraits>::Insert(ValueType const& value)
	{
		std::pair<RedBlackNode*, bool> insertResult = Insert(mRoot, value);
		if (insertResult.second)
		{
			InsertFixUp(insertResult.first);
		}
		return std::pair<Iterator, bool>(Iterator(*this, insertResult.first), insertResult.second);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::Search(RedBlackNode* subtreeRoot, ValueType const& value) const
	{
		if (subtreeRoot)
		{
			if (keyCompare(TreeTraits::ExtractKey(value), TreeTraits::ExtractKey(subtreeRoot->mValue)))
			{
				subtreeRoot = Search(subtreeRoot->mLeft, value);
			}
			else if (keyCompare(TreeTraits::ExtractKey(subtreeRoot->mValue), TreeTraits::ExtractKey(value)))
			{
				subtreeRoot = Search(subtreeRoot->mRight, value);
			}
		}
		return subtreeRoot;
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::LowerBound(RedBlackNode* subtreeRoot, ValueType const& value) const
	{
		if (subtreeRoot)
		{
			if (!keyCompare(TreeTraits::ExtractKey(value), TreeTraits::ExtractKey(subtreeRoot->mValue)))
			{
				subtreeRoot = Search(subtreeRoot->mLeft, value);
			}
		}
		return subtreeRoot;
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::UpperBound(RedBlackNode* subtreeRoot, ValueType const& value) const
	{
		if (subtreeRoot)
		{
			if (keyCompare(TreeTraits::ExtractKey(subtreeRoot->mValue), TreeTraits::ExtractKey(value)))
			{
				subtreeRoot = Search(subtreeRoot->mRight, value);
			}
		}
		return subtreeRoot;
	}

	template <typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::RedBlackNode*, bool> RedBlackTree<TreeTraits>::Insert(RedBlackNode* subtreeRoot, ValueType const& value)
	{
		std::pair<RedBlackNode*, bool> insertionResult(nullptr, false);
		if (subtreeRoot)
		{
			if (keyCompare(TreeTraits::ExtractKey(value), TreeTraits::ExtractKey(subtreeRoot->mValue)))
			{
				insertionResult = Insert(subtreeRoot->mLeft, value);
				if (!subtreeRoot->mLeft)
				{
					subtreeRoot->mLeft = insertionResult.first;
				}
				if (!insertionResult.first->mParent)
				{
					insertionResult.first->mParent = subtreeRoot;
				}
			}
			else if (!keyCompare(TreeTraits::ExtractKey(subtreeRoot->mValue), TreeTraits::ExtractKey(value)))
			{
				insertionResult = {subtreeRoot, false };
			}
			else
			{
				insertionResult = Insert(subtreeRoot->mRight, value);
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
			insertionResult = { new RedBlackNode(value), true };
		}
		else
		{
			mRoot = new RedBlackNode(value);
			insertionResult = { mRoot, true };
		}
		return insertionResult;
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::InsertFixUp(RedBlackNode* node)
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

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::Remove(RedBlackNode* subtreeRoot, ValueType const& value)
	{
		RedBlackNode* nodeToDataSwap = Search(subtreeRoot, value);
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
				nodeToDataSwap->mValue = std::move(nodeToDelete->mValue);

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

	template <typename TreeTraits>
	inline size_t RedBlackTree<TreeTraits>::Size(RedBlackNode* subtreeRoot) const
	{
		if (subtreeRoot == nullptr)
		{
			return 0;
		}

		return 1 + Size(subtreeRoot->mLeft) + Size(subtreeRoot->mRight);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::FindMin(RedBlackNode* subtreeRoot) const
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

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::FindMax(RedBlackNode* subtreeRoot) const
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

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RotateRight(RedBlackNode* node)
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

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RotateLeft(RedBlackNode* node)
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

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::CopySubtree(RedBlackNode* subtreeRoot, RedBlackNode* otherSubtreeRoot)
	{
		if (otherSubtreeRoot)
		{
			RedBlackNode* nodeAddress = static_cast<RedBlackNode*>(malloc(sizeof(RedBlackNode)));
			return new (nodeAddress) RedBlackNode(subtreeRoot, CopySubtree(nodeAddress, otherSubtreeRoot->mLeft), CopySubtree(nodeAddress, otherSubtreeRoot->mRight), *otherSubtreeRoot);
		}
		return nullptr;
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::DeleteSubtree(RedBlackNode* node)
	{
		if (node)
		{
			DeleteSubtree(node->mLeft);
			DeleteSubtree(node->mRight);
			delete node;
		}
	}
#if defined(UNIT_TEST)
	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::VerifyRedBlackTree()
	{
		int treeBlackHeight = FindBlackHeight();

		int currentBlackHeight = 0;

		return VerifyNode(mRoot, treeBlackHeight, currentBlackHeight);
	}

	template <typename TreeTraits>
	inline int RedBlackTree<TreeTraits>::FindBlackHeight()
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

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::VerifyNode(RedBlackTree<TreeTraits>::RedBlackNode* node, int const& treeBlackHeight, int& currentBlackHeight)
	{
		if (node)
		{
			//Increase current black height if necessary
			if (node->mColor == Color::Black)
			{
				currentBlackHeight++;
			}

			//Verify the left child is less than this node.
			if (node->mLeft && (node->mValue <= node->mLeft->mValue))
			{
				return false;
			}
			//Verify the right child is greater than this node.
			if (node->mRight && (node->mValue >= node->mRight->mValue))
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