Video:

- https://www.youtube.com/watch?v=nC1U1LJQL8o
- https://www.youtube.com/watch?v=1VnnbpHDBBA
- https://www.youtube.com/watch?v=R2WyBwZNuMI

sudo /etc/init.d/cron restart
sudo service cron reload


## Введение

1. Стадии компиляции
- Создание объектоных файлов
- Компановка исполняемого файла

2. Интерпретатор ELF (для линукс lib64/ld-linux-x...so)
- программа которая реально запускатся для загрузки и ращмещения в памяти
- выполняет поиск всех зависимых библиотек
- загружает в память библиоткеки и сам файл
- выделяет память на стеке
- передает упралвение на entry point

**Посмотреть список зависимостей**
```sh
air@air-virtual-machine:~/elf$ ldd foo
        linux-vdso.so.1 (0x00007ffd5677f000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff7731c0000)
        /lib64/ld-linux-x86-64.so.2 (0x00007ff7733f7000)
```

3. **Пример**
- Makefile
```makefile
first:
	echo "Pass: library, program-no-rpath or program-with-rpath"

program-no-rpath: library ./src/program.c
	mkdir bin || true
	gcc -o ./bin/program ./src/program.c \
	-L./lib -lmygreatlib
# gcc - являются оболочками для запуска ldd (динамический линковщик, интерпретатор elf)
# -L указывает где искать библиотеки
# -l указывает библиотеку


program-with-rpath: library ./src/program.c
	mkdir bin || true
	gcc -o ./bin/program ./src/program.c \
	-L./lib -lmygreatlib \
	-wl,-rpath,'$$ORIGIN/../lib/'

library: ./src/mygreatlib.c ./src/mygreatlib.h
	mkdir lib || true
	gcc -shared -fPIC -o ./lib/libmygreatlib.so ./src/mygreatlib.c
# -shared - итог компоновки будет elf файл без функции main
# -fPIC - обязательная для 64, генерация позиционно независимого кода, относительная позиционизация

clean:
	rm -f ./bin/program
	rm -f ./lib/libvmguestlib.so
```

- program.c
```c
#include "mygreatlib.h"

int main (int argc, char **argv){
    say_hello(argv[1]);
    return 0;
}
```

- mygreatlib.c
```c
#include "mygreatlib.h"

void say_hello(const char * to_whom){
    printf("Hellow, %s", to_whom);
}
```

- mygreatlib.h
```c
void			say_hello(const char * who_m);
```

  1. Запускаем сборку библиотеки
```sh
air@air-virtual-machine:~/elf$ make library
mkdir lib || true
gcc -shared -fPIC -o ./lib/libmygreatlib.so ./src/mygreatlib.c

# Создалась библиотека lib/libmygreatlib.so
```

  2. Запускаем сборку программы без указания rpath
```sh
air@air-virtual-machine:~/elf$ make program-no-rpath

# Собрался бинарник /bin/program
# Пробуем запустить

air@air-virtual-machine:~/elf$ ./bin/program
./bin/program: error while loading shared libraries: libmygreatlib.so: cannot open shared object file: No such file or directory

# Добавим переменую окружения LD_LIBRARY_PATH
air@air-virtual-machine:~/elf$ export LD_LIBRARY_PATH=/home/air/elf/lib
air@air-virtual-machine:~/elf$ ./bin/program Airat
Hellow, Airat

# Магия заключается в том что в elf есть секции DT_RPATH и DT_RUNPATH для поиска зависимостей
```
  3. Запускаем cборку с указание rpath
