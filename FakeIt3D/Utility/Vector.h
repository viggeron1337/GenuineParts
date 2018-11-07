#pragma once

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

	/*
		Increase the capacity of the internal array

		Params:
		capacity	new capacity of the array
	*/
	void Reserve(size_type _capacity);

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
	return *reinterpret_cast<Vector<T>::type*>(m_buffer);;
}

////////////////////////////////////////////////////
template<class T>
typename Vector<T>::type & Vector<T>::Back() const
{
	return *reinterpret_cast<Vector<T>::type*>(m_buffer + (sizeof(T) * (m_size - 1)));;
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

////////////////////////////////////////////////////
template<class T>
void Vector<T>::Reserve(size_type _capacity)
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



