#include "common.h"

namespace strategies 
{
    template <typename data_t> struct strtod;

    template <> struct strtod<std::vector<float> > {
        template <typename It>
        size_t parse(It f, It l, std::vector<float>& data) const {
            errno = 0;
            char* next = nullptr;
            while (errno == 0 && f && f<(l-12) ) {
                data.push_back(::strtod(f, &next)); f = next;
                data.push_back(::strtod(f, &next)); f = next;
                data.push_back(::strtod(f, &next)); f = next;
            }
            return data.size();
        }
    };

    template <typename data_t> struct strtod {
        using It = typename boost::range_value<decltype(std::declval<data_t>().get_data())>::type;

        size_t parse(It f, It l, data_t& data) const {
            errno = 0;
            char* next = nullptr;
            while (errno == 0 && f && f<(l-12) ) {
                auto x = ::strtod(f, &next); f = next;
                auto y = ::strtod(f, &next); f = next;
                auto z = ::strtod(f, &next); f = next;
                data.push_back({x,y,z});
            }
            return data.size();
        }
    };

    template <typename _data_t, typename source_it> struct qi_phrase_parse {
        using data_t = _data_t;
        size_t parse(source_it f, source_it l, data_t& data) const;
    };

    extern template struct qi_phrase_parse<std::vector<float>, char const*>;
    extern template struct qi_phrase_parse<std::vector<float>, std::vector<char>::const_iterator>;
    extern template struct qi_phrase_parse<std::vector<data::float3>, char const*>;
    extern template struct qi_phrase_parse<std::vector<data::float3>, std::vector<char>::const_iterator>;

    template <typename _data_t, typename source_it> struct x3_phrase_parse {
        using data_t = _data_t;
        size_t parse(source_it f, source_it l, data_t& data) const;
    };

    template <typename source_it> struct x3_phrase_parse<data::float_vector, source_it> {
        using data_t = data::float_vector;
        size_t parse(source_it f, source_it l, data_t& data) const;
    };

    extern template struct x3_phrase_parse<std::vector<float>, char const*>;
    extern template struct x3_phrase_parse<std::vector<float>, std::vector<char>::const_iterator>;
    extern template struct x3_phrase_parse<std::vector<data::float3>, char const*>;
    extern template struct x3_phrase_parse<std::vector<data::float3>, std::vector<char>::const_iterator>;
}
