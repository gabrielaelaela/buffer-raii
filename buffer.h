#pragma once

#include <cstddef>
#include <cstring>
#include <utility>
#include <algorithm>

class BufferView;

class Buffer
{
public:
    // Конструктор по умолчанию, создает пустой буфер
    Buffer() noexcept = default;

    // Конструктор, создающий буфер указанного размера
    explicit Buffer(size_t capacity);

    // Конструктор, создающий буфер из существующих данных, копируя их
    // внутрь буфера
    Buffer(void * data, size_t size);

    // Конструктор, создающий владеющий буфер из невладеющего, копируя
    // данные из него внутрь буфера
    Buffer(const BufferView & buffer_view);

    // Конструктор копирования
    Buffer(const Buffer & buffer);

    // Конструктор перемещения
    Buffer(Buffer && buffer);

    // Копирующий оператор присваивания
    Buffer & operator=(const Buffer & buffer);

    // Перемещающий оператор присваивания
    Buffer & operator=(Buffer && buffer) noexcept;

    // Деструктор
    ~Buffer();

    // Получить указатель на данные в буфере
    void * get_data();
    const void * get_data() const;

    // Получить размер данных в буфере
    size_t get_size() const;

    // Установить размер данных в буфере
    void set_size(size_t new_size);

    // Получить емкость буфера
    size_t get_capacity() const;

    // Установить емкость буфера
    void set_capacity(size_t new_capacity);

private:
    void * m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
};
