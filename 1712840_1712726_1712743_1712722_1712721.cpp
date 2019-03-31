#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <vector>

using namespace std;

#define MAX 4
#define BIN_MAX 128

//Số bin cộng 1
string binCong1(string& Q)
{
	string temp = Q;
	//Ý tưởng ta duyệt từ cuối mảng về nếu gặp 1 thì đổi thành 0, nếu gặp 0 thì đổi thành 1 và break
	for (int i = temp.length() - 1; i >= 0; i--)
	{
		if ((temp[i] - 48) == 1)
		{
			temp[i] = 48;
		}
		else
		{
			temp[i] = 49;
			break;
		}
	}
	return temp;
}

//Số bin trừ 1
string binTru1(string& Q)
{
	string temp = Q;
	//Ý tưởng duyệt từ cuối mảng về nếu gặp 0 thì đổi thành 1, nếu gặp 1 thì đổi thành 0 và break
	for (int i = temp.length() - 1; i >= 0; i--)
	{
		if ((temp[i] - 48) == 0)
		{
			temp[i] = 49;
		}
		else
		{
			temp[i] = 48;
			break;
		}
	}
	return temp;
}

//Lấy bù 1 của chuối bin, 0->1 và 1->0
string Bu1(string& Q)
{
	string tmp = Q;
	for (int i = 0; i < tmp.length(); i++)
	{
		if (tmp[i] - 48 == 0)
		{
			tmp[i] = 49;
		}
		else
		{
			tmp[i] = 48;
		}
	}
	return tmp;
}

//Chuyển từ nhị phân sang thập lục phân
string binToHex(string& Q)
{
	string temp = Q;
	string res = "";	//Chuỗi kết quả
	string s = "0123456789ABCDEF"; //Tương ứng 0='0', ..., 10='A' , ..., 15='F'
	int n = temp.length();
	//Ý tưởng là ta sẽ chia ra từng cụm 4 bit để chuyển về Hex
	//Nếu số lượng bit không chia hết cho 4 thì ta thêm bit 0 vào đầu chuỗi
	if (n % 4 != 0)
	{
		temp.insert(0, 4 - n % 4, '0');
	}
	n = temp.length();
	int k = n - 1;
	for (int i = 0; i < n / 4; i++) //Số lần duyệt là n/4
	{
		int t = 0;
		for (int j = 0; j < 4; j++)	//Mỗi lần lấy 4 bit chuyển sang Hex
		{
			t = t | (temp[k] - 48)*(1 << j);
			k--;
		}
		res = s[t] + res;
	}
	while (res[0] == '0') //VD: Khi chuỗi Hex là 0000AF9 thì chuyển thành AF9
	{
		res.erase(0, 1);
	}
	return res;
}

//Cộng 2 số thập phân
string decPlusDec(string& A, string& B)
{
	int na = A.length(); //Độ dài chuỗi A
	int nb = B.length(); //Độ dài chuỗi B
						 //Làm cho độ dài A và B bằng nhau
	if (na > nb)
	{
		B.insert(0, na - nb, '0');
	}
	else if (nb > na)
	{
		A.insert(0, nb - na, '0');
	}
	string res; //Chuỗi kết quả
	int n = A.length(); //n là độ dài 2 chuỗi sau khi làm thành bằng nhau
	int du = 0;
	string s = "0123456789"; //Tương ứng 0='0', ..., 9='9'
							 //Ý tưởng thực hiện phép cộng như sắp phép tính cộng trên giấy cộng tay
	for (int i = n - 1; i >= 0; i--)
	{
		int t = A[i] + B[i] - 2 * 48 + du;
		res = s[t % 10] + res;
		du = t / 10;
	}
	if (du != 0) //Lấy phần dư cuối cùng đưa vào res
	{
		res = s[du % 10] + res;
	}
	int j = res.length();
	if (j == 0)
	{
		res += "0";
	}
	return res;
}

//lấy 1 số thập nhân 2
string decMulTwo(string& Q)
{
	//A x 2 = A + A
	string res = decPlusDec(Q, Q);
	return res;
}

//2^n
string twoPowDec(int x)
{
	string res = "1"; //Giá trị khởi tạo là 1
					  //Ý tưởng 2^2 = ?
					  //a = 1
					  //a = a + a = 2
					  //a = a + a = 2 + 2 = 4 = 2^2
	for (int i = 0; i < x; i++)
	{
		res = decMulTwo(res);
	}
	return res;
}

//Chuyển từ nhị phân sang thập phân
string binToDec(string& Q)
{
	string res = ""; //Chuối kết quả
	int n = Q.length();
	string temp = Q;
	if (Q[0] - 48 != 0)	//Kiểm tra số nhập vào có phải số âm không, nếu âm chuyển sang dạng bù 2
	{
		temp = binTru1(temp);
		temp = Bu1(temp);
	}
	for (int i = 0; i < temp.length(); i++)
	{
		if (temp[temp.length() - i - 1] - 48 == 0)
		{
			continue;
		}
		else
		{
			res = decPlusDec(res, twoPowDec(i));
		}
	}
	if (Q[0] - 48 != 0) //Kiểm tra âm dương để thêm dấu '-'
	{
		res.insert(0, 1, '-');
	}
	int j = res.length();
	if (j == 0)
	{
		res += "0";
	}
	return res;
}

