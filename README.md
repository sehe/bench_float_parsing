For context, see http://stackoverflow.com/questions/17465061/how-to-parse-space-separated-floats-in-c-quickly/17479702

### compile

    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON .
    make

### run

To get statistical measures:

    ./bench_float_parsing

To create the interactive HTML chart

    ./bench_float_parsing -r html -o bench_float_parsing.html

### generating testdata

You can generate testdata with command like

    LANG=C od -f -A none --width=12 /dev/urandom | head -n 10000 > input.txt
