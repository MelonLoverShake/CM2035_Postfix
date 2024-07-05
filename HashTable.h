class HashTable {
private:
    static const int LETTERS_COUNT = 26;
    double values[LETTERS_COUNT];

    int hashFunc(char key);
    void checkVariable(char key);

public:
    HashTable();
    void insert(char key, double value);
    double search(char key);
    void remove(char key);
    void print();
    void clear();
};

