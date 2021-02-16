# voj-tool
Load and submit VOJ problems on Codeforces from the terminal.<br/>
(Also please bear with me for this horrible coding style, I'm just a beginner.)

# Requirements
- GNU GCC (that supports C++11 or later)
- (Highly recommended) <a href="https://github.com/xalanq/cf-tool">cf-tool</a> (for submitting problems)
- Currently works in Unix systems (needs extra editing to work on Windows)

# Build
- Build using this command: `g++ -o voj voj.cpp -std=c++11`
- Set the environment variable to the directory `VOJ_PATH`
    + Open `~/.bash_profile`
    + Add this line: `export VOJ_PATH=path/to/VOJData`
    + Source the file: `source ~/.bash_profile`

# Usage
Open the problem inside the your default browser: <br/>
    `voj open [problem]`

Submit the solution for the problem:<br/>
    `voj submit [problem]`

# Dependencies
- <a href="https://github.com/nlohmann/json">nlohmann/json</a> (already included in the repo)
