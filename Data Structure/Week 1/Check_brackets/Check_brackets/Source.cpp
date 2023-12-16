#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

struct stack_item
{
	char type;
	int index;
};

string Balance(string str)
{
	stack<stack_item> ck_stack;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
		{
			stack_item item;
			item.type = str[i];
			item.index = i;
			ck_stack.push(item);
		}
		else if (str[i] == ')' || str[i] == ']' || str[i] == '}')
		{
			if (ck_stack.empty())
				return to_string(i + 1);
			stack_item top = ck_stack.top();
			ck_stack.pop();
			if (top.type == '(' && str[i] != ')' || top.type == '[' && str[i] != ']' || top.type == '{' && str[i] != '}')
			{
				return to_string(i + 1);
			}
		}
	}

	return (ck_stack.empty() ? "Success" : to_string(ck_stack.top().index + 1));
}

int main()
{
	string str;
	getline(cin, str);

	cout << Balance(str) << endl;

	return 0;
}
