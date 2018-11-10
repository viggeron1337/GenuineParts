#pragma once
#include <assert.h>
#include <memory>
template<class T, class Allocator = std::allocator<T>>
class Vector
{
public:
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::size_type size_type;
	using type = T;
	using iterator = T*;
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

	Vector<T, Allocator>& operator=(const Vector<T, Allocator>& other);

private:
	size_type m_size;
	size_type m_reserved;
	pointer m_buffer;
	Allocator m_alloc;

};


////////////////////////////////////////////////////
template<class T, class Allocator>
Vector<T,Allocator>::Vector() :
m_size		(0),
m_reserved	(0),
m_buffer	(nullptr)
{

}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector<type>& copy)
{
	m_size = copy.m_size;
	m_reserved = copy.m_reserved;

	m_buffer = m_alloc.allocate(m_reserved);

	for (size_type i = 0; i < m_size; i++)
	{
		m_alloc.construct(m_buffer + i, copy.m_buffer[i]);
	}
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(unsigned int _capacity) :
m_size		(_capacity),
m_reserved	(_capacity),
m_buffer	(m_alloc.allocate(_capacity))
{
	
}

template<class T, class Allocator>
Vector<T, Allocator>::~Vector()
{
	clear();
	m_alloc.deallocate(m_buffer, m_reserved);
}

////////////////////////////////////////////////////
template<class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T,Allocator>::begin() const
{
	return reinterpret_cast<type*>(m_buffer);
}

////////////////////////////////////////////////////
template<class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::end() const
{
	return reinterpret_cast<type*>(m_buffer + (sizeof(T) * m_size));
}

////////////////////////////////////////////////////
template<class T, class Allocator>
typename Vector<T, Allocator>::type & Vector<T, Allocator>::Front() const
{
	return *reinterpret_cast<typename Vector<T>::pointer>(m_buffer);
}

////////////////////////////////////////////////////
template<class T, class Allocator>
typename Vector<T, Allocator>::type & Vector<T, Allocator>::Back() const
{
	return *reinterpret_cast<typename Vector<T>::pointer>(m_buffer + (sizeof(T) * (m_size - 1)));
}

////////////////////////////////////////////////////
template<class T, class Allocator>
void Vector<T, Allocator>::PushBack(const type & _value)
{
	if (m_size >= m_reserved)
		Reserve(m_reserved + 2);

	m_alloc.construct(m_buffer + m_size, _value);
	m_size++;
}

template<class T, class Allocator>
void Vector<T,Allocator>::PopBack()
{
	m_alloc.destroy(m_buffer + m_size - 1);
	--m_size;
}

template<class T, class Allocator>
typename Vector<T, Allocator>::type & Vector<T, Allocator>::operator[](int index) const
{
	assert(index < Size());
	return m_buffer[index];
}

////////////////////////////////////////////////////
template<class T, class Allocator>
void Vector<T, Allocator>::Reserve(size_type _capacity)
{
	// Only reserve if we dont have the requested capacity
	if (m_reserved < _capacity)
	{
	

		T* newBuffer = m_alloc.allocate(_capacity);

		for (size_type i = 0; i < m_size; i++)
		{
			m_alloc.construct(newBuffer + i, m_buffer[i]);
			m_alloc.destroy(m_buffer + i);
		}
		
		m_alloc.deallocate(m_buffer, m_reserved);
		m_buffer = newBuffer;
		m_reserved = _capacity;
	}

}

////////////////////////////////////////////////////
template<class T, class Allocator>
void Vector<T, Allocator>::Resize(size_type _capacity)
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

template<class T, class Allocator>
typename Vector<T, Allocator>::size_type Vector<T, Allocator>::Size() const
{
	return m_size;
}

template<class T, class Allocator>
bool Vector<T, Allocator>::empty() const
{
	return m_size == 0;
}

template<class T, class Allocator>
void Vector<T, Allocator>::clear()
{
	while (m_size != 0)
		PopBack();
}

template<class T, class Allocator>
typename Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector<T, Allocator>& other)
{
	if (this != &other)
	{
		delete[] m_buffer;
		m_size = other.m_size;
		m_reserved = other.m_reserved;

		m_buffer = m_alloc.allocate(m_reserved);

		for (size_type i = 0; i < m_size; i++)
		{
			m_alloc.construct(m_buffer + i, other.m_buffer[i]);
		}

	}
	return *this;
}



