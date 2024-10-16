// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    int sz;
    T* pMem;
public:
    TDynamicVector(int size = 1) : sz(size)
    {
        if (sz <= 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size exceeds maximum allowed size");
        pMem = new T[sz]();
    }

    TDynamicVector(T* arr, int s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }

    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v) return *this;
        if (sz != v.sz) {
            T* p = new T[v.sz];
            delete[] pMem;
            sz = v.sz;
            pMem = p;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    int size() const noexcept { return sz; }

    // индексация
    T& operator[](int ind)
    {
        return pMem[ind];
    }

    const T& operator[](int ind) const
    {
        return pMem[ind];
    }

    // индексация с контролем
    T& at(int ind)
    {
        if (ind < 0 || ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    const T& at(int ind) const
    {
        if (ind < 0 || ind >= sz)
            throw out_of_range("Index out of range");
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (int i = 0; i < sz; i++) 
            if (pMem[i] != v.pMem[i]) return false;
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++) 
            tmp.pMem[i] = pMem[i] + val;
        return tmp;
    }

    TDynamicVector operator-(T val)
    {
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] - val;
        return tmp;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] * val;
        return tmp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Vectors must be of the same size");
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] + v.pMem[i];
        return tmp;
    }

    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz)
            throw invalid_argument("Vectors must be of the same size");
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] - v.pMem[i];
        return tmp;
    }

    T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
    {
        if (sz != v.sz)
            throw invalid_argument("Vectors must be of the same size");
        T res = T();
        for (int i = 0; i < sz; i++)
            res += pMem[i] * v.pMem[i];
        return res;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (int i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; 
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (int i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; 
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(int s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s <= 0)
            throw out_of_range("Matrix size should be greater than zero");
        if (s > MAX_MATRIX_SIZE)
            throw out_of_range("Matrix size exceeds maximum allowed size");
        for (int i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];
    using TDynamicVector<TDynamicVector<T>>::at;
    using TDynamicVector<TDynamicVector<T>>::size;

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] * val;
        return tmp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size())
            throw invalid_argument("Matrix and vector sizes do not match");
        TDynamicVector<T> tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp[i] = pMem[i] * v;
        return tmp;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrices must be of the same size");
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] + m.pMem[i];
        return tmp;
    }

    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrices must be of the same size");
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
            tmp.pMem[i] = pMem[i] - m.pMem[i];
        return tmp;
    }

    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz)
            throw invalid_argument("Matrices must be of the same size");
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                for (int k = 0; k < sz; k++)
                    tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
            istr >> v.pMem[i];
        return str;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (int i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << '\n';
        return ostr;
    }
};

#endif
