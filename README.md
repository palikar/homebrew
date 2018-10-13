# Abstract

`homebrew` is just my personal C++ stuff that I just &ldquo;kind of write&rdquo;. It&rsquo;s a collection of utilities, programs and APIs that I&rsquo;ve either written or have found somewhere on the internet and have modified them a little bit. The idea is to keep all my C++ code that is not part of a bigger application but rather it can be reused here and there. The are however also several concrete runnable programs here that I&rsquo;ve deemed as &ldquo;necessary&rdquo;&#x2026; at least for me.


# Installation.

Clone the repository, create a build folder and build with `cmake` and `make`. An install target is also available. The scripts `build.sh`, `buil_and_run.sh` and `run.sh` are there just o make the whole building process easier form the root directory of the project. The whole installation should look something like:

```sh
git clone https://github.com/palikar/homebrew
cd homebrew
mkdir build_debug
cmake .. -DCMAKE_INSTALL_PREFIX="/usr" -DCMAKE_BUILD_TYPE="Debug"
make -j4 && make install
```


# Program utilities


## Wgrep

The `wgrep` program runs a regular expression on an entire file, not diving it line by line. My idea is to have one extra utility to be used in conjunction with `grep`, `sed` and `awk`. Loading a whole file in search space is considered a bad practice but if you use it responsibly, you shouldn&rsquo;t have any problems. A thing to consider is that if the examined file shouldn&rsquo;t be too big as it is loaded into memory. I don&rsquo;t know what would happen if there isn&rsquo;t enough memory to hold the file, so..&ldquo;undefined behavior&rdquo; I guess.

    Usage:  wgrep file expr [options] 
    Runs regex on a whole file. (I've always wanted this and its pretty dangeraous but ahhh, fuckt it!):
      --help                produce help message
      -f [ --file ] arg     file to match against
      -m [ --match ] arg    matches to print if there are more than one
      -e [ --expr ] arg     regex to run on the file
    Version: 1.0.0


# Programming utilities


## Utils

*Header: homebrew/utils.hpp* Some useful function which functionality I found myself using again and again. If a particular task is common enough, I abstract it away in function and put it here. There is no general category for the function in here.

-   `template<class T> int dump(const std::vector<T>& vec, const std::string& file)`

Dumps the content of a vector (`vec`) in a file (`file`).

-   `template<class T> int load(std::vector<T>& vec, const std::string& file)`

Loads the contents of a file (`file`) into a vector (`vev`) on a per line basis.

-   `std::vector<std::vector<std::string>> regex_file(const std::string& file, const std::string& regex)`

Runs regular expression (`regex`) on the contents of a file (`file`). Return a vector of vectors. The first dimension contains the individual matches and the second the matched groups of the corresponding match.

-   `std::string make_usage_string(const std::string& program_name, const po::options_description& desc, po::positional_options_description& p)`

Generates a nice(ish) &ldquo;help&rdquo;-string for program&rsquo;s options. The string also contains the USAGE.
