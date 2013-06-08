//http://acm.hdu.edu.cn/showproblem.php?pid=3439
// Cal C(n,k) mod m
// cal Derangements(n) mod m
// m<=10^5, n,k <= 10^9

#include<stdio.h>
#include<string.h>

typedef long long int LL;

int ss[405] = {1,1};
int pp[405 >> 1],plen = 0;
int fac[32][2],flen ;
int F[100005];
int n,k,m;

int cnt_of_p;
int p,P;

void mklist(){
    int i,j;
    for(i = 2; i * i < 405; ++ i) if(! ss[i]) for(j = i; j * i < 405; ++ j) ss[i * j] = 1;
    for(i = 2; i < 405; ++ i) if(! ss[i]) pp[plen ++]  =  i;
}

void split(int n){
    flen= 0;
    int i;
    for(i = 0; i < plen && pp[i] <= n; ++ i){
        if(n % pp[i]) continue;
        fac[flen][0] = pp[i];
        fac[flen][1] = 0;
        while(n % pp[i] == 0) n/= pp[i], ++ fac[flen][1];
        ++ flen;
    }
    if(n != 1){
        fac[flen][0] = n;
        fac[flen ++][1] = 1;
    }
}
inline int mod(LL a,int b,int c){
    LL ret = 1 % c;
    while(b){
        if(b&0x1) ret= ret * a % c;
        a = a * a % c;
        b >>=1;
    }
    return ret;
}
int ext_gcd(int a, int b, int &x, int &y){
    int t, d;
    if (b == 0) { x = 1; y = 0; return a; }
    d = ext_gcd(b, a % b, x, y);
    t = x;
    x = y;
    y = t - a / b*y;
    return d;
}
inline int InvMod(int a,int n){
    int x,y;
    if (ext_gcd(a,n,x,y)!=1)return -1;
    return (x%n+n)%n;
}

void init(){
    F[0] = 1;cnt_of_p = 0;
    int i,tmp;
    for(i = 1; i < P; ++ i){
        F[i] = F[i - 1];
        if(i % p) F[i] = (LL)F[i] * i % P;
    }
}

int cal_fac_modP(int n,int op){//(1 * 2 * 3 * ... * n) mod P, P = p ^ cntk
    if(n <= 1) return 1;
    LL ans = 1;
    int cnt_of_seg = n / P,cnt_of_rem = n % P;
    ans = mod(F[P - 1], cnt_of_seg, P) * F[cnt_of_rem];
    if(op > 0)cnt_of_p += n /= p; else cnt_of_p -= n /= p;
    ans = ans * cal_fac_modP(n ,op);
    return ans % P;
}

int CTR(int b[], int w[], int k) {
    int i;
    int d, x, y, a = 0, m, n = 1;
    for (i = 0; i < k; i++) n *= w[i];
    for (i = 0; i < k; i++) {
        m = n / w[i];
        d = ext_gcd(w[i], m, x, y);
        LL yy = y; yy = yy * m % n; yy = yy * b[i] % n;
        a = (a + yy) % n;
    }
    if (a >= 0) return a;
    else return (a + n);
}

int Cal_Cnk_mod_P_K(int n,int k,int _p,int _P){
    p = _p;
    P = _P;
    init();
    LL ans = cal_fac_modP(n, 1);
    ans = ans * InvMod( cal_fac_modP(k, - 1), P) % P ;
    ans = ans * InvMod( cal_fac_modP(n - k, - 1), P) % P;
    ans = ans * mod(p,cnt_of_p,P) % P;
    return ans;
}

int b[55],w[55];
int idx = 0;
int g(int n,int p)  {
    int i;
    LL m=1, res = 0;
	for(i=n; i>=0&&m;i--)  {
		if(i&1)  res-=m;  else  res+=m;
		m = m * i % p;
		res %= p;
	}
	if( res < 0) res += p;
	return res;
}
void work(){
    ++ idx;
    printf("Case %d: ",idx);
    if(m == 1){
        puts("0");
        return;
    }
    k = n - k;
    if(k == 0){
        puts("1");
        return ;
    }
    if(k == 1) {
        puts("0");
        return ;
    }
    int i,j;
    for(i = 0; i < flen; ++ i){
        w[i] = 1;
        for(j = 0; j < fac[i][1]; ++ j) w[i] *= fac[i][0];
        b[i] = Cal_Cnk_mod_P_K(n,k,fac[i][0],w[i]);
    }
    LL ans = CTR(b,w,flen);
    ans = ans * g( k, m ) % m;
    printf("%I64d\n",ans);
}

void get(){scanf("%d%d%d",&n,&k,&m);}
int main(){
    mklist();
    int T;
    scanf("%d",&T);
    while(T --){
        get();
        split(m);
        work();
    }
    return 0;
}