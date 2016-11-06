> ### UPDATE
Since Spirit X3 is available for testing, I've updated the benchmarks. Meanwhile I've used [Nonius](https://github.com/rmartinho/nonius) to get statistically sound benchmarks.
>
> All charts below are available [interactive online](http://stackoverflow-sehe.s3.amazonaws.com/7c513b34-6e06-4115-b3c3-ee040e7b13bd/bench_float_parsing.html)
>
> Benchmark CMake project + testdata used is on github: https://github.com/sehe/bench_float_parsing/blob/master/bench_float_parsing.html

### Summary:

Spirit parsers are fastest. If you can use C++14 consider the experimental version Spirit X3:

[![enter image description here][1]][1]

The above is measures using memory mapped files. Using IOstreams, it will be slower accross the board, 

[![enter image description here][2]][2]

but not as slow as `scanf` using C/POSIX `FILE*` function calls:

[![enter image description here][3]][3]

------

What follows is parts from the OLD answer

------

> I implemented the Spirit version, and ran a benchmark comparing to the other suggested answers. 
> 
> Here's my results, all tests run on the same body of input (515Mb of `input.txt`). See below for exact specs.
> 
> <img src="http://i.stack.imgur.com/i1jkm.png" width="200" />
> <br/>
> <sup>(wall clock time in seconds, average of 2+ runs)</sup>
> 
> To my own surprise, Boost Spirit turns out to be fastest, and most elegant:
> 
>  * handles/reports errors
>  * supports +/-Inf and NaN and variable whitespace
>  * no problems at all detecting the end of input (as opposed to the other mmap answer)
>  * looks nice:
> 
>         bool ok = phrase_parse(f,l,               // source iterators
>              (double_ > double_ > double_) % eol, // grammar
>              blank,                               // skipper
>              data);                               // output attribute
> 
> Note that `boost::spirit::istreambuf_iterator` was unspeakably much slower (15s+). I hope this helps!
> 
> ## Benchmark details
> 
> All parsing done into `vector` of `struct float3 { float x,y,z; }`.
> 
> Generate input file using
> 
>     od -f -A none --width=12 /dev/urandom | head -n 11000000
> 
> This results in a 515Mb file containing data like
> 
>          -2627.0056   -1.967235e-12  -2.2784738e+33
>       -1.0664798e-27  -4.6421956e-23   -6.917859e+20
>       -1.1080849e+36   2.8909405e-33   1.7888695e-12
>       -7.1663235e+33  -1.0840628e+36   1.5343362e-12
>       -3.1773715e-17  -6.3655537e-22   -8.797282e+31
>         9.781095e+19   1.7378472e-37        63825084
>       -1.2139188e+09  -5.2464635e-05  -2.1235992e-38
>        3.0109424e+08   5.3939846e+30  -6.6146894e-20
> 
> Compile the program using:
> 
>     g++ -std=c++0x -g -O3 -isystem -march=native test.cpp -o test -lboost_filesystem -lboost_iostreams
> 
> Measure wall clock time using
> 
>     time ./test < input.txt 

## Environment:

 *  Linux desktop 4.2.0-42-generic #49-Ubuntu SMP x86_64
 *  Intel(R) Core(TM) i7-3770K CPU @ 3.50GHz
 *  32GiB RAM

## Full Code

Full code to the old benchmark is in the [edit history of this post](http://stackoverflow.com/revisions/17479702/3), the newest version is [on github](https://github.com/sehe/bench_float_parsing/blob/master/bench_float_parsing.html)

  [1]: https://i.stack.imgur.com/cdKQw.png
  [2]: https://i.stack.imgur.com/Sf9Al.png
  [3]: https://i.stack.imgur.com/wDuBR.png

