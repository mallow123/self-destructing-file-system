#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int file_exists(char filename[]){
    char command[256];

    #ifdef _WIN32
    sprintf(command, "if exist \"%s\" (exit 0) else (exit 1)",filename);
    #else
    sprintf(command,"test -f \"%s\" > /dev/null 2>&1", filename);
    #endif

    int result = system(command);
    return (result == 0);
    }

void self_destruct(char filename[], int seconds){
    printf("File '%s' will self destruct in %d seconds....\n", filename,seconds);

    for (int i = seconds; i>0;i--){
        printf("Time left before destruction: %d seconds....\n",i);
        sleep(1);
    }

    if(file_exists(filename)){
        char delete_command[256];

        #ifdef _WIN32
        sprintf(delete_command, "del /f /q \"%s\"", filename);
        #else
        sprintf(delete_command, "rm -f \"%s\"", filename);
        #endif

        int delete_result = system(delete_command);
        if (delete_result == 0){
            printf("ggs file '%s' has been deleted\n",filename);
        }else{
            printf("there's an error in deleting file '%s'\n", filename);
        }
    }else{
        printf("file '%s' was not found. it might've been deleted already??\n", filename);
    }
}
int main(){
    char filename[256];
    int seconds;

    printf("Enter the full path of the file to self-destruct:  ");
    scanf(" %255[^\n]", filename);

    printf("Enter the countdown time (in seconds): ");
    scanf("%d", &seconds);

    if(seconds <= 0){
        printf("enter a number greater than 0 bruv\n");
        return 1;
    }

    if(!file_exists(filename)){
        printf("file '%s' not found!!check your file name and path please. \n", filename);
        return 1;
    }
    char confirm;
    printf("Are you sure you want to delete '%s'? (y/n): ", filename);
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') {
        printf("deletion cancelled! your file's still there.    \n");
        return 0;
    }
    self_destruct(filename, seconds);

    return 0;
}

