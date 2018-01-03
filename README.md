# Inter-Process Communication Protocol
Simplifying inter-process communication by allowing you to call functions through pipes.

## How does it work?
IPCP works by first creating a pipe from the host process that lists specified function names, the corresponding pointers to those functions, and their signatures. Another process, known as the client, can connect to host pipe and retrieve the list accordingly. Next,  a second pipe is created between the client and the host which allows the client to call a function from the list with the parameters specified in the signature, and the host returns pointers to the value of each function called through the IPCP.

## Why not Remote Procedure Calls (RPCs)?
RPC methods can be slow and sometimes wind up with unintended effects. Hackers can easily exploit RPCs by delegating them to functions they have created, causing the RPC to perform tasks that they weren't intended for. IPCP mitigates this issue by using pipes instead of broadly-defined functions that any other process can use. Only the connected pipe can call the specified functions in the host process.
