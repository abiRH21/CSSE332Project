all: bootload shell kernel floppya.img loadFile run
run: floppya.img
	qemu-system-i386 -fda floppya.img -boot order=a &
bootload: bootload.asm
	nasm bootload.asm
floppya.img: bootload shell message.txt
	dd if=/dev/zero of=floppya.img bs=512 count=2880
	dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
	dd if=kernel of=floppya.img bs=512 conv=notrunc seek=3
	dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc
	dd if=bigmess.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc
	dd if=tstprg of=floppya.img bs=512 count=1 seek=30 conv=notrunc
	dd if=tstpr2 of=floppya.img bs=512 count=1 seek=30 conv=notrunc
	dd if=map.img of=floppya.img bs=512 count=1 seek=1 conv=notrunc
	dd if=dir.img of=floppya.img bs=512 count=1 seek=2 conv=notrunc
kernel.o: kernel.c
	bcc -ansi -c -o kernel.o kernel.c
kernel_asm.o: kernel.asm
	as86 kernel.asm -o kernel_asm.o
kernel: kernel_asm.o kernel.o
	ld86 -o kernel -d kernel.o kernel_asm.o
shell.o: shell.c
	bcc -ansi -c -o shell.o shell.c
lib.o: lib.asm
	as86 lib.asm -o lib.o
shell: lib.o shell.o
	ld86 -o shell -d shell.o lib.o
loadFile: loadFile.c
	gcc -o loadFile loadFile.c
	./loadFile shell
	./loadFile message.txt
	./loadFile bigmess.txt
	./loadFile tstprg
	./loadFile tstpr2
clean:
	rm -f kernel shell bootload *.o floppya.img loadFile





