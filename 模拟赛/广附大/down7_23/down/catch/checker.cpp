#include "testlib.h"
#include<bits/stdc++.h>
namespace my_std{
    using namespace std;
    #define pii pair<int,int>
    #define fir first
    #define sec second
    #define MP make_pair
    #define rep(i,x,y) for (int i=(x);i<=(y);i++)
    #define drep(i,x,y) for (int i=(x);i>=(y);i--)
    #define go(x) for (int i=head[x];i;i=edge[i].nxt)
    #define templ template<typename T>
    #define sz 110101
    typedef long long ll;
    typedef double db;
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    templ inline T rnd(T l,T r) {return uniform_int_distribution<T>(l,r)(rng);}
    templ inline bool chkmax(T &x,T y){return x<y?x=y,1:0;}
    templ inline bool chkmin(T &x,T y){return x>y?x=y,1:0;}
    templ inline void read(T& t)
    {
        t=0;char f=0,ch=getchar();double d=0.1;
        while(ch>'9'||ch<'0') f|=(ch=='-'),ch=getchar();
        while(ch<='9'&&ch>='0') t=t*10+ch-48,ch=getchar();
        if(ch=='.'){ch=getchar();while(ch<='9'&&ch>='0') t+=d*(ch^48),d*=0.1,ch=getchar();}
        t=(f?-t:t);
    }
    template<typename T,typename... Args>inline void read(T& t,Args&... args){read(t); read(args...);}
    char __sr[1<<21],__z[20];int __C=-1,__zz=0;
    inline void Ot(){fwrite(__sr,1,__C+1,stdout),__C=-1;}
    inline void print(int x)
    {
        if(__C>1<<20)Ot();if(x<0)__sr[++__C]='-',x=-x;
        while(__z[++__zz]=x%10+48,x/=10);
        while(__sr[++__C]=__z[__zz],--__zz);__sr[++__C]='\n';
    }
    void file()
    {
        #ifdef NTFOrz
        freopen("a.in","r",stdin);
        #endif
    }
    inline void chktime()
    {
        #ifdef NTFOrz
        cerr<<clock()/1000.0<<'\n';
        #endif
    }
    #ifdef mod
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x%mod) if (y&1) ret=ret*x%mod;return ret;}
    ll inv(ll x){return ksm(x,mod-2);}
    #else
    ll ksm(ll x,int y){ll ret=1;for (;y;y>>=1,x=x*x) if (y&1) ret=ret*x;return ret;}
    #endif
}
using namespace my_std;

int n,m,K;
int t[sz];
vector<int>V[sz];

ll dis[sz];
int id[sz];

int check(InStream &I)
{
    string ans=I.readToken();
    if (ans=="impossible") return 0;
    if ((int)ans.size()!=n) I.quitf(_wa, "wrong answer length");
    rep(i,0,n-1) if (ans[i]!='P'&&ans[i]!='U') I.quitf(_wa, "string not consisting of P and U");
    int cc=0; rep(i,0,n-1) cc+=(ans[i]=='U');
    if (cc!=K) I.quitf(_wa, "wrong number of uoj zhuangding");
    static int ok[sz];
    memset(ok,0,sizeof(ok));
    ok[1]=1;
    rep(_,1,n)
    {
        int x=id[_]; if (!ok[x]) continue;
        for (auto v:V[x]) if (dis[v]==dis[x]+t[v]&&ans[x-1]!=ans[v-1]) ok[v]=1;
    }
    if (ok[n]) I.quitf(_wa, "invalid solution");
    return 1;
}

int main(int argc, char **argv)
{
    registerTestlibCmd(argc, argv);
//	registerLemonChecker(argc, argv);
    n=inf.readInt(2,100000);
    m=inf.readInt(n-1,200000);
    K=inf.readInt(0,n);
    rep(i,1,n) t[i]=inf.readInt(1,10000);
    int x,y;
    rep(i,1,m) x=inf.readInt(1,n),y=inf.readInt(1,n),V[x].push_back(y),V[y].push_back(x);
    priority_queue<pii,vector<pii>,greater<pii>>q;
    q.push(MP(0,1)); rep(i,2,n) dis[i]=2e9;
    while (!q.empty())
    {
        pii p=q.top(); q.pop();
        int x=p.sec; if (dis[x]!=p.fir) continue;
        for (auto v:V[x]) if (chkmin(dis[v],dis[x]+t[v])) q.push(MP(dis[v],v));
    }
    rep(i,1,n) id[i]=i;
    sort(id+1,id+n+1,[](int x,int y){return dis[x]<dis[y];});
    x=check(ouf),y=check(ans);
    if (x&&!y) quitf(_fail, "wtf?");
    if (!x&&y) quitf(_wa, "fail to find a solution");
    quitf(_ok, "ok");
}
