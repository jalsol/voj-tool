# voj-tool
Load and submit VOJ problems on Codeforces from the terminal.
The JSON library used is <a href="https://github.com/nlohmann/json">nlohmann/json</a> (for parsing JSON files)
(Also please bear with me for this horrible coding style, I'm just a beginner.)

# Requirements
- GNU GCC (that supports C++11 or later)
- (Highly recommended) <a href="https://github.com/xalanq/cf-tool">cf-tool</a> (for submitting problems)
- Currently works in Unix systems (needs extra editing to work for Windows)

# Build
- Change the variable `g_HomeDirectory` to the location of the `VOJData` folder
- Build using this command: `g++ -o voj voj.cpp -std=c++11`

# Usage
Open a problem inside the default browser:
    `voj open [problem]`

Submit to a problem:
    `voj submit [problem]`
