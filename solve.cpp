
#include "trie.h"

#include <algorithm>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

trie *dictionary = new trie();
std::string letters, s;
std::vector<std::string> words;
std::unordered_set<char> set_letters;
std::unordered_map<std::string, std::vector<int>> word_paths;
std::vector<std::vector<int>> adj{{1, 4, 5},
                                  {0, 2, 4, 5, 6},
                                  {1, 3, 5, 6, 7},
                                  {2, 6, 7},
                                  {0, 1, 5, 8, 9},
                                  {0, 1, 2, 4, 6, 8, 9, 10},
                                  {1, 2, 3, 5, 7, 9, 10, 11},
                                  {2, 3, 6, 10, 11},
                                  {4, 5, 9, 12, 13},
                                  {4, 5, 6, 8, 10, 12, 13, 14},
                                  {5, 6, 7, 9, 11, 13, 14, 15},
                                  {6, 7, 10, 14, 15},
                                  {8, 9, 13},
                                  {8, 9, 10, 12, 14},
                                  {9, 10, 11, 13, 15},
                                  {10, 11, 14}};

void dfs(int cur_sqr, trie_node *cur_node,
         std::unordered_set<int> visited = std::unordered_set<int>(),
         std::vector<int> path = std::vector<int>(), std::string word = "") {
  if (cur_node == nullptr)
    return;
  word.push_back(letters[cur_sqr]);
  visited.insert(cur_sqr);
  path.push_back(cur_sqr);
  if (cur_node->flag && !word_paths.count(word)) {
    word_paths[word] = path;
    words.push_back(word);
  }
  for (int next : adj[cur_sqr]) {
    if (!visited.count(next)) {
      dfs(next, cur_node->children[letters[next] - 'a'], visited, path, word);
    }
  }
}

int main(int argc, char **argv) {
  std::ifstream in{"full_dictionary.txt"};

  assert(argc > 1 && "No letters specified");
  letters = argv[1];
  assert(letters.size() == 16 && "Wrong number of characters");
  set_letters = std::unordered_set<char>(letters.begin(), letters.end());

  while (in >> s) {
    if (s.size() < 2 || s.size() > 16)
      continue;
    bool bad = false;
    for (char c : s) {
      if (!set_letters.count(c)) {
        bad = true;
        break;
      }
    }
    if (!bad)
      dictionary->insert(s);
  }

  for (int start = 0; start < 16; ++start)
    dfs(start, dictionary->root->children[letters[start] - 'a']);

  std::sort(words.begin(), words.end(),
            [](const std::string &a, const std::string &b) {
              return a.size() > b.size();
            });
  for (const auto &word : words) {
    for (const auto &y : word_paths[word]) {
      std::cout << y << " ";
    }
    std::cout << std::endl;
  }
}
