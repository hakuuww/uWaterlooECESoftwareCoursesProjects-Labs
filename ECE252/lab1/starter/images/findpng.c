#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

#include <sys/types.h>

#include "../png_util/lab_png.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH_MAX 4096


int isDirCurrentOrParentDirectory(const char *dirName) {
  return (strcmp(dirName, ".") == 0 || strcmp(dirName, "..") == 0);
}
int findpng(const char *path, int *count) {
  struct dirent *entry;
  DIR *dir = opendir(path);

  if (dir == NULL) { // should not happen inside reccursion
    perror("Unable to open directory");
    return -11;
  }

  while ((entry = readdir(dir)) !=
         NULL) // not end of the path list inside a directory
  {
    if (!(isDirCurrentOrParentDirectory(entry->d_name))) {

      char new_path[PATH_MAX]; // Create a new buffer to store the concatenated
                               // path
      snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);

      struct stat file_stat;
      if (lstat(new_path, &file_stat) == -1) {
        perror("Unable to get file information");
        continue;
      }
      if (S_ISDIR(file_stat.st_mode)) {
        findpng(new_path, count); // Recursive call for directories
      } else if (S_ISREG(file_stat.st_mode)) {
        if (is_png(new_path)) {
          (*count)++;
          printf("%s\n", new_path);
        }; // Process regular files
      }
    }
  }

  closedir(dir);
  return 0;
}

int main(int argc, char *argv[]) {
  
  int count = 0;
  char cwd[PATH_MAX];
  
  if(getcwd(cwd, sizeof(cwd)) == NULL){
    exit(-1);
  }

  findpng(cwd,&count);
    if (count == 0) {
      printf("findpng: No PNG file found \n");
    }

  return 0;
}

// //post order traversal
// int main() {
//     DIR *dir;
//     struct dirent *entry;

//     dir = opendir("/home/a68xu/ECE252/G_33/lab1/starter/images");
//     if (dir == NULL) {
//         perror("Unable to open directory");
//         return 1;
//     }

//     while ((entry = readdir(dir)) != NULL) {
//         // Get the full path of the entry
//         char entry_path[1024];
//         snprintf(entry_path, sizeof(entry_path), "%s/%s",
//         "/home/a68xu/ECE252/G_33/lab1/starter/images", entry->d_name);

//         // Get the entry type
//         struct stat entry_stat;
//         if (stat(entry_path, &entry_stat) == -1) {
//             perror("Unable to get file status");
//             continue;
//         }

//         // Check if the entry is a directory
//         if (S_ISDIR(entry_stat.st_mode)) {
//             printf("Directory: %s\n", entry_path);
//         } if(S_ISREG(entry_stat.st_mode)) { //Check if the file is a regular
//         file
//             printf("File: %s\n", entry_path);
//         }else{

//         }
//     }

//     closedir(dir);

//     return 0;
// }

/*

preorder reccursion



int findpng(filepath){


    struct dirent *entry;
    DIR *dir = opendir("filepath");

    if (dir == NULL) {
        perror("Unable to open directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        char entry_path[]

        if( entry->d_type = "directory"){
        snprintf(entry_path, sizeof(entry_path), "%s/%s",
"/home/a68xu/ECE252/G_33/lab1/starter/images", entry->d_name);

        findpng(entry_path); //another cycle of recursion

        }else if(entry->d_type = "regular"){
            is_png("filepath")
        }

    }
}





*/