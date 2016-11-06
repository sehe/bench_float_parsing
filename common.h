#pragma once
#include <boost/fusion/adapted.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <fstream>
#include <iterator>

namespace data {
    struct float3 {
        float x, y, z;
    };
    using float3_vector = std::vector<float3>;
    using float_vector = std::vector<float>;
}

BOOST_FUSION_ADAPT_STRUCT(data::float3, x, y, z)

namespace source {
    struct mapped_file {
        boost::iostreams::mapped_file mmap{ "input.txt", boost::iostreams::mapped_file::readonly };
        using iterator = char const*;
        boost::iterator_range<iterator> get_data() const { 
            return { mmap.const_data(), mmap.const_data() + mmap.size() }; 
        }
    };

    struct iostreams {
        std::ifstream ifs{"input.txt"};
        std::istreambuf_iterator<char> f_{ifs >> std::noskipws}, l_;
        std::vector<char> v{f_, l_};
        using iterator = std::vector<char>::const_iterator;
        boost::iterator_range<iterator> get_data() const { return { v.begin(), v.end() }; }
    };
}
