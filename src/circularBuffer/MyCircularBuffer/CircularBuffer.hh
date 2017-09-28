#ifndef MY_CIRCULAR_BUFFER
#define MY_CIRCULAR_BUFFER

#include <string>
#include <optional>
#include <queue>
#include "../../../include/ICircularBuffer.hh"

template <typename T>
class CircularBuffer : public ICircularBuffer<T>
{
    using containerType = std::queue<T>;
    using sizeType = size_t;

    std::string const label = "myCircularBuffer";
    std::string const sizeBuffer = "size";

public:
    bool init(IConfig const &conf) noexcept {
        if (conf.exist(CircularBuffer::label, CircularBuffer::sizeBuffer)){
            auto success = true;
            auto const &size = conf.get(CircularBuffer::label, CircularBuffer::sizeBuffer);

            try {
                this->size = std::stoi(size);
            }
            catch (std::exception const &e){
                std::cerr << "Init circular buffer:" << e.what() << std::endl;
                success = false;
            }
            return success;
        }
        return false;
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