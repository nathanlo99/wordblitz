
#ifndef TRIE_H
#define TRIE_H

#include <cassert>
#include <iostream>
#include <string>

#define NUM_LETTERS 26

struct trie_node {
  bool flag;
  trie_node *parent, *children[NUM_LETTERS];

  trie_node(trie_node *parent = nullptr) : parent{parent} {
    for (int i = 0; i < NUM_LETTERS; ++i)
      children[i] = nullptr;
    flag = false;
  }

  void destroy() {
    for (int i = 0; i < NUM_LETTERS; ++i)
      free(children[i]);
  }

  void traverse(std::string s) {
    if (flag)
      std::cout << s << std::endl;
    for (int i = 0; i < NUM_LETTERS; ++i) {
      if (children[i])
        children[i]->traverse(s + std::string(1, 'a' + i));
    }
  }
};

struct trie {
  trie_node *root;

  trie() { root = new trie_node(); }
  ~trie() { root->destroy(); }

  void insert(std::string s) {
    trie_node *cur_node = root;

    for (char c : s) {
      if (cur_node->children[c - 'a'] == nullptr) {
        cur_node->children[c - 'a'] = new trie_node(cur_node);
      }
      cur_node = cur_node->children[c - 'a'];
    }
    cur_node->flag = true;
  }

  void traverse() { root->traverse(""); }
};

#endif /* end of include guard: TRIE_H */
