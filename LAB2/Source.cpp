#include <iostream>
#include <stdexcept>

using namespace std;

class vect {
public:
    int dim;
    double* b;
    int num;
    static int count;

    vect(int d) : dim(d), num(++count) {
        b = new double[dim];
        for (int i = 0; i < dim; ++i) b[i] = 0;
        cout << "������ " << num << " ������." << endl;
    }

    vect(const vect& v) : dim(v.dim), num(++count) {
        b = new double[dim];
        for (int i = 0; i < dim; ++i) b[i] = v.b[i];
        cout << "������ " << num << " ������ ������������ �� ������� " << v.num << "." << endl;
    }

    ~vect() {
        delete[] b;
        cout << "������ " << num << " ���������." << endl;
    }

    vect& operator=(const vect& v) {
        if (this != &v) {
            if (dim != v.dim) {
                delete[] b;
                dim = v.dim;
                b = new double[dim];
            }
            for (int i = 0; i < dim; ++i) b[i] = v.b[i];
            cout << "������ " << num << " �������� ������� " << v.num << "." << endl;
        }
        return *this;
    }

    vect operator+(const vect& v) const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) result.b[i] = b[i] + v.b[i];
        cout << "������ " << num << " ������ � �������� " << v.num << "." << endl;
        return result;
    }

    vect operator-(const vect& v) const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) result.b[i] = b[i] - v.b[i];
        cout << "������ " << num << " ������ �� ������� " << v.num << "." << endl;
        return result;
    }

    vect operator-() const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) result.b[i] = -b[i];
        cout << "������ " << num << " ������������." << endl;
        return result;
    }

    double operator*(const vect& v) const {
        double result = 0;
        for (int i = 0; i < dim; ++i) result += b[i] * v.b[i];
        cout << "������ " << num << " ������� �� ������ " << v.num << "." << endl;
        return result;
    }

    vect operator*(double k) const {
        vect result(dim);
        for (int i = 0; i < dim; ++i) result.b[i] = b[i] * k;
        cout << "������ " << num << " ������� �� " << k << "." << endl;
        return result;
    }

    friend vect operator*(double k, const vect& v) {
        return v * k;
    }

    void print() const {
        for (int i = 0; i < dim; ++i) {
            cout << b[i] << " ";
        }
        cout << endl;
    }
};

int vect::count = 0;

class matr {
public:
    int dim;
    double* a;
    int num;
    static int count;

    matr(int d) : dim(d), num(++count) {
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; ++i) a[i] = 0;
        cout << "������� " << num << " �������." << endl;
    }

    matr(const matr& m) : dim(m.dim), num(++count) {
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; ++i) a[i] = m.a[i];
        cout << "������� " << num << " ������� ������������ �� ������� " << m.num << "." << endl;
    }

    ~matr() {
        delete[] a;
        cout << "������� " << num << " ����������." << endl;
    }

    matr& operator=(const matr& m) {
        if (this != &m) {
            if (dim != m.dim) {
                delete[] a;
                dim = m.dim;
                a = new double[dim * dim];
            }
            for (int i = 0; i < dim * dim; ++i) a[i] = m.a[i];
            cout << "������� " << num << " ��������� ������� " << m.num << "." << endl;
        }
        return *this;
    }

    matr operator+(const matr& m) const {
        matr result(dim);
        for (int i = 0; i < dim * dim; ++i) result.a[i] = a[i] + m.a[i];
        cout << "������� " << num << " ������� � �������� " << m.num << "." << endl;
        return result;
    }

    matr operator-(const matr& m) const {
        matr result(dim);
        for (int i = 0; i < dim * dim; ++i) result.a[i] = a[i] - m.a[i];
        cout << "������� " << num << " ������� �� ������� " << m.num << "." << endl;
        return result;
    }

    matr operator-() const {
        matr result(dim);
        for (int i = 0; i < dim * dim; ++i) result.a[i] = -a[i];
        cout << "������� " << num << " �������������." << endl;
        return result;
    }

    matr operator*(const matr& m) const {
        matr result(dim);
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                result.a[i * dim + j] = 0;
                for (int k = 0; k < dim; ++k) {
                    result.a[i * dim + j] += a[i * dim + k] * m.a[k * dim + j];
                }
            }
        }
        cout << "������� " << num << " �������� �� ������� " << m.num << "." << endl;
        return result;
    }

    matr operator*(double k) const {
        matr result(dim);
        for (int i = 0; i < dim * dim; ++i) result.a[i] = a[i] * k;
        cout << "������� " << num << " �������� �� " << k << "." << endl;
        return result;
    }

    friend matr operator*(double k, const matr& m) {
        return m * k;
    }

    vect operator*(const vect& v) const {
        if (dim != v.dim) throw invalid_argument("����������� ������� � ������� �� ���������");
        vect result(dim);
        for (int i = 0; i < dim; ++i) {
            result.b[i] = 0;
            for (int j = 0; j < dim; ++j) {
                result.b[i] += a[i * dim + j] * v.b[j];
            }
        }
        cout << "������� " << num << " �������� �� ������ " << v.num << "." << endl;
        return result;
    }

    void print() const {
        for (int i = 0; i < dim; ++i) {
            for (int j = 0; j < dim; ++j) {
                cout << a[i * dim + j] << " ";
            }
            cout << endl;
        }
    }
};

int matr::count = 0;

int main() {
    setlocale(LC_ALL, "ru");

    // �������� � ������ � ���������
    vect v1(3), v2(3);
    v1.b[0] = 1; v1.b[1] = 2; v1.b[2] = 3;
    v2.b[0] = 4; v2.b[1] = 5; v2.b[2] = 6;

    cout << "������ v1: ";
    v1.print();
    cout << "������ v2: ";
    v2.print();

    vect v3 = v1 + v2;
    cout << "������ v1 + v2: ";
    v3.print();

    vect v4 = v1 - v2;
    cout << "������ v1 - v2: ";
    v4.print();

    vect v5 = -v1;
    cout << "��������������� ������ v1: ";
    v5.print();

    double dotProduct = v1 * v2;
    cout << "��������� ������������ v1 � v2: " << dotProduct << endl;

    vect v6 = v1 * 2.0;
    cout << "������ v1, ���������� �� 2: ";
    v6.print();

    // �������� � ������ � ���������
    matr m1(3), m2(3);
    m1.a[0] = 1; m1.a[1] = 2; m1.a[2] = 3;
    m1.a[3] = 4; m1.a[4] = 5; m1.a[5] = 6;
    m1.a[6] = 7; m1.a[7] = 8; m1.a[8] = 9;

    m2.a[0] = 9; m2.a[1] = 8; m2.a[2] = 7;
    m2.a[3] = 6; m2.a[4] = 5; m2.a[5] = 4;
    m2.a[6] = 3; m2.a[7] = 2; m2.a[8] = 1;

    cout << "������� m1:" << endl;
    m1.print();
    cout << "������� m2:" << endl;
    m2.print();

    matr m3 = m1 + m2;
    cout << "������� m1 + m2:" << endl;
    m3.print();

    matr m4 = m1 - m2;
    cout << "������� m1 - m2:" << endl;
    m4.print();

    matr m5 = -m1;
    cout << "��������������� ������� m1:" << endl;
    m5.print();

    matr m6 = m1 * m2;
    cout << "������� m1 * m2:" << endl;
    m6.print();

    matr m7 = m1 * 2.0;
    cout << "������� m1, ���������� �� 2:" << endl;
    m7.print();

    vect v7 = m1 * v1;
    cout << "������� m1, ���������� �� ������ v1: ";
    v7.print();

    return 0;
}
