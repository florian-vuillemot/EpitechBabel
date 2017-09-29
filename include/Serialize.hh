//
// Created by florian on 28/09/17.
//

#ifndef EPITECHBABEL_SERIALIZE_H
#define EPITECHBABEL_SERIALIZE_H

#include <tuple>
#include <memory>
#include <type_traits>
#include "IConfig.hh"

#include <iostream>

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


template <typename T>
class Serialize
{
public:
    using typeSize = unsigned int;
    using type = T;
    using typePtr = std::unique_ptr<type>;

public:
    bool init(IConfig const &) noexcept {
        return true;
    }

    bool create(typeSize size, typePtr &&ptr) noexcept  {
        this->size = size;
        this->ptr = std::move(ptr);
        return true;
    }

    template <typename ... Args>
    bool create(typeSize size, Args* ...ptr) noexcept  {
        this->ptr = typePtr(ptr...);
        this->size = size;
        return true;
    }

    typePtr &&getData() noexcept  {
        return std::move(this->ptr);
    }

    typeSize getSize() const noexcept  {
        return this->size;
    }

    bool available() const noexcept  {
        return this->ptr.operator bool();
    }

private:
    typePtr ptr;
    typeSize size;
};

class SerializeParse
{
public:
    /**
     * Load var_arg from bitfield with type of template.
     * @param bitfield
     * @param f
     * @param s
     * @param args
     * @return
     */
    template<typename First, typename Second, typename ...Args>
    std::unique_ptr<char> load(std::unique_ptr<char> &&bitfield, First &f, Second &s, Args &... args) const noexcept
    {
        auto * const refPtr = bitfield.release();
        auto const *ptr = static_cast<void const *>(refPtr);
        auto const tuple = createFromBitfield<First, Second, Args...>(ptr);

        for_each_tuple(tuple, f, s, args...);

        return std::unique_ptr<char>(refPtr);
    }

    /**
     * Put var_arg in bitfield
     * @param bitfield
     * @param f
     * @param s
     * @param args
     * @return
     */
    template<typename First, typename Second, typename ...Args>
    std::unique_ptr<char> serialize(std::unique_ptr<char> &&bitfield, First const f, Second const s, Args const... args) const noexcept
    {
        auto *const refPtr = bitfield.release();
        auto *ptr = static_cast<char *>(refPtr);

        writeOnBuffer(ptr, f, s, args...);

        return std::unique_ptr<char>(refPtr);
    }

    /**
     * Return subfield from a field.
     * @param bitfield
     * @param first
     * @param number
     * @return <BitField get, bitfield given>
     */
    template <typename T, typename TNum>
    std::pair<std::unique_ptr<T>, std::unique_ptr<T>> getField(std::unique_ptr<T> &&bitfield, TNum const number, TNum const first = 0) const noexcept
    {
        static_assert(std::is_void<T>::value == false, "Can't handle move on a void*.");
        static_assert(std::is_integral<TNum>::value, "Need a integral type for iterate.");

        auto *const refPtr = bitfield.release();
        auto *cpy = static_cast<T *>(refPtr) + first;
        auto *ptrRes = new T[number];

        for (decltype(auto) i = 0; i < number; ++i){
            ptrRes[i] = cpy[i];
        }

        return std::pair(std::unique_ptr<T>(ptrRes), std::unique_ptr<T>(refPtr));
    }

    /**
     * Copy number bit from setterField in bitfield.
     * @param bitfield
     * @param setterField
     * @param number
     * @param firstBitField
     * @param firstSetField
     * @return <BitField transform, setterField>
     */
    template <typename T, typename TNum>
    std::pair<std::unique_ptr<T>, std::unique_ptr<T>> setField(std::unique_ptr<T> &&bitfield, std::unique_ptr<T> &&setterField, TNum const number, TNum const firstBitField = 0, TNum const firstSetField = 0) const noexcept
    {
        static_assert(std::is_void<T>::value == false, "Can't handle move on a void*.");
        static_assert(std::is_integral<TNum>::value, "Need a integral type for iterate.");

        for (decltype(auto) i = 0; i < number; ++i){
            bitfield.get()[i + firstBitField] = setterField.get()[i + firstSetField];
        }

        return std::pair(std::move(bitfield), std::move(setterField));
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
