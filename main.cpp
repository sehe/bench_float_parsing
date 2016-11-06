#include "strategies.h"
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

template <typename parser, typename data_t = typename parser::data_t, typename reader, size_t expectedN = 10000>
size_t generic_method(reader const& source)
{
    data_t data;
    data.reserve(expectedN);

    auto range = source.get_data();
    auto f = range.begin();
    auto l = range.end();

    return parser().parse(f, l, data);
}

template <typename data_t, size_t expectedN = 10000>
size_t scanf_method()
{
    data_t data;
    data.reserve(expectedN);

    FILE* file = fopen("input.txt", "r");
    if (NULL == file) {
        printf("Failed to open 'input.txt'");
        return 255;
    }
    typename data_t::value_type tmp;
    do {
        int nItemsRead = fscanf(file,"%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
        if (3 != nItemsRead)
            break;
        data.push_back(tmp);
    } while (1);

    return data.size();
}

#include <nonius/benchmark.h++>

//NONIUS_BENCHMARK("scanf_method", []{ scanf_method<data::float3_vector>(); })
NONIUS_BENCHMARK("scanf", []{ return scanf_method<data::float3_vector>(); })
NONIUS_BENCHMARK("qi_struct", [] {
        source::mapped_file source;
        return generic_method<strategies::qi_phrase_parse<data::float3_vector, source::mapped_file::iterator> >(source); 
    })
NONIUS_BENCHMARK("qi", [] {
        source::mapped_file source;
        return generic_method<strategies::qi_phrase_parse<data::float_vector, source::mapped_file::iterator> >(source); 
    })
NONIUS_BENCHMARK("qi_struct_iostreams", [] {
        source::iostreams source;
        return generic_method<strategies::qi_phrase_parse<data::float3_vector, source::iostreams::iterator> >(source); 
    })
NONIUS_BENCHMARK("qi_iostreams", [] {
        source::iostreams source;
        return generic_method<strategies::qi_phrase_parse<data::float_vector, source::iostreams::iterator> >(source); 
    })

NONIUS_BENCHMARK("x3_struct", [] {
        source::mapped_file source;
        return generic_method<strategies::x3_phrase_parse<data::float3_vector, source::mapped_file::iterator> >(source); 
    })
NONIUS_BENCHMARK("x3", [] {
        source::mapped_file source;
        return generic_method<strategies::x3_phrase_parse<data::float_vector, source::mapped_file::iterator> >(source); 
    })
NONIUS_BENCHMARK("x3_struct_iostreams", [] {
        source::iostreams source;
        return generic_method<strategies::x3_phrase_parse<data::float3_vector, source::iostreams::iterator> >(source); 
    })
NONIUS_BENCHMARK("x3_iostreams", [] {
        source::iostreams source;
        return generic_method<strategies::x3_phrase_parse<data::float_vector, source::iostreams::iterator> >(source); 
    })
#include <nonius/main.h++>