```sh
air@air-virtual-machine:~/elf$ make program-with-rpath
mkdir lib || true
mkdir: cannot create directory ‘lib’: File exists
gcc -shared -fPIC -o ./lib/libmygreatlib.so ./src/mygreatlib.c
mkdir bin || true
mkdir: cannot create directory ‘bin’: File exists
gcc -o ./bin/program ./src/program.c \
-L./lib -lmygreatlib \
-Wl,-rpath,'$ORIGIN/../lib/'

# Видим что тут корректно определилась зависимость
air@air-virtual-machine:~/elf$ ldd ./bin/program
        linux-vdso.so.1 (0x00007ffd8590d000)
        libmygreatlib.so => /home/air/elf/./bin/../lib/libmygreatlib.so (0x00007ff02d1b9000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff02cf84000)
        /lib64/ld-linux-x86-64.so.2 (0x00007ff02d1c5000)

air@air-virtual-machine:~/elf$ ./bin/program Airat
Hellow, Airat
```
<hr/>

## Структура ELF файла

```
            _________________________________
            |          File Header           | <- File offset 0x0
            |________________________________|
            |    Program (Segment) Header    |
            |               ...              |
            |    Program (Segment) Header    |
            |________________________________|
Segment ->  |             .interp            | <- Section 1
            |              .init             | <- Section 2
            |               ...              | <- Section N
            |              .text             | // Исполняемый машинный код
            |              .fini             |
            |             .rodata            | // read-only данные
            |               ...              |
            |________________________________| <- Section N
            |            .init_array         | <- Section M
            |            .fini_array         |
            |              .data             | // глобальные переменные
            |              .bss              | // не ициализированные данные
            |               ...              |
            |________________________________| <- Section Q
            |               ...              |
            |             .comment           |
            |             .strtab            | // таблица строк, посути линки
            |               ...              |
Segment ->  |________________________________|
            |          Section Header        |
            |               ...              |
            |          Section Header        |
            |________________________________|
```

## Заголовок ELF файла `readelf -h /bin/ls`

```
typedef struct {
    unsigned char e_ident[EI_NIDENT];
    uint16_t      e_type;
    uint16_t      e_machine;
    uint32_t      e_version;
    ElfN_Addr     e_entry;
    ElfN_Off      e_phoff;
    ElfN_Off      e_shoff;
    uint32_t      e_flags;
    uint16_t      e_ehsize;
    uint16_t      e_phentsize;
    uint16_t      e_phnum;
    uint16_t      e_shentsize;
    uint16_t      e_shnum;
    uint16_t      e_shstrndx;
} ElfN_Ehdr;
```

1. **Заголовок файла `e_ident` 16 байт**

```
unsigned char e_ident[EI_NIDENT = 16];

7f 45 4c 46 02 01 01 00   00 00 00 00 00 00 00 00
|  |  |  |  |  |  |  |    |  |  |  |  |  |  |  |
----------  -  -  -  -    -  -------------------
   Magic    Cl Dt V  OS   AB      Padding
```

- Magic - магическое число 7f 45 4с 46 - соотвествет `.ELF` (EI_MAG0, EI_MAG1, EI_MAG2, EI_MAG3);
- Cl - EI_CLASS (0 - None (Invalid), 1 - ELFCLASS32(32 Bit), 2 - ELFCLASS64(64 Bit));
- Dt - EI_DATA (0 - Node (Invalid), 1 - ELFDATA2LSB (little-endian.), 2 - ELFDATA2MSB(big-endian))
- V - EI_VERSION (всегда 1)
- OS - EI_OSABI (тип ОС, 3 - Linux)
- AB - EI_ABIVERSION (кажется что часто 0)
- Padding - EI_PAD (отступ)

2. **Тип elf файла**

- ET_NONE = 0
- ET_REL = 1 перемещаемый файл (gcc -c foo.c -o foo.o)
- ET_EXEC = 2 исполняемы (radare2radare2ra

sugit )

- ET_DYN = 3 динамический файл, аля библиотеки
- ET_CORE = 3

3. **Адрес точки входа e_entry**
   Предоставляет виртуальный адрес, на который система сначала передает управление, тем самым запуская процесс. Если файл не имеет связанной точки входа, этот элемент содержит ноль. (для либ)

