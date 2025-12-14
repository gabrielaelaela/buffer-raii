#pragma once

#include "buffer.h"

class BufferView
{
public:
    // Конструктор по умолчанию, создает пустой буфер
    BufferView() noexcept = default;

    // Конструктор, создающий буфер из существующих данных,
    // сохраняя указатель на них и их размер
    BufferView(void * const data, const size_t size) noexcept;

    // Конструктор, создающий невладеющий буфер из владеющего, копируя
    // указатель на данные из него и их размер
    BufferView(const Buffer & buffer) noexcept;

    // Конструктор копирования
    BufferView(const BufferView & buffer_view) noexcept;

    // Конструктор перемещения
    BufferView(BufferView && buffer_view) noexcept;

    // Копирующий оператор присваивания
    BufferView & operator=(const BufferView & buffer_view) noexcept;

    // Перемещающий оператор присваивания
    BufferView & operator=(BufferView && buffer_view) noexcept;

    // Деструктор
    ~BufferView() = default;

    // Получить указатель на данные в буфере
    const void * get_data() const;

    // Получить размер данных в буфере
    size_t get_size() const;

private:
    const void * m_data = nullptr;
    size_t m_size = 0;
};
