//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    MinHeap heap;
    for (int i = 0; i < nextFree; ++i) heap.push(i);

    if (heap.getSize() == 1) {
        return heap.top();
    }

    int freePtr = nextFree;

    while (heap.getSize() > 1) {
        int x = heap.pop();
        int y = heap.pop();


        int p = freePtr++;
        if (p >= MAX_NODES) {
            cerr << "Error: node limit exceeded.\n";
            exit(1);
        }
        charArr[p] = '\0';
        leftArr[p] = x;
        rightArr[p] = y;
        weightArr[p] = weightArr[x] + weightArr[y];


        heap.push(p);
    }


    return heap.top();
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    if (root < 0) return;

    bool isLeaf = (leftArr[root] == -1 && rightArr[root] == -1);
    if (isLeaf){
        if (charArr[root] >= 'a' && charArr[root] <= 'z')
            codes[charArr[root]] - 'a'] = "0";
return;
    }

    stack<pair<int, string>> st;
    st.push({root, ""});

    while (!st.empty()){
        int node = st.top().first;
        string path = st.top().second;
        st.pop();

        bool leaf = (leftArr[node] == -1 && rightArr[node] == -1);
        if (leaf){
            if (charArr[node] >= 'a' && charArr[node] <= 'z'){
                code[charArr[node] - 'a'] = path;
            }
        } else {
            if (rightArr[node] != -1) st.push({rightArr[node], path + '1'});
            if (leftArr[node] != -1) st.push({leftArr[node], path + '0'});
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}