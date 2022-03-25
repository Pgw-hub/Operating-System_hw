#define MAX_PATH 256
#define MAX_RESULT 100

void FindLargestFile(char *start_dir, char *largest, long *size);

int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("Usage: %s <start_dir>\n", argv[0]); return 0;
    }
    char *start_dir = argv[1];
    char largest[MAX_PATH] = "";
    long size = 0L; // the initial value of size should be zero FindLargestFile(start_dir, largest, &size);
    if(size > 0)
        printf("largest file = %s, size = %ld\n", largest, size);
    else
        printf("no file with size > 0.\n");
    return 0;
}
