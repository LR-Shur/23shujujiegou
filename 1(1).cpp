#include<iostream>
//#include<deque>
using namespace std;
struct deque {
	int a[1000];
	int i = 500, j = 500;
};
bool empty(deque& q)
{
	if (q.i == q.j)return true;
	else return false;
}
void push_front(deque &q,int now)
{
	q.a[--(q.i)] = now;
}
void push_back(deque &q, int now)
{
	q.a[++(q.j)] = now;

}
//1
void pop_front(deque&q)
{
	if(q.a[(q.i)] != -1)
	q.a[(q.i)++]=-1;
	else q.a[++(q.i)] = -1;
}
int main()//分别列出每个用户的到达时间，是否为vip，等待时间等信息
{
	srand(time(0));
	int v[10000];
	int n = 12,N=5;//N为业务办理时间
	v[0] = 1;
	for (int i = 1; i < n; i++)
	{
		v[i] = v[i - 1] + rand() % 3 + 1;
	}
	int a = rand() % 12, b = rand() % 12;
	if (a == b || abs(b - a) < 3)b = (b - 6 + 12) % 12;//不要管

	deque q;//双端队列
	for (int i = 0; i < 1000; i++)
		q.a[i] = -1;
	int now = 0,end=0;//[表情]w指的是下标为now的人目前未到银行，其之前的人都已经到了银行   end代表上一个人业务办理完后的结束时间
	int w[12];//每个客户开始业务办理那一时刻（出队列的时刻）
	for (int t = 0;; t++)
	{
		if (now == 12 && empty(q))break;//假如12个人都办理完了就退出循环
		if (t == v[now])//当前这个人到达银行的时间为t时
		{
			if (!empty(q)) {//假如有人排队
				if (now == a || now == b)//若为vip
					push_front(q,now);//放队首
				else push_back(q,now);//放队尾
			}
			else push_back(q,now);//若无人排队（队列为空）直接加入队首
			now++;//更新now
		}
		if (t > end&&!empty(q))//若当前之间大于上个客户办理业务时间，则代表现在无人进行业务办理，从而允许队列中排队的第一个人进行业务办理
		{
			int temp;
			if (q.a[q.i] != -1)
			{
				temp = q.a[q.i];
			}
			else { temp = q.a[q.i+1];
			}//第一个人
			pop_front(q);//出队列
			w[temp] = t;//记录出队列的时间
			//cout << t << " ";
			end = t + N - 1;//更新这个人业务办理的结束时间
		}
	}
	cout << "每个人进行业务办理时间为" << N << endl;
	for (int now = 0; now < 12; now++)
	{
		cout << "第" << now + 1 << "个用户到达时间为" << v[now] << " ";
		if (now == a || now == b)cout << "是vip" << " ";
		else cout << "不是vip" << " ";
		cout << "等待时间为" << w[now] - v[now] << endl;
	}
}