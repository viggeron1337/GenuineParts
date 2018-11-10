#pragma once
#include <assert.h>
#include <memory>
template<class T>
class Vector
{
public:
	using type = T;
	using iterator = T*;
	using size_type = unsigned int;
	using buffer_type = unsigned char;

	/*
		Default Constructor
		This constructor initializes all members to 0.
	*/
	Vector();

	Vector(const Vector<type>& copy);

	Vector(unsigned int _capacity);

	virtual ~Vector();

	/*
		Begin iterator
		
		return:
		A iterator for the first element
	*/
	iterator begin() const;

	/*
		End iterator

		return:
		A iterator for the last element
	*/
	iterator end() const;

	/*
		Gets the first element of the array

		return 
		Reference to the first element.
	*/
	type& Front() const;

	/*
		Gets the last element of the array

		return
		Reference to the last element.
	*/
	type& Back() const;

	/*
		Appends the given element value to the end of the container.

		Params:
		value		The value of the element to append
	*/
	void PushBack(const type& _value);

	void PopBack();

	type& operator[](int index) const;

	/*
		Increase the capacity of the internal array

		Params:
		capacity	new capacity of the array
	*/
	void Reserve(size_type _capacity);

	void Resize(size_type _capacity);

	size_type Size() const;
	bool empty() const;

	void clear();

	Vector<type>& operator=(const Vector<T>& other);

private:
	size_type m_size;
	size_type m_reserved;
	buffer_type* m_buffer;

};


////////////////////////////////////////////////////
template<class T>
Vector<T>::Vector() :
m_size		(0),
m_reserved	(2),
m_buffer	(new buffer_type[sizeof(type)*m_reserved])
{

}

template<class T>
Vector<T>::Vector(const Vector<type>& copy)
{
	m_size = copy.m_size;
	m_reserved = copy.m_reserved;
	m_buffer = new buffer_type[sizeof(type)*m_reserved];
	memcpy(&m_buffer[0], &copy.m_buffer[0], m_size * sizeof(type));
}

template<class T>
Vector<T>::Vector(unsigned int _capacity) :
m_size		(_capacity),
m_reserved	(_capacity),
m_buffer(new buffer_type[sizeof(type)*_capacity])
{

}

template<class T>
Vector<T>::~Vector()
{
	clear();
	delete[] m_buffer;
	m_buffer = nullptr;
}

////////////////////////////////////////////////////
template<class T>
typename Vector<T>::iterator Vector<T>::begin() const
{
	return reinterpret_cast<type*>(m_buffer);
}

////////////////////////////////////////////////////
template<class T>
typename Vector<T>::iterator Vector<T>::end() const
{
	return reinterpret_cast<type*>(m_buffer + (sizeof(T) * m_size));
}

////////////////////////////////////////////////////
template<class T>
typename Vector<T>::type & Vector<T>::Front() const
{
	return *reinterpret_cast<Vector<T>::type*>(m_buffer);
}

////////////////////////////////////////////////////
template<class T>
typename Vector<T>::type & Vector<T>::Back() const
{
	return *reinterpret_cast<Vector<T>::type*>(m_buffer + (sizeof(T) * (m_size - 1)));
}

////////////////////////////////////////////////////
template<class T>
void Vector<T>::PushBack(const type & _value)
{
	if (m_size >= m_reserved)
		Reserve(m_reserved << 1);

	type* pos = reinterpret_cast<type*>(m_buffer + (sizeof(T) * m_size++));
	*pos = _value;
}

template<class T>
void Vector<T>::PopBack()
{
	(reinterpret_cast<T*>(m_buffer)[m_size - 1]).~T();

	--m_size;
}

template<class T>
typename Vector<T>::type & Vector<T>::operator[](int index) const
{
	assert(index < Size());
	return *reinterpret_cast<Vector<T>::type*>(m_buffer + (sizeof(T) * index));
}

////////////////////////////////////////////////////
template<class T>
void Vector<T>::Reserve(size_type _capacity)
{
	// Only reserve if we dont have the requested capacity
	if (m_reserved < _capacity)
	{
		m_reserved = _capacity;

		buffer_type* newBuffer = new buffer_type[sizeof(type) * m_reserved];

		for (size_type i = 0; i < m_size; i++)
		{
			T* oldPos = reinterpret_cast<type*>(m_buffer + (sizeof(type) * i));
			T* newPos = reinterpret_cast<type*>(newBuffer + (sizeof(type) * i));
			*newPos = *oldPos;
		}
		delete[] m_buffer;
		m_buffer = newBuffer;
	}

}

////////////////////////////////////////////////////
template<class T>
void Vector<T>::Resize(size_type _capacity)
{
	if (_capacity > m_reserved)
	{
		// Reallocate forward
		Reserve(_capacity);
		m_size = _capacity;
	}
	else if (_capacity > m_size)
	{
		//// Append
		//PushBack(T());
		//memset(&m_buffer[0] + m_size, T, sizeof(T)*(_capacity - m_size));
		m_size = _capacity;
	}
	else
	{
		// Trim
		size_type trimLength = m_size - _capacity;
		for (int i = 0; i < trimLength; i++)
		{
			PopBack();
		}
	}
}

template<class T>
typename Vector<T>::size_type Vector<T>::Size() const
{
	return m_size;
}

template<class T>
bool Vector<T>::empty() const
{
	return m_size == 0;
}

template<class T>
void Vector<T>::clear()
{
	while (m_size != 0)
		PopBack();
}

template<class T>
typename Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		delete[] m_buffer;
		m_size = other.m_size;
		m_reserved = other.m_reserved;
		m_buffer = new buffer_type[sizeof(type)*m_reserved];
		memcpy(&m_buffer[0], &other.m_buffer[0], m_size * sizeof(type));
	}
	return *this;
}



