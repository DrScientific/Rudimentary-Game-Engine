#include "RedBlackTree.h"

namespace FIEAGameEngine
{
	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackNode::RedBlackNode(KeyValueType const& value, RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right) :mKeyAndValue(value), mParent(parent), mLeft(left), mRight(right)
	{
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackNode::RedBlackNode(RedBlackNode const& other) : mKeyAndValue(other.mKeyAndValue), mColor(other.mColor)
	{
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackNode::RedBlackNode(RedBlackNode&& other) : mKeyAndValue(other.mKeyAndValue), mColor(other.mColor)
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
		return mKeyAndValue == other.mKeyAndValue;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::operator!=(RedBlackNode const& other) const
	{
		return !operator==(other);
	}


	template<typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::IsRoot() const
	{
		return !mParent;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::IsLeftChild()const
	{
		return mParent && mParent->mLeft == this;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::RedBlackNode::IsRightChild() const
	{
		return mParent && mParent->mRight == this;
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

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::Search(KeyType const& key) const
	{
		if (this)
		{
			if (keyCompare(key, TreeTraits::ExtractKey(mKeyAndValue)))
			{
				return mLeft->Search(key);
			}
			else if (keyCompare(TreeTraits::ExtractKey(mKeyAndValue), key))
			{
				return mRight->Search(key);
			}
		}
		return const_cast<RedBlackNode*>(this);
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::LowerBound(KeyType const& key) const
	{
		RedBlackNode* smallestNodeGreaterOrEqualToKey = nullptr;
		LowerBoundRecursive(key, smallestNodeGreaterOrEqualToKey);
		return smallestNodeGreaterOrEqualToKey;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::UpperBound(KeyType const& key) const
	{
		RedBlackNode* smallestNodeGreaterThanKey = nullptr;
		UpperBoundRecursive(key, smallestNodeGreaterThanKey);
		return smallestNodeGreaterThanKey;
	}

	template<typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::RedBlackNode*, typename RedBlackTree<TreeTraits>::RedBlackNode*> RedBlackTree<TreeTraits>::RedBlackNode::EqualRange(KeyType const& key) const
	{
		return std::pair<RedBlackNode*, RedBlackNode*>(LowerBound(key),UpperBound(key));
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::FindRoot()
	{
		RedBlackNode* root = this;
		while (root->mParent)
		{
			root = root->mParent;
		}
		return root;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode const* RedBlackTree<TreeTraits>::RedBlackNode::FindRoot() const
	{
		RedBlackNode const* root = this;
		while (root->mParent)
		{
			root = root->mParent;
		}
		return root;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::FindMin()
	{
		RedBlackNode* min = this;
		while (min->mLeft)
		{
			min = min->mLeft;
		}
		return min;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode const* RedBlackTree<TreeTraits>::RedBlackNode::FindMin() const
	{
		RedBlackNode const * min = this;
		while (min->mLeft)
		{
			min = min->mLeft;
		}
		return min;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::FindMax()
	{
		RedBlackNode* max = this;
		while (max->mRight)
		{
			max = max->mRight;
		}
		return max;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode const* RedBlackTree<TreeTraits>::RedBlackNode::FindMax() const
	{
		RedBlackNode const * max = this;
		while (max->mRight)
		{
			max = max->mRight;
		}
		return max;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::RotateRight()
	{
		RedBlackNode* newParent = mLeft;
		mLeft = newParent->mRight;

		if (newParent->mRight)
		{
			newParent->mRight->mParent = this;
		}
		newParent->mParent = mParent;

		if (mParent)
		{
			if (mParent->mRight == this)
			{
				mParent->mRight = newParent;
			}
			else
			{
				mParent->mLeft = newParent;
			}
		}

		newParent->mRight = this;
		mParent = newParent;

		return mParent;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::RotateLeft()
	{
		RedBlackNode* newParent = mRight;
		mRight = newParent->mLeft;

		if (newParent->mLeft)
		{
			newParent->mLeft->mParent = this;
		}
		newParent->mParent = mParent;

		if (mParent)
		{
			if (mParent->mLeft == this)
			{
				mParent->mLeft = newParent;
			}
			else
			{
				mParent->mRight = newParent;
			}
		}

		newParent->mLeft = this;
		mParent = newParent;

		return mParent;
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::CreateSubtreeCopy()
	{
		return CreateSubtreeCopyRecursive(nullptr, this);
	}

	template<typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::RedBlackNode::DeleteSubtree()
	{
		if (mLeft)
		{
			mLeft->DeleteSubtreeRecursive();
		}
		if (mRight)
		{
			mRight->DeleteSubtreeRecursive();
		}
		if (IsLeftChild())
		{
			mParent->mLeft = nullptr;
		}
		else if (IsRightChild())
		{
			mParent->mRight = nullptr;
		}
		delete this;
	}

	template<typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::RedBlackNode::LowerBoundRecursive(KeyType const& key, RedBlackNode*& smallestNodeGreaterOrEqualToKey) const
	{

		//If the value is greater than or equal to the key.
		//The key is less or equal to than the value.
		if (!keyCompare(TreeTraits::ExtractKey(mKeyAndValue), key))
		{
			//If we have not yet encountered a value greater than or equal to the key or this value is less than or equal to the previous smallest value we found.
			if (!smallestNodeGreaterOrEqualToKey || !keyCompare(TreeTraits::ExtractKey(smallestNodeGreaterOrEqualToKey->mKeyAndValue), TreeTraits::ExtractKey(mKeyAndValue)))
			{
				smallestNodeGreaterOrEqualToKey = const_cast<RedBlackNode*>(this);
			}
			if (mLeft)
			{
				mLeft->LowerBoundRecursive(key, smallestNodeGreaterOrEqualToKey);
			}
		}
		//If the value is less than the key.
		//The key is greater than the value.
		else if (mRight)
		{
			mRight->LowerBoundRecursive(key, smallestNodeGreaterOrEqualToKey);
		}
	}

	template<typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::RedBlackNode::UpperBoundRecursive(KeyType const& key, RedBlackNode*& smallestNodeGreaterThanKey) const
	{
		//If the key is less than the value.
		//The value is greater than the key.
		if (keyCompare(key, TreeTraits::ExtractKey(mKeyAndValue)))
		{
			//If we have not yet encountered a value greater than the key or this value is less than or equal to the previous smallest value we found.
			if (!smallestNodeGreaterThanKey || !keyCompare(TreeTraits::ExtractKey(smallestNodeGreaterThanKey->mKeyAndValue), TreeTraits::ExtractKey(mKeyAndValue)))
			{
				smallestNodeGreaterThanKey = const_cast<RedBlackNode*>(this);
			}
			if (mLeft)
			{
				mLeft->UpperBoundRecursive(key, smallestNodeGreaterThanKey);
			}
		}
		//If the key is greater than or equal to the value.
		//The value is less than or equal to the key.
		else if(mRight)
		{
			mRight->UpperBoundRecursive(key, smallestNodeGreaterThanKey);
		}
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::RedBlackNode* RedBlackTree<TreeTraits>::RedBlackNode::CreateSubtreeCopyRecursive(RedBlackNode* parent, RedBlackNode* otherSubtreeRootToCopy)
	{
		if (otherSubtreeRootToCopy)
		{
			RedBlackNode* nodeAddress = static_cast<RedBlackNode*>(malloc(sizeof(RedBlackNode)));
			return new (nodeAddress) RedBlackNode(parent, CreateSubtreeCopyRecursive(nodeAddress, otherSubtreeRootToCopy->mLeft), CreateSubtreeCopyRecursive(nodeAddress, otherSubtreeRootToCopy->mRight), *otherSubtreeRootToCopy);
		}
		return nullptr;
	}

	template<typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::RedBlackNode::DeleteSubtreeRecursive()
	{
		if (mLeft)
		{
			mLeft->DeleteSubtreeRecursive();
		}
		if (mRight)
		{
			mRight->DeleteSubtreeRecursive();
		}
		delete this;
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::TreeIterator::TreeIterator(RedBlackTree const& owner, RedBlackNode* node) : mOwner(&owner), mNode(node)
	{
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::TreeIterator::TreeIterator(RedBlackTree const* owner, RedBlackNode* node) : mOwner(owner), mNode(node)
	{
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeIterator& RedBlackTree<TreeTraits>::TreeIterator::operator++()
	{
		if (!mOwner)
		{
			throw std::exception(attemptToIncrementOrphanedIteratorException.c_str());
		}
		else if (!mNode)
		{
			throw std::exception(attemptToIteratePastLastElementException.c_str());
		}
		else if (mNode->mRight)
		{
			mNode = mNode->mRight->FindMin();
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
		if (!mOwner)
		{
			throw std::exception(attemptToDecrementOrphanedIteratorException.c_str());
		}
		if (mNode == mOwner->mRoot->FindMin())
		{
			throw std::exception(attemptToDecrementBeforeFirstElementException.c_str());
		}
		else if (!mNode)
		{
			mNode = mOwner->mRoot->FindMax();
		}
		else if (mNode->mLeft)
		{
			mNode = mNode->mLeft->FindMax();
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
		return mNode == other.mNode;;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::TreeIterator::operator!=(TreeIterator const& other) const
	{
		return !operator==(other);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::KeyValueType& RedBlackTree<TreeTraits>::TreeIterator::operator*()
	{
		if (!mNode)
		{
			throw std::exception(attemptToDerferenceEndIterator.c_str());
		}
		return mNode->mKeyAndValue;
	}

	template<typename TreeTraits>
	inline RedBlackTree<TreeTraits>::TreeConstIterator::TreeConstIterator(RedBlackTree const& owner, RedBlackNode* node) : mOwner(&owner), mNode(node)
	{
	}

	template<typename TreeTraits>
	inline RedBlackTree<TreeTraits>::TreeConstIterator::TreeConstIterator(RedBlackTree const* owner, RedBlackNode* node) : mOwner(owner), mNode(node)
	{
	}

	template<typename TreeTraits>
	inline RedBlackTree<TreeTraits>::TreeConstIterator::TreeConstIterator(TreeIterator const& other) : mOwner(other.mOwner), mNode(other.mNode)
	{
	}

	template<typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::TreeConstIterator& RedBlackTree<TreeTraits>::TreeConstIterator::operator++()
	{
		if (!mOwner)
		{
			throw std::exception(attemptToIncrementOrphanedIteratorException.c_str());
		}
		else if (!mNode)
		{
			throw std::exception(attemptToIteratePastLastElementException.c_str());
		}
		else if (mNode->mRight)
		{
			mNode = mNode->mRight->FindMin();
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
		if (mNode == mOwner->mRoot->FindMin())
		{
			throw std::exception(attemptToDecrementBeforeFirstElementException.c_str());
		}
		else if (!mNode)
		{
			mNode = mOwner->mRoot->FindMax();
		}
		else if (mNode->mLeft)
		{
			mNode = mNode->mLeft->FindMax();
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
		return mNode == other.mNode;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::TreeConstIterator::operator!=(TreeConstIterator const& other) const
	{
		return !operator==(other);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::KeyValueType& RedBlackTree<TreeTraits>::TreeConstIterator::operator*()
	{
		if (!mNode)
		{
			throw std::exception(attemptToDerferenceEndIterator.c_str());
		}
		return mNode->mKeyAndValue;
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>::RedBlackTree(std::initializer_list<KeyValueType> iList)
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
	inline RedBlackTree<TreeTraits>::RedBlackTree(RedBlackTree&& other)
	{
		*this = std::move(other);
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>& RedBlackTree<TreeTraits>::operator=(RedBlackTree const& other)
	{
		Clear();
		mRoot = other.mRoot->CreateSubtreeCopy();
		mSize = other.mSize;
		return *this;
	}

	template <typename TreeTraits>
	inline RedBlackTree<TreeTraits>& RedBlackTree<TreeTraits>::operator=(RedBlackTree&& other)
	{
		Clear();
		mRoot = other.mRoot;
		mSize = other.mSize;
		other.mRoot = nullptr;
		other.mSize = 0;
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
		if (mSize == other.mSize)
		{
			bAreEqual = true;
			ConstIterator thisIt = cbegin();
			ConstIterator rhsIt = other.cbegin();

			while (bAreEqual && thisIt != cend())
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
		if (mRoot)
		{
			return Iterator(*this, mRoot->FindMin());
		}
		return end();
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
		if (mRoot)
		{
			return ConstIterator(*this, mRoot->FindMin());
		}
		return cend();
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::cend() const
	{
		return ConstIterator(*this, nullptr);
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::Find(KeyType const& key)
	{
		if (mRoot)
		{
			return Iterator(*this, mRoot->Search(key));
		}
		return end();
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::Find(KeyType const& key) const
	{
		if (mRoot)
		{
			return ConstIterator(*this, mRoot->Search(key));
		}
		return cend();
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::Contains(KeyType const& key) const
	{
		if (mRoot)
		{
			return mRoot->Search(key);
		}
		return false;
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::LowerBound(KeyType const& key)
	{
		if (mRoot)
		{
			return Iterator(*this, mRoot->LowerBound(key));
		}
		return end();
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::LowerBound(KeyType const& key) const
	{
		if (mRoot)
		{
			return ConstIterator(*this, mRoot->LowerBound(key));
		}
		return cend();
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::UpperBound(KeyType const& key)
	{
		if (mRoot)
		{
			return Iterator(*this, mRoot->UpperBound(key));
		}
		return end();
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::ConstIterator RedBlackTree<TreeTraits>::UpperBound(KeyType const& key) const
	{
		if (mRoot)
		{
			return ConstIterator(*this, mRoot->UpperBound(key));
		}
		return end();
	}

	template <typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::Iterator, typename RedBlackTree<TreeTraits>::Iterator> RedBlackTree<TreeTraits>::EqualRange(KeyType const& key)
	{
		return std::pair<Iterator, Iterator>(LowerBound(key), UpperBound(key));
	}

	template <typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::ConstIterator, typename RedBlackTree<TreeTraits>::ConstIterator> RedBlackTree<TreeTraits>::EqualRange(KeyType const& key) const
	{
		return std::pair<ConstIterator, ConstIterator>(LowerBound(key), UpperBound(key));
	}

	template <typename TreeTraits>
	inline size_t RedBlackTree<TreeTraits>::Count(KeyType const& key) const
	{
		size_t count = 0;
		std::pair<ConstIterator, ConstIterator> range = EqualRange(key);
		for (ConstIterator i = range.first; i != range.second; i++)
		{
			count++;
		}
		return count;
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::Swap(RedBlackTree& other)
	{
		RedBlackNode* tempRoot = mRoot;
		size_t tempSize = mSize;
		mRoot = other.mRoot;
		mSize = other.mSize;
		other.mRoot = tempRoot;
		other.mSize = tempSize;
	}

	template <typename TreeTraits>
	inline size_t RedBlackTree<TreeTraits>::Size() const
	{
		return mSize;
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::IsEmpty() const
	{
		return !mSize;
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::Clear()
	{
		if (mRoot)
		{
			mRoot->DeleteSubtree();
			mRoot = nullptr;
			mSize = 0;
		}
	}

	template <typename TreeTraits>
	inline typename RedBlackTree<TreeTraits>::KeyCompare const& RedBlackTree<TreeTraits>::GetKeyComparison() const
	{
		return keyCompare;
	}

	template <typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::Iterator, bool> RedBlackTree<TreeTraits>::Insert(KeyValueType const& keyAndValue)
	{
		std::pair<RedBlackNode*, bool> insertResult = Insert(mRoot, keyAndValue);
		if (insertResult.second)
		{
			mSize++;
			InsertFixUp(insertResult.first);
		}
		return std::pair<Iterator, bool>(Iterator(*this, insertResult.first), insertResult.second);
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::Remove(KeyType const& key)
	{
		std::pair<ConstIterator, ConstIterator> equalRange = EqualRange(key);
		for (ConstIterator i = equalRange.first; i != equalRange.second;)
		{
			Remove(i++);
		}
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::Remove(ConstIterator elementToRemove)
	{
		if (elementToRemove != end())
		{
			delete (Extract(elementToRemove).mNode);
		}
	}

	template <typename TreeTraits>
	inline std::pair<typename RedBlackTree<TreeTraits>::RedBlackNode*, bool> RedBlackTree<TreeTraits>::Insert(RedBlackNode* subtreeRoot, KeyValueType const& keyAndValue)
	{
		std::pair<RedBlackNode*, bool> insertionResult(nullptr, false);
		if (subtreeRoot)
		{
			if (keyCompare(TreeTraits::ExtractKey(keyAndValue), TreeTraits::ExtractKey(subtreeRoot->mKeyAndValue)))
			{
				insertionResult = Insert(subtreeRoot->mLeft, keyAndValue);
				if (!subtreeRoot->mLeft)
				{
					subtreeRoot->mLeft = insertionResult.first;
				}
				if (!insertionResult.first->mParent)
				{
					insertionResult.first->mParent = subtreeRoot;
				}
			}
			else if (keyCompare(TreeTraits::ExtractKey(subtreeRoot->mKeyAndValue), TreeTraits::ExtractKey(keyAndValue)) || bIsMulti)
			{
				insertionResult = Insert(subtreeRoot->mRight, keyAndValue);
				if (!subtreeRoot->mRight)
				{
					subtreeRoot->mRight = insertionResult.first;
				}
				if (!insertionResult.first->mParent)
				{
					insertionResult.first->mParent = subtreeRoot;
				}
			}
			else
			{
				insertionResult = { subtreeRoot, false };
			}
		}
		else if (mRoot)
		{
			insertionResult = { new RedBlackNode(keyAndValue), true };
		}
		else
		{
			mRoot = new RedBlackNode(keyAndValue);
			insertionResult = { mRoot, true };
		}
		return insertionResult;
	}

	template <typename TreeTraits>
	inline void RedBlackTree<TreeTraits>::InsertFixUp(RedBlackNode* subtree)
	{
		RedBlackNode* currentNode = subtree;
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
					RedBlackNode* potentialNewRoot;
					//Case 2A
					if (currentNode == parent->mRight)
					{
						potentialNewRoot = parent->RotateLeft();
						if (potentialNewRoot->IsRoot())
						{
							mRoot = potentialNewRoot;
						}
						currentNode = parent;
						parent = parent->mParent;
					}
					//Case 3A
					potentialNewRoot = grandParent->RotateRight();
					if (potentialNewRoot->IsRoot())
					{
						mRoot = potentialNewRoot;
					}
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
					RedBlackNode* potentialNewRoot;
					//Case 2B
					if (currentNode == parent->mLeft)
					{
						potentialNewRoot = parent->RotateRight();
						if (potentialNewRoot->IsRoot())
						{
							mRoot = potentialNewRoot;
						}
						currentNode = parent;
						parent = parent->mParent;
					}
					//Case 3B
					potentialNewRoot = grandParent->RotateLeft();
					if (potentialNewRoot->IsRoot())
					{
						mRoot = potentialNewRoot;
					}
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
	inline typename RedBlackTree<TreeTraits>::Iterator RedBlackTree<TreeTraits>::Extract(RedBlackTree<TreeTraits>::ConstIterator it)
	{
		RedBlackNode* nodeToExtract = it.mNode;

		if (nodeToExtract)
		{
			mSize--;

			RedBlackNode* replacementNode = nullptr;
			RedBlackNode* replacementNodeParent = nullptr;

			//If the nodeToExtract has one or no subtrees.
			if (!nodeToExtract->mLeft || !nodeToExtract->mRight)
			{
				//The node to extract has either a right subtree or no subtrees(It is a leaf.) It's right child will be moved up to replace it.
				if (!nodeToExtract->mLeft)
				{
					replacementNode = nodeToExtract->mRight;
				}
				//The node to extract a left subtree. It's left child will be moved up to replace it
				else if (!nodeToExtract->mRight)
				{
					replacementNode = nodeToExtract->mLeft;
				}

				replacementNodeParent = nodeToExtract->mParent;
				if (replacementNode)
				{
					replacementNode->mParent = replacementNodeParent;
				}

				//Fix up pointers of replacementNodeParent
				if (mRoot == nodeToExtract)
				{
					mRoot = replacementNode;
				}
				else if (replacementNodeParent->mLeft == nodeToExtract)
				{
					replacementNodeParent->mLeft = replacementNode;
				}
				else
				{
					replacementNodeParent->mRight = replacementNode;
				}

				if (mRoot)
				{
					//Fix up children of root if necessary.
					if (mRoot->mLeft == nodeToExtract)
					{
						mRoot->mLeft = replacementNode ? replacementNode->FindMin() : replacementNodeParent;
					}
					if (mRoot->mRight == nodeToExtract)
					{
						mRoot->mRight = replacementNode ? replacementNode->FindMax() : replacementNodeParent;
					}
				}

			}
			//The node to extract must have two subtrees.
			else
			{
				ConstIterator successor = it;							//Copy the current iterator to get it's successor without incrementing the original iterator.
				++successor;
				RedBlackNode* successorNode = successor.mNode;

				replacementNode = successorNode->mRight;			//In this case the replacement node is the node right of it's successor.

				nodeToExtract->mLeft->mParent = successorNode;
				successorNode->mLeft = nodeToExtract->mLeft;

				//If the node to extract's right child is it's successor
				if (nodeToExtract->mRight == successorNode)
				{
					replacementNodeParent = successorNode;			//TODO: Confirm that this prevents the replacementNodeParent from parenting itself???
				}
				else
				{
					replacementNodeParent = successorNode->mParent;
					if (replacementNode)
					{
						replacementNode->mParent = replacementNodeParent;
					}
					replacementNodeParent->mLeft = replacementNode;
					successorNode->mRight = nodeToExtract->mRight;
					nodeToExtract->mRight->mParent = successorNode;
				}

				if (mRoot == nodeToExtract)
				{
					mRoot = successorNode;
				}
				else if (nodeToExtract->mParent->mLeft == nodeToExtract)
				{
					nodeToExtract->mParent->mLeft = successorNode;
				}
				else
				{
					nodeToExtract->mParent->mRight = successorNode;
				}

				successorNode->mParent = nodeToExtract->mParent;
				Color tempColor = successorNode->mColor;
				successorNode->mColor = nodeToExtract->mColor;
				nodeToExtract->mColor = tempColor;
			}


			//Case 1: The node to delete is red. Only thing left to do is to delete the node.

			//Case 2: The node to delete is black. The properties of the tree need to fixed up.
			if (nodeToExtract->mColor == Color::Black)
			{
				if (replacementNode)
				{
					if (replacementNode->mColor == Color::Black)
					{
						replacementNode->mColor = Color::DoubleBlack;
					}
					else
					{
						replacementNode->mColor = Color::Black;
					}
				}
				RedBlackNode* currentNode = replacementNode;
				RedBlackNode* parent = replacementNodeParent;
				RedBlackNode* sibling;
				while ((!currentNode || currentNode->mColor == Color::DoubleBlack) && currentNode != mRoot)
				{
					sibling = (currentNode == parent->mLeft ? parent->mRight : parent->mLeft);

					RedBlackNode* potentialNewRoot;

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
								potentialNewRoot = parent->RotateRight();
								if (potentialNewRoot->IsRoot())
								{
									mRoot = potentialNewRoot;
								}
							}
							//Left-Right Case (Only the sibling's right child is red)
							else
							{
								sibling->mRight->mColor = parent->mColor;
								potentialNewRoot = sibling->RotateLeft();
								if (potentialNewRoot->IsRoot())
								{
									mRoot = potentialNewRoot;
								}
								potentialNewRoot = parent->RotateRight();
								if (potentialNewRoot->IsRoot())
								{
									mRoot = potentialNewRoot;
								}
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
								potentialNewRoot = parent->RotateLeft();
								if (potentialNewRoot->IsRoot())
								{
									mRoot = potentialNewRoot;
								}
							}
							//Right-Left Case (Only the sibling's left child is red)
							else
							{
								sibling->mLeft->mColor = parent->mColor;
								potentialNewRoot = sibling->RotateRight();
								if (potentialNewRoot->IsRoot())
								{
									mRoot = potentialNewRoot;
								}
								potentialNewRoot = parent->RotateLeft();
								if (potentialNewRoot->IsRoot())
								{
									mRoot = potentialNewRoot;
								}
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
							potentialNewRoot = parent->RotateRight();
						}
						else
						{
							potentialNewRoot = parent->RotateLeft();
						}
						if (potentialNewRoot->IsRoot())
						{
							mRoot = potentialNewRoot;
						}
						sibling->mColor = Color::Black;
						parent->mColor = Color::Red;
					}
				}
				if (mRoot)
				{
					mRoot->mColor = Color::Black;
				}
			}

			it.mOwner = nullptr;						//The returend iterator will be valid, but it has been orphaned from the list.
			it.mNode->mParent = nullptr;				//Any other iterators pointing to the node to extract will be invalidated.
			it.mNode->mLeft = nullptr;
			it.mNode->mRight = nullptr;
		}
		return Iterator(it.mOwner, it.mNode);
	}

#if defined(UNIT_TEST)
	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::VerifyRedBlackTree() const
	{
		size_t treeBlackHeight = FindBlackHeight();

		size_t currentBlackHeight = 0;

		return VerifyNode(mRoot, treeBlackHeight, currentBlackHeight);
	}

	template <typename TreeTraits>
	inline bool RedBlackTree<TreeTraits>::VerifySize() const
	{
		return mSize == TreeSize(mRoot);
	}

	template <typename TreeTraits>
	inline size_t RedBlackTree<TreeTraits>::TreeSize(RedBlackNode* subtreeRoot) const
	{
		if (subtreeRoot == nullptr)
		{
			return 0;
		}

		return 1 + TreeSize(subtreeRoot->mLeft) + TreeSize(subtreeRoot->mRight);
	}


	template <typename TreeTraits>
	inline size_t RedBlackTree<TreeTraits>::FindBlackHeight() const
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
	inline bool RedBlackTree<TreeTraits>::VerifyNode(RedBlackTree<TreeTraits>::RedBlackNode* node, size_t const& treeBlackHeight, size_t& currentBlackHeight) const
	{
		if (node)
		{
			//Increase current black height if necessary
			if (node->mColor == Color::Black)
			{
				currentBlackHeight++;
			}

			//If this node is less than it's left child, the tree is invalid.
			if (node->mLeft && keyCompare(TreeTraits::ExtractKey(node->mKeyAndValue), TreeTraits::ExtractKey(node->mLeft->mKeyAndValue)))
			{
				return false;
			}
			//If this node's right child is less than this node, the tree is invalid.
			if (node->mRight && keyCompare(TreeTraits::ExtractKey(node->mRight->mKeyAndValue), TreeTraits::ExtractKey(node->mKeyAndValue)))
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