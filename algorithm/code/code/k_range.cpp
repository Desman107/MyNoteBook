#include<iostream>

using namespace std;

typedef long long ll;
ll ans;
const int N = 100010;
int a[N],s[N], res[N];

int main(){
    // ios::sync_with_stido(false);
    
    int n, k;
    
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> a[i];
        s[i] = (s[i - 1] + a[i]) % k;
        ans += res[s[i]];
        res[s[i]]++;
    }
    cout << ans + res[0];
}