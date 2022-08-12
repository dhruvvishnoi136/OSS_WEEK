
#ifndef TRIE_HPP 
#define TRIE_HPP 
#include<iostream>
#include<vector>
#include<string>
// This code is for TRIE Data Structure

class trie_node {
private:
	char data = ' ';
	bool end;
	std::vector<trie_node*> next;
	void* operator new(size_t size) {
		return (void*)malloc(size);
	};
	void operator delete(void*) {};
	void* operator new[](size_t) {};
	void operator delete[](void*) {};
	trie_node() {
		this->end = false;

	}
	trie_node(char data, bool end = false) {
		this->data = data;
		this->end = end;
	}
public:
	friend class trie;
};
class trie {
private:
	trie_node root;
	/* It Counts Root Node as first Node*/
	size_t max_height = 0;
	void space_generator(std::vector<std::string>& datas, std::vector<std::string>& slashes , trie_node current_node, int level = 1);
public:
	trie(std::vector<std::string> list_of_string);
	void delete_data(std::string data);
	void insert_data(std::string data);
	int count();
	void printer();
};

trie::trie(std::vector<std::string> list_of_string) {
	for (int i = 0; i < list_of_string.size(); i++)
	{
		std::string data = list_of_string[i];
		this->insert_data(list_of_string[i]);
	}
}
void trie::insert_data(std::string data)
{
	size_t data_size = data.size();
	this->max_height = ((data_size+1) * (this->max_height < data_size) + (this->max_height) * (this->max_height >= data_size));
	trie_node* temp = &this->root;
	for (size_t i = 0; i < data_size; i++)
	{
		size_t size_next = temp->next.size();
		bool end_parser = true * ((i + 1) >= data_size);
		if (size_next == 0) {
			trie_node* newnode = new trie_node(data[i], end_parser);
			temp->next.push_back(newnode);
			temp = newnode;
			continue;
		}
		bool if_there = false;
		size_t stored_index = 0;
		for (size_t j = 0; j < size_next; j++)
		{
			if_there = (data[i] == temp->next[j]->data);
			stored_index = j * (if_there);
			if (if_there) {
				break;
			}
		}
		if (!if_there) {
			trie_node* newnode = new trie_node(data[i], end_parser);
			temp->next.push_back(newnode);
			temp = newnode;
			continue;
		}
		else {
			temp->next[stored_index]->end = 1*(temp->next[stored_index]->end) + end_parser*(!(temp->next[stored_index]->end));
			temp = temp->next[stored_index];
			continue;
		}
	}
}

///////////////////// Code Beneath This Is Not Functional Yet ... Under Development/////////////////////
void trie::delete_data(std::string data) {
	return;
}

void trie::space_generator(std::vector<std::string>& datas, std::vector<std::string>& slashes, trie_node current_node, int level) {
	try {
		size_t temp = current_node.next.size();
		datas[level].push_back(' ');
		datas[level].push_back(current_node.data);
		for (size_t i = 0; i < temp; i++) {
			slashes[level].push_back(' ');
			if (i <= (temp / 2)) {
				slashes[level].push_back('/');
			}
			else {
				slashes[level].push_back('\\');
			}
			space_generator(datas, slashes, *current_node.next[i], (level + 1));
		}
		if (temp % 2 != 0) {
			slashes[level].replace(((slashes[level].size()) / 2), 1, "|");
		}
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
	}

}

void trie::printer() {
	if (this->max_height) {
		std::cout << "The Trie is Empty";
	}
	std::vector<std::string> level(this->max_height), slashes(this->max_height - 1);
	this->space_generator(level, slashes, this->root);
	size_t sizee = level.size();
	for (size_t j = 0; j < sizee; j++) {
		std::cout << slashes[j] << "\n";
		std::cout << level[j] << "\n";
	}
	return;
}
#endif //!TRIE_HPP


