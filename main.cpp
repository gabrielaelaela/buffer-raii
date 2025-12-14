#include <iostream>
#include <cassert>
#include <cstring>

#include "buffer.h"
#include "buffer_view.h"

int main() {

    // 1. Создание буфера заданной емкости
    Buffer buf(16);
    assert(buf.get_capacity() == 16);
    assert(buf.get_size() == 0);

    // 2. Запись данных в буфер
    const char text[] = "hello";
    std::memcpy(buf.get_data(), text, sizeof(text));
    buf.set_size(sizeof(text));

    // 3. Проверка содержимого
    assert(buf.get_size() == sizeof(text));
    assert(std::memcmp(buf.get_data(), text, sizeof(text)) == 0);

    // 4. Копирование буфера
    Buffer copy(buf);
    assert(copy.get_size() == buf.get_size());
    assert(std::memcmp(copy.get_data(), buf.get_data(), buf.get_size()) == 0);

    // 5. Перемещение буфера
    Buffer moved(std::move(buf));
    assert(buf.get_data() == nullptr);
    assert(moved.get_size() == sizeof(text));

    // 6. Невладеющий view
    BufferView view(moved);
    assert(view.get_size() == moved.get_size());
    assert(std::memcmp(view.get_data(), moved.get_data(), view.get_size()) == 0);

    // 7. Изменение емкости
    moved.set_capacity(32);
    assert(moved.get_capacity() == 32);
    assert(std::memcmp(moved.get_data(), text, sizeof(text)) == 0);

    std::cout << "All Buffer tests passed\n";
    return 0;
}