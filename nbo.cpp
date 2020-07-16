/*bob9th [보안컨설팅]김현수 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

uint32_t nbo(uint32_t n) { //Network Byte Order function
    return (n & 0xff000000) >> 24 | (n & 0x00ff0000) >> 8 | (n & 0x0000ff00) << 8 | (n & 0x000000ff) << 24;
}
int endian_classfication() { //Endian_classfication function
    int endian = 1;
    if (*((char*)&endian + 0) == 1) { //little Endian
        return 1;
    }
    else { //big Endia
        return 0;
    }
}
void add_print(uint32_t first_num, uint32_t second_num) { //Addition operation and Print function
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", first_num, first_num, second_num, second_num,first_num+second_num,first_num+second_num);
}
int main(int argc, char* argv[]) {
    uint32_t first_num; //argv 1
    uint32_t second_num; //argv 2

    if (argc != 3) {
        printf("--help <file1> <file2>\n");
        return -1;
    }
    
    FILE* fd = fopen(argv[1], "r");
    FILE* fd2 = fopen(argv[2], "r");


    if(fd == NULL || fd2 == NULL){
	printf("File Open Error..\n");
	return -1;
    }

    uint32_t buf[2]; 

    fread(buf, sizeof(char), 4, fd); //argv 1
    fread(buf + 1, sizeof(char), 4, fd2); //argv 2

    uint32_t* p = reinterpret_cast<uint32_t*>(buf); //casting
    first_num = *p; //argv 1
    second_num = *(p + 1); //argv 2

    if (endian_classfication()) { //Little Endian Classfication
        first_num = nbo(first_num);
        second_num = nbo(second_num);
    }

    add_print(first_num,second_num);

    fclose(fd);
    fclose(fd2);
    
    return 0;
}
