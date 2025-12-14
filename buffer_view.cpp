#include "buffer_view.h"

BufferView::BufferView(void * const data, const size_t size) noexcept : m_data(data), m_size(size) {}

BufferView::BufferView(const Buffer & buffer) noexcept : m_data(buffer.get_data()), m_size(buffer.get_size()) {}

BufferView::BufferView(const BufferView & buffer_view) noexcept : m_data(buffer_view.m_data), m_size(buffer_view.m_size) {}

BufferView::BufferView(BufferView && buffer_view) noexcept
: m_data(std::exchange(buffer_view.m_data, nullptr))
, m_size(std::exchange(buffer_view.m_size, 0))
{}

const void * BufferView::get_data() const 
{
    return m_data;
}

size_t BufferView::get_size() const 
{
    return m_size;
}