#pragma once
#include <string>
#include <exception>
#include <initializer_list>
#include "TemplateLogic.h"

namespace FIEAGameEngine
{
	template <typename TreeTraits>
	class RedBlackTree
	{
	public:

		class TreeIterator;
		class TreeConstIterator;

		using ValueType = typename TreeTraits::ValueType;
		using KeyType = typename TreeTraits::KeyType;

		using ValueCompare = typename TreeTraits::ValueCompare;
		using KeyCompare = typename TreeTraits::KeyCompare;

		using Iterator = ConditionalType<AreSameClass<KeyType, ValueType>, TreeConstIterator, TreeIterator>;
		using ConstIterator = TreeConstIterator;

		static constexpr bool bIsMulti = TreeTraits::bIsMulti;
		
	private:
		enum class Color : unsigned char
		{
			Red,
			Black,
			DoubleBlack,
		};
	protected:
		struct RedBlackNode
		{
			explicit RedBlackNode(ValueType const& key, RedBlackNode* parent = nullptr, RedBlackNode* left = nullptr, RedBlackNode* right = nullptr);
			explicit RedBlackNode(RedBlackNode const& other);
			explicit RedBlackNode(RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right, RedBlackNode const& other);
			
			bool operator==(RedBlackNode const& other) const;

			bool operator!=(RedBlackNode const& other) const;

			RedBlackNode* GetSibling() const;
			bool IsLeftChild() const;
			bool IsRightChild() const;
			bool HasRedChild() const;
			bool HasRedSibling() const;

			RedBlackNode* mParent = nullptr;
			RedBlackNode* mLeft = nullptr;
			RedBlackNode* mRight = nullptr;
			ValueType mValue;
			Color mColor = Color::Red;
		};
	public:
		class TreeIterator
		{
		public:

			TreeIterator(TreeIterator const&) = default;

			TreeIterator(TreeIterator &&) = default;

			TreeIterator& operator= (TreeIterator const&) = default;

			TreeIterator& operator= (TreeIterator&&) = default;

			~TreeIterator() = default;

			TreeIterator& operator++();

			TreeIterator operator++(int);

			TreeIterator& operator--();

			TreeIterator operator--(int);

			bool operator==(TreeIterator const& other) const;

			bool operator!=(TreeIterator const& other) const;

			ValueType& operator*();

		private:

			explicit TreeIterator(RedBlackTree const& owner, RedBlackNode* node = nullptr);
			const RedBlackTree* mOwner = nullptr;
			RedBlackNode* mNode = nullptr;

			friend class TreeConstIterator;
			friend class RedBlackTree<TreeTraits>;
		};

	public:
		class TreeConstIterator
		{
		public:
			TreeConstIterator(TreeConstIterator const&) = default;

			TreeConstIterator(TreeConstIterator&&) = default;

			TreeConstIterator& operator= (TreeConstIterator const&) = default;

			TreeConstIterator& operator= (TreeConstIterator&&) = default;

			~TreeConstIterator() = default;

			TreeConstIterator& operator++();

			TreeConstIterator operator++(int);

			TreeConstIterator& operator--();

			TreeConstIterator operator--(int);

			bool operator==(TreeConstIterator const& other) const;

			bool operator!=(TreeConstIterator const& other) const;

			ValueType& operator*();

		private:
			explicit TreeConstIterator(RedBlackTree const& owner, RedBlackNode* node = nullptr);
			const RedBlackTree* mOwner = nullptr;
			RedBlackNode* mNode = nullptr;

			friend class TreeIterator;
			friend class RedBlackTree<TreeTraits>;
		};
	public:
		RedBlackTree() = default;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="iList"></param>
		RedBlackTree(std::initializer_list<ValueType> iList);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		RedBlackTree(RedBlackTree const& other);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		RedBlackTree(RedBlackTree && other);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		RedBlackTree & operator=(RedBlackTree const& other);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		RedBlackTree & operator=(RedBlackTree && other);
		
