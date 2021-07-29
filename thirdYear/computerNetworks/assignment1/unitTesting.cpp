#include<iostream>
#include "errorDetection.hpp"
#include "injecterror.hpp"
using namespace std;

int main(){
    string binData = "1110001101000111011010110111100000111111010011001010111110111101";

    //LRC
    string lrcEncoding = LRC::encodeData(binData);
    cout << "LRC encoding: " << lrcEncoding << "\n";
    lrcEncoding = injectError(lrcEncoding);
    cout << "Has error: " << LRC::hasError(lrcEncoding) << "\n";

    //VRC
    string vrcEncoding = VRC::encodeData(binData);
    cout << "LRC encoding: " << vrcEncoding << "\n";
    cout << "Has error: " << VRC::hasError(vrcEncoding) << "\n";

    // Checksum
    string checksumEncoding = CheckSum::encodeData(binData);
    cout << "Check sum encoding:   " << checksumEncoding << "\n";
    checksumEncoding = injectError(checksumEncoding);
    cout << "Afer injecting error: " << checksumEncoding << "\n";
    cout << "Has error: " << CheckSum::hasError(checksumEncoding) << "\n";

    //CRC
    string crcEncoding = CRC::encodeData(binData);
    cout << "CRC encoding: " << crcEncoding << "\n";
    cout << "Has error: " << CRC::hasError(crcEncoding) << "\n";

}
