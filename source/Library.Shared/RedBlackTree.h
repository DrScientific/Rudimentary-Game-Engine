#pragma once
#include <string>
#include <exception>
#include <initializer_list>

namespace FIEAGameEngine
{
	template <typename TKey, typename LessThanFunctor = std::less<TKey>>
	class RedBlackTree
	{
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
			explicit RedBlackNode(TKey const& key, RedBlackNode* parent = nullptr, RedBlackNode* left = nullptr, RedBlackNode* right = nullptr);
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
			TKey const mKey;
			Color mColor = Color::Red;
		};
	public:
		class Iterator
		{
		public:

			Iterator(Iterator const&) = default;

			Iterator(Iterator &&) = default;

			Iterator& operator= (Iterator const&) = default;

			Iterator& operator= (Iterator&&) = default;

			~Iterator() = default;

			Iterator& operator++();

			Iterator operator++(int);

			Iterator& operator--();

			Iterator operator--(int);

			bool operator==(Iterator const& other) const;

			bool operator!=(Iterator const& other) const;

			TKey const& operator*() const;

		private:

			explicit Iterator(RedBlackTree const& owner, RedBlackNode* node = nullptr);
			const RedBlackTree* mOwner = nullptr;
			RedBlackNode* mNode = nullptr;

			friend class const_Iterator;
			friend class RedBlackTree<TKey, LessThanFunctor>;
		};
		
	public:
		//const_Iterator and Iterator are the same in a red black tree. Once key is put in it should not be altered.
		using const_Iterator = Iterator;

		RedBlackTree() = default;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="iList"></param>
		RedBlackTree(std::initializer_list<TKey> iList);
		
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
		const_Iterator begin() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		Iterator end();

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const_Iterator end() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const_Iterator cbegin() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		const_Iterator cend() const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair<Iterator, bool> Insert(TKey const& key);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		Iterator Find(TKey const& key);
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		const_Iterator Find(TKey const& key) const;

		/// <summary>
		/// TODO: Test
		/// https://en.cppreference.com/w/cpp/container/set/lower_bound
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		Iterator LowerBound(TKey const& key);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		const_Iterator LowerBound(TKey const& key) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		Iterator UpperBound(TKey const& key);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		const_Iterator UpperBound(TKey const& key) const;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair<Iterator, Iterator> EqualRange(TKey const& key);

		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		std::pair <const_Iterator, const_Iterator> EqualRange(TKey const& key) const;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="key"></param>
		void Remove(TKey const& key);

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
		LessThanFunctor GetKeyComparison() const;
	protected:

		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <param name="key"></param>
		/// <returns></returns>
		RedBlackNode* Search(RedBlackNode* subtreeRoot, TKey const& key) const;

		RedBlackNode* LowerBound(RedBlackNode* subtreeRoot, TKey const& key) const;

		RedBlackNode* UpperBound(RedBlackNode* subtreeRoot, TKey const& key) const;
		
		/// <summary>
		/// 
		/// </summary>
		/// <param name="subtreeRoot"></param>
		/// <param name="key"></param>
		/// <returns></returns>
		template<typename NodeType> std::pair<NodeType*, bool> Insert(RedBlackNode* subtreeRoot, TKey const& key);
		
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
		void Remove(RedBlackNode* subtreeRoot, TKey const& key);
		
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
		template<typename NodeType> NodeType* CopySubtree(NodeType * subtreeRoot, NodeType * otherSubtreeRoot);
		void DeleteSubtree(RedBlackNode* node);

		/// <summary>
		/// 
		/// </summary>
		RedBlackNode* mRoot = nullptr;

		/// <summary>
		/// 
		/// </summary>
		static inline const LessThanFunctor lessThan;

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