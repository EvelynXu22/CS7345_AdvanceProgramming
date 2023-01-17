compile:
	clang++ -g -std=c++14 ./*.cpp -o output
	./output
emcc:
	# emcc -std=c++14 -O2 -pthread -s PROXY_TO_PTHREAD -s ALLOW_MEMORY_GROWTH=1 -s NO_DISABLE_EXCEPTION_CATCHING -s LLD_REPORT_UNDEFINED -s ERROR_ON_UNDEFINED_SYMBOLS=1 ./*.cpp -o index.html

	emcc -std=c++14 -O2 -pthread -s PROXY_TO_PTHREAD -s ALLOW_MEMORY_GROWTH=1 -s NO_DISABLE_EXCEPTION_CATCHING -s LLD_REPORT_UNDEFINED -s ERROR_ON_UNDEFINED_SYMBOLS=1 ./*.cpp -o example.js

	node --experimental-wasm-threads --experimental-wasm-bulk-memory example.js

	# emcc -std=c++14 -pthread -s PROXY_TO_PTHREAD -s ALLOW_MEMORY_GROWTH=1 -s NO_DISABLE_EXCEPTION_CATCHING -s LLD_REPORT_UNDEFINED -s ERROR_ON_UNDEFINED_SYMBOLS=1 ./*.cpp -o example.js -s EXPORTED_FUNCTIONS="['_Start','_Stop','_Kill','_Exit']" -s EXPORTED_RUNTIME_METHODS=ccall
	