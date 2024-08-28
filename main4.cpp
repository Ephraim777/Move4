#include <iostream>
#include <string>
#include <algorithm>

class big_integer {
    std::string str;

public:
    big_integer(std::string val) : str(std::move(val)) {}

    big_integer(const big_integer& val) : str(val.str) {}

    big_integer(big_integer&& val) noexcept : str(std::move(val.str)) {}

    big_integer& operator=(const big_integer& val) {
        if (this != &val) {
            str = val.str;
        }
        return *this;
    }

    big_integer& operator=(big_integer&& val) noexcept {
        if (this != &val) {
            str = std::move(val.str);
        }
        return *this;
    }

    big_integer operator+(const big_integer& val) const {
        std::string result;
        int index1 = str.size() - 1;
        int index2 = val.str.size() - 1;
        int carry = 0;

        while (index1 >= 0 || index2 >= 0 || carry) {
            int sum = carry;

            if (index1 >= 0) {
                sum += str[index1] - '0';
                index1--;
            }

            if (index2 >= 0) {
                sum += val.str[index2] - '0';
                index2--;
            }

            result.push_back((sum % 10) + '0');
            carry = sum / 10;
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    big_integer operator*(const big_integer& val) const {
        long long temp = std::stoll(str);
        long long temp1 = std::stoll(val.str);
        long long temp2 = temp * temp1;
        return big_integer(std::to_string(temp2));
    }

    big_integer operator*(const int val) const {
        long long temp = std::stoll(str);
        long long temp2 = temp * val;
        return big_integer(std::to_string(temp2));
    }

    friend std::ostream& operator<<(std::ostream& ex, const big_integer& obj) {
        ex << obj.str;
        return ex;
    }
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl; // 193099
    
    return 0;
}