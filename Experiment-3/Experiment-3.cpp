#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<char> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int maxStaleAtten = 0;
    for (int i = 0; i < n; i++) {
        int p = 0, a = 0;
        for (int j = i; j < n; j++) {
            if (arr[j] == 'P'){
                p++;
            }else {
                a++;
            }
            if (p == a) {
                maxStaleAtten = max(maxStaleAtten, j - i + 1);
            }
        }
    }
    cout << maxStaleAtten << endl;
    return 0;
}