#include "MyStr.h"

#pragma warning(disable : 6386)  // buffer overrun warning
#pragma warning(disable : 6385)  // invalid data read warning
#pragma warning(disable : 4244)  // conversion possible loss of data
#pragma warning(disable : 4267)  // conversion from size_t to int

// ========================= CONSTRUCTORS =========================

MyStr::MyStr()
{
    this->str = nullptr;
    this->length = 0;
}

MyStr::MyStr(const char ch)
{
    this->length = 1;
    this->str = new char[length + 1];
    this->str[0] = ch;
    this->str[1] = '\0';
}

MyStr::MyStr(const char* str)
{
    try
    {
        if (str == nullptr)
            throw "MyStr(const char*): null pointer passed!";

        this->length = 0;
        while (str[length] != '\0')
            length++;
        this->str = new char[length + 1];
        for (int i = 0; i < length; i++)
            this->str[i] = str[i];
        this->str[length] = '\0';
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        this->str = nullptr;
        this->length = 0;
    }
}

MyStr::MyStr(int n, char ch)
{
    try
    {
        if (n <= 0)
            throw "MyStr(int,char): size must be greater than 0!";

        this->length = n;
        this->str = new char[length + 1];
        for (int i = 0; i < n; i++)
            this->str[i] = ch;
        this->str[length] = '\0';
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        this->str = nullptr;
        this->length = 0;
    }
}

MyStr::MyStr(int n)
{
    if (n == 0)
    {
        this->length = 1;
        this->str = new char[2];
        this->str[0] = '0';
        this->str[1] = '\0';
        return;
    }
    bool negative = (n < 0);
    int  absN = negative ? -n : n;
    int digits = 0;
    int temp = absN;
    while (temp > 0) { temp /= 10; digits++; }
    this->length = digits + (negative ? 1 : 0);
    this->str = new char[this->length + 1];
    int i = this->length - 1;
    while (absN > 0)
    {
        this->str[i--] = (absN % 10) + '0';
        absN /= 10;
    }
    if (negative) this->str[0] = '-';
    this->str[this->length] = '\0';
}

MyStr::MyStr(const MyStr& other)
{
    this->length = other.length;
    this->str = new char[this->length + 1];
    for (int i = 0; i < length; i++)
        this->str[i] = other.str[i];
    this->str[length] = '\0';
}

MyStr::~MyStr()
{
    this->length = 0;
    delete[] this->str;
    this->str = nullptr;
}

// ========================= ASSIGNMENT =========================

MyStr& MyStr::operator=(const MyStr& other)
{
    if (this != &other)
    {
        delete[] this->str;
        this->length = other.length;
        this->str = new char[this->length + 1];
        for (int i = 0; i < this->length; i++)
            this->str[i] = other.str[i];
        this->str[length] = '\0';
    }
    return *this;
}

// ========================= ELEMENT ACCESS =========================

char& MyStr::at(int pos)
{
    try
    {
        if (pos < 0 || pos >= length)
            throw "at(): index out of bounds!";
        return this->str[pos];
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        static char dummy = '\0';
        return dummy;
    }
}

const char& MyStr::at(int pos) const
{
    try
    {
        if (pos < 0 || pos >= length)
            throw "at(): index out of bounds!";
        return this->str[pos];
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        static char dummy = '\0';
        return dummy;
    }
}

char& MyStr::operator[](int pos)
{
    try
    {
        if (pos < 0 || pos >= this->length)
            throw "operator[]: index out of bounds!";
        return this->str[pos];
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        static char dummy = '\0';
        return dummy;
    }
}

const char& MyStr::operator[](int pos) const
{
    try
    {
        if (pos < 0 || pos >= this->length)
            throw "operator[]: index out of bounds!";
        return this->str[pos];
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        static char dummy = '\0';
        return dummy;
    }
}

char& MyStr::front()
{
    try
    {
        if (this->length == 0 || this->str == nullptr)
            throw "front(): called on empty string!";
        return this->str[0];
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        static char dummy = '\0';
        return dummy;
    }
}

char& MyStr::back()
{
    try
    {
        if (this->length == 0 || this->str == nullptr)
            throw "back(): called on empty string!";
        return this->str[this->length - 1];
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        static char dummy = '\0';
        return dummy;
    }
}

