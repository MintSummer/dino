#include <bits/stdc++.h>
using namespace std;

namespace TYC
{
    typedef long long ll;
    const ll p = 1e9 + 7;

    const ll f[] = {0, 0, 1, 2, 3, 2, 4, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 4, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3,
                    2, 4, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 4, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 4, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3,
                    2, 4, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 4, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 4, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3};

    const ll lcm[] = {0, 1, 2, 6, 12, 60, 60, 420, 840, 2520, 2520, 27720, 27720, 360360,
                    360360, 360360, 720720, 12252240, 12252240, 232792560, 232792560, 232792560,
                    232792560, 5354228880, 5354228880, 26771144400, 26771144400, 80313433200,
                    80313433200, 2329089562800, 2329089562800, 72201776446800, 144403552893600,
                    144403552893600, 144403552893600, 144403552893600, 144403552893600, 5342931457063200,
                    5342931457063200, 5342931457063200, 5342931457063200, 219060189739591200, 219060189739591200,
                    1000000000000000010};

    ll qpow(ll x, ll tim)
    {
        ll ans = 1;
        for (; tim; tim >>= 1, x = x * x % p)
            if (tim & 1)
                ans = ans * x % p;
        return ans;
    }

    void work()
    {
        ll n;
        scanf("%lld", &n);
        int cnt = 2;
        while (lcm[cnt] <= n)
            cnt++;
        cnt--;
        ll ans = qpow(2, (n - 1) / 2);
        for (int i = 2; i <= cnt; i++)
            ans = ans * qpow(f[i + 1] + 1, n / lcm[i] - n / lcm[i + 1] - (i == 2)) % p;
        printf("%lld\n", ans);
    }
} // namespace TYC

int main()
{
    TYC::work();
    return 0;
}