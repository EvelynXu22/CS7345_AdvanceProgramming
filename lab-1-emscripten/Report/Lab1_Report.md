# Lab1

**Yiwen Xu**	

**48377645**

## Setup the Emscripten

I completed the installation by following the instructions in the [official documentation](https://emscripten.org/docs/getting_started/downloads.html).

### Download and install using emsdk

```shell
# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git
```

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5xsyps9u7j20vu0b0dhz.jpg" alt="image-20220906145739142" style="zoom:50%;" />

```shell
# Fetch the latest version of the emsdk (not needed the first time)
git pull


# Download and install the latest SDK tools.
# Will installed nodejs, python, etc.
./emsdk install latest

# Make the "latest" SDK "active" for the current user. (writes .emscripten file)
./emsdk activate latest

# Activate PATH and other environment variables in the current terminal
source ./emsdk_env.sh
```

- Install

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5xsylkxtbj217e0iujyb.jpg" alt="image-20220906150441325" style="zoom:50%;" />

- Activate SDK

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5xsyap1bgj20wk0eygom.jpg" alt="image-20220906150556494" style="zoom:50%;" />

- Activate PATH

![image-20220906205125440](https://tva1.sinaimg.cn/large/e6c9d24egy1h5xsyetepwj20gh072q47.jpg)

### Verifying the installation

```shell
emcc -- version
```

- Verify

![image-20220906210633158](https://tva1.sinaimg.cn/large/e6c9d24egy1h5xtduv5jzj20gh02u74m.jpg)

#### Running Emscripten

We can now compile C/C++ file to JavaScript.

Note: Our newly opened terminal window is not capable of executing `emcc` and needs to be activated each time with the following command.

```shell
cd emsdk
./emsdk activate latest
source ./emsdk_env.sh
```



First, we create a C++ file:`hello_world.cpp`.

```cpp
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]){
    cout << "hello world\n";
    return 0;
}
```

To build the JavaScript version of this code. We open a new terminal, active `emcc`. Go from this terminal window to the folder where you saved this C++ file. Then execute the following command in the terminal.

```shell
emcc hello_world.cpp -o index.html
```

After that, we get three files:

- index.html
- index.js
- index.wasm

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5xx30wyy2j206l04yweh.jpg" alt="image-20220906231429961"  />

Open the HTML file through Live Sever. We can see `hello world` shows correctly on this page.

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5xx5ox1m9j21370bcaah.jpg" alt="image-20220906231700819" style="zoom:50%;" />



## Identify code base

I wrote a Fibonacci output function based on C++ language as a code base.

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5zoj6c7qvj20u00uedjx.jpg" alt="image-20220908114936324" style="zoom:50%;" />



## Test code base compiling

Then I used the same way and commands before to verify code base is functional and to ensure compiling is possible.

```shell
emcc fib.cpp -o fib.html
```

I get three new files which can run through Live Server.

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5zpg1sp5lj20cs09omxd.jpg" alt="image-20220908122123887" style="zoom:50%;" />

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h5zpdq5604j20y00u0wfu.jpg" alt="image-20220908121904867" style="zoom:50%;" />



## Build code base to WebAssembly

Deleted those three transpiling files before. We now only compile WebAssembly file and JavaScript file with `emcc`.

First, I changed part of the code base to prepare a interface. And return `1` to prove that all work is done.

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h60rrzczn3j20bn0ds3yw.jpg" alt="image-20220909102736722" style="zoom: 50%;" />

Then, compile it with this command below:

```shell
Fibonacci % emcc fib.cpp -o fib.js -s EXPORTED_FUNCTIONS=_getFib -s EXPORTED_RUNTIME_METHODS=ccall
```

Create an a `test.js` and `index.html` file to call `getFib` method and show the execution time on console.

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h60ry9ath9j20f90693yv.jpg" alt="image-20220909103338485" style="zoom:67%;" />



<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h60rx021krj20yc0pswgr.jpg" alt="image-20220909103227104" style="zoom:50%;" />

## Compare execution time

In this step, I ran this code base 100 times both in C++ and in browser and save the results in `cpp_time.txt` and `browser_time.txt`.

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h61ggnai0gj20yc0psn1v.jpg" alt="image-20220910004143015" style="zoom:50%;" />

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h61ghw5nrmj20xq0u0jve.jpg" alt="image-20220910004255045" style="zoom:50%;" />

Next, I wrote a python-based code for running time analysis and confidence interval calculation, named `confidenceInterval.py`. This function read the results were saved before and calculate confidenceInterval with `numpy` and `scipy`.

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h61gnoxmc3j210g0ocdjj.jpg" alt="image-20220910004828440" style="zoom:50%;" />

As the screenshot before, we can get 95% confidence interval:

- native (C++): (0.10579144538509686, 0.14679045461490317)
- WASM-based code: (0.5419682017893873, 1.228425798206798)

According to these execution time, we can see WASM-based code takes about 10 times longer to execute than the native code.

However, the data distribution does not conform to a normal distribution. The data distribution is shown below.

**Nativa Code Runtime Distribution:**

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h61jhcuaepj20yg0ou3zk.jpg" alt="image-20220910022612849" style="zoom: 33%;" />

**WASM-based Code Runtime Distribution:**<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h61jj11i9zj20yg0ou0ti.jpg" alt="image-20220910022749660" style="zoom: 33%;" />

And we can also see that there are some unusually large values. In my analysis, the reason for such large differences could be that there are times when the memory is over-occupied by other processes during the running of the program, resulting in a few particularly irregular runtime values that are particularly large.

Since these problems may have caused errors in the mean and standard values, we can learn that the confidence intervals obtained can be considered statistically insignificant.

## Improve performance

We can optimize by specifying the optimization flags, which are:-O0, -O1, -O2, -Os, -Oz, -O3. Here I choose -O2 level optimization for compiled.

```shell
Fibonacci % emcc -O2 fib.cpp -o fib.js -s EXPORTED_FUNCTIONS=_getFib -s EXPORTED_RUNTIME_METHODS=ccall
```

After running this function 100 times and saving the output to `browser_O2_time.txt', we can get its 95% confidence interval in the same way as before.

- native (C++): (0.10579144538509686, 0.14679045461490317)
- WASM-based code: (0.5419682017893873, 1.228425798206798)

- WASM-based code (-O2): (0.07599345381156607, 0.16062854619367917)

**WASM-based Code (-O2) Runtime Distribution:**

<img src="https://tva1.sinaimg.cn/large/e6c9d24egy1h620m2ct7dj20yg0ougmh.jpg" alt="image-20220910121853080" style="zoom: 33%;" />

Although its distribution is also skewed and can be considered statistically insignificant, we can still learn that it is actually much faster than the WASM-based code without any optimization, and its performance is even close to that of the native code.