//Chia nguyên số thập phân cho 2
string decDivTwo(string& A)
{
	string res; //Chuỗi kết quả
	string s = "0123456789"; //Tương ứng 0='0', ..., 9='9'
	int du = 0;	//Phần dư
	int temp;
	if (A == "0" || A == "1") //Kiểm tra nếu A = 0 hoặc A = 1 thì kết quả phép chia sẻ bằng 0
	{
		res = "0";
	}
	//Thực hiện phép chia như chia trên giấy
	for (int i = 0; i < A.length(); i++)
	{
		temp = (A[i] - 48) + 10 * du;
		du = temp % 2;
		if (temp / 2 > 0 || i > 0)
		{
			res = res + s[temp / 2];
		}
	}
	return res;
}

//Chuyển từ hệ thập phân sang nhị phân
string decToBin(string& Q)
{
	int dau = 0;	//Lưu dấu của số
	string tmp = Q;
	if (Q[0] == '-')	//Kiểm tra số đó là âm hay dương
	{
		dau = 1;	//Lưu dấu lại
		tmp.erase(0, 1);	//Xóa dấu đi để nó trờ thành số dương
	}
	string res;	//Chuỗi kết quả
	string s = "01";
	while (tmp != "0")
	{
		//Chúng ta xét số cuối cùng của chuỗi số nếu lẻ thì dư là 1 và ngược lại là 0
		res = s[(tmp[tmp.length() - 1] - 48) % 2] + res;
		tmp = decDivTwo(tmp);	//Tìm thương của phép chia
	}
	int n = res.length();
	res.insert(0, BIN_MAX - n, '0');	//Nếu chuỗi kết quả chưa đủ 128 bit thì ta thêm bit 0 vào cho đủ
	if (dau == 1) //nếu số ban đầu là âm thì ta chuyển về dang bù 2 của nó
	{
		res = Bu1(res);
		res = binCong1(res);
	}
	return res;
}

//Chuyển từ thập phân sang nhị phân ở dạng 32 bit
string decToBin_KhongDau32Bit(unsigned int Q)
{

	unsigned int tmp = Q;
	string res;
	string s = "01";
	while (tmp != 0)
	{
		res = s[tmp % 2] + res;
		tmp = tmp / 2;
	}
	int n = res.length();
	res.insert(0, 32 - n, '0');
	return res;
}

//chuyển từ thập phân sang thập lục phân
string decToHex(string& Q)
{
	//Ý tưởng chuyển từ thập phân sang nhị phân sau đó từ nhị phân sang thập lục phân
	string tmp = decToBin(Q);
	string res = binToHex(tmp);
	return res;
}

//Chuyển từ thập lục phân sang nhị phân
string hexToBin(string& Q)
{
	//Ý tưởng chuyển từ số thập lục phân sang nhị phân 4 bit sau đó ghép lại
	string res;
	for (int i = 0; i < Q.length(); i++)
	{
		switch (Q[i])
		{
		case '0': res += "0000"; break;
		case '1': res += "0001"; break;
		case '2': res += "0010"; break;
		case '3': res += "0011"; break;
		case '4': res += "0100"; break;
		case '5': res += "0101"; break;
		case '6': res += "0110"; break;
		case '7': res += "0111"; break;
		case '8': res += "1000"; break;
		case '9': res += "1001"; break;
		case 'A': res += "1010"; break;
		case 'B': res += "1011"; break;
		case 'C': res += "1100"; break;
		case 'D': res += "1101"; break;
		case 'E': res += "1110"; break;
		case 'F': res += "1111"; break;
		}
	}
	int n = res.length();
	res.insert(0, BIN_MAX - n, '0');	//Thêm vào cho đủ 128 bit
	return res;
}

//Khai báo class QInt, các thuộc tính và phương thức
class QInt
{
private:
	unsigned int arrayBits[MAX] = { 0 };	//Sử dụng mảng int không dấu
public:
	QInt();
	QInt(int, string);
	~QInt();
	void ScanQInt(int);	//nhập QInt theo hệ base từ bàn phím
	void PrintQInt(int);	//Xuất QInt theo hệ yêu cầu ra màn hình
	string Print(int);	//Trả ra chuỗi số theo hệ yêu cầu

	QInt& operator+(const QInt&);	//Cộng hai số QInt
	QInt& operator-(const QInt&);	//Trừ hai số QInt
	QInt& operator-();	//Tìm số đối của QInt
	QInt& operator*(const QInt&);	//Tích hai số QInt
	QInt& operator/(const QInt&);	//Thương hai số QInt

	bool operator==(const QInt&);	//So sánh bằng
	bool operator<=(const QInt&);	//So sánh <=
	bool operator>=(const QInt&);	//So sánh >=
	bool operator<(const QInt&);	//So sánh <
	bool operator>(const QInt&);	//So sánh >
	QInt& operator=(const QInt&);	//Phép gán bằng

	QInt& operator&(const QInt&);	//Phép AND
	QInt& operator|(const QInt&);	//Phép OR
	QInt& operator^(const QInt&);	//Phép XOR
	QInt& operator~();	//Phép NOT

