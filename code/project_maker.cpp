#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

#define WIN32_LEAN_AND_MEAN

char GetDriveLetter()
{
    char drive[4];
    
    do
    {
        printf("Enter parent drive letter: ");
        fgets(drive, 3, stdin);
        drive[1] = '\0';
        
    }while((drive[0] < 'A' && drive[0] > 'Z') ||
           (drive[0] < 'a' && drive[0] > 'z'));
    
    return drive[0];
}

void GetProjectName(char projectName[])
{
    printf("Enter project name under 20 characters: ");
    fgets(projectName, 100, stdin);
}

void MakePath(char pathString[])
{
    char driveLetter = GetDriveLetter();
    char projectName[100] = {'\0'};
    GetProjectName(projectName);
    projectName[strlen(projectName) - 1] = '\0';
    
    sprintf_s(pathString, MAX_PATH,"%c:\\%s",driveLetter, projectName);
}

DWORD MakeProjectDirectory(char pathString[])
{
    
    DWORD error = CreateDirectory(pathString, NULL);
    return error;
}

DWORD MakeProjectCodeDirectory(char pathString[])
{
    char codeDirectory[MAX_PATH] = {'\0'};
    strcpy(codeDirectory, pathString);
    strcat(codeDirectory, "\\code");
    
    DWORD error = CreateDirectory(codeDirectory, NULL);
    return error;
}

void ExtendPath(char oldPath[], char newPath[], char pathExtension[])
{
    strcpy(newPath, oldPath);
    strcat(newPath, pathExtension);
}

void CopyProjectTools(char projectPath[])
{
    char mainPathOld[] = "..\\tools\\main.cpp";
    char editorProjectPathOld[] = "..\\tools\\project.4coder";
    char buildPathOld[] = "..\\tools\\build.bat";
    
    
    MakeProjectCodeDirectory(projectPath);
    char mainPathNew[MAX_PATH];
    ExtendPath(projectPath, mainPathNew, "\\code\\main.cpp");
    
    char editorProjectPathNew[MAX_PATH];
    ExtendPath(projectPath, editorProjectPathNew, "\\project.4coder");
    
    char buildPathNew[MAX_PATH];
    ExtendPath(projectPath, buildPathNew,"\\build.bat");
    
    CopyFileA(mainPathOld, mainPathNew, TRUE);
    CopyFileA(editorProjectPathOld, editorProjectPathNew, TRUE);
    CopyFileA(buildPathOld, buildPathNew, TRUE);
}

int main(int argc, char *argv[])
{
    DWORD noError = 1;
    char pathName[MAX_PATH];
    do
    {
        MakePath(pathName);
        noError = MakeProjectDirectory(pathName);
        if(!noError)
        {
            printf("There was a problem creating the project. Either the directory\n");
            printf("contains an existing project, or the chosen drive does not exist. Try again...\n\n");
        }
    }while(!noError);
    CopyProjectTools(pathName);
    
    return 0;
}
