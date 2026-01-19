//Time Complexity- 3T(n/2)+n logn
//Using case 1(Master Theorem)- O(n^log2(3))

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

long long operations = 0;
int maxDepth = 0;

void complexRec(int n, int depth) {
    operations++; 
    maxDepth = max(maxDepth, depth);

    if (n <= 2) {
        return;
    }

    int p = n;
    operations++;

    while (p > 0) {
        operations++;
        vector<int> temp(n);
        operations += n;
        for (int i = 0; i < n; i++) {
            temp[i] = i ^ p;
            operations++; 
        }
        p >>= 1;
        operations++;
    }
    vector<int> small(n);
    operations += n;
    for (int i = 0; i < n; i++) {
        small[i] = i * i;
        operations++;
    }

    reverse(small.begin(), small.end());
    operations += n;

    complexRec(n / 2, depth + 1);
    complexRec(n / 2, depth + 1);
    complexRec(n / 2, depth + 1);
}

int main() {
    int n;
    cin >> n;

    operations = 0;
    maxDepth = 0;

    auto start = high_resolution_clock::now();
    complexRec(n, 1);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Operations- " << operations << endl;
    cout << "Depth- " << maxDepth << endl;
    cout << "Time(ms)- " << duration.count() << endl;

    return 0;
}
