all:
	emcc -lembind -o asm.js -I../csr-visual/include ../csr-visual/common/utils.cpp \
		 ../csr-visual/mstatus/main.cpp ../csr-visual/sstatus/main.cpp \
		 ../csr-visual/mie/main.cpp ../csr-visual/medeleg/main.cpp \
		 ../csr-visual/sie/main.cpp
	sed -i 's/^var Module/export &/g' asm.js
	sed -i 's/asm.wasm/app\/wasm\/asm.wasm/g' asm.js