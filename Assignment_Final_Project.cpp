#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <bitset>
#include <fstream>
#include <cstdint>
#include <algorithm>

using namespace std;

// Defining initial hash values (first 32 bits of square roots of primes 2-19)
uint32_t hashValues[] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };

// Defining SHA-256 round constants (first 32 bits of cube roots of primes 2-311)
const uint32_t roundConstants[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Macros for bitwise operations used in SHA-256
#define rotate_right(x, n) ((x >> n) | (x << (32 - n)))
#define CHOOSE(x, y, z) ((x & y) ^ (~x & z))
#define MAJORITY(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SIGMA0(x) (rotate_right(x, 2) ^ rotate_right(x, 13) ^ rotate_right(x, 22))
#define SIGMA1(x) (rotate_right(x, 6) ^ rotate_right(x, 11) ^ rotate_right(x, 25))
#define sigma0(x) (rotate_right(x, 7) ^ rotate_right(x, 18) ^ (x >> 3))
#define sigma1(x) (rotate_right(x, 17) ^ rotate_right(x, 19) ^ (x >> 10))

// Function to read the input file into a string
string loadFile(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        exit(1);
    }
    return string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
}

// Function to compute the SHA-256 hash of a given text
string computeSha256(const string &inputText) {
    uint32_t hashState[8];
    copy(begin(hashValues), end(hashValues), hashState);
    
    vector<uint8_t> data(inputText.begin(), inputText.end());
    uint64_t messageBitLength = inputText.size() * 8;
    data.push_back(0x80);
    
    while ((data.size() % 64) != 56) data.push_back(0x00);
    
    for (int i = 7; i >= 0; --i)
        data.push_back((messageBitLength >> (i * 8)) & 0xFF);
    
    for (size_t i = 0; i < data.size(); i += 64)
        ; // SHA-256 compression function should be applied here
    
    ostringstream hashOutput;
    for (uint32_t val : hashState)
        hashOutput << hex << setfill('0') << setw(8) << val;
    
    return hashOutput.str();
}

// Main function
int main() {
    // Load text from file
    string textData = loadFile("The_book_of_Mark.txt");
    
    // Display the original text
    cout << "Showing the text of The Boook of Mark:" << textData << endl;
    
    // Compute and display SHA-256 hash
    cout << "SHA-256 Hash of The Book of Mark: " << computeSha256(textData) << endl;
    return 0;
}