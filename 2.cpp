#include<iostream>
using namespace std;
int main()
{
              //2 ,3 ,8 ,8 ,8 ,8,
              //4, 5, 7, 8, 8, 8,
              //9, 3, 9, 6, 8, 8,
              //9, 9, 5, 4, 2, 8,
              //9, 9, 9, 7, 1, 8,
              //9, 9, 9, 9, 6, 9 
	int a[16] = {2 ,3 , 4, 5, 7, 3, 9, 6,5, 4, 2, 7, 1,8,6, 9};
	
	int i, j;
	cout << "请输入下标i：";
		cin >> i;
	cout << "请输入下标j：";
	cin >> j;
	cout << "矩阵下标(i,j)上的元素是：";
	if (j - i >= 2)cout << 8 << " ";
	else if (i - j >= 2)cout << 9 << " ";
	else
		cout << a[2 * i + j - 3] << " ";

}