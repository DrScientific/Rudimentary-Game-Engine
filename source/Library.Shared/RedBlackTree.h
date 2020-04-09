#pragma once
#include <string>
#include <exception>
#include <initializer_list>

namespace FIEAGameEngine
{
	template <typename T, typename LessThanFunctor = std::less<T>>
	class RedBlackTree
	{
	private:
		enum class Color : unsigned char
		{
			Red,
			Black,
			DoubleBlack,
		};

		struct Node final
		{
			Node(T const& data, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr);
			Node* GetSibling() const;
			bool IsLeftChild() const;
			bool IsRightChild() const;
			bool HasRedChild() const;
			bool HasRedSibling() const;
			bool HasInnerRedChild() const;
			bool HasOuterRedChild() const;
			Node* GetInnerRedChild() const;
			Node* GetOuterRedChild() const;


			Node* mParent = nullptr;
			Node* mLeft = nullptr;
			Node* mRight = nullptr;
			T const mData;
			Color mColor = Color::Red;
		};
	public:
		class Iterator
		{
		public:

			Iterator() = default;

			Iterator(Iterator const&) = default;

			Iterator(Iterator &&) = default;

			Iterator& operator= (const Iterator&) = default;

			Iterator& operator= (Iterator&&) = default;

			~Iterator() = default;

			Iterator& operator++();

			Iterator operator++(int);

			Iterator& operator--();

			Iterator operator--(int);

			bool operator==(Iterator const& rhs) const;

			bool operator!=(Iterator const& rhs) const;

			T const& operator*() const;

		private:

			Iterator(const RedBlackTree& owner, Node* node = nullptr);
			const RedBlackTree* mOwner = nullptr;
			Node* mNode = nullptr;

			friend class const_Iterator;
			friend class RedBlackTree<T>;
		};
		
	public:
		//const_Iterator and Iterator are the same in a red black tree. Once data is put in it should not be altered.
		using const_Iterator = Iterator;

		RedBlackTree() = default;
		RedBlackTree(std::initializer_list<T> iList);
		RedBlackTree(RedBlackTree const& other);
		RedBlackTree(RedBlackTree && other);
		RedBlackTree & operator=(RedBlackTree const& other);
		RedBlackTree & operator=(RedBlackTree && other);
		~RedBlackTree();

		Iterator begin();

		const_Iterator begin() const;

		Iterator end();

		const_Iterator end() const;

		const_Iterator cbegin() const;

		const_Iterator cend() const;

		std::pair<Iterator, bool> Insert(T const& data);
		Iterator Find(T const& data) const;
		void Remove(T const& data);
		size_t Size() const;
		bool IsEmpty() const;
		void Clear();

	private:

		std::pair<Node*, bool> Insert(Node* subtreeRoot, T const& data);
		void Remove(Node* subtreeRoot, T const& data);
		size_t Size(Node* subtreeRoot) const;
		Node* Search(Node* subtreeRoot, T const& data) const;
		Node* FindMin(Node* subtreeRoot) const;
		Node* FindMax(Node* subtreeRoot) const;
		void InsertFixUp(Node* node);
		void RemoveFixUp(std::pair<Node*, Node*> childAndParent);
		void PushUpBlackLevel(Node* node, Node* parent);

		/// <summary>
		/// Rotates a node to the right. (All rotations occur in a downward direction.)
		/// The node's left child will become its parent.
		/// The node's new left child will be its old left child's right child.
		/// </summary>
		/// <param name="node">The node to rotate to the right.</param>
		/// <returns></returns>
		Node* RotateRight(Node* node);

		/// <summary>
		/// Rotates a node to the left. (All rotations occur in a downward direction.)
		/// The node's right child will become its parent.
		/// The node's new right child will be its old right child's left child.
		/// </summary>
		/// <param name="node">The node to rotate to the left.</param>
		/// <returns></returns>
		Node* RotateLeft(Node* node);

		void DeleteSubtree(Node* node);

		Node* mRoot = nullptr;
		static inline const LessThanFunctor lessThan;

		inline static const std::string attemptToIteratarePastLastElementException = "Attempted to increment an iterator past end of the red black tree.\n";

		inline static const std::string attemptToIteratareBeforeFirstElementException = "Attempted to decrement an iterator past the beginning of the red black tree.\n";

		inline static const std::string ownerIsNullException = "Iterator owner is null and cannot be dereferenced.\n";

#if defined(UNIT_TEST)
		public:
			bool VerifyRedBlackTree();
		private:
			int FindBlackHeight();
			bool VerifyNode(Node* node, int const& treeBlackHeight, int& currentBlackHeight);
#endif
	};
	
}

#include "RedBlackTree.inl"