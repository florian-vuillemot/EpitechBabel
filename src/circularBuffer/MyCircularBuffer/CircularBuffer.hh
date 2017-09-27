#ifndef MY_CIRCULAR_BUFFER
#define MY_CIRCULAR_BUFFER

#include <optional>
#include <queue>
#include "../../../include/ICircularBuffer.hh"

class IConfig;

template <typename T>
class CircularBuffer : public ICircularBuffer<T>
{
    using containerType = std::queue<T>;
    using sizeType = size_t;

public:
    bool init(IConfig const &) noexcept {
        this->size = 5;
        return true;
    }

    void put(T &&e) noexcept {
        this->container.push(std::move(e));

        this->resize();
    }

    T &&get() noexcept {
        auto &&res = std::move(this->container.front());

        this->container.pop();
        return std::move(res);
    }

    bool canGet() const noexcept {
        return !this->container.empty();
    }

private:
    void resize(){
        while (this->container.size() > this->size){
            this->container.pop();
        }
    }

private:
    containerType container;
    sizeType size;
};

#endif