#include "common.h"
#include "strategies.h"
#include <boost/spirit/home/x3.hpp>
#include <iostream>

namespace x3 = boost::spirit::x3;

namespace strategies 
{
    template <typename data_t, typename source_it>
        size_t x3_phrase_parse<data_t, source_it>::parse(source_it f, source_it l, data_t& data) const {
            using namespace x3;
            static const auto r = x3::rule<struct _, typename data_t::value_type> {} = double_ > double_ > double_;
            bool ok = phrase_parse(f, l, r % eol, blank, data);
#ifdef DEBUG
            if (ok)   
                std::cout << "parse success\n";
            else 
                std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

            if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
            std::cout << "data.size(): " << data.size() << "\n";
#endif
            return data.size();
        }

    template <typename source_it>
        size_t x3_phrase_parse<data::float_vector, source_it>::parse(source_it f, source_it l, data::float_vector& data) const {
            using namespace x3;
            bool ok = phrase_parse(f, l, *double_, space, data);
#ifdef DEBUG
            if (ok)   
                std::cout << "parse success\n";
            else 
                std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

            if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";
            std::cout << "data.size(): " << data.size() << "\n";
#endif
            return data.size();
        }

    template struct x3_phrase_parse<std::vector<float>, char const*>;
    template struct x3_phrase_parse<std::vector<float>, std::vector<char>::const_iterator>;
    template struct x3_phrase_parse<std::vector<data::float3>, char const*>;
    template struct x3_phrase_parse<std::vector<data::float3>, std::vector<char>::const_iterator>;
}