	QInt& operator<<(const int);	//Phép dịch trái k bit
	QInt& operator >> (const int);	//Phép dịch phải k bit
	QInt& ROL(const int);	//Phép xoay trái k bit
	QInt& ROR(const int);	//Phép xoay phải k bit
};

//Khởi tạo QInt
QInt::QInt()
{

}

//Khởi tạo có tham số
QInt::QInt(int base, string s) //Truyền vào hệ base và chuỗi số tương ứng
{
	int n = s.length();
	switch (base)
	{
	case 2:	//Nếu là hệ 2 thì chỉ cần thêm đủ bit 0 cho đủ 128 bit
		s.insert(0, BIN_MAX - n, '0');
		break;
	case 10: s = decToBin(s); break; //Nếu là hệ 10 thì chuyển sang hệ 2
	case 16: s = hexToBin(s); break;	//Nếu là hệ 16 thì chuyển sang hệ 2
	}
	//Tách mỗi 32 bit lưu vào arrayBits[i]
	for (int i = s.length() - 1; i >= 0; i--)
	{
		arrayBits[i / 32] = arrayBits[i / 32] | ((s[i] - 48)*(1 << ((BIN_MAX - i - 1) % 32)));
	}
}

//Hàm hủy
QInt::~QInt()
{

}

//Nhập QInt từ bàn phím theo hệ yêu cầu được truyền vào
void QInt::ScanQInt(int x) //Truyền vào hệ x
{
	//Phần bên dưới tương tự như hàm khởi tạo có tham số
	string tmp;
	cin >> tmp;
	int n = tmp.length();
	switch (x)
	{
	case 2:
		tmp.insert(0, BIN_MAX - n, '0');
		break;
	case 10: tmp = decToBin(tmp); break;
	case 16: tmp = hexToBin(tmp); break;
	}
	for (int i = tmp.length() - 1; i >= 0; i--)
	{
		arrayBits[i / 32] = arrayBits[i / 32] | ((tmp[i] - 48)*(1 << ((BIN_MAX - i - 1) % 32)));
	}
}

//Xuất số QInt ra màn hình theo hệ yêu cầu được nhập từ bàn phím
void QInt::PrintQInt(int x)
{
	string res;
	for (int i = 0; i < MAX; i++)
	{
		res = res + decToBin_KhongDau32Bit(arrayBits[i]);
	}
	switch (x)
	{
	case 2:
		while (res[0] == '0')
		{
			int n = res.length();
			if (n == 1)
			{
				break;
			}
			res.erase(0, 1);
		}
		break;
	case 10: res = binToDec(res); break;
	case 16: res = binToHex(res); break;
	}
	cout << res << endl;
}

string QInt::Print(int x)
{
	string res;
	for (int i = 0; i < MAX; i++)
	{
		res = res + decToBin_KhongDau32Bit(arrayBits[i]);
	}
	switch (x)
	{
	case 2:
		while (res[0] == '0')
		{
			int n = res.length();
			if (n == 1)
			{
				break;
			}
			res.erase(0, 1);
		}
		break;
	case 10: res = binToDec(res); break;
	case 16: res = binToHex(res); break;
	}
	return res;
}

//Cộng hai số QInt
QInt & QInt::operator+(const QInt &B)
{
	//Ý tưởng lợi dụng vấn đề tràn bit để thực hiện phép cộng
	QInt *tmp = new QInt;
	int du = 0;	//Ban đầu khởi tạo dư = 0
	for (int i = MAX - 1; i >= 0; i--)
	{
		unsigned int a = this->arrayBits[i];
		unsigned int b = B.arrayBits[i];
		unsigned int c = a + b;
		tmp->arrayBits[i] = c + du;
		unsigned int min;
		if (a < b)
		{
			min = a;
		}
		else
		{
			min = b;
		}
		//Phát hiện tràn bit, nếu tràn bit thì dư = 1
		if (c < min)
		{
			du = 1;
		}
		else
		{
			du = 0;
		}
	}
	return *tmp;
}

//Trừ hai số QInt
QInt & QInt::operator-(const QInt &B)
{
	//Ý tưởng lợi dụng vấn đề tràn bit để thực hiện phép trừ
	QInt *tmp = new QInt;
	int du = 0; //Khởi tạo dư = 0
	for (int i = MAX - 1; i >= 0; i--)
	{
		unsigned int a = this->arrayBits[i];
		unsigned int b = B.arrayBits[i];
		unsigned int c = a - b - du;
		//Phát hiện tràn bit, nếu tràn bit thù dư = 1
		if (a < b)
		{
			du = 1;
		}
		else
		{
			du = 0;
		}
		tmp->arrayBits[i] = c;
	}
	return *tmp;
}

//Tìm số đối của QInt
QInt & QInt::operator-()
{
	QInt* res = new QInt;
	QInt numberOne;
	numberOne.arrayBits[3] = 1;
	*res = ~(*this) + numberOne;
	return *res;
}

//Tích 2 số QInt
QInt & QInt::operator*(const QInt &Q)
{
	QInt* res = new QInt;
	QInt* tmp = new QInt;
	*tmp = *this;
	for (int i = 0; i < BIN_MAX; i++)
	{
		if ((Q.arrayBits[(BIN_MAX - i - 1) / 32] >> (i % 32)) & 1)
		{
			*res = *res + *tmp;
		}
		*tmp = (*tmp) << 1;
	}
	return *res;
}

