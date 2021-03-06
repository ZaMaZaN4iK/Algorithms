//�������� �������� ��� ���������� ���������� �� 1 ������� �� ���� ��������� �� �(MlogN) � �������������� ��������� ������ ����
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;
//������������� �������� ������ � ����, � ������� ��� ������ ����
const int maxe=100,maxv=100;
int ef[maxe],es[maxe],ev[maxe],next[maxe],first[maxv],c=0,i;
vector<long long> d(maxv+1,100000000),p(maxv+1);//������ ���������� � ������ �������(��� �������������� ����)
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;//��� � ���� ���� ����,� ��� �� ����� ������� ����, � ������� ������ �������� - ���,
//� 2-�� - ��� ����� �������

//��������� �����

void add(int v1,int v2,int value)
{
    next[++c]=first[v1];first[v1]=c;
    ef[c]=v1;es[c]=v2;ev[c]=value;
}

//�������������� ����

void init()
{
    int x,y,z;
    for(i=0;i<5;++i)
    {
        scanf("%d%d%d",&x,&y,&z);
        add(x,y,z);
        add(y,x,z);
    }
}

//������� �������.��� ��� ��������: � s �� ����� ����� �������, �� ������� ����� ������ �����.� ������� d � ��� �������� ���������� �� ������� s �� ������ ���
//�������� i(���������� ��� ������ ��������������� ��� ���������� ������ ���������).�� ���� ���� �������(0,i).
//� d[s] �� ����� 0,��� ��� ���������� ���� � ���� ����� 0.� �������� � ���� ����
//(0,s).����� �������,��� ������ ����� ���� �������� ���������:"����������� ���������� �� ������� s �� ������� i, ��� ���������� - ��� 1-�� ������� ����, � ������� i
// - 2-��.� ������ �� ��� ���, ���� ���� �� �����, ������ ���������:��������� ���� �� ����, ������� �.� ����� �� ������ ��������, ������� ����� ������ ������������
//�������� ��������� - ���� ����������, ������� �� �������� �� ���� �� ������� i ������, ��� ���������� �� ������� i � ������ d, �� ��������� �� ��������� ��������
//���������.��� ����� ������ ������������� ���� ��� ����� �������� - ��� ��� ������ ��� ������� �� �� ������ �����, �� ��� ����� �������� �� �������� ������ ��������
//������� � ���� �� �� �����, ��������.��� ��������, ������ ��� ������ � ������ d � ��� �������� ���������� �� ������, � � ���� � ��� �������� ��������� �������
//��������.���� �� ��� ��� ���������� �� ������, �� �� ������� ��� ����, ��������� �� ������� i(��� �� �������, ������� �� �������� �� ����).
//� �������: ���� ���������� �� ������� i(�� ��� ���� �������� �� ����) + ���������� �� i �� 2-��� ����� ����� ������ ������, ��� �������� � ������� d ��� 2-��� 
//����� �����(� ��� ���������� ���� ���������� �� ������� s �� ����� �������� �����), �� �� ���������� � ������ d � ������� 2-��� ����� ����� ��������
//���������� �� ������� i(�� ��� ���� �������� �� ����) + ���������� �� i �� 2-��� ����� �����(� ��� ���� ������ ��� �����).� ����� ���� � ����� ����������� ��
//���� ������� � ���� ������� � ����.� �����, ���� ��� ����� �� ������ ������ ����������� ��������� ����, �� � ������������ ���, �� � ������ ������� (p) � ������ 
// � ������� 2-��� ����� ����� �� ������� ����� �������, �� ������� �� �������� �� �� ����������, � ��� ���� ����� i(� ���� ��� to).

//��������� ��� ��.� ����� ������ ��������� � d[i] ����� �������� ����������� ���������� �� ������� s �� ������� i.������� ��������, ��� �������� �������� ������
// ��� ������ � ������������� ����� ���� - ��� ������������� ��� ��������� ������.����� ���� � ��� � d[i] ����� �������������, �� �� ���� ������ ����� ������.

//������� �������������� ���� ������� ������ - �������� �� ��� �������, �� ������� ������ �����.� ��� ��� � ��� �������� � ������� ������ �� �������, �� ������� 
//�� ������ � ��, �� ��������� �� ������� �� ��� ���, ���� �� ������ �� ������� s.� ����� ���������� ������������������ ��������������, � �������� ���������� ����.

void dist()
{
    int s=1;
    d[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
    {
        int to=q.top().second;int line=q.top().first;
        q.pop();
        if(line>d[to])  continue;
        for(int h=first[to];h;h=next[h])
            if(line+ev[h] < d[es[h]])
            {
                d[es[h]]=line+ev[h];
                p[es[h]]=to;
                q.push(make_pair(d[es[h]],es[h]));
            }
    }
}

//��� ������ �������������� ����, ����� ������� ��������, � ������� ���������� �� 2 �������

int main()
{
    init();
    dist();
    cout<<d[2]<<endl;
    system("pause");
    return 0;
}
