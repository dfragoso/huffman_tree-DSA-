#pragma once
#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <queue>          
#include <vector>         
#include <functional>
#include <math.h>

class huffman_tree {
public:
	struct Node {
		int frequency;
		char nodeChar;
		Node* leftChild;
		Node* rightChild;
	};
	struct compareFreq {
		bool operator()(Node const* lhs, Node const* rhs)const
		{
			return lhs->frequency > rhs->frequency;
		}
	};
	huffman_tree(const std::string &file_name);
	~huffman_tree();
	std::string get_character_code(char character) const;
	std::string encode(const std::string &file_name) const;
	std::string decode(const std::string &string_to_decode) const;

	Node* buildTree(std::vector<Node*> &treeNodes) const;
	void buildHuffmanTable(Node* root, std::string code, std::unordered_map<char, std::string > &table) const;
	bool isLeaf(Node* root) const;
	std::string getCharCode(char c) const;

	Node* root = new Node();
	std::unordered_map<char, std::string > theHuffmanCode;
};

#endif