//Thương 2 số QInt
QInt & QInt::operator/(const QInt &B)
{
	QInt* C = new QInt;
	QInt* tmp = new QInt;
	QInt* tmp1 = new QInt;
	QInt* tmp2 = new QInt;
	*tmp = B;
	int i = BIN_MAX;
	int dau = 0;
	if (this->arrayBits[0] >> 31)
	{
		dau++;
		*this = -(*this);
	}
	if (B.arrayBits[0] >> 31)
	{
		dau++;
		*tmp = -(*tmp);
	}
	while (i)
	{
		*tmp2 = (*this >> (i - 1)) - *tmp1;
		*C = *C << 1;
		if (*tmp2 >= *tmp)
		{
			C->arrayBits[3] = C->arrayBits[3] | 1;
			*tmp1 = *tmp1 + *tmp;
		}
		*tmp1 = *tmp1 << 1;
		i--;
	}
	if (dau % 2 == 0)
	{
		return *C;
	}
	return -(*C);
}

//Phép AND
QInt & QInt::operator&(const QInt &B)
{
	//Ý tưởng ta AND lần lượt các phần tử arrayBits với nhau
	QInt* tmp = new QInt;
	tmp->arrayBits[0] = arrayBits[0] & B.arrayBits[0];
	tmp->arrayBits[1] = arrayBits[1] & B.arrayBits[1];
	tmp->arrayBits[2] = arrayBits[2] & B.arrayBits[2];
	tmp->arrayBits[3] = arrayBits[3] & B.arrayBits[3];
	return *tmp;
}

//Phép OR
QInt & QInt::operator|(const QInt &B)
{
	//Ý tưởng ta OR lần lượt các phần tử arrayBits với nhau
	QInt* tmp = new QInt;
	tmp->arrayBits[0] = arrayBits[0] | B.arrayBits[0];
	tmp->arrayBits[1] = arrayBits[1] | B.arrayBits[1];
	tmp->arrayBits[2] = arrayBits[2] | B.arrayBits[2];
	tmp->arrayBits[3] = arrayBits[3] | B.arrayBits[3];
	return *tmp;
}

//Phép XOR
QInt & QInt::operator^(const QInt &B)
{
	//Ý tưởng ta XOR lần lượt các phần tử arrayBits với nhau
	QInt* tmp = new QInt;
	tmp->arrayBits[0] = arrayBits[0] ^ B.arrayBits[0];
	tmp->arrayBits[1] = arrayBits[1] ^ B.arrayBits[1];
	tmp->arrayBits[2] = arrayBits[2] ^ B.arrayBits[2];
	tmp->arrayBits[3] = arrayBits[3] ^ B.arrayBits[3];
	return *tmp;
}

//Phép NOT
QInt & QInt::operator~()
{
	//Ý tưởng ta NOT lần lượt các phần tử arrayBits
	QInt* tmp = new QInt;
	tmp->arrayBits[0] = ~arrayBits[0];
	tmp->arrayBits[1] = ~arrayBits[1];
	tmp->arrayBits[2] = ~arrayBits[2];
	tmp->arrayBits[3] = ~arrayBits[3];
	return *tmp;
}

//Phép dịch trái k bit
QInt & QInt::operator<<(const int k)
{
	QInt* tmp = new QInt;
	*tmp = *this;
	for (int i = 0; i < k; i++)
	{
		tmp->arrayBits[0] = tmp->arrayBits[0] << 1;
		tmp->arrayBits[0] = tmp->arrayBits[0] | ((tmp->arrayBits[1] >> 31) & 1);
		tmp->arrayBits[1] = tmp->arrayBits[1] << 1;
		tmp->arrayBits[1] = tmp->arrayBits[1] | ((tmp->arrayBits[2] >> 31) & 1);
		tmp->arrayBits[2] = tmp->arrayBits[2] << 1;
		tmp->arrayBits[2] = tmp->arrayBits[2] | ((tmp->arrayBits[3] >> 31) & 1);
		tmp->arrayBits[3] = tmp->arrayBits[3] << 1;
	}
	return *tmp;
}

//Phép dịch phải k bit
QInt & QInt::operator >> (const int k)
{
	QInt* tmp = new QInt;
	*tmp = *this;
	for (int i = 0; i < k; i++)
	{
		tmp->arrayBits[3] = (tmp->arrayBits[3]) >> 1;
		tmp->arrayBits[3] = tmp->arrayBits[3] | ((1 & tmp->arrayBits[2]) << 31);
		tmp->arrayBits[2] = tmp->arrayBits[2] >> 1;
		tmp->arrayBits[2] = tmp->arrayBits[2] | ((1 & tmp->arrayBits[1]) << 31);
		tmp->arrayBits[1] = tmp->arrayBits[1] >> 1;
		tmp->arrayBits[1] = tmp->arrayBits[1] | ((1 & tmp->arrayBits[0]) << 31);
		tmp->arrayBits[0] = tmp->arrayBits[0] >> 1;
	}
	return *tmp;
}

