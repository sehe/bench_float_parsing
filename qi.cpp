#include "common.h"
#include "strategies.h"
#include <boost/spirit/include/qi.hpp>
#include <iostream>

namespace qi = boost::spirit::qi;

namespace strategies 
{
    template <typename data_t, typename source_it>
        size_t qi_phrase_parse<data_t, source_it>::parse(source_it f, source_it l, data_t& data) const {
            using namespace qi;
            bool ok = phrase_parse(f,l,(double_ > double_ > double_) % eol, blank, data);
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

    template struct qi_phrase_parse<std::vector<float>, char const*>;
    template struct qi_phrase_parse<std::vector<float>, std::vector<char>::const_iterator>;
    template struct qi_phrase_parse<std::vector<data::float3>, char const*>;
    template struct qi_phrase_parse<std::vector<data::float3>, std::vector<char>::const_iterator>;
}
