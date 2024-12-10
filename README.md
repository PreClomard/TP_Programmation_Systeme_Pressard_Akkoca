# TP_Programmation_Systeme_Pressard_Akkoca
Lab of IT Major by PRESSARD Clovis and AKKOCA Erwan 

Clovis PRESSARD 

Erwan AKKOCA 

Class: 2G1 TD2 TP3 

LAB1: Synthesys Practical Work Ensea in the Shell 

  

The lab goal is to create a micro shell called enseash, that is used to launche commands and display information about their execution. 

  

Forbiden commands are printf because it does not work with read and write. 

  

Note: When using "fortune" command in the main shell using linux, please download the "fortune" package using command: 

  

sudo apt install fortune-mod 

  

 When you use the shell it is normal if after 6 enter you leave your shell it is originally for testing it, if you want to change it you have to change the loop for in the enseash function by a while(1). Warning if you use it before questions 3 you will need to use the keys CTRL+C for living the shell. 

  

1- The first step is to Display a welcome message when opening the shell.  

You can see "enseash%" at the beginning of the text Input area field. 

  

Please see "EnseashQ1.c" source file 

You should have : 

$ ./enseash 

Welcome to ENSEA Tiny Shell. 

Type 'exit' to quit. 

enseash % 

$ 

  

--------------------------------------- 

2- This part is to allow the user to type various commands in the "enseash%" section that will launch them after entering it. It enables the user to enter continuously the commands thanks to a while loop. 

When taking the user’s input, the function call_command create a child that attempt to execute the given command by using execvp(). 

  

Please see "EnseashQ2.c" source file. 

enseash % fortune 

Today is what happened to yesterday. 

enseash % date 

Sun Dec 13 13:19:40 CET 2020 

enseash % 

 

It is the ls I have yours can maybe different. 

 

--------------------------------------- 

3- This part give you the possibility to exit of your micro shell if you typed exit or use your keyboard with the keys CTRL+D, by comparing the typed text with “exit” with the strcmp() function. Before quitting the micro shell a message “bye bye” appears.  

When Ctrl D is pressed, the variable read() returns a null length that indicates that there is no input, and it fits the if condition to exit the shell. 

 

Please see "EnseashQ3.c" source file 

 

Exemple of result you should have if you test it: 

enseash % exit 

Bye bye... 

$ 

Or with CTRL+D 

enseash % 

Bye bye... 

$ 

  

--------------------------------------- 

  

4- In this part we have display the prompt based on the child process status if it exit or sign. 

Please see "EnseashQ4.c" source file 

You should see if you do the command fortune for example: 

 enseash %%fortune 

To stand and be still, 

At the Birkenhead drill, 

Is a damned tough bullet to chew. 

		-- Rudyard Kipling 

enseash [exit:0] % 

 

--------------------------------------- 

  

5- We add to the enseshQ4.c the information of the time the child need to do the process. 

Please see "EnseashQ5.c" source file 

 You should see something similar if you do the fortune 

enseash %%fortune 

What is tolerance? -- it is the consequence of humanity.  We are all formed 

of frailty and error; let us pardon reciprocally each other's folly -- 

that is the first law of nature. 

		-- Voltaire 

enseash [exit:0|22ms] % 

 

--------------------------------------- 

  

6- There is a problem with "fortune -s osfortune" command, the osfortune doesn't exist anymore or is wrongly installed.  It split the entered command into separated strings, each is used as an input for the parse_command that stores into an array ending with null character so execvp() function interpret it as the end of the string. 

Please see "EnseashQ6.c" source file 

 

You should see something similar if you do hostname –i: 

enseash %%hostname -i 

127.0.1.1 

enseash [exit:0|40ms] % 

 

 
