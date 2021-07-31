#include<iostream>
#include "../header/injecterror.hpp"
#include "../header/errorDetection.hpp"
using namespace std;

int main(){
    string binData = "1110001101000111011010110111100000111111010011001010111110111101";
    int bitFlips;

    //LRC
    string lrcEncoding = LRC::encodeData(binData);
    cout << "LRC encoding: " << lrcEncoding << "\n";
    lrcEncoding = injectErrorRandom(lrcEncoding, bitFlips);
    cout << "Has error: " << LRC::hasError(lrcEncoding) << "\n";

    //VRC
    string vrcEncoding = VRC::encodeData(binData);
    cout << "LRC encoding: " << vrcEncoding << "\n";
    cout << "Has error: " << VRC::hasError(vrcEncoding) << "\n";

    // Checksum
    string checksumEncoding = CheckSum::encodeData(binData);
    cout << "Check sum encoding:   " << checksumEncoding << "\n";
    checksumEncoding = injectErrorRandom(checksumEncoding, bitFlips);
    cout << "Afer injecting error: " << checksumEncoding << "\n";
    cout << "Has error: " << CheckSum::hasError(checksumEncoding) << "\n";

    //CRC
    string crcEncoding = CRC::encodeData(binData);
    cout << "CRC encoding: " << crcEncoding << "\n";
    cout << "Has error: " << CRC::hasError(crcEncoding) << "\n";

}
