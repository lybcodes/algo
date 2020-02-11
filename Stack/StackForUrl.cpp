#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main()
{
	stack<string> backward, forward; //����ģ����ʵ�֣�stack�����Ĭ�Ϲ�����ʽ
	string now, b, c = "xxx.xxx.com.cn"; //nowΪ�µ���ַ��c����ǰҳ��
	while (1)
	{
		cin >> b;
		if (b == "VISIT")
		{
			cin >> now;
			cout << now << endl;
			backward.push(now);
			while (!forward.empty())
			{
				forward.pop();
			}
		}
		if (b == "BACK")
		{
			if (backward.size() != 0)
			{
				c = backward.top();
				backward.pop();
				cout << c << endl;
				forward.push(now);
				now = c;
			}
			else
			{
				cout << "Ignored" << endl;
			}
		}
		if (b == "FORWARD")
		{
			if (forward.size() != 0)
			{
				c = forward.top();
				forward.pop();
				cout << c << endl;
				backward.push(now);
				now = c;
			}
			else
			{
				cout << "Ignored" << endl;
			}
		}
		if (b == "QUIT")
		{
			break;
		}
		if (b != "VISIT" && b != "BACK" && b != "FORWARD" && b != "QUIT")
			cout << "error input" << endl;
	}
}