//Phép xoay trái k bit
QInt & QInt::ROL(const int k)
{
	QInt *res = new QInt;
	*res = *this;
	for (int i = 0; i < k; i++)
	{
		unsigned int tmp = (res->arrayBits[0] >> 31) & 1;;
		*res = *res << 1;
		res->arrayBits[3] = res->arrayBits[3] | tmp;
	}
	return *res;
}

//Phép xoay phải k bit
QInt & QInt::ROR(const int k)
{
	QInt *res = new QInt;
	*res = *this;
	for (int i = 0; i < k; i++)
	{
		unsigned int tmp = (res->arrayBits[3]) & 1;
		*res = *res >> 1;
		res->arrayBits[3] = res->arrayBits[3] | (tmp << 31);
	}
	return *res;
}

//So sánh bằng
bool QInt::operator==(const QInt &B)
{
	for (int i = 0; i < MAX; i++)
	{
		if (arrayBits[i] != B.arrayBits[i])
			return false;
	}
	return true;
}

//So sánh <=
bool QInt::operator<=(const QInt &B)
{
	if ((*this < B) || (*this == B))
	{
		return true;
	}
	return false;
}

//So sánh >=
bool QInt::operator>=(const QInt &B)
{
	if ((*this > B) || (*this == B))
	{
		return true;
	}
	return false;
}

//So sánh <
bool QInt::operator<(const QInt &B)
{
	int a = arrayBits[0];
	int b = B.arrayBits[0];
	a = (a >> 31) & 1;
	b = (b >> 31) & 1;
	if (a > b)
	{
		return true;
	}
	else if (a < b)
	{
		return false;
	}
	for (int i = 0; i < MAX; i++)
	{
		if (arrayBits[i] < B.arrayBits[i])
		{
			return true;
		}
		else if (arrayBits[i] == B.arrayBits[i])
		{
			continue;
		}
		return false;
	}
}

//So sánh >
bool QInt::operator>(const QInt &B)
{
	int a = arrayBits[0];
	int b = B.arrayBits[0];
	a = (a >> 31) & 1;
	b = (b >> 31) & 1;
	if (a > b)
	{
		return false;
	}
	else if (a < b)
	{
		return true;
	}
	for (int i = 0; i < MAX; i++)
	{
		if (arrayBits[i] > B.arrayBits[i])
		{
			return true;
		}
		else if (arrayBits[i] == B.arrayBits[i])
		{
			continue;
		}
		return false;
	}
}

//Phép gán bằng
QInt & QInt::operator=(const QInt &B)
{
	for (int i = 0; i < MAX; i++)
	{
		this->arrayBits[i] = B.arrayBits[i];
	}
	return *this;
}

//Hàm đếm số khoảng trắng của 1 chuỗi
int demKhoangTrang(string s)
{
	int d = 0;
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == 32)
		{
			d = d + 1;
		}
	}
	return d;
}

class ChamDong
{
private:
public:
	virtual void Scan(string q);
	virtual void Print();
	ChamDong();
	~ChamDong();
};




class Qfloat :public ChamDong
{
private:
	char x[100000];
public:
	void Scan(string q);
	void Print();
	void PrintQfloat();
	void DecToBin();
	char getx(int n);
	void setarr(char u, char v[], char z[]);
	Qfloat();
	~Qfloat();
};
void ChamDong::Scan(string q)
{
}

void ChamDong::Print()
{
}

ChamDong::ChamDong()
{
}


ChamDong::~ChamDong()
{
}

class Bit : public ChamDong
{
private:
	bool bit[128] = { 0 };
public:
	void Scan(string q);
	void Print();
	void PrintBit();
	void BinToDec();
	bool getbit(int n);
	void set(int n, int x);
	Bit();
	~Bit();
};
// đọc vô mảng bit
void Bit::Scan(string q)
{
	ChamDong::Scan(q);
	for (int i = 0; i < q.length(); i++)
	{
		bit[i] = q[i] - 48;
	}
	for (int i = q.length(); i < 128; i++)
	{
		bit[i] = 0;
	}
}
//int bit
void Bit::Print()
{
	ChamDong::Print();
	BinToDec();
}
// Kiểm tra mảng
bool KT(bool bit[], int start, int end, int gt)
{
	for (int i = start; i <= end; i++)
	{
		if (bit[i] != gt)
		{
			return false;
		}
	}
	return true;
}
//in bit
void Bit::PrintBit()
{
	cout << bit[0] << " ";
	for (int i = 1; i <= 15; i++)
	{
		cout << bit[i];
	}
	cout << " ";
	for (int i = 16; i < 128; i++)
	{
		cout << bit[i];
	}
	cout << endl;
}
//lấy giá trị bit
bool Bit::getbit(int n)
{
	return bit[n];
}
//thay đổi giá trị mảng bin
void Bit::set(int n, int x)
{
	bit[n] = x;
}
//tính 2^n
int Pow(int n)
{
	int luythua = 1;
	for (int i = 0; i < n; i++)
	{
		luythua *= 2;
	}
	return luythua;
}
// sủa mảng thêm 1 vào đầu mảng
void Sua(char v[])
{
	int n;
	for (int i = 0;; i++)
	{
		if (v[i] == '\0')
		{
			n = i;
			break;
		}
	}
	for (int i = n; i > 0; i--)
	{
		v[i] = v[i - 1];
	}
	v[n + 1] = '\0';
	v[0] = '1';
}
//nhân 2 mảng
void mul2(char v[], int c)
{
	v[0] += (v[0] - 48);
	if (v[0] > 57)
	{
		v[0] -= 10;
		Sua(v);
		for (int i = 2; i < 20000; i++)
		{
			if (v[i] != '\0')
			{
				v[i] += (v[i] - 48);
				if (v[i] > 57)
				{
					v[i] -= 10;
					v[i - 1] += 1;
				}
			}
			else
			{
				v[i - 1] += c;
				break;
			}
		}
	}
	else {
		for (int i = 1; i < 20000; i++)
		{
			if (v[i] != '\0')
			{
				v[i] += (v[i] - 48);
				if (v[i] > 57)
				{
					v[i] -= 10;
					v[i - 1] += 1;
				}
			}
			else
			{
				v[i - 1] += c;
				break;
			}
		}
	}
}
//chia 2 mảng
void div2(char v[], int c)
{
	for (int i = 0; i < 200000; i++)
	{
		if (v[i] != '\0')
		{
			int a = (v[i] - 48) % 2;
			v[i] -= (v[i] - 48) / 2 + a;
			if (a == 1)
			{
				if (v[i + 1] != '\0')
					v[i + 1] += 10;
				else
				{
					v[i + 1] = '5';
					v[i + 2] = '\0';
					break;
				}
			}
		}
	}
	v[0] += c * 5;
}


