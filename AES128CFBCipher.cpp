#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>

using namespace std;

void displayInHEX(const vector<uint8_t>& convertedToUTF8)
{
    for (uint8_t item : convertedToUTF8)
    {
        cout << hex << setfill('0') << setw(2) << static_cast<int>(item) << " ";
    }
    cout << dec;
}

int main()
{
    cout << "Введите текст для шифрования: ";
    string inputFromUser;
    getline(cin, inputFromUser);
    vector<uint8_t> convertedToUTF8;

    for (size_t i = 0; i < inputFromUser.size(); i++)
    {
        convertedToUTF8.push_back(static_cast<uint8_t>(inputFromUser[i]));
    }
    displayInHEX(convertedToUTF8);
    return 0;
}