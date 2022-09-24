all:
	emcc -lembind -o asm.js ../csr-visual/mstatus/main.cpp
	sed -i 's/^var Module/export &/g' asm.js
	sed -i 's/asm.wasm/app\/wasm\/asm.wasm/g' asm.js