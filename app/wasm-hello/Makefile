all:
	# clang --target=wasm32 -emit-llvm -c -S math.c
	# llc -march=wasm32 -filetype=obj math.ll
	# wasm-objdump -x math.o > math.wat
	# wasm-ld-10 --no-entry --export-all -o math.wasm math.o
	clang --target=wasm32 -O3 -flto -nostdlib -Wl,--no-entry -Wl,--export-all -Wl,--lto-O3 -o math.wasm math.c