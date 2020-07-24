#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
	char character;
	uint32_t frequency;
	Node* left;
	Node* right;
	Node(pair<char, uint32_t> arg)
	{
		left = right = nullptr;
		this->character = arg.first;
		this->frequency = arg.second;
	}
};

bool pair_comparator(const pair<char, uint32_t>& a, const pair<char, uint32_t>& b)
{
	return a.second < b.second;
}

struct Comparator {
	bool operator()(Node* left, Node* right)
	{
		return (left->frequency > right->frequency);
	}
};

map<char, uint32_t> count_occurrences(string text)
{
	/* count occurrences of characters */
	/* and save in std::map */
	map<char, uint32_t> pair_map;
	for (auto& x : text)
	{
		++pair_map[x];
	}
	return pair_map;
}

vector<pair<char, uint32_t>> init_vector(map<char, uint32_t> unsorted_map)
{
	/* convert map into vector of pairs */
	vector<pair<char, uint32_t>> pair_vector;
	for (auto& it : unsorted_map)
	{
		pair_vector.push_back(it);
	}

	/* sort vector of pairs */
	sort(pair_vector.begin(), pair_vector.end(), pair_comparator);
	return pair_vector;
}

void fill_codes_vector(struct Node* root, string str, vector<pair<char, string>>& codes)
{
	/* if !root need break (nullptr) */
	if (!root)
	{
		return;
	}
	/* if not dollar its mean, that Node represent one char */
	/* so, we can add this Node to our vector */
	if (root->character != '$') {
		pair<char, string> it = make_pair(root->character, str);
		codes.push_back(it);
	}
	/* recurring call of this method */
	/* left son has zero at the end of the string */
	/* right son has one at the end of the string */
	fill_codes_vector(root->left, str + "0", codes);
	fill_codes_vector(root->right, str + "1", codes);
}

priority_queue<Node*, vector<Node*>, Comparator> init_min_heap(vector<pair<char, uint32_t>> arg_vector)
{
	struct Node* left;
	struct Node* right;
	struct Node* top;

	/* init priority queue */
	priority_queue<Node*, vector<Node*>, Comparator> min_heap;
	for (auto& it : arg_vector) {
		min_heap.push(new Node(it));
	}

	/* loop while size is not equal to one*/
	while (min_heap.size() != 1)
	{
		/* extract rarest elements from begin*/
		left = min_heap.top();
		min_heap.pop();
		right = min_heap.top();
		min_heap.pop();

		/* make one Node from removed Nodes */
		/* value is sum of components, key is dollar */
		/* dollar means that the node does not represent one, but several chars */
		pair<char, uint32_t> tmp_pair = make_pair('$', left->frequency + right->frequency);
		top = new Node(tmp_pair);

		/* add children to new Node*/
		top->left = left;
		top->right = right;

		/* add new Node to heap */
		/* he will get to the right place */
		min_heap.push(top);
	}
	return min_heap;
}

int main()
{
	string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. In sagittis, nunc ac suscipit consectetur, augue nibh dictum erat, non feugiat mauris diam in ex. Nulla ac aliquet dolor, ac pretium sem. Suspendisse potenti. Proin eu nisl sem. Morbi nibh leo, efficitur a enim non, rhoncus tincidunt dolor. Integer condimentum ac lorem vitae imperdiet. Quisque posuere sem sed viverra faucibus. Donec semper lorem a ante vestibulum eleifend. Nullam interdum sagittis mauris, ac accumsan felis condimentum eget. Proin eleifend non justo nec pretium. Aliquam in magna luctus, viverra purus id, tempor turpis. Quisque euismod augue ex, in auctor nulla accumsan eu. Maecenas bibendum ut eros a dignissim. In leo mi, rhoncus a interdum a, mattis in dolor. Vestibulum nec ex id tellus lobortis placerat id quis est.";
	auto my_map = count_occurrences(text);
	auto my_vec = init_vector(count_occurrences(text));
	auto my_heap = init_min_heap(my_vec);
	vector<pair<char, string>> my_codes;
	fill_codes_vector(my_heap.top(), "", my_codes);
	for (auto& it : my_codes)
	{
		cout << "Char: " << it.first << "\tBinary: " << it.second << "\n";
	}


	return 0;
}