# Simple-Shell
In this repository, I have a simple shell that I programmed in an OS course.
# how does it work ?

this program has 3 section :

in the first section we read a line and get the function that the user enter it .

in the second section we split the words .

and in the third section we give the instruction to the dash function to check it.

our shell can be run in two mood :intractive and batch mood.in intractive mood we input our instructions 
in the shell and the shell will run it but in batch mood we input the adress of 
file that our instructions are there and shell will open that file and read lines and run all of 
that instructins step by step .

our shell is not over when we input _ctrl + s_ and if we input it iur shell will identifies 
it as a instructin and give a massage that the instruction is not a command and if want to countinue 
our program we should input enter .



# the functions : 

we have two kinds of functions :

some of our functions are system calls which we dont implement them and if we want use them we should just call them with execive function and some
of them are are the functions that i implement them .

if we want to use a function at first we creat a new process with fork and then 
we implement the function .

### cd :
if we want to to change the directory we use cd .for example if you want to go to the
/home/user/Desktop     you can type with below syntax  :    _cd  /home/user/Desktop_
.and then the main directory is changed to the new directory ,

### history :

all of the instructions that we type in the shell are stored in a file and we access 
to all of them with the instruction history.if we input _history_ all of the instruction that 
we used will advent.

### pipe :

we can use pipe instruction . in this function we have tow instruction that the 
output of first is input of the second instruction ,for exampple if we wnat use ls an then grep we can 
input it whit this syntax :  _pipe ls grep .c_ .

### mkdir  :
in this instruction we can make new file in the current diroction .if we want to make new file at first we should input mkdir and 
then we should input the name of the file.
for example if we want to creat a folder with name folder1 in the current direction the syntax is 
_mkdir folder1_ .note that if we want to creat a filder in diffrent diroction at first we should change 
the direction with _cd_ . 

### echo : 
if you want to input the string and shell print it in the shell you can use this instruction .

### bash :
 if tou want to run the instructions in batch_mood you can use this instruction .
 it gets the address of the directory that you want run its instructions .for example if you want to 
 run the instructions of the file which in /home/user  directory and your file name is instruction.txt the syntax is:
_bash /home/user/instruction.txt_.

### exit : 
if you want to finished the program you can use this instruction .

if you want to use other instructions whitch they are use system call you can input your instructions 
like linux terminal .




