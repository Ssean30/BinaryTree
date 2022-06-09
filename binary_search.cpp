#include <iostream>
#include <cstdlib>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

vector<int> vc;

int binarySearch(vector<int> vc, int size, int num) {

    // defining the top and the bottom values
    int low = 0;
    int high = size -1;
    int mid;

    // executing binary Search
    while (low <= high)
    {
        mid = (high + low) / 2;

        if (num == vc[mid]) 
        {
            return mid;
        } 
        else if (num > vc[mid]) 
        {
            low = mid + 1;    
        } 
        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

int generate(int req) {

    int prev_val;
    int next_val;

    vc.push_back(rand() % 100 + 1);

    for (int i = 0; i < 10000000; i++)
    {
        prev_val =  vc.back();
        next_val = prev_val + rand() % 100 + 1;
        vc.push_back(next_val);
    }

    return 0;
}

int main() {
    int num;
    int req;
    
    
    cout << "How many numbers Do you want to generate (ENTER : 10000000)" << endl;
    cin >> req;
    generate(req);

    vc.shrink_to_fit();
    for (auto i = vc.begin(); i != vc.end(); ++i) {
        int output;
        output = binarySearch(vc, 10000000, *i);
        if (output >= 0) 
        {
            cout << "Value " << *i << " located at location " << output << " of vector" << "\n" << endl;
        } 
        else 
        {
            cout << "Value was not located in the array (ERROR)" << endl;
        }
    }



}