4. **Начало заголовка программы (Segment) e_phoff**
   Этот элемент содержит смещение файла таблицы заголовков программы в байтах. Если в файле нет таблицы заголовков программы, этот элемент содержит ноль.

5. **Начало заголовка разделов (Section) e_shoff**
   Этот элемент содержит смещение файла таблицы заголовка раздела в байтах. Если в файле нет таблицы заголовков разделов, этот элемент содержит ноль.

6. **Размер каждого заголовка программы (Segment) e_phentsize**
   Этот элемент содержит размер в байтах одной записи в таблице заголовка программы файла; все записи имеют одинаковый размер.

7. **Количество заголовков программы (Segment) e_phnum**

8. **Размер каждого заголовка разделов (Section) e_shentsize**
   Этот элемент содержит размер в байтах одной записи в таблице заголовка разделов файла; все записи имеют одинаковый размер.

9. Количество заголовков разделов (Section) e_shnum

10. Где находятся таблица строк имен разделов e_shstrndx
## Заголовок программы (Header Segment) `readelf --segments /bin/ls`, `readelf -l /bin/ls`

```
typedef struct {
    uint32_t   p_type;
    Elf32_Off  p_offset;
    Elf32_Addr p_vaddr;
    Elf32_Addr p_paddr;
    uint32_t   p_filesz;
    uint32_t   p_memsz;
    uint32_t   p_flags;
    uint32_t   p_align;
} Elf32_Phdr;
```

1. Тип программы (сегмента) p_type

- PT_LOAD - сегмент загрузки ()

2. p_offset содержит смещение от начала файла, в котором находится первый байт сегмента.
3. p_vaddr содержит виртуальный адрес, по которому первый байт сегмента находится в памяти.
4. p_paddr элемент зарезервирован для физического адреса сегмента. В BSD этот элемент не используется и должен быть равен нулю.
5. p_filesz количество байтов в образе файла сегмента. Он может быть равен нулю.
6. p_memsz содержит количество байтов в образе сегмента памяти. Он может быть равен нулю.
7. p_flags содержит битовую маску флагов, относящихся к сегменту:

- PF_X Исполняемый сегмент.
- PF_W Доступный для записи сегмент.
- PF_R Читаемый сегмент.

## Загловок разделов (Sections) `readelf --sections /bin/ls`, `readelf -S /bin/ls`

```
typedef struct {
uint32_t sh_name;
 uint32_t sh_type;
 uint32_t sh_flags;
 Elf32_Addr sh_addr;
 Elf32_Off sh_offset;
 uint32_t sh_size;
 uint32_t sh_link;
 uint32_t sh_info;
 uint32_t sh_addralign;
 uint32_t sh_entsize;
} Elf32_Shdr;
```

1. **sh_name имя раздела.** Его значением является индекс в разделе таблицы строк заголовка раздела, указывающий местоположение строки, заканчивающейся нулем.
2. **sh_type классифицирует содержимое и семантику раздела**

- SHT_STRTAB В этом разделе содержится таблица строк. Объектный файл может иметь несколько разделов таблицы строк.

3. sh_flags Разделы поддерживают однобитовые флаги, которые описывают разные атрибуты. Если в sh_flags установлен бит флага, атрибут "включен" для раздела. В противном случае атрибут "выключен" или не применяется.

- SHF_WRITE - Этот раздел содержит данные, которые должны быть доступны для записи во время выполнения процесса.

4. sh_addr Если этот раздел появляется в образе памяти процесса, этот элемент содержит адрес, по которому должен находиться первый байт раздела.
5. sh_offset - Значение этого элемента содержит смещение в байтах от начала файла до первого байта в разделе.
6. sh_size Этот элемент содержит размер раздела в байтах. Если тип раздела не SHT_NOBITS, раздел занимает байты sh_size в файле.
7. sh_info Этот элемент содержит дополнительную информацию, интерпретация которой зависит от типа раздела.
