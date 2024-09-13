#include <iostream>

int solve(long long n, int k = 16) {
    long long s = 0;
    for (int i = 0; i < k; i++) {
        s = 10 * s + 1;
    }

    int count = 0;
    while (s <= n) {
        count += k;
        n -= s;
    }

    if (n != 0)
        return count + std::min(solve(n, k - 1), k + solve(s - n, k - 1));
    else
        return count;
}

int main() {
    long long n;
    std::cin >> n;
    std::cout << solve(n) << std::endl;
}
