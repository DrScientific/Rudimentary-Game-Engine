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

		using KeyType = typename TreeTraits::KeyType;
		using ValueType = typename TreeTraits::ValueType;
		using KeyValueType = typename TreeTraits::KeyValueType;

		using KeyValueCompare = typename TreeTraits::KeyValueCompare;
		using KeyCompare = typename TreeTraits::KeyCompare;

		using Iterator = ConditionalType<AreSameClass<KeyType, KeyValueType>, TreeConstIterator, TreeIterator>;
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
			explicit RedBlackNode() = default;
			explicit RedBlackNode(KeyValueType const& keyAndValue, RedBlackNode* parent = nullptr, RedBlackNode* left = nullptr, RedBlackNode* right = nullptr);
			explicit RedBlackNode(RedBlackNode const& other);
			explicit RedBlackNode(RedBlackNode && other);
			explicit RedBlackNode(RedBlackNode* parent, RedBlackNode* left, RedBlackNode* right, RedBlackNode const& other);

			bool operator==(RedBlackNode const& other) const;

			bool operator!=(RedBlackNode const& other) const;

			/// <summary>
			/// Returns true if this node has no parent and is thus the root of its tree. 
			/// </summary>
			/// <returns>Whether the node has a parent.</returns>
			bool IsRoot() const;

			/// <summary>
			/// Returns true if this node is the left child of its parent.
			/// </summary>
			/// <returns>Whether the node is the left child of its parent.</returns>
			bool IsLeftChild() const;

			/// <summary>
			/// Returns true if this node is the right child of its parent.
			/// </summary>
			/// <returns>Whether the node is the right child of its parent.</returns>
			bool IsRightChild() const;

			/// <summary>
			/// Returns true if either of the nodes children are red.
			/// </summary>
			/// <returns>Whether either of the node's children are red.</returns>
			bool HasRedChild() const;
			
			/// <summary>
			/// Returns true if the sibling of this node is red.
			/// </summary>
			/// <returns>Whether this node has a red sibling.</returns>
			bool HasRedSibling() const;

			/// <summary>
			/// Returns the sibling of this node.
			/// </summary>
			/// <returns>The sibling of this node.</returns>
			RedBlackNode* GetSibling() const;

			/// <summary>
			/// 
			/// </summary>
			/// <param name="subtreeRoot"></param>
			/// <param name="key"></param>
			/// <returns></returns>
			RedBlackNode* Search(KeyType const& key) const;

			/// <summary>
			/// Returns the first element below the node with a key not less than the provided key.
			/// </summary>
			/// <param name="key">The key to compare.</param>
			/// <returns>The first element below the node with a key not less than the provided key.</returns>
			RedBlackNode* LowerBound(KeyType const& key) const;

			/// <summary>
			/// Returns the first element below the node with a key greater than the provided key.
			/// </summary>
			/// <param name="key">The key to compare.</param>
			/// <returns>The first element below the node with a key greater than the provided key.</returns>
			RedBlackNode* UpperBound(KeyType const& key) const;

			/// <summary>
			/// Returns a range of pointers spanning from the first element found that is not less than the key to the first element found that is not greater than the key.
			/// </summary>
			/// <param name="key">The key to compare.</param>
			/// <returns>A range of pointers spanning from the first element found that is not less than the key to the first element found that is not greater than the key.</returns>
			std::pair<RedBlackNode*, RedBlackNode*> EqualRange(KeyType const& key) const;

			/// <summary>
			/// Climbs the parent chain until a node with no parent is found. Returns that node.
			/// </summary>
			/// <returns>The root of the tree the node is contained in.</returns>
			RedBlackNode* FindRoot();

			/// <summary>
			/// Climbs the parent chain until a node with no parent is found. Returns that node.
			/// </summary>
			/// <returns>The root of the tree the node is contained in.</returns>
			RedBlackNode const* FindRoot() const;

			/// <summary>
			/// Climbs down the left child chain until a node with no left child is found. Returns that node.
			/// </summary>
			/// <returns>The smallest node below this node.</returns>
			RedBlackNode* FindMin();

			/// <summary>
			/// Climbs down the left child chain until a node with no left child is found. Returns that node.
			/// </summary>
			/// <returns>The smallest node below this node.</returns>
			RedBlackNode const* FindMin() const;

			/// <summary>
			/// Climbs down the right child chain until a node with no right child is found. Returns that node.
			/// </summary>
			/// <returns>The largest node below this node.</returns>
			RedBlackNode* FindMax();

			/// <summary>
			/// Climbs down the right child chain until a node with no right child is found. Returns that node.
			/// </summary>
			/// <returns>The largest node below this node.</returns>
			RedBlackNode const* FindMax() const;

			/// <summary>
			/// Rotates a node to the right. (All rotations occur in a downward direction.)
			/// The node's left child will become its parent.
			/// The node's new left child will be its old left child's right child.
			/// NOTE: This DOES NOT update the root of any tree. After a node is rotated it the owning tree should check if it needs to update it's root.
			/// </summary>
			/// <returns>The new parent of the rotated node.</returns>
			RedBlackNode* RotateRight();

			/// <summary>
			/// Rotates a node to the left. (All rotations occur in a downward direction.)
			/// The node's right child will become its parent.
			/// The node's new right child will be its old right child's left child.
			/// NOTE: This DOES NOT update the root of any tree. After a node is rotated it the owning tree should check if it needs to update it's root.
			/// </summary>
			/// <param name="node">The node to rotate to the left.</param>
			/// <returns>The new parent of the rotated node.</returns>
			RedBlackNode* RotateLeft();

			/// <summary>
			/// Deletes this node and all nodes below this node and points parent node to nullptr.
			/// </summary>
			void DeleteSubtree();

			/// <summary>
			/// Creates a copy of the subtree the function is called on.
			/// The returned pointer must be captured or memory will leak.
			/// The newly created subtree is dynamically allocated and needs to have it's memory managed by something.
			/// When pointing a node to the new subtree do not forget to fix up its parent pointer.
			/// </summary>
			/// <returns>A pointer to the newly created subtree.</returns>
			RedBlackNode* CreateSubtreeCopy();

		private:
			/// <summary>
			/// Helper function which recursively locates the smallest node greater than or equal to the key.
			/// </summary>
			/// <param name="key">The key to compare.</param>
			/// <param name="smallestNodeGreaterOrEqualToKey">A reference to a pointer to the smallest node found so far that is greater than or equal to the key.</param>
			void LowerBoundRecursive(KeyType const& key, RedBlackNode*& smallestNodeGreaterOrEqualToKey) const;

			/// <summary>
			/// Helper function which recursively locates the smallest node greater than the key.
			/// </summary>
			/// <param name="key">The key to compare.</param>
			/// <param name="smallestNodeGreaterOrEqualToKey">A reference to a pointer to the smallest node found so far that is greater than the key.</param>
			void UpperBoundRecursive(KeyType const& key, RedBlackNode*& smallestNodeGreaterThanKey) const;

			/// <summary>
			/// Deletes this node and all nodes below this node. Does not point the parent node to nullptr.
			/// This function exists because it is really only neccessary to do pointer fix up with the subtree root, not any of the nodes deleted under it.
			/// </summary>
			void DeleteSubtreeRecursive();

			/// <summary>
			/// Recursive helper function used to copy a subtree.
			/// </summary>
			/// <param name="parent">A pointer to the parent of the node that is currently being constructed.</param>
			/// <param name="otherSubtreeRootToCopy">A pointer to the current node we are copying from the other subtree.</param>
			/// <returns>A pointer to the newly constructed node or the nullptr if the pointer to the current node we are copying is the nullptr.</returns>
			RedBlackNode* CreateSubtreeCopyRecursive(RedBlackNode* parent, RedBlackNode* otherSubtreeRootToCopy);
		public:

			RedBlackNode* mParent = nullptr;
			RedBlackNode* mLeft = nullptr;
			RedBlackNode* mRight = nullptr;
			KeyValueType mKeyAndValue;
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

			KeyValueType& operator*();

		private:

			explicit TreeIterator(RedBlackTree const& owner, RedBlackNode* node = nullptr);
			explicit TreeIterator(RedBlackTree const* owner, RedBlackNode* node = nullptr);
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

			TreeConstIterator(TreeIterator const& other);

			TreeConstIterator& operator++();

			TreeConstIterator operator++(int);

			TreeConstIterator& operator--();

			TreeConstIterator operator--(int);

			bool operator==(TreeConstIterator const& other) const;

			bool operator!=(TreeConstIterator const& other) const;

			KeyValueType& operator*();

		private:
			explicit TreeConstIterator(RedBlackTree const& owner, RedBlackNode* node = nullptr);
			explicit TreeConstIterator(RedBlackTree const* owner, RedBlackNode* node = nullptr);
			const RedBlackTree* mOwner = nullptr;
			RedBlackNode* mNode = nullptr;

			friend class TreeIterator;
			friend class RedBlackTree<TreeTraits>;
		};
	public:
		RedBlackTree() = default;
		
		/// <summary>
		/// Initializer list constructor of the tree.
		/// </summary>
		/// <param name="iList">The initializer list to construct from.</param>
		RedBlackTree(std::initializer_list<KeyValueType> iList);
		
		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other">The tree we are copy constructing from.</param>
		RedBlackTree(RedBlackTree const& other);
		
		/// <summary>
		/// Move constructor
		/// </summary>
		/// <param name="other">The tree we are move constructing from.</param>
		RedBlackTree(RedBlackTree && other);
		
		/// <summary>
		/// Assignment operator
		/// </summary>
		/// <param name="other">The tree we are copy constructing from.</param>
		/// <returns>A reference to this tree.</returns>
		RedBlackTree & operator=(RedBlackTree const& other);

		/// <summary>
		/// Move assignment operator.
		/// </summary>
		/// <param name="other">The tree we are moving into this tree.</param>
		/// <returns></returns>
		RedBlackTree & operator=(RedBlackTree && other);
		
		/// <summary>
		/// Destructor. Deletes all nodes contained in the tree.
		/// </summary>
		virtual ~RedBlackTree();

		/// <summary>
		/// Compares all of the node values in the tree in order. If they are all equal, returns true.
		/// </summary>
		/// <param name="other">The tree to compare with.</param>
		/// <returns>Whether the trees are equal.</returns>
		bool operator==(RedBlackTree const& other) const;

		/// <summary>
		/// Compares all of the node values in the tree in order. If any of them are all not equal, returns true.
		/// </summary>
		/// <param name="other">The tree to compare with.</param>
		/// <returns>Whether the trees are not equal.</returns>
		bool operator!=(RedBlackTree const& other) const;

		/// <summary>
		/// Returns an iterator to the first element in the tree.
		/// </summary>
		/// <returns>An iterator to the first element in the tree.</returns>
		Iterator begin();

		/// <summary>
		/// Returns a const iterator to the first element in the tree.
		/// </summary>
		/// <returns>A const iterator to the first element in the tree.</returns>
		ConstIterator begin() const;

		/// <summary>
		/// Returns an iterator to the element past the last element of the tree.
		/// </summary>
		/// <returns>An iterator to the element past the last element of the tree</returns>
		Iterator end();

		/// <summary>
		/// Returns a const iterator to the element past the last element of the tree.
		/// </summary>
		/// <returns>A const iterator to the element past the last element of the tree</returns>
		ConstIterator end() const;

		/// <summary>
		/// Returns a const iterator to the first element in the tree.
		/// </summary>
		/// <returns>A const iterator to the first element in the tree.</returns>
		ConstIterator cbegin() const;

		/// <summary>
		/// Returns a const iterator to the element past the last element of the tree.
		/// </summary>
		/// <returns>A const iterator to the element past the last element of the tree</returns>
		ConstIterator cend() const;

		/// <summary>
		/// Attempts to insert a node containing a new KeyValueType object equal to the passed in object into the tree.
		/// If a node with a key equal to the key of the passed in KeyValueType object exists a new value will not be inserted unless this is bIsMulti is true.
		/// If a value is inserted the iterator in the return value will point to the newly inserted node and the boolean will be true.
		/// If a value is not inserted the iterator in the return value will point to the existing node that prevented the insertion and the boolean will be false.
		/// </summary>
		/// <param name="keyAndValue">The KeyValueType object to attempt to insert into the tree.</param>
		/// <returns>A pair where the first value is an iterator to either the inserted element or the found element, and the second value is whether the insertion was successful.</returns>
		std::pair<Iterator, bool> Insert(KeyValueType const& keyAndValue);
		
		/// <summary>
		/// Removes all nodes with a key of the given value from the tree, freeing their memory and invalidating any iterators pointing to them.
		/// </summary>
		/// <param name="key">Key to remove.</param>
		void Remove(KeyType const& key);

		/// <summary>
		/// Removes the provided iterator from the tree, freeing the memory of it's node and invalidating the iterator.
		/// </summary>
		/// <param name="key">Iterator to remove from the tree.</param>
		void Remove(ConstIterator elementToRemove);

		/// <summary>
		/// Returns an iterator to the first element in the tree with a key value eqaul to the provided key. If no node equal to the provided key is found returns the end iterator.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>An iterator to the first element in the tree with a key value eqaul to the provided key. If no node equal to the provided key is found returns the end iterator.</returns>
		Iterator Find(KeyType const& key);
		
		/// <summary>
		/// Returns a const iterator to the first element in the tree with a key value eqaul to the provided key. If no node equal to the provided key is found returns the end const iterator.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>A const iterator to the first element in the tree with a key value eqaul to the provided key. If no node equal to the provided key is found returns the end const iterator.</returns>
		ConstIterator Find(KeyType const& key) const;

		/// <summary>
		/// Returns true if an element in the tree has a key value eqaul to the provided key.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>Whether an element in the tree has a key value eqaul to the provided key.</returns>
		bool Contains(KeyType const& key) const;

		/// <summary>
		/// Returns the first element in the tree with a key not less than the provided key.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>The first element in the tree with a key not less than the provided key.</returns>
		Iterator LowerBound(KeyType const& key);

		/// <summary>
		/// Returns the first element in the tree with a key not less than the provided key.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>The first element in the tree with a key not less than the provided key.</returns>
		ConstIterator LowerBound(KeyType const& key) const;

		/// <summary>
		/// Returns the first element in the tree with a key greater than the provided key.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>The first element in the tree with a key greater than the provided key</returns>
		Iterator UpperBound(KeyType const& key);

		/// <summary>
		/// Returns the first element in the tree with a key greater than the provided key.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>The first element in the tree with a key greater than the provided key</returns>
		ConstIterator UpperBound(KeyType const& key) const;

		/// <summary>
		/// Returns a range of iterators spanning from the first element found that is not less than the key to the first element found that is not greater than the key.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>A range of iterators spanning from the first element found that is not less than the key to the first element found that is not greater than the key.</returns>
		std::pair<Iterator, Iterator> EqualRange(KeyType const& key);

		/// <summary>
		/// Returns a range of iterators spanning from the first element found that is not less than the key to the first element found that is not greater than the key.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>A range of iterators spanning from the first element found that is not less than the key to the first element found that is not greater than the key.</returns>
		std::pair <ConstIterator, ConstIterator> EqualRange(KeyType const& key) const;
		
		/// <summary>
		/// Returns the number of elements in the tree that have a key equal to the provided key.
		/// </summary>
		/// <param name="key">The key to compare.</param>
		/// <returns>The number of elements in the tree that have a key equal to the provided key.</returns>
		size_t Count(KeyType const& key) const;

		/// <summary>
		/// Exchanges the contents of this tree and the provided tree.
		/// </summary>
		/// <param name="other">The tree to exchange values with.</param>
		void Swap(RedBlackTree& other);
		
		/// <summary>
		/// Returns the number of elements in the tree.
		/// </summary>
		/// <returns>The number of elements in the tree.</returns>
		size_t Size() const;
		
		/// <summary>
		/// Returns whether the tree is empty.
		/// </summary>
		/// <returns>Whether the tree is empty.</returns>
		bool IsEmpty() const;

		/// <summary>
		/// Deletes all nodes in the tree, sets root to the nullptr, and size to 0.
		/// </summary>
		void Clear();

		/// <summary>
		/// Returns the KeyCompare function object used by the tree.
		/// </summary>
		/// <returns>The KeyCompare function object used by the tree</returns>
		KeyCompare const& GetKeyComparison() const;
	protected:
		
		/// <summary>
		/// Attempts to insert a node containing a new KeyValueType object equal to the passed in object into the subtree.
		/// If a node with a key equal to the key of the passed in KeyValueType object exists a new value will not be inserted unless this is bIsMulti is true.
		/// If a value is inserted the iterator in the return value will point to the newly inserted node and the boolean will be true.
		/// If a value is not inserted the iterator in the return value will point to the existing node that prevented the insertion and the boolean will be false.
		/// </summary>
		/// <param name="subtreeRoot">The subtree to perform the insertion on,</param>
		/// <param name="keyAndValue">The KeyValueType object to attempt to insert into the subtree.</param>
		/// <returns>A pair where the first value is an pointer to either the inserted element or the found element, and the second value is whether the insertion was successful.</returns>
		std::pair<RedBlackNode*, bool> Insert(RedBlackNode* subtreeRoot, KeyValueType const& keyAndValue);
		
		/// <summary>
		/// After a node is inserted the properties of the red black tree may be violated.
		/// This function repairs the red black tree after an insertion.
		/// </summary>
		/// <param name="node">The subtree to repair</param>
		void InsertFixUp(RedBlackNode* subtree);
		
		/// <summary>
		/// Removes a node from the tree and returns an iterator to the orphaned node.
		/// The node is not deleted and if something else does not take ownership of its memory it will be leaked.
		/// </summary>
		/// <param name="elementToExtract">A const iterator to the element to extract.</param>
		/// <returns>An iterator to the extracted node. This iterator is orphaned.</returns>
		Iterator Extract(ConstIterator elementToExtract);

		/// <summary>
		/// The root of the tree.
		/// </summary>
		RedBlackNode* mRoot = nullptr;

		/// <summary>
		/// Size of the tree tracked by incrementing when nodes are added and decrementing when nodes are removed.
		/// </summary>
		size_t mSize = 0;

		/// <summary>
		/// The KeyCompare function object used by the tree to compare the key values of its nodes.
		/// </summary>
		static inline const KeyCompare keyCompare;

		inline static const std::string attemptToIteratePastLastElementException = "Attempted to increment an iterator past end of the red black tree.\n";

		inline static const std::string attemptToIncrementOrphanedIteratorException = "Attempted to increment an iterator with no owning red black tree.\n";

		inline static const std::string attemptToDecrementOrphanedIteratorException = "Attempted to decrement an iterator with no owning red black tree.\n";

		inline static const std::string attemptToDecrementBeforeFirstElementException = "Attempted to decrement an iterator before the beginning of the red black tree.\n";

		inline static const std::string attemptToDerferenceEndIterator = "Attempted to dereference end iterator.\n";

#if defined(UNIT_TEST)
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool VerifyRedBlackTree() const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		bool VerifySize() const;
	private:
		size_t TreeSize(RedBlackNode* subTreeRoot) const;

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		size_t FindBlackHeight() const;
			
		/// <summary>
		/// 
		/// </summary>
		/// <param name="node"></param>
		/// <param name="treeBlackHeight"></param>
		/// <param name="currentBlackHeight"></param>
		/// <returns></returns>
		bool VerifyNode(RedBlackNode* node, size_t const& treeBlackHeight, size_t& currentBlackHeight) const;
#endif
	};
}

#include "RedBlackTree.inl"