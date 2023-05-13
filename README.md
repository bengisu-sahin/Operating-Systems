# Operating-Systems
This repository has been opened to learn UNIX commands and understand basic operating system concepts. It includes the projects given in the operating systems laboratory course.

## Project 1 - UNIX and C Programming

### Procedure:
  A study path folder is created with the student number (Ex: Desktop/152120151028/). All operations are performed inside this folder via the terminal.
### Step 1
  Write the source code (Ex: 152120151028_uyg1C.<language>) that lists the largest prime numbers less than the number received from the user and the smallest prime numbers greater than the same number.
### Step 2
  Write a .sh script that automates the operations in the sub-steps (Ex: 152120151028_uyg1C.sh). Except for the repeated steps, each of the operations in the sub-steps must be performed with a single-line terminal command.
  #### Step 2.1
  If it doesn't exist, create a folder named tempFiles. If there is a folder with the same name, the relevant command must be created in such a way that it does not cause an error or warning!
  #### Step 2.2
  All content in the artifact is listed along with the artifact path, subfolder contents, and (for this step only) dimensions. This step is repeated right after all the sub-steps until the code compilation sub-step.
  #### Step 2.3
  <language> and all files with .sh extension are moved to tempFiles folder.
  #### Step 2.4
  All files in the working path (all content except folder) are deleted.
  #### Step 2.5
  All content in the 2.5.tempFiles folder is copied to the work path.
  #### Step 2.6
  The 2.6.tempFiles folder (with its contents) is deleted.
  #### Step 2.7
  Written source code is compiled.
  #### Step 2.8
  The compiled file is run so that the output produced by the program (Ex: 152120151028_uyg1C_output.txt) is directed to the file, and the number of characters in the output file is printed on the screen immediately after each redirect. output file should be.
  #### Step 2.9
  The entire content of the output file is printed to the screen.
    
![image](https://user-images.githubusercontent.com/71591780/230410990-e7b96c59-bc32-4d0f-8413-2932aa864aa0.png)
    
## Project 2 - Process Creation and Execution
### Procedure:
  Procedure: Write the code that creates the process tree below.
  ### Step 1
  The process tree is deepened according to the numerical value that the user enters as an argument. The parent process has two children, independent of the change of the value entered by the user. Only the side of the tree with Child1 is created according to the depth information.
  ### Step 2   
  The user can enter terminal option(s) while running the program (Hint: getopt() <---> #include <unistd.h>). Example: $ ./app2 -o 4
-i : Student number and name information is printed on the top line of the program. Example: $ ./app2 -i 0
                Output: 152120151028 @sergenasik wrote this.  
  ### Step 3  
  The depth minimum value will be assumed to be 2 for the correct depth setup. Terminal arguments control should be performed accordingly. Hint: int dummyint = atoi(char); //char* to integer in c  
  ### Step 4  
  Each process must print the process ID of itself and its parent.  
  ### Step 5  
  There should be a minimum number of fork() system call lines in the source code.
        ❖ Invalid example #1:
             myFunc(){fork();}
        ❖ Invalid example #2:
             goto line x ...
             line x: fork();  
  ### Step 6  
  Each process must call a maximum of one system function for additional operations other than the wait shown in the figure and requested in the sub-steps. System call results should be kept in the process-based log file (logAll.log), with the information clause (Hint: $ echo) in the top line (Hint: output redirection).
  #### Step 6.1    
  The parent process creates a folder named logs and a log (logAll.log) file in the directory with the system function containing the relevant command, and prints the date information (Indian: $ date). Then it waits for 1 second for other processes to be created (The purpose of this wait is symbolic and to ensure that other processes occur in an orderly manner according to the specified hierarchy). Then, among the system function that performs the relevant command and the applications running on the operating system at that moment, it prints only the upper process tree with the PID information to the log file under the logs folder and completes the process.
               Hint: $man pstree $ pstree <options?> <PID>
               Hint: char mychar[size]; sprintf(mychar, "%s %d", dummytext, dummyint); //hybrid string+int to char* in c
  #### Step 6.2  
  Child1 (depth1) prints the contents of the log file (the results of previous runs will be visible in the file, the current run will also be printed shortly).
  #### Step 6.3     
  All other processes except the parent wait 2 seconds after creating the next process according to the depth information (the purpose of these waits is also symbolic and to ensure that the process tree is seen regularly) and completes the process.
  ##### Note:  
  Each of the above-mentioned operations may also have a significance in the ranking. For the correct result, do what is requested in the order in the document.

## Project 3 - Threads
### Procedure:
### Step 1
   The necessary user parameters for the program to run (pathRepository, pathSubmission) should be passed as terminal code arguments (Hint: ./app3 pathRep pathSub). The program stops running and displays an error message if insufficient or excessive arguments are provided.
    
➢ pathRep (pathRepository): The directory of the server data repository where the backed-up files are located.
➢ pathSub (pathSubmission): The directory where user operations are performed.
### Step 2
  The program has two threads (threadChecker and threadWorker_TimeAndChanges), both of which receive the directory information (pathSub) as an argument.
    
➢ threadChecker: Checks for changes in the user's upload area at one-second intervals (its only task).
Hint: last modification date .
Hint: shared variable 
    
➢ threadWorker_TimeAndChanges: Prints the current date and time continuously (for example, at intervals of 100 ms) and, when change information is detected:
    
• The current contents of the user's upload directory (pathSub) are displayed on the screen, along with the subfolders and their sizes, and the relevant content information is processed into a .log file in the server path (pathRep).
    
• The current contents of the user's upload directory (pathSub) are copied to the server path (pathRep) (ignore details such as whether the file is the same or different, copying all contents is sufficient for this application).
## Project-4 IPC
### Procedure: 
    Code the desired procedure for communication between the parent process and the child process. The parent process will shape its behavior according to the message sent by the child process.
### Step 1    
    The user parameter (pathInputFile) required for the program to run must be sent as terminal argument (Hint: ./app4 pathInp). When missing or extra arguments are entered, the program stops running with an error message. pathInp: The message sent to the parent process is read from this file by the child process.