void Bit::BinToDec()
{
	if ((KT(bit, 1, 15, 0) && KT(bit, 16, 127, 0)) || KT(bit, 1, 15, 1))
	{
		if (KT(bit, 1, 15, 0) && KT(bit, 16, 127, 0) && bit[0] == 1)
			cout << "-0" << endl;
		if (KT(bit, 1, 15, 0) && KT(bit, 16, 127, 0) && bit[0] == 0)
			cout << "+0" << endl;
		if (KT(bit, 1, 15, 1) && KT(bit, 16, 127, 0) && bit[0] == 1)
			cout << "am vo cung" << endl;
		if (KT(bit, 1, 15, 1) && KT(bit, 16, 127, 1) && bit[0] == 0)
			cout << "duong vo cung" << endl;
		if (KT(bit, 1, 15, 1) && !KT(bit, 16, 127, 0))
			cout << "NAN" << endl;
	}
	else {
		Qfloat x;
		char u, v[20000], z[20000];

		if (bit[0] == 0) {
			u = '+';
		}
		if (bit[0] == 1) {
			u = '-';
		}
		int t = 0;
		for (int i = 1; i <= 15; i++)
		{
			t += bit[i] * Pow(15 - i);
		}
		t -= 16383;
		v[0] = '0';
		v[1] = '\0';
		z[0] = '0';
		z[1] = '\0';
		int k;
		for (int i = 127;; i--)
		{
			if (bit[i] == 1)
			{
				k = i;
				break;
			}
			if (i == 16)
			{
				k = 15;
				break;
			}
		}
		if (t >= 0) {
			v[0] = '1';
			v[1] = '\0';
			for (int i = 16; i < t + 16; i++)
			{
				int c = 0;
				if (i<127)
				{
					c = bit[i];
				}
				mul2(v, c);
			}
			if (k >= t + 16)
			{
				z[0] = '5';
				z[1] = '\0';
				for (int i = k - 1; i >= t + 16; i--)
				{
					int c = 0;
					if (bit[i] == 1)
					{
						c = 1;
					}
					div2(z, c);
				}
			}
		}
		else {
			z[0] = '5';
			z[1] = '\0';
			for (int i = k - 1; i >= 16; i--)
			{
				int c = 0;
				if (bit[i] == 1)
				{
					c = 1;
				}
				div2(z, c);
			}
			div2(z, 1);
			for (int i = 0; i < abs(t) - 1; i++)
			{
				div2(z, 0);
			}
		}
		x.setarr(u, v, z);
		x.PrintQfloat();
	}
}

