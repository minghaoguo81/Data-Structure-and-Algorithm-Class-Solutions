#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

struct Query 
{
	string type;
	string name;
	int number;
};

vector<Query> read_queries() 
{
	int n;
	cin >> n;
	vector<Query> queries(n);
	for (int i = 0; i < n; ++i) {
		cin >> queries[i].type;
		if (queries[i].type == "add")
			cin >> queries[i].number >> queries[i].name;
		else
			cin >> queries[i].number;
	}
	return queries;
}

void write_responses(const vector<string>& result) 
{
	for (size_t i = 0; i < result.size(); ++i)
		cout << result[i] << endl;
}

vector<string> process_queries(const vector<Query>& queries) {
	vector<string> result;

	vector<Query> contacts;
	for (size_t i = 0; i < queries.size(); ++i)
		if (queries[i].type == "add") {
			bool was_founded = false;

			for (size_t j = 0; j < contacts.size(); ++j)
				if (contacts[j].number == queries[i].number) {
					contacts[j].name = queries[i].name;
					was_founded = true;
					break;
				}

			if (!was_founded)
				contacts.push_back(queries[i]);
		}
		else if (queries[i].type == "del") {
			for (size_t j = 0; j < contacts.size(); ++j)
				if (contacts[j].number == queries[i].number) {
					contacts.erase(contacts.begin() + j);
					break;
				}
		}
		else {
			string response = "not found";
			for (size_t j = 0; j < contacts.size(); ++j)
				if (contacts[j].number == queries[i].number) {
					response = contacts[j].name;
					break;
				}
			result.push_back(response);
		}
	return result;
}

vector<string> process_queries_address(const vector<Query>& queries) 
{
	vector<string> result;

	const int contacts_size = 10000000;
	vector<string> contacts(contacts_size);

	for (size_t i = 0; i < queries.size(); ++i)
		if (queries[i].type == "add") {
			contacts[queries[i].number] = queries[i].name;
		}
		else if (queries[i].type == "del") {
			contacts[queries[i].number] = "";
		}
		else {
			if (contacts[queries[i].number] == "")
				result.push_back("not found");
			else
				result.push_back(contacts[queries[i].number]);
		}
	return result;
}


int main() 
{
	write_responses(process_queries_address(read_queries()));
	return 0;
}