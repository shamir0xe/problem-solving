package "data-scturctures"

import "fmt"

type ITrie[T comparable] interface {
	Insert(sequence []T, value any)
	PrefixKeys(sequence []T) ([][]T, error)

	// Deletes the sequence if found,
	// asPrefix can be set to true in order to delete the whole subtree
	Delete(sequence []T, asPrefix bool) error
}

type Trie[T comparable] struct {
	value    any
	children map[T]*Trie[T]
	par      *Trie[T]
	key      T
}

// Validate the interface imp.
var _ ITrie[rune] = (*Trie[rune])(nil)

func NewTrie[T comparable]() *Trie[T] {
	var root *Trie[T] = &Trie[T]{
		value:    nil,
		children: make(map[T]*Trie[T]),
	}
	return root
}

func (node *Trie[T]) insert(sequence []T, index int, value any) {
	if index >= len(sequence) {
		node.value = value
	} else {
		var next *Trie[T]
		if _, ok := node.children[sequence[index]]; !ok {
			var child *Trie[T] = NewTrie[T]()
			child.par = node
			child.key = sequence[index]
			node.children[sequence[index]] = child
		}

		next = node.children[sequence[index]]
		next.insert(sequence, index+1, value)
	}
}

func (node *Trie[T]) Insert(sequence []T, value any) {
	node.insert(sequence, 0, value)
}

func (node *Trie[T]) pack() []T {
	if node.par == nil {
		return []T{}
	}
	res := node.par.pack()
	res = append(res, node.key)
	return res
}

func (node *Trie[T]) aggregateSubtree() [][]T {
	var res [][]T
	if node.value != nil {
		res = append(res, node.pack())
	}
	for _, u := range node.children {
		res = append(res, u.aggregateSubtree()...)
	}
	return res
}

func (node *Trie[T]) prefixKeys(sequence []T, index int) ([][]T, error) {
	if index >= len(sequence) {
		return node.aggregateSubtree(), nil
	}
	var next *Trie[T]
	if nx, ok := node.children[sequence[index]]; ok {
		next = nx
	} else {
		// We don't have this prefix
		return [][]T{}, fmt.Errorf("Prefix not found")
	}
	return next.prefixKeys(sequence, index+1)
}

func (node *Trie[T]) PrefixKeys(sequence []T) ([][]T, error) {
	return node.prefixKeys(sequence, 0)
}

func (node *Trie[T]) delete(sequence []T, index int, asPrefix bool) error {
	if index >= len(sequence) {
		node.value = nil
		// Check wether all the subtree should be deleted
		if asPrefix {
			// GC will cleanse this
			node.children = make(map[T]*Trie[T])
		}
	} else {
		var next *Trie[T]
		if nx, ok := node.children[sequence[index]]; ok {
			next = nx
		} else {
			// We don't have this prefix
			return fmt.Errorf("Prefix not found")
		}
		return next.delete(sequence, index+1, asPrefix)
	}
	return nil
}

func (node *Trie[T]) Delete(sequence []T, asPrefix bool) error {
	return node.delete(sequence, 0, asPrefix)
}
