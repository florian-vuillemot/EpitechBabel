#ifndef ICIRCULAR_BUFFER
#define ICIRCULAR_BUFFER

template <typename T>
class ICircularBuffer
{
public:
    /**
     * Put element.
     */
    virtual void put(T &&) noexcept = 0;
    /**
     * Return element.
     * @return
     */
    virtual T&& get() noexcept = 0;
    /**
     * Return true if you can get element.
     * @return
     */
    virtual bool canGet() const noexcept = 0;
};

#endif