//����������� �������� ������ �� O(NlogN) ������� �������� ����� DSU(������� ���������������� ��������)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;
typedef long long ll;

const ll maxn=100,maxm=200;//�������� ������ � �������� ����
vector<ll> d(maxn,-1);//������ ��� DSU
vector<pair<ll,pair<ll,ll> > > a(maxm),p;//��� ����� ������� ����.������ ������� - ��� �����, 2-�� � 3-�� - ������ � ����� �����
ll i,j,k,z=0,temp,r,n,m;

//������� ��� ��������� ����� ������� ���������.��������� �������� � �������� ������ DSU

ll findroot(ll v)
{
    return d[v]==-1 ? v : d[v]=findroot(d[v]);
}

//������� ����������� ���� ��������.��������� �������� � �������� ������ DSU

bool union_set(ll a,ll b)
{
    ll q1,q2;
    q1=findroot(a);
    q2=findroot(b);
    if(q1 != q2)
    {
        r=rand() % 2;
        r==0 ? d[q1]=q2 : d[q2]=q1;
        return true;
    }
    return false;
}

//������ ���� �� ������� ����� ������ ����������� �����

void input()
{
    scanf("%I64d %I64d",&n,&m);
    for(i=0;i<m;++i)
    {
        scanf("%I64d %I64d %I64d",&a[i].second.first,&a[i].second.second,&a[i].first);
    }
}

//������� ������� ���������.�������� ��������� �������: �� ��������� � ������� ����������� ����� �� ����.����� ����� ������ n-1 ����
//(��� ��� ������ ����� �������� �� n-1 ����� �� ������� � ��������) � ���� ����� �� ����������� ������ ���������(�� ���� �� ���������), �� ����� ��� �����
//�������� ��� � ����������� ��������� ������, � ���������� ����� ����� � ���� ���������.� ��� �� ��� ���, ���� �� ������� � ����� N-1 ��� �����.
//� ������ ���������� �� �� ����������� ��� ��������, � ���� �����, �� ������� ����� �������� ������������ �������� ������

void sol()
{
    sort(a.begin(),a.begin()+m);
    temp=n-1;
    for(i=0;i<m && z<temp;++i)
    {
        if(union_set(a[i].second.first,a[i].second.second))
        {
            ++z;
            p.push_back(a[i]);
        }
    }
}

//����� ����������� ������

void output()
{
    for(i=0;i<p.size();++i)
        printf("%I64d -> %I64d = %I64d\n",p[i].second.first,p[i].second.second,p[i].first);
}

//�� � ��� ������� �������� rand(), ����� ������ ����, ������� min_ost � ������� ���

int main()
{
    srand(time(0));
    input();
    sol();  
    output();  
    system("pause");
    return 0;
}
