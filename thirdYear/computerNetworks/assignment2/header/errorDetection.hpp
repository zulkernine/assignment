#include<string>
#include<vector>
using namespace std;

class CRC{

    static string const polynomial; //  X^16 + X^12 + X^5 + 1

    static string xor1(string a, string b){
        string result = "";

        int n = b.length();
        for (int i = 1; i < n; i++){
            if (a[i] == b[i])
                result += "0";
            else
                result += "1";
        }
        return result;
    }

    // Performs Modulo-2 division
    static string mod2div(string divident, string divisor){
        int pick = divisor.length();
        string tmp = divident.substr(0, pick);

        int n = divident.length();

        while (pick < n){
            if (tmp[0] == '1')
                tmp = xor1(divisor, tmp) + divident[pick];
            else
                tmp = xor1(std::string(pick, '0'), tmp) + divident[pick];

            pick += 1;
        }
        if (tmp[0] == '1')
            tmp = xor1(divisor, tmp);
        else
            tmp = xor1(std::string(pick, '0'), tmp);

        return tmp;
    }

    static string binaryToString(const vector<char> &data){
        string str = "";
        for (char ch : data){
            string format = "00000000";

            for (int i = 0, j = 7;i < sizeof(char) * 8;i++, j--){
                char t = (1) << i;
                if (ch & t){
                    format[j] = '1';
                }
            }
            str+=format;
        }
        return str;
    }

    static vector<char> stringToBinary(const string &str){
        vector<char> bin;
        for (int i = 0;i < str.length();i += 8){
            char ch = 0;
            for (int j = i + 7, k = 0;j >= i;j--, k++){
                if (str[j] - '0'){
                    ch += (1 << k);
                }
            }
            bin.push_back(ch);
        }
        bin.shrink_to_fit();
        return bin;
    }

public:

    static vector<char> encodeData(const vector<char> &bin_data){
        string data = binaryToString(bin_data);
        string divident = data + string(polynomial.length() - 1, '0');
        string remainder = mod2div(divident, polynomial);
        return stringToBinary(data + remainder);
    }

    static bool hasError(const vector<char> &bin_data){
        string data = binaryToString(bin_data);
        string remainder = mod2div(data, polynomial);
        for (char ch : remainder)
            if (ch == '1') return true;

        return false;
    }
};

const string CRC::polynomial = "10001000000100001"; //  X^16 + X^12 + X^5 + 1
