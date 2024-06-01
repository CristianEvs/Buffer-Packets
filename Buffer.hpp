
#ifndef BUFFERSECTION_H
#define BUFFERSECTION_H
#include <iostream>

short getdata(char *buf, int start, int len);
void putdata(char *buf, int start, int len, short value);

class BufferSection {
private:
    char *buffer;
    int offset;
    int size;

public:
    BufferSection(char *buf, int offset, int size) : buffer(buf), offset(offset), size(size) {}

    BufferSection(const BufferSection &other, int additionalOffset, int newSize)
        : buffer(other.buffer), offset(other.offset + additionalOffset), size(newSize) {}

    char getByte(int index) const {
        if (index >= 0 && index < size) {
            return buffer[offset + index];
        }
        throw std::out_of_range("Index out of range");
    }

    void setByte(int index, char value) {
        if (index >= 0 && index < size) {
            buffer[offset + index] = value;
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    BufferSection createSubsection(int subOffset, int subSize) const {
        if (subOffset >= 0 && (subOffset + subSize) <= size) {
            return BufferSection(buffer, offset + subOffset, subSize);
        }
        throw std::out_of_range("Subsection out of range");
    }

    short getdata(int start, int len) const {
        return ::getdata(buffer + offset, start, len);
    }

    void putdata(int start, int len, short value) {
        ::putdata(buffer + offset, start, len, value);
    }
};

#endif // BUFFERSECTION_H