const char* MyStr::c_str() const
{
    try
    {
        if (this->str == nullptr)
            throw "c_str(): string is null!";
        return this->str;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        return "";
    }
}

// ========================= CAPACITY =========================

bool MyStr::empty() const { return (this->length == 0); }
int  MyStr::size()  const { return this->length; }
int  MyStr::Length() { return this->length; }
int  MyStr::max_size() { return 99999; }
int  MyStr::capacity() { return this->length; }

void MyStr::reserve(int n)
{
    try
    {
        if (n < 0)
            throw "reserve(): size cannot be negative!";
        if (n < this->length) return;

        MyStr temp;
        temp.length = n;
        temp.str = new char[temp.length + 1];
        for (int i = 0; i < this->length; i++)
            temp.str[i] = this->str[i];
        for (int i = this->length; i < temp.length; i++)
            temp.str[i] = '0';
        temp.str[temp.length] = '\0';
        *this = temp;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
}

void MyStr::shrink_to_fit()
{
    char* temp = new char[length + 1];
    for (int i = 0; i < length; i++)
        temp[i] = str[i];
    temp[length] = '\0';
    delete[] str;
    str = temp;
}

void MyStr::resize(int newSize, char ch)
{
    try
    {
        if (newSize < 0)
            throw "resize(): size cannot be negative!";

        if (newSize > this->length)
        {
            char* temp = new char[newSize + 1];
            int i = 0;
            for (i = 0; i < this->length; i++)
                temp[i] = this->str[i];
            while (i < newSize)
                temp[i++] = ch;
            temp[newSize] = '\0';
            delete[] this->str;
            this->str = temp;
            this->length = newSize;
        }
        else
        {
            this->length = newSize;
            this->str[this->length] = '\0';
        }
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
}

// ========================= MODIFIERS =========================

MyStr& MyStr::insert(int pos, const char ch)
{
    try
    {
        if (pos < 0 || pos > this->length)
            throw "insert(): position out of bounds!";

        MyStr temp;
        temp.length = this->length + 1;
        temp.str = new char[temp.length + 1];
        for (int i = 0; i < pos; i++)
            temp.str[i] = this->str[i];
        temp.str[pos] = ch;
        for (int i = pos + 1; i < temp.length; i++)
            temp.str[i] = this->str[i - 1];
        temp.str[temp.length] = '\0';
        *this = temp;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
    return *this;
}

MyStr& MyStr::insert(int pos, const char* first)
{
    try
    {
        if (first == nullptr)
            throw "insert(): null pointer passed!";
        if (pos < 0 || pos > this->length)
            throw "insert(): position out of bounds!";

        int l = 0;
        while (first[l] != '\0') l++;
        MyStr temp;
        temp.length = this->length + l;
        temp.str = new char[temp.length + 1];
        int i = 0;
        for (int j = 0; j < pos; j++)  temp.str[i++] = this->str[j];
        for (int j = 0; j < l; j++)    temp.str[i++] = first[j];
        for (int j = pos; j < this->length; j++) temp.str[i++] = this->str[j];
        temp.str[temp.length] = '\0';
        *this = temp;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
    return *this;
}

MyStr& MyStr::insert_range(int pos, const char* first, const char* last)
{
    try
    {
        if (first == nullptr || last == nullptr)
            throw "insert_range(): null pointer passed!";
        if (pos < 0 || pos > length)
            throw "insert_range(): position out of bounds!";
        if (last < first)
            throw "insert_range(): last is before first!";

        int len = last - first;
        if (len <= 0) return *this;
        MyStr temp;
        temp.length = this->length + len;
        temp.str = new char[temp.length + 1];
        int i = 0;
        for (int j = 0; j < pos; j++)           temp.str[i++] = this->str[j];
        for (int j = 0; j < len; j++)           temp.str[i++] = first[j];
        for (int j = pos; j < this->length; j++) temp.str[i++] = this->str[j];
        temp.str[temp.length] = '\0';
        *this = temp;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
    return *this;
}

MyStr& MyStr::erase(int pos, int count)
{
    try
    {
        if (pos < 0 || pos > this->length)
            throw "erase(): position out of bounds!";
        if (count < 0)
            throw "erase(): count cannot be negative!";

        if (pos + count > this->length)
            count = this->length - pos;
        int i = pos;
        while (i + count < this->length)
        {
            this->str[i] = this->str[i + count];
            i++;
        }
        length -= count;
        str[length] = '\0';
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
    return *this;
}

MyStr& MyStr::assign(const char* word)
{
    try
    {
        if (word == nullptr)
            throw "assign(): null pointer passed!";

        int i = 0;
        while (word[i] != '\0') i++;
        this->length = i;
        delete[] this->str;
        this->str = new char[i + 1];
        for (int j = 0; j < i; j++)
            this->str[j] = word[j];
        this->str[i] = '\0';
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
    return *this;
}

MyStr& MyStr::assign_range(const char* first, const char* last)
{
    try
    {
        if (first == nullptr || last == nullptr)
            throw "assign_range(): null pointer passed!";
        if (last < first)
            throw "assign_range(): last is before first!";

        int len = last - first;
        delete[] this->str;
        this->length = len;
        this->str = new char[this->length + 1];
        for (int i = 0; i < this->length; i++)
            this->str[i] = first[i];
        this->str[this->length] = '\0';
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
    return *this;
}

MyStr& MyStr::get_allocator() { return *this; }

MyStr& MyStr::operator+=(const MyStr& other)
{
    MyStr temp;
    temp.length = this->length + other.length;
    temp.str = new char[temp.length + 1];
    int i = 0;
    for (int j = 0; j < this->length; j++)  temp.str[i++] = this->str[j];
    for (int j = 0; j < other.length; j++)  temp.str[i++] = other.str[j];
    temp.str[temp.length] = '\0';
    *this = temp;
    return *this;
}

MyStr& MyStr::operator+=(char c)
{
    MyStr temp;
    temp.length = this->length + 1;
    temp.str = new char[temp.length + 1];
    int i = 0;
    for (int j = 0; j < this->length; j++) temp.str[i++] = this->str[j];
    temp.str[i++] = c;
    temp.str[temp.length] = '\0';
    *this = temp;
    return *this;
}

MyStr& MyStr::append(const MyStr& s)
{
    char* temp = new char[length + s.length + 1];
    for (int i = 0; i < length; i++)   temp[i] = str[i];
    for (int i = 0; i < s.length; i++) temp[length + i] = s.str[i];
    temp[length + s.length] = '\0';
    delete[] str;
    str = temp;
    length += s.length;
    return *this;
}

MyStr& MyStr::append_range(const MyStr& s) { return append(s); }

MyStr& MyStr::replace(const MyStr& other)
{
    if (*this == other) return *this;
    delete[] this->str;
    this->length = other.length;
    this->str = new char[this->length + 1];
    for (int i = 0; i < this->length; i++)
        this->str[i] = other.str[i];
    this->str[this->length] = '\0';
    return *this;
}

int MyStr::copy(char*& dest, int count, int pos)
{
    try
    {
        if (pos < 0 || pos >= this->length)
            throw "copy(): position out of bounds!";
        if (count < 0)
            throw "copy(): count cannot be negative!";

        if (pos + count > this->length)
            count = this->length - pos;
        dest = new char[count + 1];
        for (int i = 0; i < count; i++)
            dest[i] = this->str[pos + i];
        dest[count] = '\0';
        return count;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        return -1;
    }
}

void MyStr::push_back(char ch)
{
    char* temp = new char[length + 2];
    for (int i = 0; i < length; i++) temp[i] = str[i];
    temp[length] = ch;
    temp[length + 1] = '\0';
    delete[] str;
    str = temp;
    length++;
}

void MyStr::pop_back()
{
    try
    {
        if (length == 0)
            throw "pop_back(): string is already empty!";
        length--;
        str[length] = '\0';
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
}

void MyStr::clear()
{
    this->length = 0;
    delete[] this->str;
    this->str = new char[1];
    this->str[0] = '\0';
}

void MyStr::swap(MyStr& other)
{
    char* tempStr = this->str;
    int   tempLen = this->length;
    this->str = other.str;
    this->length = other.length;
    other.str = tempStr;
    other.length = tempLen;
}

// ========================= SEARCH =========================

int MyStr::find(const MyStr& s, int pos)
{
    try
    {
        if (pos < 0 || pos >= this->length)
            throw "find(): position out of bounds!";
        if (s.length == 0)
            throw "find(): search string is empty!";

        for (int i = pos; i <= this->length - s.length; i++)
        {
            bool match = true;
            for (int j = 0; j < s.length; j++)
                if (this->str[i + j] != s.str[j]) { match = false; break; }
            if (match) return i;
        }
        return -1;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        return -1;
    }
}

int MyStr::rfind(const MyStr& sub)
{
    try
    {
        if (sub.length == 0)
            throw "rfind(): search string is empty!";
        if (sub.length > length) return -1;

        for (int i = length - sub.length; i >= 0; i--)
        {
            bool match = true;
            for (int j = sub.length - 1; j >= 0; j--)
                if (str[i + j] != sub.str[j]) { match = false; break; }
            if (match) return i;
        }
        return -1;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        return -1;
    }
}

int MyStr::find_first(char ch)
{
    for (int i = 0; i < this->length; i++)
        if (this->str[i] == ch) return i;
    return -1;
}

int MyStr::find_first(const MyStr& sub) const
{
    try
    {
        if (sub.length == 0)
            throw "find_first(): search string is empty!";
        if (sub.length > length) return -1;

        for (int i = 0; i <= length - sub.length; i++)
        {
            bool match = true;
            for (int j = 0; j < sub.length; j++)
                if (str[i + j] != sub.str[j]) { match = false; break; }
            if (match) return i;
        }
        return -1;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        return -1;
    }
}

int MyStr::find_last(char ch)
{
    for (int i = length - 1; i >= 0; i--)
        if (str[i] == ch) return i;
    return -1;
}

int MyStr::find_last(const MyStr& sub) const
{
    try
    {
        if (sub.length == 0)
            throw "find_last(): search string is empty!";
        if (sub.length > length) return -1;

        for (int i = length - sub.length; i >= 0; i--)
        {
            bool match = true;
            for (int j = sub.length - 1; j >= 0; j--)
                if (str[i + j] != sub.str[j]) { match = false; break; }
            if (match) return i;
        }
        return -1;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        return -1;
    }
}

int* MyStr::find_all(char ch, int& count)
{
    count = 0;
    for (int i = 0; i < this->length; i++)
        if (this->str[i] == ch) count++;
    if (count == 0) return nullptr;
    int* arr = new int[count];
    int k = 0;
    for (int i = 0; i < this->length; i++)
        if (this->str[i] == ch) arr[k++] = i;
    return arr;
}

int* MyStr::find_all(const MyStr& sub, int& count) const
{
    try
    {
        if (sub.length == 0)
            throw "find_all(): search string is empty!";

        count = 0;
        if (sub.length > this->length) return nullptr;
        for (int i = 0; i <= this->length - sub.length; i++)
        {
            bool match = true;
            for (int j = 0; j < sub.length; j++)
                if (this->str[i + j] != sub.str[j]) { match = false; break; }
            if (match) count++;
        }
        if (count == 0) return nullptr;
        int* arr = new int[count];
        int k = 0;
        for (int i = 0; i <= this->length - sub.length; i++)
        {
            bool match = true;
            for (int j = 0; j < sub.length; j++)
                if (this->str[i + j] != sub.str[j]) { match = false; break; }
            if (match) arr[k++] = i;
        }
        return arr;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        count = 0;
        return nullptr;
    }
}

int* MyStr::AllSubString(const char* sub, int& count) const
{
    try
    {
        if (sub == nullptr)
            throw "AllSubString(): null pointer passed!";

        count = 0;
        int subLen = 0;
        while (sub[subLen] != '\0') subLen++;
        if (subLen == 0 || this->length == 0 || subLen > this->length) return nullptr;

        for (int i = 0; i <= this->length - subLen; i++)
        {
            bool found = true;
            for (int j = 0; j < subLen; j++)
                if (sub[j] != this->str[i + j]) { found = false; break; }
            if (found) count++;
        }
        if (count == 0) return nullptr;
        int* arr = new int[count];
        int idx = 0;
        for (int i = 0; i <= this->length - subLen; i++)
        {
            bool found = true;
            for (int j = 0; j < subLen; j++)
                if (sub[j] != this->str[j + i]) { found = false; break; }
            if (found) arr[idx++] = i;
        }
        return arr;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        count = 0;
        return nullptr;
    }
}

// ========================= REMOVE / INSERT AT =========================

void MyStr::remove_at(int idx)
{
    try
    {
        if (idx < 0 || idx >= length)
            throw "remove_at(): index out of bounds!";

        MyStr temp;
        temp.length = this->length - 1;
        temp.str = new char[temp.length + 1];
        int k = 0;
        for (int i = 0; i < this->length; i++)
        {
            if (i == idx) continue;
            temp.str[k++] = this->str[i];
        }
        temp.str[temp.length] = '\0';
        *this = temp;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
}

void MyStr::insert_at(int idx, char ch)
{
    try
    {
        if (idx < 0 || idx > length)
            throw "insert_at(): index out of bounds!";

        MyStr temp;
        temp.length = this->length + 1;
        temp.str = new char[temp.length + 1];
        int k = 0;
        for (int i = 0; i <= this->length; i++)
        {
            if (i == idx) temp.str[i] = ch;
            else          temp.str[i] = this->str[k++];
        }
        temp.str[temp.length] = '\0';
        *this = temp;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
}

void MyStr::insert_at(int idx, const MyStr sub)
{
    try
    {
        if (idx < 0 || idx > length)
            throw "insert_at(): index out of bounds!";

        MyStr temp;
        temp.length = length + sub.length;
        temp.str = new char[temp.length + 1];
        int k = 0;
        for (int i = 0; i < idx; i++)        temp.str[k++] = str[i];
        for (int i = 0; i < sub.length; i++) temp.str[k++] = sub.str[i];
        for (int i = idx; i < length; i++)   temp.str[k++] = str[i];
        temp.str[temp.length] = '\0';
        *this = temp;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
}

void MyStr::remove_first(char ch)
{
    int first = -1;
    for (int i = 0; i < this->length; i++)
        if (this->str[i] == ch) { first = i; break; }
    if (first == -1) return;
    MyStr temp;
    temp.length = this->length - 1;
    temp.str = new char[temp.length + 1];
    int k = 0;
    for (int i = 0; i < this->length; i++)
    {
        if (i == first) continue;
        temp.str[k++] = this->str[i];
    }
    temp.str[temp.length] = '\0';
    *this = temp;
}

void MyStr::remove_last(char ch)
{
    int last = -1;
    for (int i = this->length - 1; i >= 0; i--)
        if (this->str[i] == ch) { last = i; break; }
    if (last == -1) return;
    MyStr temp;
    temp.length = this->length - 1;
    temp.str = new char[temp.length + 1];
    int k = 0;
    for (int i = 0; i < this->length; i++)
    {
        if (i == last) continue;
        temp.str[k++] = this->str[i];
    }
    temp.str[temp.length] = '\0';
    *this = temp;
}

void MyStr::remove_all(char ch)
{
    int count = 0;
    for (int i = 0; i < length; i++)
        if (str[i] == ch) count++;
    if (count == 0) return;
    MyStr temp;
    temp.length = this->length - count;
    temp.str = new char[temp.length + 1];
    int k = 0;
    for (int i = 0; i < this->length; i++)
    {
        if (this->str[i] == ch) continue;
        temp.str[k++] = this->str[i];
    }
    temp.str[temp.length] = '\0';
    *this = temp;
}

// ========================= COMPARE =========================

int MyStr::compare(const MyStr& s) const
{
    int n = (this->length < s.length) ? this->length : s.length;
    for (int i = 0; i < n; i++)
    {
        if (this->str[i] != s.str[i])
            return (this->str[i] > s.str[i]) ? 1 : -1;
    }
    if (this->length < s.length) return -1;
    if (this->length > s.length) return  1;
    return 0;
}

bool MyStr::isEqual(const MyStr& M) const
{
    if (this->length != M.length) return false;
    for (int i = 0; i < this->length; i++)
        if (this->str[i] != M.str[i]) return false;
    return true;
}

bool MyStr::isLess(const MyStr& M) const
{
    int n = (this->length < M.length) ? this->length : M.length;
    for (int i = 0; i < n; i++)
    {
        if (this->str[i] != M.str[i])
            return (this->str[i] < M.str[i]);
    }
    return (this->length < M.length);
}

bool MyStr::isGreater(const MyStr& M) const
{
    int n = (this->length < M.length) ? this->length : M.length;
    for (int i = 0; i < n; i++)
    {
        if (this->str[i] != M.str[i])
            return (this->str[i] > M.str[i]);
    }
    return (this->length > M.length);
}

bool MyStr::starts_with(const MyStr& s) const
{
    if (s.length > this->length) return false;
    for (int i = 0; i < s.length; i++)
        if (s.str[i] != this->str[i]) return false;
    return true;
}

bool MyStr::ends_with(const MyStr& s) const
{
    if (s.length > this->length) return false;
    int offset = this->length - s.length;
    for (int i = 0; i < s.length; i++)
        if (this->str[offset + i] != s.str[i]) return false;
    return true;
}

bool MyStr::contains(const MyStr& s) const
{
    if (s.length == 0 || s.length > length) return false;
    for (int i = 0; i <= length - s.length; i++)
    {
        bool match = true;
        for (int j = 0; j < s.length; j++)
            if (str[i + j] != s.str[j]) { match = false; break; }
        if (match) return true;
    }
    return false;
}

// ========================= CASE =========================

void MyStr::ToUpper()
{
    for (int i = 0; i < this->length; i++)
        if (this->str[i] >= 'a' && this->str[i] <= 'z')
            this->str[i] -= 32;
}

void MyStr::ToLower()
{
    for (int i = 0; i < this->length; i++)
        if (this->str[i] >= 'A' && this->str[i] <= 'Z')
            this->str[i] += 32;
}

MyStr MyStr::ToUpper(MyStr s)
{
    for (int i = 0; i < s.length; i++)
        if (s.str[i] >= 'a' && s.str[i] <= 'z')
            s.str[i] -= 32;
    return s;
}

MyStr MyStr::ToLower(MyStr s)
{
    for (int i = 0; i < s.length; i++)
        if (s.str[i] >= 'A' && s.str[i] <= 'Z')
            s.str[i] += 32;
    return s;
}

// ========================= UTILITY =========================

void MyStr::ReplaceFirst(char c)
{
    try
    {
        if (this->length == 0)
            throw "ReplaceFirst(): string is empty!";
        this->str[0] = c;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
}

void MyStr::Print()
{
    try
    {
        if (this->str == nullptr)
            throw "Print(): string is null!";
        cout << this->str;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
    }
}

MyStr MyStr::Trim()
{
    int start = 0, end = this->length - 1;
    while (start < length && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')) start++;
    while (end >= 0 && (str[end] == ' ' || str[end] == '\n' || str[end] == '\t')) end--;
    int newLength = (end < start) ? 0 : end - start + 1;
    MyStr temp;
    temp.length = newLength;
    temp.str = new char[temp.length + 1];
    int ct = 0;
    for (int i = start; i <= end; i++) temp.str[ct++] = this->str[i];
    temp.str[temp.length] = '\0';
    return temp;
}

MyStr MyStr::Trim(const MyStr& other)
{
    int start = 0, end = other.length - 1;
    while (start < other.length && (other.str[start] == ' ' || other.str[start] == '\t' || other.str[start] == '\n')) start++;
    while (end >= 0 && (other.str[end] == ' ' || other.str[end] == '\n' || other.str[end] == '\t')) end--;
    int newLength = (end < start) ? 0 : end - start + 1;
    MyStr temp;
    temp.length = newLength;
    temp.str = new char[temp.length + 1];
    int ct = 0;
    for (int i = start; i <= end; i++) temp.str[ct++] = other.str[i];
    temp.str[temp.length] = '\0';
    return temp;
}

int MyStr::stoi(const MyStr s)
{
    try
    {
        if (s.length == 0)
            throw "stoi(): empty string!";

        int  num = 0, i = 0;
        bool negative = false;
        if (s.str[0] == '-') { negative = true; i = 1; }
        for (; i < s.length; i++)
        {
            if (s.str[i] < '0' || s.str[i] > '9')
                throw "stoi(): non-numeric character found!";
            num = num * 10 + (s.str[i] - '0');
        }
        return negative ? -num : num;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        return 0;
    }
}

float MyStr::stof(const MyStr& s)
{
    try
    {
        if (s.length == 0)
            throw "stof(): empty string!";

        const char* str = s.c_str();
        float result = 0.0f, sign = 1.0f;
        int i = 0;
        if (str[i] == '-') { sign = -1.0f; i++; }
        while (str[i] != '\0' && str[i] != '.')
        {
            if (str[i] < '0' || str[i] > '9')
                throw "stof(): non-numeric character found!";
            result = result * 10 + (str[i] - '0');
            i++;
        }
        if (str[i] == '.')
        {
            i++;
            float divisor = 10.0f;
            while (str[i] != '\0')
            {
                if (str[i] < '0' || str[i] > '9')
                    throw "stof(): non-numeric character after decimal!";
                result = result + (str[i] - '0') / divisor;
                divisor *= 10.0f;
                i++;
            }
        }
        return result * sign;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        return 0.0f;
    }
}

MyStr MyStr::itos(int num)
{
    if (num == 0)
    {
        MyStr t;
        t.length = 1;
        t.str = new char[2];
        t.str[0] = '0';
        t.str[1] = '\0';
        return t;
    }
    bool negative = (num < 0);
    int  absNum = negative ? -num : num;
    int tmp = absNum, digits = 0;
    while (tmp > 0) { tmp /= 10; digits++; }
    MyStr t;
    t.length = digits + (negative ? 1 : 0);
    t.str = new char[t.length + 1];
    int i = t.length - 1;
    while (absNum > 0) { t.str[i--] = (absNum % 10) + '0'; absNum /= 10; }
    if (negative) t.str[0] = '-';
    t.str[t.length] = '\0';
    return t;
}

MyStr* MyStr::Split(char delim, int& count) const
{
    try
    {
        if (this->length == 0)
            throw "Split(): cannot split an empty string!";

        count = 1;
        for (int i = 0; i < this->length; i++)
            if (this->str[i] == delim) count++;

        MyStr* arr = new MyStr[count];
        int start = 0, part = 0;
        for (int i = 0; i < this->length; i++)
        {
            if (this->str[i] == delim)
            {
                int subLen = i - start;
                arr[part].length = subLen;
                arr[part].str = new char[subLen + 1];
                for (int j = 0; j < subLen; j++) arr[part].str[j] = this->str[start + j];
                arr[part].str[subLen] = '\0';
                part++;
                start = i + 1;
            }
        }
        int subLen = this->length - start;
        arr[part].length = subLen;
        arr[part].str = new char[subLen + 1];
        for (int i = 0; i < subLen; i++) arr[part].str[i] = this->str[start + i];
        arr[part].str[subLen] = '\0';
        return arr;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        count = 0;
        return nullptr;
    }
}

MyStr* MyStr::tokenize(const char* delim, int& count) const
{
    try
    {
        if (delim == nullptr)
            throw "tokenize(): null delimiter passed!";
        if (this->length == 0)
            throw "tokenize(): cannot tokenize an empty string!";

        int s = 0;
        while (delim[s] != '\0') s++;
        count = 0;
        for (int i = 0; i < this->length; i++)
            for (int j = 0; j < s; j++)
                if (this->str[i] == delim[j]) count++;
        count++;

        MyStr* arr = new MyStr[count];
        int start = 0, part = 0;
        for (int i = 0; i < this->length; i++)
        {
            for (int j = 0; j < s; j++)
            {
                if (this->str[i] == delim[j])
                {
                    int subLen = i - start;
                    arr[part].str = new char[subLen + 1];
                    arr[part].length = subLen;
                    for (int k = 0; k < subLen; k++) arr[part].str[k] = this->str[k + start];
                    arr[part].str[subLen] = '\0';
                    part++;
                    start = i + 1;
                }
            }
        }
        int subLen = this->length - start;
        arr[part].str = new char[subLen + 1];
        arr[part].length = subLen;
        for (int i = 0; i < subLen; i++) arr[part].str[i] = this->str[i + start];
        arr[part].str[subLen] = '\0';
        return arr;
    }
    catch (const char* err)
    {
        cout << "Error: " << err << endl;
        count = 0;
        return nullptr;
    }
}

// ========================= FRIEND OPERATORS =========================

MyStr operator+(const MyStr& lhs, const MyStr& rhs)
{
    MyStr temp;
    temp.length = lhs.length + rhs.length;
    temp.str = new char[temp.length + 1];
    int i = 0;
    for (int j = 0; j < lhs.length; j++) temp.str[i++] = lhs.str[j];
    for (int j = 0; j < rhs.length; j++) temp.str[i++] = rhs.str[j];
    temp.str[temp.length] = '\0';
    return temp;
}

bool operator==(const MyStr& lhs, const MyStr& rhs)
{
    if (lhs.length != rhs.length) return false;
    for (int i = 0; i < lhs.length; i++)
        if (lhs.str[i] != rhs.str[i]) return false;
    return true;
}

bool operator!=(const MyStr& lhs, const MyStr& rhs) { return !(lhs == rhs); }

bool operator<(const MyStr& lhs, const MyStr& rhs)
{
    int n = (lhs.length < rhs.length) ? lhs.length : rhs.length;
    for (int i = 0; i < n; i++)
    {
        if (lhs.str[i] != rhs.str[i])
            return (lhs.str[i] < rhs.str[i]);
    }
    return (lhs.length < rhs.length);
}

bool operator>(const MyStr& lhs, const MyStr& rhs)
{
    int n = (lhs.length < rhs.length) ? lhs.length : rhs.length;
    for (int i = 0; i < n; i++)
    {
        if (lhs.str[i] != rhs.str[i])
            return (lhs.str[i] > rhs.str[i]);
    }
    return (lhs.length > rhs.length);
}

bool operator<=(const MyStr& lhs, const MyStr& rhs) { return !(lhs > rhs); }
bool operator>=(const MyStr& lhs, const MyStr& rhs) { return !(lhs < rhs); }

ostream& operator<<(ostream& out, const MyStr& s)
{
    if (s.str != nullptr)
        out << s.str;
    else
        out << "Error: Empty!";
    return out;
}

istream& operator>>(istream& in, MyStr& s)
{
    s.clear();
    char c;
    while (in.get(c) && (c == ' ' || c == '\n' || c == '\t' || c == '\r')) {}
    if (!in) return in;
    s.push_back(c);
    while (in.get(c) && c != ' ' && c != '\n' && c != '\t' && c != '\r')
        s.push_back(c);
    return in;
}

istream& getline(istream& in, MyStr& s)
{
    return getline(in, s, '\n');
}

istream& getline(istream& in, MyStr& s, char delim)
{
    s.clear();
    char ch;
    while (in.get(ch))
    {
        if (ch == delim) break;
        s.push_back(ch);
    }
    return in;
}

MyStr MyStr::to_string() const
{
    return MyStr(str);
}
MyStr MyStr::to_string(int value)
{
    if (value == 0)
        return MyStr("0");

    bool negative = false;
    if (value < 0)
    {
        negative = true;
        value = -value;
    }

    char buffer[20];
    int i = 0;

    while (value > 0)
    {
        buffer[i++] = (value % 10) + '0';
        value /= 10;
    }

    if (negative)
        buffer[i++] = '-';

    buffer[i] = '\0';

    // reverse string
    for (int j = 0; j < i / 2; j++)
    {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }

    return MyStr(buffer);
}
MyStr MyStr::to_string(float value)
{
    int intPart = (int)value;
    float frac = value - intPart;

    MyStr result = MyStr::to_string(intPart);

    // no decimal part
    if (frac == 0)
        return result;

    char buffer[10];
    int i = 0;

    buffer[i++] = '.';

    frac = frac * 100;   // 2 decimal precision
    int f = (int)frac;

    buffer[i++] = (f / 10) + '0';
    buffer[i++] = (f % 10) + '0';
    buffer[i] = '\0';

    result += buffer;   // ✅ uses your operator+=
    return result;
}