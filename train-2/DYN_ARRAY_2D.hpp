#ifndef DYN_ARRAY_2D
#define DYN_ARRAY_2D

template <typename T>
class dynArray2D {

private:
	T *head;

public:
	size_t length;
	size_t size;

	size_t row; // ÐÐ
	size_t col; // ÁÐ

public:
	// default constructor
	dynArray2D() = default;
	// constructor
	dynArray2D (const size_t row_, const size_t col_)			noexcept
		:	row(row_), col(col_), 
			size(col_ * row_), length(0), 
			head(new T[col_ * row_]) 
	{}

	// copy constructor
	dynArray2D (const dynArray2D &copied)						noexcept
		:	row(copied.row), col(copied.col), 
			size(copied.row * copied.col), length(copied.length), 
			head(new T[copied.size]) 
	{
		memcpy(head, copied.begin(), size);
	}
	// move constructor
	dynArray2D (dynArray2D &&moved) 
		:	row(moved.row), col(moved.col),
			size(moved.size), length(moved.length)
	{
		swap(head, moved.begin());
		moved.col = 0;		moved.row = 0;
		moved.length = 0;	moved.size = 0;
	}

	// copy = operator
	dynArray2D &operator = (const dynArray2D &copied)			noexcept {

		if (this != &copied) {

			delete this->head;
			col  = copied.col;	row    = copied.row;
			size = copied.size;	length = copied.length;
			this->head = new T[size];

			for (size_t i = 0; i < col * row; i++) {
				*(head + i) = *(copied.begin() + i);
			}
		}

		return *this;
	}
	// move = operator
	dynArray2D &operator = (dynArray2D &&moved) {

		if (this != &moved) {

			col = moved.col;	row = moved.row;
			size = moved.size;	length = moved.length;
			this->head = moved.begin();
			
			moved.col = 0;		moved.row = 0;
			moved.length = 0;	moved.size = 0;
		}

		return *this;
	}


	// clear all elem
	inline void clear()											noexcept {
		for (int i = 0; i < size; i++)
			*(head + i) = T();
		return;
	}

	// push elem if length < size, else row++
	inline void push(const T data)								noexcept {

		if (length == size) {
			T *tmp = new T[size + col];
			for (int i = 0; i < size; i++)
				*(tmp + i) = *(head + i);
			size += col;
			row++;

			*(tmp + length) = data;
			length++;

			delete head;
			head = tmp;
		}
		else {
			*(head + length) = data;
			length++;
		}

		return;
	}

	// pop the last elem
	inline void pop() {
		*(head + length - 1) = T();
	}

	// erase [row_, col_]
	inline T erase(size_t row_, size_t col_) {
		T toReturn = *(head + row_ * col + col_);
		*(head + row_ * col + col_) = T();
		return toReturn;
	}

	// change [row_, col_]
	inline void change(size_t row_, size_t col_, T input) {
		*(head + row_ * col + col_) = input;
	}

	// return head
	inline T *begin() {
		return head;
	}
	
	// return tail
	inline T *end() {
		return head + length - 1;
	}
};


#endif // !DYN_ARRAY_2D
