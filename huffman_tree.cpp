#include "huffman_tree.h"

bool huffman_tree::isLeaf(Node* root) const {
	if (root->rightChild == nullptr && root->leftChild == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

huffman_tree::huffman_tree(const std::string &file_name) {	
	char superChar; 
	std::unordered_map<char, int> frequencies;
	std::vector<Node*> treeNodes;
	std::ifstream file (file_name);	
	if (file.is_open()) {
		while (true) {			
			file.get(superChar);
			if (file.eof()) {
				break;
			}
			if (frequencies.find(superChar) != frequencies.end()) {
				frequencies.at(superChar)++;
			}
			else {
				frequencies.emplace(superChar, 1);
				Node* temp = new Node();
				temp->nodeChar = superChar;
				treeNodes.push_back(temp);
			}			
		}
	}

	std::cout << "Fequency of each character:" << std::endl;
	for (int i = 0; i < treeNodes.size(); i++) {
		treeNodes[i]->frequency = frequencies.at(treeNodes[i]->nodeChar);
		std::cout << treeNodes[i]->nodeChar << " " << treeNodes[i]->frequency << std::endl;
	}
	root = buildTree(treeNodes);
	if (isLeaf(root)) {
		theHuffmanCode.emplace(root->nodeChar, "1");
		return;
	}
	else {
		buildHuffmanTable(root, "" , theHuffmanCode);
	}
	std::cout << "The huffman code of each character in the tree:" << std::endl;
	for (auto i : theHuffmanCode)
		std::cout << i.first << " " << i.second << std::endl;	
}

huffman_tree:: Node* huffman_tree::buildTree(std::vector<Node*> &treeNodes)const {
	std::priority_queue<Node*, std::vector<Node*>, compareFreq> priorityQ;
	for (int i = 0; i < treeNodes.size(); i++) {
		priorityQ.push(treeNodes[i]);
	}
	Node* left;
	Node* right;
	while (priorityQ.size() != 0) {
		if (priorityQ.size() > 1) {
			left = priorityQ.top();
			priorityQ.pop();

			right = priorityQ.top();
			priorityQ.pop();

			Node* parent = new Node();
			parent->frequency = left->frequency + right->frequency;
			parent->leftChild = left;
			parent->rightChild = right;
			priorityQ.push(parent);
		}
		else {
			return priorityQ.top();
		}		
	}
	return priorityQ.top();
}

/*Big tree*/
huffman_tree::~huffman_tree() {
	delete root;
	root = nullptr;
}

void huffman_tree::buildHuffmanTable (Node* head, std::string code, std::unordered_map<char, std::string > &table) const {
	std::string charSequence = code;
	if (head == nullptr) {
		return;
	}	
	if (isLeaf(head)) {
		table.emplace(head->nodeChar, charSequence);		
	}
	if (head->leftChild != nullptr) {
		buildHuffmanTable(head->leftChild, charSequence += '0', table);
		charSequence.pop_back();
	}
	if (head->rightChild != nullptr) {
		buildHuffmanTable(head->rightChild, charSequence += '1', table);
		charSequence.pop_back();
	}
}

//:)
std::string huffman_tree::get_character_code(char character) const {
	if (theHuffmanCode.find(character) != theHuffmanCode.end()) {
		return theHuffmanCode.at(character);
	}
	else {
		return "";
	}
}

//:)
std::string huffman_tree::encode(const std::string &file_name) const {
	if (isLeaf(root)) {
		return "1";
	}
	std::string translation;
	char c;
	std::ifstream file(file_name);

	if (file.is_open()) {
		while (true) {
			file.get(c);
			if (file.eof()) {
				break;
			}
			translation += get_character_code(c);
			if (translation == "") {
				return "";
			}
		}
	}
	else {
		return "";
	}
	return translation;
}

//:)
std::string huffman_tree::decode(const std::string &string_to_decode) const {
	std::string plainText;
	Node* temp = root;
	int i = 0;
	if (string_to_decode.size()==0) {
		return "";
	}
	if (root == nullptr){
		return "";
	}
	if (isLeaf(root) && (string_to_decode.size() > 1 || string_to_decode != "1")) {
		return "";
	}
	
	while (i < string_to_decode.size()) {
		if (string_to_decode[i] == '0') {
			if (isLeaf(temp)) {
				plainText += temp->nodeChar;
				temp = root;
			}
			else {
				temp = temp->leftChild;
				if (isLeaf(temp)) {
					plainText += temp->nodeChar;
					temp = root;
				}
			}
		}
		else if(string_to_decode[i] == '1') {
			if (isLeaf(temp)) {
				plainText += temp->nodeChar;
				temp = root;
			}
			else {
				temp = temp->rightChild;
				if (isLeaf(temp)) {
					plainText += temp->nodeChar;
					temp = root;
				}
			}
		}
		else {
			return "";
		}
		i++;
	}
	return plainText;
}

