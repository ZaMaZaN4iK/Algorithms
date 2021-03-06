#pragma comment(linker, "/STACK:65777216")
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <queue>
#include <string>
#include <memory.h>
#include <iterator>
#define y1 trololoy1
#define y0 trololoy0
#define mem(A,X) memset(A,X,sizeof(A))
#define memo(A) memset(A,0,sizeof(A))
#define forn(I,B) for (int I=1;I<=(B);I++)
#define forg(H,V) for (int H=first[V];h;h=next[H])
#define rep(I,B) for (int I=0;I<(B);I++) 
#define labs(X) (((X)>0)?(X):(-(X)))
#define ropen(X) freopen(X,"r",stdin)
#define wopen(X) freopen(X,"w",stdout)
#define rwopen(X) freopen(X".in","r",stdin);freopen(X".out","w",stdout)
#define pb push_back
#define mp make_pair
#define all(X) (X).begin(),(X).end()
#define sqr(X) ((X)*(X))

using namespace std;

typedef pair <int,int> pii;
typedef double ld;
typedef long long ll;
typedef pair <ll,ll> pll;
typedef vector<int> vi;
const int N=200000;
const int INF=111111111;
const double eps=1e-9;
const double pi=3.14159265358979;

struct treap{
	int ls,rs,y,sz,color,b;
	ll cost,sum,a;
	treap(){}
	treap(int ls,int rs,int y,ll cost,int sz,ll sum,int color,ll a,int b):ls(ls),rs(rs),y(y),cost(cost),sz(sz),sum(sum),color(color),a(a),b(b){}
} t[N];

int a[N],root,n,c,m,p[N],res;
char s;

inline int getInt(){
	res=0;
	do{
		s=getchar();
	} while (s<'0' || s>'9');
	do{
		res=res*10+s-'0';
		s=getchar();
	} while (s>='0' && s<='9');
	return res;
}

void put(ll x){
	if (x){
		put(x/10ll);
		putchar(x%10ll+'0');
	}
}

inline void putLl(ll x){
	if (x) put(x);
	else putchar('0');
	putchar('\n');
}           

inline int szof(int x){
	if (x) return t[x].sz; else return 0;
}

inline ll sumof(int x){
	if (x){
		if (t[x].color==-1) return t[x].sum+t[x].sz*t[x].a+((t[x].sz+1ll)*t[x].b*t[x].sz>>1);
		else return t[x].sz*t[x].color+t[x].sz*t[x].a+((t[x].sz+1ll)*t[x].b*t[x].sz>>1);
	} else return 0;
}

inline void recalc(int x){
	if (x){
		t[x].sz=szof(t[x].ls)+szof(t[x].rs)+1;
		t[x].sum=sumof(t[x].ls)+sumof(t[x].rs)+t[x].cost;
	}
}

inline void push(int x){
	if (x && t[x].color!=-1){
		t[x].cost=t[x].color;
		t[t[x].ls].color=t[x].color;
		t[t[x].rs].color=t[x].color;
		t[x].color=-1;
		t[t[x].ls].a=t[t[x].ls].b=t[t[x].rs].a=t[t[x].rs].b=0;
	}
	if (x && (t[x].a || t[x].b)){
		t[t[x].ls].b+=t[x].b;
		t[t[x].rs].b+=t[x].b;
		t[t[x].ls].a+=t[x].a;
		t[t[x].rs].a+=t[x].a+(szof(t[x].ls)+1)*t[x].b;
		t[x].cost+=t[x].a+(szof(t[x].ls)+1)*t[x].b;
		t[x].a=t[x].b=0;
	}
}

void merge(int &x,int l,int r){
	if (!l || !r) x=l?l:r;
	else if (t[l].y>t[r].y) push(l),x=l,merge(t[x].rs,t[x].rs,r);
	else push(r),x=r,merge(t[x].ls,l,t[x].ls);
	recalc(x);
}

void split (int x,int key,int &l,int &r){
	if (!x) l=r=0;
	else {
		if (key==0) r=x,l=0;
		else{
			push(x);
			int ck=szof(t[x].ls)+1;
			if (ck<=key) l=x,split(t[x].rs,key-ck,t[x].rs,r);
			else r=x,split(t[x].ls,key,l,t[x].ls);
			recalc(x);
		}
	}
}

inline void insert(int pos,int x){
	t[++c]=treap(0,0,a[c-1],x,1,x,-1,0,0);
	int l,r,m;
	split(root,pos,l,r);
	merge(m,l,c);
	merge(root,m,r);
}

inline void coloring(int l,int r,int color){
	int L,M,R,L1;
	split(root,r,L,R);
	split(L,l-1,L1,M);
	t[M].color=color;
	t[M].a=t[M].b=0;
	merge(L,L1,M);
	merge(root,L,R);
}

inline void update(int l,int r,int x){
	int L,M,R,L1;
	split(root,r,L,R);
	split(L,l-1,L1,M);
	t[M].b+=x;
	merge(L,L1,M);
	merge(root,L,R);
}

inline void get_sum(int l,int r){
	int L,M,R,L1;
	split(root,r,L,R);
	split(L,l-1,L1,M);
	putLl(sumof(M));
	merge(L,L1,M);
	merge(root,L,R);
}

void go(int x){
	if (!x) return;
	go(t[x].ls);
	go(t[x].rs);
	t[x].sz=t[t[x].ls].sz+t[t[x].rs].sz+1;
	t[x].sum=t[t[x].ls].sum+t[t[x].rs].sum+t[x].cost;
}

void build(){
	int last=1,cur;
	root=++c;
	t[1]=treap(0,0,a[0],0,1,0,-1,0,0);
	t[1].cost=getInt();
	forn(i,n-1){
		t[++c]=treap(0,0,a[c-1],0,1,0,-1,0,0);
		t[c].cost=getInt();
		if (t[c].y<t[last].y){
			p[c]=last;
			t[last].rs=c;
			last=c;
			continue;
		}
		if (t[c].y>t[root].y){
			p[root]=c;
			t[c].ls=root;
			root=last=c;
			continue;
		}
		cur=last;
		while (t[cur].y<t[c].y) cur=p[cur];
		t[c].ls=t[cur].rs;
		p[t[cur].rs]=c;
		p[c]=cur;
		t[cur].rs=last=c;
	}
	go(root);
}		

int main(){
	ropen("input.txt");
	wopen("output.txt");
	n=getInt();m=getInt();
	srand(n+m);
	rep(i,n+m) a[i]=i;
	random_shuffle(a,a+n+m);
	build();
	int T;
	forn(i,m){
		T=getInt();
		if (T==1) coloring(getInt(),getInt(),getInt());
		else if (T==2) update(getInt(),getInt(),getInt());
		else if (T==3) insert(getInt()-1,getInt());
		else get_sum(getInt(),getInt());
	}
	return 0;
}