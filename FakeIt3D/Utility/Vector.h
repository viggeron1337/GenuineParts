#pragma once

template<class T>
class Vector
{
public:
	using type = T;
	using iterator = T*;
	using size_type = unsigned int;
	using buffer_type = unsigned char;

	Vector();

	iterator Begin();
	type& Front() const;

	void PushBack(const type& _value);

	void Reserve(size_type _capacity);

private:
	size_type m_size;
	size_type m_capacity;
	buffer_type* m_buffer;

};


////////////////////////////////////////////////////
template<class T>
Vector<T>::Vector() :
	m_size(0),
	m_capacity(2),
	m_buffer(new buffer_type[sizeof(type)*m_capacity])
{

}

template<class T>
typename Vector<T>::iterator Vector<T>::Begin()
{
	return reinterpret_cast<type*>(m_buffer);
}

template<class T>
typename Vector<T>::type & Vector<T>::Front() const
{
	T*p = reinterpret_cast<T*>(m_buffer);
	return *p;
}

template<class T>
void Vector<T>::PushBack(const type & _value)
{
	if (m_size >= m_capacity)
		Reserve(m_capacity << 1);

	buffer_type* pos = (m_buffer + (sizeof(T) * m_size));
	pos = _value;
}

template<class T>
void Vector<T>::Reserve(size_type _capacity)
{
	m_capacity = _capacity;

	buffer_type* newBuffer = new buffer_type[sizeof(type) * m_capacity];

	for (size_type i = 0; i < m_size; i++)
	{
		newBuffer[i] = m_buffer[i];
	}
	delete[] m_buffer;
	m_buffer = newBuffer;
}



