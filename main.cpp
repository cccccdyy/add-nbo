#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <stdlib.h>

void error(const char* errormsg){
    printf("%s", errormsg);
    exit(1);
}

uint32_t getnum(const char* filename){

    uint32_t size = 0, value = 0;

    /* open file */
    FILE* fp = fopen(filename, "rb");
    if (!fp) error("FILE OPEN ERROR");

    /* get file size */
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);

    /* check file size */
    if (size != sizeof(uint32_t)) error("FILE SIZE ERROR");

    /* read file */
    if (fread(&value, 1, size, fp) != size) error("FILE READ ERROR");
    
    return ntohl(value);
}


int main(int argc, char* argv[]){

    uint32_t value1 = 0;
    uint32_t value2 = 0;
    uint32_t res = 0;
    
    value1 = getnum(argv[1]);
    value2 = getnum(argv[2]);
    res = value1 + value2; 

    printf("%d(0x%2x) + %d(0x%2x) = %d(0x%2x)\n", value1, value1, value2, value2, res, res);

    return 0;
}