		/// <summary>
		/// 
		/// </summary>
		virtual ~RedBlackTree();

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator==(RedBlackTree const& other) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool operator!=(RedBlackTree const& other) const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Iterator begin();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstIterator begin() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Iterator end();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstIterator end() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		ConstIterator cend() const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair<Iterator, bool> Insert(ValueType const& key);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		Iterator Find(KeyType const& key);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		ConstIterator Find(KeyType const& key) const;

		/// <summary>
		/// TODO: Test
		/// https://en.cppreference.com/w/cpp/container/set/lower_bound
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		Iterator LowerBound(KeyType const& key);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		ConstIterator LowerBound(KeyType const& key) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		Iterator UpperBound(KeyType const& key);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		ConstIterator UpperBound(KeyType const& key) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair<Iterator, Iterator> EqualRange(KeyType const& key);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair <ConstIterator, ConstIterator> EqualRange(KeyType const& key) const;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		void Remove(KeyType const& key);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="other"></param>
		void Swap(RedBlackTree& other);
		
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		size_t Size() const;
		
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool IsEmpty() const;

		/// <summary>
		/// 
		/// </summary>
		void Clear();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		KeyCompare GetKeyComparison() const;
	protected:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <param name="key"></param>
		/// <returns></returns>
		RedBlackNode* Search(RedBlackNode* subtreeRoot, KeyType const& key) const;

		RedBlackNode* LowerBound(RedBlackNode* subtreeRoot, KeyType const& key) const;

		RedBlackNode* UpperBound(RedBlackNode* subtreeRoot, KeyType const& key) const;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair<RedBlackNode*, bool> Insert(RedBlackNode* subtreeRoot, ValueType const& key);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="node"></param>
		void InsertFixUp(RedBlackNode* node);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <param name="key"></param>
		void Remove(RedBlackNode* subtreeRoot, KeyType const& key);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <returns></returns>
		size_t Size(RedBlackNode* subtreeRoot) const;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <returns></returns>
		RedBlackNode* FindMin(RedBlackNode* subtreeRoot) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <returns></returns>
		RedBlackNode* FindMax(RedBlackNode* subtreeRoot) const;

		/// <summary>
		/// Rotates a node to the right. (All rotations occur in a downward direction.)
		/// The node's left child will become its parent.
		/// The node's new left child will be its old left child's right child.
		/// </summary>
		/// <param name="node">The node to rotate to the right.</param>
		/// <returns></returns>
		RedBlackNode* RotateRight(RedBlackNode* node);

		/// <summary>
		/// Rotates a node to the left. (All rotations occur in a downward direction.)
		/// The node's right child will become its parent.
		/// The node's new right child will be its old right child's left child.
		/// </summary>
		/// <param name="node">The node to rotate to the left.</param>
		/// <returns></returns>
		RedBlackNode* RotateLeft(RedBlackNode* node);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <param name="otherSubtreeRoot"></param>
		/// <returns></returns>
		RedBlackNode* CopySubtree(RedBlackNode* subtreeRoot, RedBlackNode* otherSubtreeRoot);
		void DeleteSubtree(RedBlackNode* node);

		/// <summary>
		/// 
		/// </summary>
		RedBlackNode* mRoot = nullptr;

		/// <summary>
		/// 
		/// </summary>
		static inline const KeyCompare keyCompare;

		inline static const std::string attemptToIteratarePastLastElementException = "Attempted to increment an iterator past end of the red black tree.\n";

		inline static const std::string attemptToIteratareBeforeFirstElementException = "Attempted to decrement an iterator past the beginning of the red black tree.\n";

		inline static const std::string ownerIsNullException = "Iterator owner is null and cannot be dereferenced.\n";

#if defined(UNIT_TEST)
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool VerifyRedBlackTree();
	private:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		int FindBlackHeight();
			
		/// <summary>
		/// 
		/// </summary>
		/// <param name="node"></param>
		/// <param name="treeBlackHeight"></param>
		/// <param name="currentBlackHeight"></param>
		/// <returns></returns>
		bool VerifyNode(RedBlackNode* node, int const& treeBlackHeight, int& currentBlackHeight);
#endif
	};
}

#include "RedBlackTree.inl"