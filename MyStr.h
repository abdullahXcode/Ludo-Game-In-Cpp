#pragma once
#include <iostream>
using namespace std;

class MyStr
{
private:
    char* str;
    int length;
public:

    // Constructors & Destructor
    MyStr();
    MyStr(const char ch);
    MyStr(const char* str);
    MyStr(int n, char ch);
    MyStr(int n);
    MyStr(const MyStr& other);
    ~MyStr();

    MyStr& operator=(const MyStr& other);

    char& at(int pos);
    const char& at(int pos) const;
    char& operator[](int pos);
    const char& operator[](int pos) const;
    char& front();
    char& back();
    const char* c_str() const;

    bool empty() const;
    int size() const;
    int Length();
    int max_size();
    void reserve(int n);
    int capacity();
    void shrink_to_fit();
    void resize(int newSize, char ch = '\0');

    MyStr& insert(int pos, const char str);
    MyStr& insert(int pos, const char* first);
    MyStr& insert_range(int pos, const char* first, const char* last);
    MyStr& erase(int pos, int count);
    MyStr& assign(const char* word);
    MyStr& assign_range(const char* first, const char* last);
    MyStr& get_allocator();
    MyStr& operator+=(const MyStr& other);
    MyStr& operator+=(char c);
    MyStr& append(const MyStr& s);
    MyStr& append_range(const MyStr& s);
    MyStr& replace(const MyStr& other);
    int copy(char*& dest, int count, int pos);
    void push_back(char ch);
    void pop_back();
    void clear();
    void swap(MyStr& other);

    int find(const MyStr& s, int pos);
    int rfind(const MyStr& sub);
    int find_first(char ch);
    int find_first(const MyStr& sub) const;
    int find_last(char ch);
    int find_last(const MyStr& sub) const;
    int* find_all(char ch, int& count);
    int* find_all(const MyStr& sub, int& count) const;
    int* AllSubString(const char* sub, int& count) const;

    void remove_at(int idx);
    void insert_at(int idx, char ch);
    void insert_at(int idx, const MyStr sub);
    void remove_first(char ch);
    void remove_last(char ch);
    void remove_all(char ch);

    int compare(const MyStr& s) const;
    bool isEqual(const MyStr& M) const;
    bool isLess(const MyStr& M) const;
    bool isGreater(const MyStr& M) const;
    bool starts_with(const MyStr& s) const;
    bool ends_with(const MyStr& s) const;
    bool contains(const MyStr& s) const;

    void ToUpper();
    void ToLower();
    static MyStr ToUpper(MyStr s);
    static MyStr ToLower(MyStr s);

    void ReplaceFirst(char c);
    void Print();
    MyStr Trim();
    static MyStr Trim(const MyStr& other);
    static int stoi(const MyStr s);
    MyStr itos(int num);
    static float stof(const MyStr& s);
    MyStr* Split(char delim, int& count) const;
    MyStr* tokenize(const char* delim, int& count) const;

    MyStr to_string() const;
    static MyStr to_string(int value);
    static MyStr to_string(float value);


    friend MyStr operator+(const MyStr& lhs, const MyStr& rhs);
    friend bool operator==(const MyStr& lhs, const MyStr& rhs);
    friend bool operator!=(const MyStr& lhs, const MyStr& rhs);
    friend bool operator<(const MyStr& lhs, const MyStr& rhs);
    friend bool operator>(const MyStr& lhs, const MyStr& rhs);
    friend bool operator<=(const MyStr& lhs, const MyStr& rhs);
    friend bool operator>=(const MyStr& lhs, const MyStr& rhs);
    friend ostream& operator<<(ostream& out, const MyStr& s);
    friend istream& operator>>(istream& in, MyStr& s);
    friend istream& getline(istream& in, MyStr& s, char delim);
};

istream& getline(istream& in, MyStr& s, char delim = '\n');