Bit::Bit()
{
}
Bit::~Bit()
{
}
//đọc dec
void Qfloat::Scan(string q)
{
	ChamDong::Scan(q);
	for (int i = 0; i < q.length(); i++)
	{
		x[i] = q[i];
	}
	x[q.length()] = '\0';
}
//chuyển số chấm động sang bin và in
void Qfloat::Print()
{
	ChamDong::Print();
	DecToBin();
}
//in mảng
void Qfloat::PrintQfloat()
{
	if (x[0] != '+')
		cout << x[0];
	for (int i = 1; i < 100000; i++)
	{
		if (x[i] == '\0')
			break;
		cout << x[i];
	}
	cout << endl;
}
// lấy giá trị mảng
char Qfloat::getx(int n)
{
	return x[n];
}
// nối mảng
void Qfloat::setarr(char u, char v[], char z[])
{
	x[0] = u;
	int n;
	for (int i = 1; i < 100000; i++)
	{
		x[i] = v[i - 1];
		if (v[i] == '\0') {
			n = i + 1;
			break;
		}

	}
	x[n] = '.';
	for (int i = n + 1; i < 100000; i++)
	{
		x[i] = z[i - n - 1];
		if (z[i - n - 1] == '\0')
			break;
	}
}
// Tách số chấm động theo từng phần dấu phần nguyên và phần số phẩy
void Tach(char x[], int& u, char v[], char z[])
{
	if (x[0] == '-' || x[0] == '+')
	{
		if (x[0] == '-')
			u = 1;
		else
			u = 0;
		int n = 100000;
		for (int i = 1; i<100000; i++)
		{
			if (x[i] != '.' && x[i] != '\0')
			{
				v[i - 1] = x[i];
			}
			else
			{
				v[i - 1] = '\0';
				if (x[i] == '\0')
				{
					z[0] = '0';
					z[1] = '\0';
					return;
				}
				else
				{
					n = i + 1;
					break;
				}
			}
		}
		for (int i = n; i<100000; i++)
		{
			if (x[i] != '\0')
			{
				z[i - n] = x[i];
			}
			else {
				z[i - n] = '\0';
				break;
			}
		}
	}
	else
	{
		u = 0;
		int n;
		for (int i = 0;; i++)
		{
			if (x[i] != '.' && x[i] != '\0')
			{
				v[i] = x[i];
			}
			else
			{
				v[i] = '\0';
				if (x[i] == '\0')
				{
					z[0] = '0';
					z[1] = '\0';
					return;
				}
				else
				{
					n = i + 1;
					break;
				}
			}
		}
		for (int i = n; i<100000; i++)
		{
			if (x[i] != '\0')
			{
				z[i - n] = x[i];
			}
			else {
				z[i - n] = '\0';
				break;
			}
		}
	}
}
// xóa đầu mảng
void delFirst(char v[])
{
	for (int i = 0;; i++)
	{
		v[i] = v[i + 1];
		if (v[i + 1] == '\0')
			break;
	}
}
// xóa cuối mảng
void delLast(char v[])
{
	if (v[0] != '\0') {
		for (int i = 1;; i++)
		{
			if (v[i] == '\0')
			{
				v[i - 1] = '\0';
				break;
			}
		}
	}
}
//chia 2 mảng trả về số dư
int div(char v[])
{
	int a;
	for (int i = 0; i < 100000; i++)
	{
		if (v[i] != '\0')
		{
			a = (v[i] - 48) % 2;
			v[i] -= (v[i] - 48) / 2 + a;
			if (a == 1)
			{
				if (v[i + 1] != '\0')
					v[i + 1] += 10;
				else
				{
					break;
				}
			}
		}
		else {
			break;
		}
	}
	while (v[0] == '0')
		delFirst(v);
	return a;
}
// nhân 2 mảng
int mul(char v[])
{
	int a = 0;
	v[0] += (v[0] - 48);
	if (v[0] > 57)
	{
		a = 1;
		v[0] -= 10;
	}
	for (int i = 1; i < 100000; i++)
	{
		if (v[i] != '\0')
		{
			v[i] += (v[i] - 48);
			if (v[i] > 57)
			{
				v[i] -= 10;
				v[i - 1] += 1;
			}
		}
		else
		{
			if (v[i - 1] == '0')
				delLast(v);
			break;
		}
	}
	return a;
}
//thêm vào cuối mảng
void addFirst(char v[], int a)
{
	int n;
	for (int i = 0;; i++)
	{
		if (v[i] == '\0')
		{
			n = i;
			break;
		}
	}
	for (int i = n; i >= 1; i--)
	{
		v[i] = v[i - 1];
	}
	v[n + 1] = '\0';
	v[0] = a + 48;
}
// chuyển phần nguyên về bin
void ToBin1(char v[])
{
	char u[100000];
	u[0] = '\0';
	int a;
	int t = 0;
	while (v[0] != '\0')
	{
		a = div(v);
		t++;
		addFirst(u, a);
	}
	for (int i = 0; i < 100000; i++)
	{
		v[i] = u[i];
		if (u[i] == '\0')
			break;
	}
}
// thêm vào cuối mảng
void addLast(char v[], int a)
{
	for (int i = 0;; i++)
	{
		if (v[i] == '\0')
		{
			v[i] = 48 + a;
			v[i + 1] = '\0';
			break;
		}
	}
}
// chuyển từ số phẩy sang số bin
void ToBin2(char v[])
{
	char u[100000];
	u[0] = '\0';
	int a;
	int t = 0;
	while (v[0] != '\0' && t != 10000)
	{
		a = mul(v);
		t++;
		addLast(u, a);
	}
	for (int i = 0; i < 100000; i++)
	{
		v[i] = u[i];
		if (u[i] == '\0')
			break;
	}
}

