#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;

ll N, M, K;
vvl A;
vvl P;
vvvl F;

void solve() {
  for (auto k = 0; k < K; ++k) {
    // 1 & 2
    for (auto i = 1; i <= N; ++i) {
      for (auto j = 1; j <= N; ++j) {
        if (F[i][j].size() == 0) continue;

        sort(F[i][j].begin(), F[i][j].end());

        ll added = 0;
        vl nq{};
        for (const auto& f : F[i][j]) {
          if (f <= P[i][j]) {
            nq.push_back(f + 1);
            P[i][j] -= f;
          } else {
            added += f / 2;
          }
        }

        F[i][j] = nq;
        P[i][j] += added;
      }
    }

    // 3
    for (auto i = 1; i <= N; ++i) {
      for (auto j = 1; j <= N; ++j) {
        for (const auto& f : F[i][j]) {
          if (f % 5 == 0) {
            for (auto di = -1; di <= 1; ++di) {
              for (auto dj = -1; dj <= 1; ++dj) {
                if (di == 0 && dj == 0) continue;

                const auto& ni = i + di;
                const auto& nj = j + dj;
                if (ni < 1 || N < ni || nj < 1 || N < nj) continue;
                F[ni][nj].push_back(1);
              }
            }
          }
        }
      }
    }

    // 4
    for (auto i = 1; i <= N; ++i) {
      for (auto j = 1; j <= N; ++j) {
        P[i][j] += A[i][j];
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N >> M >> K;

  A = vvl(N + 1, vl(N + 1, 0));
  for (auto i = 1; i <= N; ++i) {
    for (auto j = 1; j <= N; ++j) {
      cin >> A[i][j];
    }
  }

  F = vvvl(N + 1, vvl(N + 1, vl{}));
  P = vvl(N + 1, vl(N + 1, 5));
  for (auto i = 0; i < M; ++i) {
    ll x, y, z;
    cin >> x >> y >> z;
    F[x][y].push_back(z);
  }

  solve();

  ll ans = 0;
  for (auto i = 1; i <= N; ++i) {
    for (auto j = 1; j <= N; ++j) {
      ans += F[i][j].size();
    }
  }
  cout << ans;

  return 0;
}