#pragma once
#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <valarray>

template<typename T>
class Matrix {
private:

	using PTR = typename stdext::checked_array_iterator<T*>;
	using D_IL = typename std::initializer_list<std::initializer_list<T>>;

	std::valarray<T> _array;
	size_t _rows, _colums;

public:

	Matrix() = default;

	explicit Matrix(const size_t rows, const size_t colums, const T& value = T()) : _rows(rows), _colums(colums), _array(std::valarray<T>(value, rows* colums))
	{
	}

	explicit Matrix(D_IL lists)
	{
		_rows = lists.size();
		_colums = (lists.begin())->size();
		_array = std::valarray<T>(_rows * _colums);

		auto index = std::size_t{ 0 };

		for (auto& l : lists) {
			if (l.size() > _colums)
				throw std::invalid_argument("too many colums");
			std::copy(l.begin(), l.end(), (std::begin(_array) + index * _colums));
			++index;
		}
	}

	PTR operator[](const size_t index)
	{
		return index >= _rows ? PTR{ std::begin(_array), _rows * _colums, index * _colums }
		: PTR{ &_array[index * _colums], _colums };
	}

	void operator+=(const Matrix<T>& m)
	{
		_array += m._array;
	}

	Matrix<T> operator+(const Matrix<T>& m)
	{
		Matrix<T> r(_rows, _colums);
		r._array = _array + m._array;
		return r;
	}

	void operator-=(const Matrix<T>& m)
	{
		_array -= m._array;
	}

	Matrix<T> operator-(const Matrix<T>& m)
	{
		Matrix<T> r(_rows, _colums);
		r._array = _array - m._array;
		return r;
	}

	Matrix<T> operator*(const Matrix<T>& m)
	{
		Matrix<T> r(_rows, m._colums);
		if (_colums != m._rows)
			return r;
		for (size_t x = 0; x < _rows; x++) {
			for (size_t y = 0; y < m._colums; y++) {
				auto t = get_row(x) * m.get_column(y);
				r._array[x * m._colums + y] = t.sum();
			}
		}
		return r;
	}

	std::valarray<T> get_row(const size_t index) const noexcept
	{
		return _array[std::slice((index % _rows) * _colums, _colums, 1)];
	}
	std::valarray<T> get_column(const size_t col) const noexcept
	{
		return _array[std::slice(col % _colums, _rows, _colums)];
	}

	friend std::ostream& operator <<(std::ostream& os, const Matrix& m)
	{
		for (size_t i = 0; i < m._array.size(); ++i) {
			if (!(i % m._colums))
				os << '\n';
			os << std::fixed << std::setprecision(2)
				<< std::setw(8) << std::left << m._array[i];
		}
		return os;
	}

	Matrix<T>& ciclic_shift(const int n) noexcept
	{
		_array = _array.cshift(n);
		return *this;
	}

	Matrix<T> transpose() noexcept
	{
		Matrix m(_colums, _rows);
		m._array[std::gslice(0, { _rows, _colums }, { 1, _rows })] = _array;
		return m;
	}

	void operator=(const Matrix<T>& m) {
		this->_array = m._array;
		this->_colums = m._colums;
		this->_rows = m._rows;
	}

	std::pair<size_t, size_t> getSize()
	{
		return std::make_pair(_rows, _colums);
	}

	size_t getRowsCount()
	{
		return _rows;
	}

	size_t getColumsCount()
	{
		return _colums;
	}

	Matrix<T> subMatrix(const std::gslice& g) const noexcept
	{
		//размер массива количеств
		const std::valarray<size_t> vs = g.size();
		const size_t sz = vs.size(), first = (sz == 2) ? 1 : vs[0];
		Matrix<T> t(first * vs[sz - 2], vs[sz - 1]);
		t._array = (this->_array)[g];
		return t;
	}

	//некоторый срез матрицы(общий и одинарный)
	std::gslice_array<T> operator[](const std::gslice& g)
	{
		return _array[g];
	}

	std::slice_array<T> operator[](const std::slice& s)
	{
		return _array[s];
	}

	~Matrix() {
	}

};