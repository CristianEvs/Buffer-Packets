#include "Buffer.hpp"

short getdata(char *buf, int start, int len) {
    int byteIndex = start / 8;
    int bitOffset = start % 8;
    short result = 0;

    for (int i = 0; i < len; ++i) {
        int currentBit = (buf[byteIndex] >> bitOffset) & 1;
        result |= (currentBit << i);

        bitOffset++;
        if (bitOffset == 8) {
            bitOffset = 0;
            byteIndex++;
        }
    }

    if (result & (1 << (len - 1))) {
        result |= ~((1 << len) - 1);
    }

    return result;
}

void putdata(char *buf, int start, int len, short value) {
    int byteIndex = start / 8;
    int bitOffset = start % 8;

    for (int i = 0; i < len; ++i) {
        int currentBit = (value >> i) & 1;

        if (currentBit) {
            buf[byteIndex] |= (1 << bitOffset);
        } else {
            buf[byteIndex] &= ~(1 << bitOffset);
        }

        bitOffset++;
        if (bitOffset == 8) {
            bitOffset = 0;
            byteIndex++;
        }
    }
}




int main() {
    char buf[20] = {0};

    // Пример использования putdata и getdata
    putdata(buf, 0, 11, 933); 
    std::cout << std::dec << getdata(buf, 0, 11) << std::endl;  // Должно вывести 933

    // Создание и использование BufferSection
    BufferSection bufferSection(buf, 0, 20);

    bufferSection.putdata(0, 11, 933);  
    std::cout << std::dec << bufferSection.getdata(0, 11) << std::endl;  // Должно вывести 933

    BufferSection subsection = bufferSection.createSubsection(10, 10);
    subsection.setByte(0, static_cast<unsigned char>(122));  
    std::cout << std::dec << (int)subsection.getByte(0) << std::endl;  // Должно вывести 122

    // Проверка оригинального буфера
    std::cout << std::dec << (int)bufferSection.getByte(10) << std::endl;  // Должно вывести 122

    return 0;
}