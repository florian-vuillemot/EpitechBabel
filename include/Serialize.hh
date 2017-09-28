//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_SERIALIZE_H
#define EPITECHBABEL_SERIALIZE_H

#include <tuple>
#include <memory>
#include "IConfig.hh"


#include <stdlib.h>

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
for_each_tuple(std::tuple<Tp...> const &)
{ }

template<std::size_t I = 0, typename... Tp, typename First, typename ...Args>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
for_each_tuple(std::tuple<Tp...> const & t, First &f, Args &... args)
{
    f = std::get<I>(t);
    for_each_tuple<I + 1, Tp...>(t, args...);
}


template <typename Type>
class Serialize
{
    using typeSize = unsigned int;

public:
    bool init(IConfig const &) noexcept {
        return true;
    }

    bool create(typeSize size, std::unique_ptr<Type> &&ptr) noexcept  {
        this->size = size;
        this->ptr = std::move(ptr);
        return true;
    }

    template <typename ... Args>
    bool create(typeSize size, Args* ...ptr) noexcept  {
        this->ptr = std::unique_ptr<Type>(ptr...);
        this->size = size;
        return true;
    }

    std::unique_ptr<Type> &&getData() noexcept  {
        return std::move(this->ptr);
    }

    typeSize getSize() const noexcept  {
        return this->size;
    }

    bool available() const noexcept  {
        return this->ptr.operator bool();
    }

private:
    std::unique_ptr<Type> ptr;
    typeSize size;
};

class SerializeParse
{
public:
    template<typename First, typename Second, typename ...Args>
    std::unique_ptr<char> load(std::unique_ptr<char> &&bitfield, First &f, Second &s, Args &... args) const noexcept
    {
        auto * const refPtr = bitfield.release();
        auto const *ptr = static_cast<void const *>(refPtr);
        auto const tuple = createFromBitfield<First, Second, Args...>(ptr);

        for_each_tuple(tuple, f, s, args...);

        return std::unique_ptr<char>(refPtr);
    }

    template<typename First, typename Second, typename ...Args>
    std::unique_ptr<char> serialize(std::unique_ptr<char> &&bitfield, First const f, Second const s, Args const... args) const noexcept
    {
        auto *const refPtr = bitfield.release();
        auto *ptr = static_cast<char *>(refPtr);

        writeOnBuffer(ptr, f, s, args...);

        return std::unique_ptr<char>(refPtr);
    }

private:
    template <typename Last>
    std::tuple<Last> createFromBitfield(void const *bitfield) const noexcept
    {
        return std::make_tuple(*static_cast<Last const *>(bitfield));
    }

    template <typename First, typename Second, typename ...Args>
    std::tuple<First, Second, Args...> createFromBitfield(void const *bitfield) const noexcept
    {
        auto const *ptr = static_cast<First const *>(bitfield);
        First const a = *ptr;
        auto const *nextPtr = static_cast<void const *>(ptr + 1);

        return std::tuple_cat (std::make_tuple(a), createFromBitfield<Second, Args...>(nextPtr));
    }

    template <typename Last>
    void writeOnBuffer(void *bitfield, Last const last) const noexcept
    {
        *static_cast<Last *>(bitfield) = last;
    }

    template <typename First, typename Second, typename ...Args>
    void writeOnBuffer(void *bitfield, First const f, Second const s, Args const... args) const noexcept
    {
        auto *ptr = static_cast<First *>(bitfield);
        auto *nextPtr = static_cast<void *>(ptr + 1);

        *ptr = f;

        writeOnBuffer(nextPtr, s, args...);
    }
};

#endif //EPITECHBABEL_SERIALIZE_H
