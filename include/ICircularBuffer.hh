#ifndef ICIRCULAR_BUFFER
#define ICIRCULAR_BUFFER

#include "IConfig.hh"

template <typename T>
class ICircularBuffer
{
    /**
     * Thread safe
     */
public:
    /**
     * Load parameter of circular buffer.
     * @return
     */
    virtual bool init(IConfig const &) noexcept = 0;
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
    virtual bool canGet() noexcept = 0;
};

#endif