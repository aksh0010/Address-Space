#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int arg_checker(int n)
{
    int arr[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    int count = 0;
    for (int i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
    {
        if (n == arr[i])
        {
            count++;
        }
    }

    if (count == 1)
    {
        return n;
    }
    else
    {
        return 0;
    }

    return n;
}

void convert_to_binary(unsigned long int decimal, unsigned short int bits)
{
    unsigned short int binary[bits];
    int c = 0;
    for (int i = 0; decimal > 0; i++)
    {
        binary[i] = decimal % 2;
        decimal = decimal / 2;
        c++;
    }
    for (int i = c - 1; i >= 0; i--)
    {
        printf("%d", binary[i]);
    }

    printf("\n");
}
int main(int argc, char *argv[])
{
    // Check for the correct I/Ps
    if (argc > 4)
    {
        printf("You entered more Arugments (%d)(expected 3 only)\n", argc - 1);
        return -1;
    }
    else if (argc < 4)
    {
        printf("You entered less Arugments (%d) (expected more 3 )\nexiting...\n", argc - 1);
        return -1;
    }

    if (atoi(argv[1]) != 1 && atoi(argv[1]) != 2)
    {
        printf("argv[1] should be either 1 or 2, you entered %d\nexiting...\n", atoi(argv[1]));
        return -1;
    }
    if (!(atoi(argv[2]) >= 8 && atoi(argv[2]) <= 65))
    {
        printf("argv[2] should be between 8-65, you entered %d\nexiting...\n", atoi(argv[2]));
        return -1;
    }
    if (arg_checker(atoi(argv[3])) == 0)
    {
        printf("Bad args\nPage size and frame size are not equal\nexiting...\n");
        return -1;
    }

    // I/P of CLI arguments by user
    printf("\nINPUT\n");
    printf("command line arguments \t \t \t \t %d %d %d\n", atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

    // O/P of CLI arguments by user
    printf("\nOUTPUT\n");

    unsigned long long total_bits = pow(2, atoi(argv[2]));
    unsigned long long memory_size = total_bits / 1024 / 1024 / 1024 / 1024;
    if (memory_size > 0 && memory_size < 1000)
        printf("size of the memory \t \t \t \t %lluTB\n", memory_size);
    else
    {
        memory_size = total_bits / 1024 / 1024 / 1024;
        if (memory_size > 0 && memory_size < 1000)
            printf("size of the memory \t \t \t \t %lluGB\n", memory_size);
        else
        {
            memory_size = total_bits / 1024 / 1024;
            printf("size of the memory \t \t \t \t %lluMB\n", memory_size);
        }
    }

    unsigned long long page = total_bits / atoi(argv[3]) / 1024;
    printf("total number of pages \t \t \t \t %llu\n", page);

    unsigned long long pte = page;
    printf("total number of PTE (page table entries) \t %llu\n", pte);

    unsigned long long size_page_table = page * 4;
    printf("size of page table \t \t \t \t %llu\n", size_page_table);

    unsigned long long offsets = log(atoi(argv[3])) + 11;
    unsigned long long vpn = atoi(argv[2]) - offsets;
    printf("number of bits for VPN \t \t \t \t %llu\n", vpn);
    printf("number of bits for page offset \t \t \t %llu\n", offsets);

    if (atoi(argv[1]) == 2) // For type 2
    {
        unsigned long long bits_pti = offsets - 2;
        unsigned long long pte_page = pow(2, bits_pti);
        printf("number of PTE in a page of page table \t \t %llu\n", pte_page);

        unsigned long long bits_pdi = vpn - bits_pti;
        unsigned long long pno_pt = pow(2, bits_pdi);
        printf("number of pages in a page table \t \t %llu\n", pno_pt);
        printf("number of bits for page directory index \t %llu\n", bits_pdi);
        printf("number of bits for page table index \t \t %llu\n", bits_pti);
    }

    unsigned long long address;
    while (1)
    {
        printf("\nINPUT\n");
        printf("\nDecimal virtual address \t\t: ");
        scanf("%llu\n", &address);
        if (address == 00)
            break;

        printf("\nINPUT\n");
        printf("decimal virtual address \t \t \t %llu\n", address);

        if (address > total_bits)
        {

            printf("bad Virtual address( %llu ) as it is not consistent with the args\n", address);
            if (memory_size > 0 && memory_size < 1000)
                printf("%llu address cannot be accepted because memory size is %lluTB.\n", address, memory_size);
            else
            {
                memory_size = total_bits / 1024 / 1024 / 1024;
                if (memory_size > 0 && memory_size < 1000)
                    printf("%llu address cannot be accepted because memory size is %lluGB.\n", address, memory_size);
                else
                {
                    memory_size = total_bits / 1024 / 1024;
                    printf("%llu address cannot be accepted because memory size is %lluMB.\n", address, memory_size);
                }
            }
            continue;
        }

        printf("\nOUTPUT\n");
        // Decimal outputs only
        unsigned long long virtual_vpn = address / atoi(argv[3]) / 1024;
        printf("VPN of the address in decimal \t \t \t %llu\n", virtual_vpn);
        printf("page offset of the address in decimal \t \t %llu\n", address % (atoi(argv[3]) * 1024));
        if (atoi(argv[1]) == 2) // For type 2
        {
            printf("page directory index in decimal \t \t %llu\n", (virtual_vpn / (atoi(argv[1]) * 1024)));
            printf("page table index in decimal \t \t \t %llu\n", (virtual_vpn % (atoi(argv[1]) * 1024)));
        }
        // binaray outputs only
        printf("VPN of the address in binary \t \t \t ");
        convert_to_binary(virtual_vpn, atoi(argv[2]));
        printf("page offset of the address in binary \t \t ");
        convert_to_binary((address % (atoi(argv[3]) * 1024)), atoi(argv[2]));
        printf("the input address in binary \t \t \t ");
        convert_to_binary(address, atoi(argv[2]));

        if (atoi(argv[1]) == 2) // For type 2
        {
            printf("page directory index in binary \t \t \t ");
            convert_to_binary((virtual_vpn / (atoi(argv[1]) * 1024)), atoi(argv[2]));
            printf("page table index in binary \t \t \t ");
            convert_to_binary((virtual_vpn % (atoi(argv[1]) * 1024)), atoi(argv[2]));
        }
    }

    return 0;
}
