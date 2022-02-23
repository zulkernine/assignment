#include<string>
using namespace std;

class VRC{
public:
    //Even parity
    static string encodeData(string data){
        int count = 0;
        for(char ch : data)
            if(ch == '1')
                count++;
        if(count%2) return (data + "1");
        else return (data+"0");
    }
    
    //check for even parity
    static bool hasError(string data){
        int count = 0;
        for (char ch : data)
            if (ch == '1')
                count++;
        return count%2 ;
    }
};

class LRC{
public:
    //Divide data in 4 group, Asumption: data length is multiple of 4
    static string encodeData(string data){
        if(data.length()%4 != 0){
            throw string("INVALID data for LRC: data length must be multiple of 4");
        }

        int k = data.length()/4 ;
        string parityRow="";

        for(int i=0;i<k;i++){
            int count = 0;
            for(int j=0;j<4;j++)
                if(data[j*k + i] == '1') count++;
            if(count%2) parityRow += "1";
            else parityRow += "0";
        }
        data += parityRow;
        return data;
    }

    //Divide data in 5 group, Asumption: data length is multiple of 5
    static bool hasError(string data){
        if (data.length() % 5 != 0){
            return true;
        }

        int k = data.length() / 5;

        for (int i = 0;i < k;i++){
            int count = 0;
            for (int j = 0;j < 5;j++)
                if (data[j * k + i] == '1') count++;
            if (count % 2) return true;
        }
        return false;
    }
};

class CheckSum{
    const static int frameLength=16;

    static string complement(string data){
        for(int i=0;i<data.length();i++){
            if(data[i]=='0') data[i] = '1';
            else data[i] = '0';
        }
        return data;
    }

    // Assumption: Both the string have length = frameLength
    static string sum(string s1,string s2){
        string result;
        result.resize(frameLength);
        int carry = 0;
        for(int i = frameLength-1; i>=0;i--){
            int n;
            n = (s1[i] - '0') + (s2[i] - '0') + carry;
            switch(n){
                case 0:break;
                case 1:{
                    n = 1;
                    carry = 0;
                }break;
                case 2:{
                    n = 0;
                    carry = 1;
                }break;
                case 3:{
                    n = 1;
                    carry = 1;
                }break;
            }
            result[i] = '0' + n;
        }
        if(carry){
            string c = "";
            for(int i=0;i<frameLength-1;i++) c += '0';
            c += '1';
            return sum(c,result);
        }else
            return result;
    }
public:
    static string encodeData(string data){
        if(data.length()%frameLength != 0){
            throw string("NOT compatible with ChekcSum encoding!");
        }

        string padding = data.substr(0,frameLength);

        for(int i=1;i*frameLength < data.length(); i++)
            padding = sum(padding,data.substr(i*frameLength , frameLength));

        data += complement(padding);
        return data;
    }

    static bool hasError(string data){
        if (data.length() % frameLength != 0){
            throw string("NOT compatible with ChekcSum encoding!");
        }

        string padding = data.substr(0, frameLength);

        for (int i = 1;i * frameLength < data.length(); i++)
            padding = sum(padding, data.substr(i * frameLength, frameLength));

        padding = complement(padding);
        for(char ch : padding)
            if(ch == '1') return true;
        
        return false;
    }
};

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

public:
    static string encodeData(string data){
        string divident = data + string(polynomial.length() - 1, '0');
        string remainder = mod2div(divident,polynomial);
        return (data+remainder) ;
    }

    static bool hasError(string data){
        string remainder = mod2div(data,polynomial);
        for(char ch:remainder)
            if(ch == '1') return true;
        
        return false;
    }
};

const string CRC::polynomial = "10001000000100001" ; //  X^16 + X^12 + X^5 + 1
