//
// Created by florian on 29/09/17.
//

#ifndef EPITECHBABEL_SERIALIZEPARSE_HH
#define EPITECHBABEL_SERIALIZEPARSE_HH

#include <tuple>
#include <type_traits>
#include <memory>
#include <netinet/in.h>

namespace Serialize {

    template<std::size_t I = 0, typename... Tp>
    inline typename std::enable_if<I == sizeof...(Tp), void>::type
    for_each_tuple(std::tuple<Tp...> const &) {}

    template<std::size_t I = 0, typename... Tp, typename First, typename ...Args>
    inline typename std::enable_if<I < sizeof...(Tp), void>::type
    for_each_tuple(std::tuple<Tp...> const &t, First &f, Args &... args) {
        f = std::get<I>(t);
        for_each_tuple<I + 1, Tp...>(t, args...);
    }

    class SerializeParse {
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
        bit_field
        load(bit_field &&bitfield, First &f, Second &s, Args &... args) const noexcept {
            auto *const refPtr = bitfield.release();
            auto const *ptr = static_cast<void const *>(refPtr);
            auto const tuple = createFromBitfield<First, Second, Args...>(ptr);

            for_each_tuple(tuple, f, s, args...);

            return bit_field(refPtr);
        }

        /**
         * Put a variable in bitfield
         * @tparam First
         * @param bitfield
         * @param f
         * @return
         */
        template<typename First>
        bit_field
        serialize(bit_field &&bitfield, First const f) const noexcept {
            auto *const refPtr = bitfield.release();
            auto *ptr = static_cast<char *>(refPtr);

            writeOnBuffer(ptr, f);

            return bit_field(refPtr);
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
        bit_field
        serialize(bit_field &&bitfield, First const f, Second const s, Args const... args) const noexcept {
            auto *const refPtr = bitfield.release();
            auto *ptr = static_cast<char *>(refPtr);

            writeOnBuffer(ptr, f, s, args...);

            return bit_field(refPtr);
        }

        /**
         * Return subfield from a field.
         * @param bitfield not touch
         * @param number
         * @param first
         * @return <BitField create, bitfield given (not touch)>
         */
        template<typename T, typename TNum>
        std::pair <std::unique_ptr<T[]>, std::unique_ptr<T[]>>
        getField(std::unique_ptr <T[]> &&bitfield, TNum const number, TNum const first = 0) const noexcept {
            static_assert(std::is_void<T>::value == false, "Can't handle move on a void*.");
            static_assert(std::is_integral<TNum>::value, "Need a integral type for iterate.");

            auto *const refPtr = bitfield.release();
            auto *cpy = static_cast<T *>(refPtr) + first;
            auto *ptrRes = new T[number];

            for (TNum i = 0; i < number; ++i) {
                ptrRes[i] = cpy[i];
            }

            return std::pair(std::unique_ptr<T[]>(ptrRes), std::unique_ptr<T[]>(refPtr));
        }

        /**
         * Copy number bit from setterField in bitfield.
         * @param bitfield
         * @param setterField not touch
         * @param number
         * @param firstBitField
         * @param firstSetField
         * @return <BitField transform, setterField return not touch>
         */
        template<typename T,
                    typename TNum, typename TNumBitField = TNum, typename TNumSetField = TNum,
                    typename Type = std::remove_pointer<T>
                >
        std::pair <std::unique_ptr<T>, std::unique_ptr<T>>
        setField(std::unique_ptr <T> &&bitfield, std::unique_ptr <T> &&setterField, TNum const number,
                 TNumBitField const firstBitField = 0, TNumSetField const firstSetField = 0) const noexcept
        {
            static_assert(std::is_void<Type>::value == false, "Can't handle move on a void*.");
            static_assert(std::is_integral<TNum>::value, "Need a integral type for iterate.");
            static_assert(std::is_integral<TNumBitField>::value, "Need a integral type for iterate.");
            static_assert(std::is_integral<TNumSetField>::value, "Need a integral type for iterate.");

            for (TNum i = 0; i < number; ++i) {
                bitfield.get()[i + firstBitField] = setterField.get()[i + firstSetField];
            }

            return std::pair(std::move(bitfield), std::move(setterField));
        }

        template <typename Numeric>
        Numeric convertFromNetwork(Numeric const nb) const noexcept
        {
            return ntohl(nb);
        }

        template <typename Numeric>
        Numeric convertForNetwork(Numeric const nb) const noexcept
        {
            return htonl(nb);
        }

        template<typename Iterable, typename TNum,
                size_t sizeType = sizeof(typename Iterable::value_type)>
        bit_field toBitField(Iterable const &iterable, TNum const size) const
        {
            static_assert(std::is_integral<TNum>::value, "Need a integral type for iterate.");

            auto const sizeAlloc = size * sizeType;
            auto *alloc = new char[sizeAlloc];

            for (size_t i = 0, cursor = 0; i < size; ++i) {
                auto const *mem = (char const *)(&(iterable[i]));

                for (size_t cursorAlloc = 0; cursorAlloc < sizeType; ++cursorAlloc, ++cursor) {
                    alloc[cursor] = mem[cursorAlloc];
                }
            }

            return std::move(bit_field(alloc));
        }


    private:
        template<typename Last>
        std::tuple <Last> createFromBitfield(void const *bitfield) const noexcept {
            return std::make_tuple(*static_cast<Last const *>(bitfield));
        }

        template<typename First, typename Second, typename ...Args>
        std::tuple<First, Second, Args...> createFromBitfield(void const *bitfield) const noexcept {
            auto const *ptr = static_cast<First const *>(bitfield);
            First const a = *ptr;
            auto const *nextPtr = static_cast<void const *>(ptr + 1);

            return std::tuple_cat(std::make_tuple(a), createFromBitfield<Second, Args...>(nextPtr));
        }

        template<typename Last>
        void writeOnBuffer(void *bitfield, Last const last) const noexcept {
            *static_cast<Last *>(bitfield) = last;
        }

        template<typename First, typename Second, typename ...Args>
        void writeOnBuffer(void *bitfield, First const f, Second const s, Args const... args) const noexcept {
            auto *ptr = static_cast<First *>(bitfield);
            auto *nextPtr = static_cast<void *>(ptr + 1);

            *ptr = f;

            writeOnBuffer(nextPtr, s, args...);
        }
    };
}

#endif //EPITECHBABEL_SERIALIZEPARSE_HH