void Qfloat::DecToBin()
{
	Bit a;
	int u = 1;
	char v[100000];
	char z[100000];
	Tach(x, u, v, z);
	if (v[0] == '0' && ((z[0] == '0' && z[1] == '\0') || z[0] == '\0'))
	{
		a.set(0, u);
		for (int i = 1; i < 128; i++)
		{
			a.set(i, 0);
		}
	}
	else
	{
		ToBin1(v);
		ToBin2(z);
		int n = 16383;
		int p[15] = { 0 };
		if (v[0] != '0')
		{
			for (int i = 0; ; i++)
			{
				if (v[i] == '\0')
				{
					n = n + i - 1;
					break;
				}
			}
			int i = 14;
			while (n > 0)
			{
				p[i] = n % 2;
				n /= 2;
				i--;
			}
			int b;
			a.set(0, u);
			for (int i = 1; i < 16; i++)
			{
				a.set(i, p[i - 1]);
			}
			for (int i = 16; i < 128; i++)
			{
				if (v[i - 15] != '\0')
				{
					a.set(i, v[i - 15] - 48);
				}
				else
				{
					b = i;
					break;
				}
			}
			for (int i = b; i < 128; i++)
			{
				if (z[i - b] == '\0')
				{
					break;
				}
				else
				{
					a.set(i, z[i - b] - 48);
				}
			}
		}
		else
		{
			for (int i = 0;; i++)
			{
				if (z[i] == '1')
				{
					n = n - i - 1;
					break;
				}
				if (z[i] == '\0')
				{
					break;
				}
			}
			int d = 16383 - n;
			int i = 14;
			while (n > 0)
			{
				p[i] = n % 2;
				n /= 2;
				i--;
			}
			int b;
			a.set(0, u);
			for (int i = 1; i < 16; i++)
			{
				a.set(i, p[i - 1]);
			}
			for (int i = 16; i < 128; i++)
			{
				if (z[i + d - 16] == '\0')
				{
					a.set(i, 0);
					break;
				}
				else
				{
					a.set(i, z[i + d - 16] - 48);
				}
			}
		}
	}
	a.PrintBit();
}

Qfloat::Qfloat()
{
}


Qfloat::~Qfloat()
{
}

int main(int mun, char**arg)
{
	if (strcmp(arg[3], "QInt") == 0)
	{
		int dem = 0;
		vector<string>kq; //Chứa chuỗi kết quả sẽ xuất ra file output
		string tmp;
		while (!cin.eof())	//Đọc đến cuối file
		{
			freopen(arg[1], "rt", stdin);	//Mở file để đọc
			cin.seekg(dem, ios::cur);
			getline(cin, tmp);	//Đọc vào chuỗi tmp từng dòng để xét xem dòng đó đang thực hiện phép tính gì
			dem += tmp.length() + 2;
			int n = tmp.length();
			cin.seekg(-(n + 2), ios::cur);
			int t = demKhoangTrang(tmp);	//Đếm số khoảng trắng của tmp để xét trường hợp
			if (t == 2)	//t = 2 chuyền từ hệ A sang hệ B và phép NOT (~)
			{
				int base1, base2;
				string s1, s2;
				cin >> base1 >> s1;
				if (s1 == "~")
				{
					cin >> s2;
					QInt A(base1, s2);
					A = ~A;
					kq.push_back(A.Print(base1));
				}
				else {
					int j = s1.length();
					cin.seekg(-j, ios::cur);
					cin >> base2 >> s2;
					QInt A(base1, s2);
					kq.push_back(A.Print(base2));
				}
			}
			//Ngược lại  t= 3 sẽ các phép toán: +, -, *, / , &, |, , ^, >, >=, <, <=, ==
			//Đặc biệt với các kiểu so sánh thì dữ liệu trả về là YES nếu so sánh đúng
			// là No nếu só sánh sai
			else
			{
				int base, k;
				string st1, st2, st3;
				cin >> base >> st1 >> st2;
				QInt A(base, st1);
				QInt res;
				if (st2 == "+")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A + B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "-")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A - B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "*")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A * B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "/")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A / B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "&")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A & B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "|")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A | B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "^")
				{
					cin >> st3;
					QInt B(base, st3);
					res = A ^ B;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "<<")
				{
					cin >> k;
					res = A << k;
					kq.push_back(res.Print(base));
				}
				else if (st2 == ">>")
				{
					cin >> k;
					res = A >> k;
					kq.push_back(res.Print(base));
				}
				else if (st2 == "ROL")
				{
					cin >> k;
					res = A.ROL(k);
					kq.push_back(res.Print(base));
				}
				else if (st2 == "ROR")
				{
					cin >> k;
					res = A.ROR(k);
					kq.push_back(res.Print(base));
				}
				else if (st2 == ">")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A > B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
				else if (st2 == "<")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A < B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
				else if (st2 == ">=")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A >= B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
				else if (st2 == "<=")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A <= B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
				else if (st2 == "==")
				{
					cin >> st3;
					QInt B(base, st3);
					if (A == B)
					{
						kq.push_back("YES");
					}
					else
					{
						kq.push_back("NO");
					}
				}
			}
		}
		freopen(arg[2], "wt", stdout);
		for (int i = 0; i < kq.size(); i++)
		{
			cout << kq[i] << endl;
		}
	}
	else
	{
		vector <ChamDong*> a;
		FILE* ps;
		ps = freopen(arg[1], "rt", stdin);
		ChamDong* temp;
		while (!cin.eof())
		{
			int b, c;
			cin >> b;
			cin >> c;
			string q;
			cin >> q;
			if (b == 2 && c == 10)
			{
				temp = new Bit;
				temp->Scan(q);
				a.push_back(temp);
			}
			else
			{
				temp = new Qfloat;
				temp->Scan(q);
				a.push_back(temp);
			}
		}
		ps = freopen(arg[2], "wt", stdout);
		for (int i = 0; i < a.size(); i++)
		{
			a[i]->Print();
		}
		for (ChamDong* &temp : a)
		{
			delete temp;
		}
	}
	return 0;
}