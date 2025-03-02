##

* Modern systems react to these situations by making abrupt changes in the control flow. In general, we refer to these abrupt changes as exceptional control flow (ECF). ECF occurs at all levels of a computer system. For example, at the hardware level, events detected by the hardware trigger abrupt control transfers to exception handlers. At the operating systems level, the kernel transfers control from one user process to another via context switches. At the application level, a process can send a signal to another process that abruptly transfers control to a signal handler in the recipient. An individual program can react to errors by sidestepping the usual stack discipline and making nonlocal jumps to arbitrary locations in other functions.

* ECF is the basic mechanism that operating systems use to implement I/O, processes, and virtual memory.

* Applications request services from the operating system by using a form of ECF known as a trap or system call. For example, writing data to a disk, reading data from a network, creating a new process, and terminating the current process are all accomplished by application programs invoking system calls.

* An exception is an abrupt change in the control flow in response to some change in the processor’s state

* At system boot time (when the computer is reset or powered on), the operat- ing system allocates and initializes a jump table called an exception table, so that entry k contains the address of the handler for exception k. Figure 8.2 shows the format of an exception table.
At run time (when the system is executing some program), the processor detects that an event has occurred and determines the corresponding exception number k. The processor then triggers the exception by making an indirect pro- cedure call, through entry k of the exception table, to the corresponding handler. Figure 8.3 shows how the processor uses the exception table to form the address of the appropriate exception handler. The exception number is an index into the ex- ception table, whose starting address is contained in a special CPU register called the exception table base register.

> Exceptions can be divided into four classes: interrupts, traps, faults, and aborts.


* Traps are intentional exceptions that occur as a result of executing an instruction. Like interrupt handlers, trap handlers return control to the next instruction. The most important use of traps is to provide a procedure-like interface between user programs and the kernel known as a system call.
User programs often need to request services from the kernel such as reading a file (read), creating a new process (fork), loading a new program (execve), or terminating the current process (exit). To allow controlled access to such kernel services, processors provide a special “syscall n” instruction that user programs can execute when they want to request service n. Executing the syscall instruction causes a trap to an exception handler that decodes the argument and calls the appropriate kernel routine.

* 
8.3 System Call Error Handling
When Unix system-level functions encounter an error, they typically return −1 and set the global integer variable errno to indicate what went wrong. Program- mers should always check for errors, but unfortunately, many skip error checking because it bloats the code and makes it harder to read. For example, here is how we might check for errors when we call the Linux fork function:
`
if ((pid = fork()) < 0) {
             fprintf(stderr, "fork error: %s\n", strerror(errno));
             exit(0);
1
2
3 4}
`
The strerror function returns a text string that describes the error associated with a particular value of errno. We can simplify this code somewhat by defining the following error-reporting function:
`
void unix_error(char *msg) /* Unix-style error */ 2{
 fprintf(stderr, "%s: %s\n", msg, strerror(errno));
 exit(0);
}
`
Given this function, our call to fork reduces from four lines to two lines: 
` if ((pid = fork()) < 0)
	unix_error("fork error");
`

