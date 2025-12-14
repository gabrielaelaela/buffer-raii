#include "buffer.h"
#include "buffer_view.h"

Buffer::Buffer(size_t capacity)
: m_data(::operator new(capacity))
, m_capacity(capacity)
{}

Buffer::Buffer(void * data, size_t size)
: m_data(::operator new(size))
, m_size(size)
, m_capacity(size)
{
    std::memcpy(m_data, data, size);
}

Buffer::Buffer(const BufferView & buffer_view) 
: m_data(::operator new(buffer_view.get_size()))
, m_size(buffer_view.get_size())
, m_capacity(buffer_view.get_size()) 
{
    std::memcpy(m_data, buffer_view.get_data(), m_size);
}

Buffer::Buffer(const Buffer & buffer)
: m_data(::operator new(buffer.m_capacity))
, m_size(buffer.m_size)
, m_capacity(buffer.m_capacity) 
{
    std::memcpy(m_data, buffer.m_data, m_size);
}

Buffer::Buffer(Buffer && buffer)
: m_data(std::exchange(buffer.m_data, nullptr))
, m_size(std::exchange(buffer.m_size, 0))
, m_capacity(std::exchange(buffer.m_capacity, 0))
{}

Buffer & Buffer::operator=(const Buffer & buffer) 
{
    if (this == &buffer) return *this;

    Buffer tmp(buffer);
    std::swap(m_data, tmp.m_data);
    std::swap(m_size, tmp.m_size);
    std::swap(m_capacity, tmp.m_capacity);

    return *this;
}

Buffer & Buffer::operator=(Buffer && buffer) noexcept 
{
    if (this == &buffer) return *this;

    ::operator delete(m_data);;

    m_size = std::exchange(buffer.m_size, 0);
    m_capacity = std::exchange(buffer.m_capacity, 0);
    m_data = std::exchange(buffer.m_data, nullptr);

    return *this;
}

Buffer::~Buffer() 
{
    ::operator delete(m_data);
}

void * Buffer::get_data()
{
    return m_data;
}

const void * Buffer::get_data() const
{
    return m_data;
}

size_t Buffer::get_size() const 
{
    return m_size;
}

void Buffer::set_size(size_t new_size) 
{
    if (m_capacity < new_size) {
        void* tmp = ::operator new(new_size);

        if (m_data && m_size > 0) {
            std::memcpy(tmp, m_data, m_size);
        }
        
        ::operator delete(m_data);
        
        m_data = tmp;
        m_capacity = new_size;
        m_size = new_size;
        return;
    } 

    m_size = new_size;
}

size_t Buffer::get_capacity() const
{
    return m_capacity;
}

void Buffer::set_capacity(size_t new_capacity) 
{
    void* tmp = ::operator new(new_capacity);

    size_t copy_size = std::min(m_size, new_capacity);

    if (m_data && m_size > 0) {
        std::memcpy(tmp, m_data, copy_size);        
    }
        
    ::operator delete(m_data);
        
    m_data = tmp;
    m_size = copy_size;
    m_capacity = new_capacity;
}